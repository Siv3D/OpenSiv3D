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

# include <Siv3D/VideoReader.hpp>
# include <Siv3D/VideoReader/VideoReaderDetail.hpp>

namespace s3d
{
	VideoReader::VideoReader()
		: pImpl{ std::make_shared<VideoReaderDetail>() } {}

	VideoReader::VideoReader(const FilePathView path)
		: VideoReader{}
	{
		open(path);
	}

	bool VideoReader::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	void VideoReader::close()
	{
		pImpl->close();
	}

	bool VideoReader::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	VideoReader::operator bool() const noexcept
	{
		return isOpen();
	}

	bool VideoReader::getFrame(Image& image)
	{
		return pImpl->getFrame(image);
	}

	Size VideoReader::getSize() const noexcept
	{
		return pImpl->getSize();
	}

	double VideoReader::getFPS() const noexcept
	{
		return pImpl->getFPS();
	}

	double VideoReader::getLengthSec() const
	{
		return pImpl->getLengthSec();
	}

	void VideoReader::setCurrentFrameIndex(const int32 index)
	{
		pImpl->setCurrentFrameIndex(index);
	}

	int32 VideoReader::getCurrentFrameIndex() const noexcept
	{
		return pImpl->getCurrentFrameIndex();
	}

	double VideoReader::getPosSec() const
	{
		return pImpl->getPosSec();
	}

	int32 VideoReader::getFrameCount() const noexcept
	{
		return pImpl->getFrameCount();
	}

	double VideoReader::getFrameDeltaSec() const noexcept
	{
		return pImpl->getFrameDeltaSec();
	}

	double VideoReader::getProgress() const noexcept
	{
		return pImpl->getProgress();
	}

	bool VideoReader::reachedEnd() const noexcept
	{
		return pImpl->reachedEnd();
	}

	const FilePath& VideoReader::path() const noexcept
	{
		return pImpl->path();
	}
}
