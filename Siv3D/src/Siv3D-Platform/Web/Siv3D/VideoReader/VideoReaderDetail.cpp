//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "VideoReaderDetail.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	VideoReader::VideoReaderDetail::VideoReaderDetail() {}

	VideoReader::VideoReaderDetail::~VideoReaderDetail()
	{
		close();
	}

	bool VideoReader::VideoReaderDetail::open(const FilePathView path)
	{
		LOG_SCOPED_TRACE(U"VideoReaderDetail::open()");

		close();

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
			.isOpen		= false,
		};

		m_thread = PseudoThread(std::chrono::milliseconds(30), &VideoReaderDetail::run, this);

		return true;
	}

	void VideoReader::VideoReaderDetail::close()
	{
		LOG_SCOPED_TRACE(U"VideoReaderDetail::close()");

		// スレッドを終了
		{
			// std::lock_guard guard(m_mutex);
			m_shared.stop = true;
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

		if (not m_info.isOpen)
		{
			m_info.resolution = m_shared.capture.getResolution();
			m_info.fps = m_shared.capture.getFPS();
			m_info.frameCount = static_cast<size_t>(m_shared.capture.getDuration() * m_info.fps);
			m_info.isOpen = true;

			m_shared.frame.unpacker.resize(m_info.resolution);

			LOG_INFO(U"ℹ️ VideoReader: file `{0}` opened (resolution: {1}, fps: {2}, frameCount: {3})"_fmt(
				m_info.fullPath, m_info.resolution, m_info.fps, m_info.frameCount));
		}

		if (m_shared.ready) 
		{
			return true;
		}

		// std::unique_lock ul(m_mutex);

		if (not m_shared.reachedEnd)
		{
			if (m_shared.capture.grab())
			{
				auto frame = m_shared.capture.capture();
				m_shared.frame.unpacker.startUnpack(frame);
				m_shared.frame.index = m_shared.readPos++;
				//LOG_TEST(U"## info ## retrieved frame {} to buffer"_fmt(m_shared.frame.index));
			}
			else
			{
				m_shared.reachedEnd = true;
				//LOG_TEST(U"## info ## m_shared.reachedEnd = true;");
			}
		}

		m_shared.ready = true;

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

		if (!m_shared.ready || !m_shared.frame.unpacker.hasFinishedUnpack())
		{
			return false;
		}

		{
			// std::unique_lock ul(m_mutex);

			if (m_shared.frame.index == m_info.readPos)
			{
				//LOG_TEST(U"## info ## getFrmae(): targetBufferIndex {} found in buffer"_fmt(m_info.readPos));
				m_shared.frame.unpacker.readPixels(image);
				++m_info.readPos;
				m_shared.ready = false;
				//LOG_TEST(U"## info ## m_shared.ready = false;");

				return true;
			}
			else
			{
				//LOG_TEST(U"## info ## getFrmae(): targetBufferIndex {} not found in buffer"_fmt(m_info.readPos));

				m_shared.readPos = m_info.readPos;
				m_shared.capture.seek(m_info.readPos / m_info.fps);
				m_shared.reachedEnd = false;
				m_shared.ready = false;
				//LOG_TEST(U"## info ## m_shared.ready = false;");
				//LOG_TEST(U"## info ## REQUESTING frame {}"_fmt(m_shared.readPos));

				//LOG_TEST(U"## info ## getFrmae(): targetBufferIndex {} found in buffer"_fmt(m_info.readPos));
				m_shared.frame.unpacker.readPixels(image);
				++m_info.readPos;
				m_shared.ready = false;

				return true;
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
		return (m_info.readPos == static_cast<int32>(m_info.frameCount));
	}

	const FilePath& VideoReader::VideoReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}
}
