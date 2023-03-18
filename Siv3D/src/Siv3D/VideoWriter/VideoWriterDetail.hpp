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

# pragma once
# include <Siv3D/VideoWriter.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	class VideoWriter::VideoWriterDetail
	{
	private:

		cv::VideoWriter m_writer;

		struct Info
		{
			FilePath fullPath;

			Size resolution = Size{ 0, 0 };

			double fps = 30.0;

			bool isOpen = false;

			cv::Mat_<cv::Vec3b> mat;

		} m_info;

	public:

		VideoWriterDetail();

		~VideoWriterDetail();

		bool open(FilePathView path, const Size& size, double fps);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		bool writeFrame(const Image& image);

		[[nodiscard]]
		const Size& getSize() const noexcept;

		[[nodiscard]]
		double getFPS() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}
