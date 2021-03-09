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

# include "VideoPlayerDetail.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	VideoPlayer::VideoPlayerDetail::VideoPlayerDetail() {}

	VideoPlayer::VideoPlayerDetail::~VideoPlayerDetail()
	{
		close();
	}

	bool VideoPlayer::VideoPlayerDetail::open(const FilePathView path)
	{
		close();

		const bool result = m_capture.open(path.narrow(), cv::CAP_ANY);

		if (not result)
		{
			return false;
		}

		const String backend = Unicode::Widen(m_capture.getBackendName());

		LOG_INFO(U"ℹ️ VideoPlayer backend: {0}"_fmt(backend));

		m_info =
		{
			.resolution = Size(static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_WIDTH)),
				static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_HEIGHT))),
			.fps = m_capture.get(cv::CAP_PROP_FPS),
			.currentFrameIndex = 0,
			.frameCount = static_cast<int32>(m_capture.get(cv::CAP_PROP_FRAME_COUNT)),
			.reachedEnd = false
		};

		LOG_INFO(U"ℹ️ Video file {0} opened (resolution: {1}, fps: {2}, frameCount: {3})"_fmt(
			path, m_info.resolution, m_info.fps, m_info.frameCount));

		return true;
	}

	void VideoPlayer::VideoPlayerDetail::close()
	{
		m_capture.release();
		m_info = {};
	}

	bool VideoPlayer::VideoPlayerDetail::isOpen() const noexcept
	{
		return m_capture.isOpened();
	}

	bool VideoPlayer::VideoPlayerDetail::getFrame(Image& image)
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

	const Size& VideoPlayer::VideoPlayerDetail::getSize() const noexcept
	{
		return m_info.resolution;
	}

	double VideoPlayer::VideoPlayerDetail::getFPS() const noexcept
	{
		return m_info.fps;
	}

	double VideoPlayer::VideoPlayerDetail::getLengthSec() const
	{
		return (getFrameDeltaSec() * m_info.frameCount);
	}

	int32 VideoPlayer::VideoPlayerDetail::getCurrentFrameIndex() const noexcept
	{
		return m_info.currentFrameIndex;
	}

	double VideoPlayer::VideoPlayerDetail::getPosSec() const
	{
		return (getProgress() * getLengthSec());
	}

	int32 VideoPlayer::VideoPlayerDetail::getFrameCount() const noexcept
	{
		return m_info.frameCount;
	}

	double VideoPlayer::VideoPlayerDetail::getFrameDeltaSec() const noexcept
	{
		return (m_info.fps ? (1.0 / m_info.fps) : (1.0 / 30.0));
	}

	double VideoPlayer::VideoPlayerDetail::getProgress() const noexcept
	{
		return (static_cast<double>(m_info.currentFrameIndex) / m_info.frameCount);
	}

	bool VideoPlayer::VideoPlayerDetail::reachedEnd() const noexcept
	{
		return m_info.reachedEnd;
	}

	void VideoPlayer::VideoPlayerDetail::setCurrentFrameIndex(int32 index)
	{
		index = Clamp(index, 0, m_info.frameCount);

		m_capture.set(cv::CAP_PROP_POS_FRAMES, index);
		m_info.currentFrameIndex = index;
		m_info.reachedEnd = (m_info.currentFrameIndex == m_info.frameCount);
	}
}
