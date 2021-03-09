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

# include <Siv3D/VideoPlayer.hpp>
# include <Siv3D/VideoPlayer/VideoPlayerDetail.hpp>

namespace s3d
{
	VideoPlayer::VideoPlayer()
		: pImpl{ std::make_shared<VideoPlayerDetail>() } {}

	VideoPlayer::VideoPlayer(const FilePathView path)
		: VideoPlayer{}
	{
		open(path);
	}

	bool VideoPlayer::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	void VideoPlayer::close()
	{
		pImpl->close();
	}

	bool VideoPlayer::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	VideoPlayer::operator bool() const noexcept
	{
		return isOpen();
	}

	bool VideoPlayer::getFrame(Image& image)
	{
		return pImpl->getFrame(image);
	}

	Size VideoPlayer::getSize() const noexcept
	{
		return pImpl->getSize();
	}

	double VideoPlayer::getFPS() const noexcept
	{
		return pImpl->getFPS();
	}

	double VideoPlayer::getLengthSec() const
	{
		return pImpl->getLengthSec();
	}

	int32 VideoPlayer::getCurrentFrameIndex() const noexcept
	{
		return pImpl->getCurrentFrameIndex();
	}

	double VideoPlayer::getPosSec() const
	{
		return pImpl->getPosSec();
	}

	int32 VideoPlayer::getFrameCount() const noexcept
	{
		return pImpl->getFrameCount();
	}

	double VideoPlayer::getFrameDeltaSec() const noexcept
	{
		return pImpl->getFrameDeltaSec();
	}

	double VideoPlayer::getProgress() const noexcept
	{
		return pImpl->getProgress();
	}

	bool VideoPlayer::reachedEnd() const noexcept
	{
		return pImpl->reachedEnd();
	}

	void VideoPlayer::setCurrentFrameIndex(const int32 index)
	{
		pImpl->setCurrentFrameIndex(index);
	}
}
