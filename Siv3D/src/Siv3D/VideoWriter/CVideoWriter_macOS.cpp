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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/String.hpp>
# include "CVideoWriter_macOS.hpp"

namespace s3d
{
	VideoWriter::CVideoWriter::CVideoWriter()
	{

	}

	VideoWriter::CVideoWriter::~CVideoWriter()
	{
		close();
	}

	bool VideoWriter::CVideoWriter::open(const FilePath& path, const Size& size, const double fps)
	{
		if (isOpened())
		{
			close();
		}

		const bool result = m_writer.open(path.narrow(), cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps, cv::Size(size.x, size.y), true);

		if (result)
		{
			m_size = size;
		}

		return result;
	}

	void VideoWriter::CVideoWriter::close()
	{
		if (!isOpened())
		{
			return;
		}

		m_writer.release();

		m_size.set(0, 0);
	}

	bool VideoWriter::CVideoWriter::isOpened() const
	{
		return m_writer.isOpened();
	}
}

# endif
