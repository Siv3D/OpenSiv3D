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
		close();

		const bool result = m_capture.open(path.narrow(), cv::CAP_ANY);

		if (not result)
		{
			return false;
		}

		const int32 videoWidth	= static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH));
		const int32 videoHeight	= static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT));
		const int32 frameCount	= static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_COUNT));
		const double videoFPS	= m_capture.get(cv::CAP_PROP_FPS);

		m_info =
		{
			.fullPath			= FileSystem::FullPath(path),
			.resolution			= Size{ videoWidth, videoHeight },
			.fps				= videoFPS,
			.currentFrameIndex	= 0,
			.frameCount			= frameCount,
			.reachedEnd			= false
		};

		LOG_INFO(U"ℹ️ Video file {0} opened (resolution: {1}, fps: {2}, frameCount: {3})"_fmt(
			path, m_info.resolution, m_info.fps, m_info.frameCount));

		return true;
	}

	void VideoReader::VideoReaderDetail::close()
	{
		m_capture.release();
		m_info = {};
	}

	bool VideoReader::VideoReaderDetail::isOpen() const noexcept
	{
		return m_capture.isOpened();
	}

	bool VideoReader::VideoReaderDetail::getFrame(Image& image)
	{
		if (not m_capture.grab())
		{
			m_info.reachedEnd = true;
			return false;
		}

		m_capture.retrieve(m_mat);
		OpenCV_Bridge::FromMatVec3b(m_mat, image, OverwriteAlpha::Yes);
		
		++m_info.currentFrameIndex;

		return true;
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

	void VideoReader::VideoReaderDetail::setCurrentFrameIndex(int32 index)
	{
		index = Clamp(index, 0, m_info.frameCount);

		m_capture.set(cv::CAP_PROP_POS_FRAMES, index);
		m_info.currentFrameIndex = index;
		m_info.reachedEnd = (m_info.currentFrameIndex == m_info.frameCount);
	}

	int32 VideoReader::VideoReaderDetail::getCurrentFrameIndex() const noexcept
	{
		return m_info.currentFrameIndex;
	}

	double VideoReader::VideoReaderDetail::getPosSec() const
	{
		return (getProgress() * getLengthSec());
	}

	int32 VideoReader::VideoReaderDetail::getFrameCount() const noexcept
	{
		return m_info.frameCount;
	}

	double VideoReader::VideoReaderDetail::getFrameDeltaSec() const noexcept
	{
		return (m_info.fps ? (1.0 / m_info.fps) : (1.0 / 30.0));
	}

	double VideoReader::VideoReaderDetail::getProgress() const noexcept
	{
		return (static_cast<double>(m_info.currentFrameIndex) / m_info.frameCount);
	}

	bool VideoReader::VideoReaderDetail::reachedEnd() const noexcept
	{
		return m_info.reachedEnd;
	}

	const FilePath& VideoReader::VideoReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}
}
