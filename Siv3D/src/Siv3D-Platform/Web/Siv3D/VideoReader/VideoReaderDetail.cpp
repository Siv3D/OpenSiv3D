//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "VideoReaderDetail.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		using CallbackDataStructure = std::tuple<bool (*)(void*), void*, long, long>;
		using CallbackData = std::unique_ptr<CallbackDataStructure>;

		void siv3dNop(long) {}

		int siv3dRequestAnimationFrameLoopCallback(double time, void* userData)
		{
			CallbackData p 
			{ 
				static_cast<CallbackDataStructure*>(userData)
			};

			auto callback = std::get<0>(*p);
			auto callbackData = std::get<1>(*p);
			auto& lastCalled = std::get<2>(*p);
			auto interval = std::get<3>(*p);

			if (static_cast<long>(time) - lastCalled > interval)
			{
				lastCalled += interval;

				auto shouldContinue = (*callback)(callbackData);

				if (shouldContinue)
				{
					p.release();
				}

				return shouldContinue;
			}

			p.release();
			return true;
		}

		template <long __interval>
		long siv3dRegisterRequestAnimationFrameLoop(bool (*functionPointer)(void*), void* userData)
		{
			CallbackData p 
			{ 
				new CallbackDataStructure(functionPointer, userData, 0, __interval)
			};

			::emscripten_request_animation_frame_loop(&siv3dRequestAnimationFrameLoopCallback, p.get());
			p.release();
			
			return 0x334;
		}
	}

	VideoReader::VideoReaderDetail::VideoReaderDetail() {}

	VideoReader::VideoReaderDetail::~VideoReaderDetail()
	{
		close();
	}

	bool VideoReader::VideoReaderDetail::open(const FilePathView path)
	{
		LOG_SCOPED_TRACE(U"VideoReaderDetail::open()");

		// close();

		const bool result = m_shared.capture.openVideo(path);

		if (not result)
		{
			return false;
		}

		m_info =
		{
			.fullPath	= FileSystem::FullPath(path),
			// .resolution	= Size{ videoWidth, videoHeight },
			// .fps		= videoFPS,
			.readPos	= 0,
			// .frameCount	= static_cast<size_t>(frameCount),
			.isOpen		= true,
		};

		m_shared.frame.resize(Shared::bufferedFramesNum);

		for (uint32 i = 0; i < Shared::bufferedFramesNum; ++i)
		{
			m_shared.frame[i].ready = false;
		}

		// m_thread = PseudoThread(std::chrono::milliseconds(30), &VideoReaderDetail::run, std::ref(*this) );
		m_thread = PseudoThread(&detail::siv3dRegisterRequestAnimationFrameLoop<30>, &detail::siv3dNop, &VideoReaderDetail::run, std::ref(*this) );

		return true;
	}

	void VideoReader::VideoReaderDetail::close()
	{
		LOG_SCOPED_TRACE(U"VideoReaderDetail::close()");

		// スレッドを終了
		{
			// std::lock_guard guard(m_mutex);
			m_thread.kill();
		}

		m_shared.capture.release();
		// m_shared = {};
		// m_info = {};
	}

	bool VideoReader::VideoReaderDetail::run()
	{
		if (not m_shared.capture.isOpened())
		{
			return true;
		}

		if (not m_info.isReady)
		{
			m_info.resolution = m_shared.capture.getResolution();
			m_info.fps = m_shared.capture.getFPS();
			m_info.frameCount = static_cast<size_t>(m_shared.capture.getDuration() * m_info.fps);
			m_info.isReady = true;

			for (auto& frame : m_shared.frame)
			{
				frame.unpacker.resize(m_info.resolution);
			}

			m_shared.capture.play();
			
			LOG_INFO(U"ℹ️ VideoReader: file `{0}` opened (resolution: {1}, fps: {2}, frameCount: {3})"_fmt(
				m_info.fullPath, m_info.resolution, m_info.fps, m_info.frameCount));
		}

		// std::unique_lock ul(m_mutex);

		if (not m_shared.reachedEnd)
		{
			auto& frame = m_shared.frame[m_shared.readPos % Shared::bufferedFramesNum];

			if (!frame.ready)
			{
				m_shared.capture.capture();
				auto frameBuffer = m_shared.capture.retrieve();
				frame.unpacker.startUnpack(frameBuffer);
				// frame.index = static_cast<int32>(m_shared.capture.tell() * m_info.fps);
				frame.index = m_shared.readPos++;
				frame.ready = true;
			}
			
			//LOG_TEST(U"## info ## m_shared.reachedEnd = true;");
			
			m_shared.reachedEnd = m_shared.capture.isReachedEnd();
		}

		//LOG_TEST(U"## info ## m_shared.ready = true;");

		return not m_shared.stop;
	}
	
	bool VideoReader::VideoReaderDetail::isOpen() const noexcept
	{
		return m_info.isOpen;
	}

	bool VideoReader::VideoReaderDetail::readFrame(Image& image)
	{
		//LOG_SCOPED_TRACE(U"VideoReaderDetail::getFrame()");

		if (static_cast<int32>(m_info.frameCount) <= m_info.readPos)
		{
			return false;
		}

		auto& frameToRead = m_shared.frame[m_ReadFrames % Shared::bufferedFramesNum];

		{
			// std::unique_lock ul(m_mutex);

			if (frameToRead.index == m_info.readPos)
			{
				//LOG_TEST(U"## info ## getFrmae(): targetBufferIndex {} found in buffer"_fmt(m_info.readPos));
				if (!frameToRead.ready || !frameToRead.unpacker.hasFinishedUnpack())
				{
					return false;
				}

				frameToRead.unpacker.readPixels(image);
				frameToRead.ready = false;

				++m_info.readPos;
				++m_ReadFrames;
			
				//LOG_TEST(U"## info ## m_shared.ready = false;");
				return true;
			}
			else
			{
				bool frameCaptured = false;

				//LOG_TEST(U"## info ## getFrmae(): targetBufferIndex {} not found in buffer"_fmt(m_info.readPos));
				if (frameToRead.ready && frameToRead.unpacker.hasFinishedUnpack())
				{
					frameToRead.unpacker.readPixels(image);
					frameCaptured = true;
				}
				
				m_shared.capture.seek(m_info.readPos / m_info.fps);
				m_shared.capture.play();

				for (uint32 i = 0; i < Shared::bufferedFramesNum; ++i)
				{
					m_shared.frame[i].ready = false;
				}
				
				m_shared.readPos = m_info.readPos;
				m_shared.reachedEnd = false;

				m_ReadFrames = m_info.readPos;
				
				//LOG_TEST(U"## info ## m_shared.ready = false;");
				//LOG_TEST(U"## info ## REQUESTING frame {}"_fmt(m_shared.readPos));

				//LOG_TEST(U"## info ## getFrmae(): targetBufferIndex {} found in buffer"_fmt(m_info.readPos));

				return frameCaptured;
			}
		}
	}

	const Size& VideoReader::VideoReaderDetail::getSize() const noexcept
	{
		return m_info.resolution;
	}

	double VideoReader::VideoReaderDetail::getFPS() const noexcept
	{
		return m_info.fps;
	}

	double VideoReader::VideoReaderDetail::getLengthSec() const
	{
		return (getFrameDeltaSec() * m_info.frameCount);
	}

	void VideoReader::VideoReaderDetail::setCurrentFrameIndex(const size_t index)
	{
		m_info.readPos = static_cast<int32>(Clamp<size_t>(index, 0, m_info.frameCount));
	}

	size_t VideoReader::VideoReaderDetail::getCurrentFrameIndex() const noexcept
	{
		return static_cast<size_t>(m_info.readPos);
	}

	double VideoReader::VideoReaderDetail::getPosSec() const
	{
		return (getProgress() * getLengthSec());
	}

	size_t VideoReader::VideoReaderDetail::getFrameCount() const noexcept
	{
		return m_info.frameCount;
	}

	double VideoReader::VideoReaderDetail::getFrameDeltaSec() const noexcept
	{
		return (m_info.fps ? (1.0 / m_info.fps) : (1.0 / 30.0));
	}

	double VideoReader::VideoReaderDetail::getProgress() const noexcept
	{
		return (static_cast<double>(m_info.readPos) / m_info.frameCount);
	}

	bool VideoReader::VideoReaderDetail::reachedEnd() const noexcept
	{
		return m_shared.reachedEnd;
	}

	const FilePath& VideoReader::VideoReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}
}
