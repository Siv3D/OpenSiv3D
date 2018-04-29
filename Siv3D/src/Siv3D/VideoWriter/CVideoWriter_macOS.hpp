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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <opencv2/videoio.hpp>
# include <Siv3D/VideoWriter.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	class VideoWriter::CVideoWriter
	{
	private:

		cv::VideoWriter m_writer;

		Size m_frameSize = Size(0, 0);

	public:

		CVideoWriter();

		~CVideoWriter();

		bool open(const FilePath& path, const Size& size, double fps);

		void close();

		bool isOpened() const;
		
		bool write(const Image& image);
		
		Size size() const;
	};
}

# endif
