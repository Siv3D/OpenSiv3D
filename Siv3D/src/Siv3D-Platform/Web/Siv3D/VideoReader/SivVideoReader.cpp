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

# include <Siv3D/VideoReader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/VideoReader/VideoReaderDetail.hpp>
# include <Siv3D/Browser.hpp>

namespace s3d
{
	VideoReader::VideoReader()
		: pImpl{ std::make_shared<VideoReaderDetail>() } 
		{
		
		}

	VideoReader::VideoReader(const FilePathView path)
		: VideoReader{}
	{
		open(path);
	}

	bool VideoReader::open(const FilePathView path)
	{
	# if SIV3D_PLATFORM(WEB)
		Platform::Web::FetchFile(path);
	# endif
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

	bool VideoReader::readFrame(Image& image)
	{
		return pImpl->readFrame(image);
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

	void VideoReader::setCurrentFrameIndex(const size_t index)
	{
		pImpl->setCurrentFrameIndex(index);
	}

	size_t VideoReader::getCurrentFrameIndex() const noexcept
	{
		return pImpl->getCurrentFrameIndex();
	}

	double VideoReader::getPosSec() const
	{
		return pImpl->getPosSec();
	}

	size_t VideoReader::getFrameCount() const noexcept
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
