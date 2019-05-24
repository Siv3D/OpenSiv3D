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

# include <Siv3D/String.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/FileSystem.hpp>
# include "VideoWriterDetail.hpp"

namespace s3d
{
	VideoWriter::VideoWriterDetail::VideoWriterDetail()
	{
		
	}
	
	VideoWriter::VideoWriterDetail::~VideoWriterDetail()
	{
		close();
	}
	
	bool VideoWriter::VideoWriterDetail::open(const FilePath& path, const Size& size, const double fps)
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
	
	void VideoWriter::VideoWriterDetail::close()
	{
		if (!isOpened())
		{
			return;
		}
		
		m_writer.release();
		
		m_frameSize.set(0, 0);
	}
	
	bool VideoWriter::VideoWriterDetail::isOpened() const
	{
		return m_writer.isOpened();
	}
	
	bool VideoWriter::VideoWriterDetail::write(const Image& image)
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
	
	Size VideoWriter::VideoWriterDetail::size() const
	{
		return m_frameSize;
	}
}
