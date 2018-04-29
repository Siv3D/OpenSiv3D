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

# include "CVideoWriter.hpp"

namespace s3d
{
	VideoWriter::CVideoWriter::CVideoWriter()
	{

	}

	VideoWriter::CVideoWriter::~CVideoWriter()
	{
		close();
	}

	bool VideoWriter::CVideoWriter::open(const FilePath& path)
	{
		if (isOpened())
		{
			close();
		}

		return true;
	}

	void VideoWriter::CVideoWriter::close()
	{
		if (!isOpened())
		{
			return;
		}
	}

	bool VideoWriter::CVideoWriter::isOpened() const
	{
		return true;
	}
}
