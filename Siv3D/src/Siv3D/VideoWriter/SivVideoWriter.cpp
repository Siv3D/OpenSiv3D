//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/VideoWriter.hpp>
# include <VideoWriter/VideoWriterDetail.hpp>

namespace s3d
{
	VideoWriter::VideoWriter()
		: pImpl(std::make_shared<VideoWriterDetail>())
	{

	}

	VideoWriter::~VideoWriter()
	{

	}

	VideoWriter::VideoWriter(const FilePath& path, const Size& size, const double fps)
		: VideoWriter()
	{
		open(path, size, fps);
	}

	bool VideoWriter::open(const FilePath& path, const Size& size, const double fps)
	{
		return pImpl->open(path, size, fps);
	}

	void VideoWriter::close()
	{
		pImpl->close();
	}

	bool VideoWriter::isOpen() const
	{
		return pImpl->isOpen();
	}

	VideoWriter::operator bool() const
	{
		return isOpen();
	}

	bool VideoWriter::writeFrame(const Image& image)
	{
		return pImpl->write(image);
	}

	Size VideoWriter::size() const
	{
		return pImpl->size();
	}
}
