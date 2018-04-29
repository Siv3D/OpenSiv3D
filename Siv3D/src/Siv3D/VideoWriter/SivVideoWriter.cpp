//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/VideoWriter.hpp>
# include "CVideoWriter_Windows.hpp"
# include "CVideoWriter_macOS.hpp"

namespace s3d
{
	VideoWriter::VideoWriter()
		: pImpl(std::make_shared<CVideoWriter>())
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

	bool VideoWriter::isOpened() const
	{
		return pImpl->isOpened();
	}

	VideoWriter::operator bool() const
	{
		return isOpened();
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
