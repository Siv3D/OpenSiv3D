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

# pragma once
# include <Siv3D/VideoWriter.hpp>
# include <Siv3D/PointVector.hpp>
# include <opencv2/videoio.hpp>

namespace s3d
{
	class VideoWriter::VideoWriterDetail
	{
	private:

		cv::VideoWriter m_writer;
		
		Size m_frameSize = Size(0, 0);

	public:

		VideoWriterDetail();

		~VideoWriterDetail();

		bool open(const FilePath& path, const Size& frameSize, double fps);

		void close();

		bool isOpened() const;

		bool write(const Image& image);

		Size size() const;
	};
}
