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
# include "CVideoWriter.hpp"

namespace s3d
{
	VideoWriter::VideoWriter()
		: pImpl(std::make_shared<CVideoWriter>())
	{

	}

	VideoWriter::~VideoWriter()
	{

	}

	VideoWriter::VideoWriter(const FilePath& path)
		: VideoWriter()
	{
		open(path);
	}

	bool VideoWriter::open(const FilePath& path)
	{
		return pImpl->open(path);
	}

	void VideoWriter::close()
	{
		pImpl->close();
	}

	bool VideoWriter::isOpened() const
	{
		return pImpl->isOpened();
	}
}
