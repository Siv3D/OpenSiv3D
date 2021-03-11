//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/VideoReader.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	class VideoReader::VideoReaderDetail
	{
	private:

		cv::VideoCapture m_capture;

		cv::Mat m_mat;

		struct Info
		{
			FilePath fullPath;

			Size resolution = Size(0, 0);

			double fps = 30.0;

			int32 currentFrameIndex = 0;

			int32 frameCount = 0;

			bool reachedEnd = false;
		} m_info;

	public:

		VideoReaderDetail();

		~VideoReaderDetail();

		bool open(FilePathView path);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		bool getFrame(Image& image);

		[[nodiscard]]
		const Size& getSize() const noexcept;

		[[nodiscard]]
		double getFPS() const noexcept;

		[[nodiscard]]
		double getLengthSec() const;

		void setCurrentFrameIndex(int32 index);

		[[nodiscard]]
		int32 getCurrentFrameIndex() const noexcept;

		[[nodiscard]]
		double getPosSec() const;

		[[nodiscard]]
		int32 getFrameCount() const noexcept;

		[[nodiscard]]
		double getFrameDeltaSec() const noexcept;

		[[nodiscard]]
		double getProgress() const noexcept;

		[[nodiscard]]
		bool reachedEnd() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}
