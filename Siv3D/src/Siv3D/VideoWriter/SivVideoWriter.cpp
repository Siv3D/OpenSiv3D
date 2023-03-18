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

# include <Siv3D/VideoWriter.hpp>
# include <Siv3D/VideoWriter/VideoWriterDetail.hpp>

namespace s3d
{
	VideoWriter::VideoWriter()
		: pImpl{ std::make_shared<VideoWriterDetail>() } {}

	VideoWriter::VideoWriter(const FilePathView path, const Size& size, const double fps)
		: VideoWriter{}
	{
		open(path, size, fps);
	}

	bool VideoWriter::open(const FilePathView path, const Size& size, const double fps)
	{
		return pImpl->open(path, size, fps);
	}

	void VideoWriter::close()
	{
		pImpl->close();
	}

	bool VideoWriter::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	VideoWriter::operator bool() const noexcept
	{
		return isOpen();
	}

	bool VideoWriter::writeFrame(const Image& image)
	{
		return pImpl->writeFrame(image);
	}

	Size VideoWriter::getSize() const noexcept
	{
		return pImpl->getSize();
	}

	double VideoWriter::getFPS() const noexcept
	{
		return pImpl->getFPS();
	}

	const FilePath& VideoWriter::path() const noexcept
	{
		return pImpl->path();
	}
}
