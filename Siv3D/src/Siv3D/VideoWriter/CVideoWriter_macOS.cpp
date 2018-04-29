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
# include <Siv3D/Image.hpp>
# include <Siv3D/FileSystem.hpp>
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
		
		if (FileSystem::Exists(path))
		{
			FileSystem::Remove(path);
		}

		const bool result = m_writer.open(path.narrow(), cv::VideoWriter::fourcc('H', '2', '6', '4'), fps, cv::Size(size.x, size.y), true);

		if (result)
		{
			m_frameSize = size;
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

		m_frameSize.set(0, 0);
	}

	bool VideoWriter::CVideoWriter::isOpened() const
	{
		return m_writer.isOpened();
	}
	
	bool VideoWriter::CVideoWriter::write(const Image& image)
	{
		if (!isOpened())
		{
			return false;
		}
		
		if (image.size() != m_frameSize)
		{
			return false;
		}
		
		cv::Mat_<cv::Vec3b> mat(m_frameSize.y, m_frameSize.x);
		{
			const Color* pSrc = image.data();
			
			for (int32 y = 0; y < m_frameSize.y; ++y)
			{
				auto* line = &mat(y, 0);
				
				for (int32 x = 0; x < m_frameSize.x; ++x)
				{
					line[x][0] = pSrc->r;
					line[x][1] = pSrc->g;
					line[x][2] = pSrc->b;
					
					++pSrc;
				}
			}
		}
		
		m_writer.write(mat);
		
		return true;
	}
	
	Size VideoWriter::CVideoWriter::size() const
	{
		return m_frameSize;
	}
}

# endif
