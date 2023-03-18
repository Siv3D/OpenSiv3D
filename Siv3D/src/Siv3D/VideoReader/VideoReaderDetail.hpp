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
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/VideoReader.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	struct MatFrame
	{
		int32 index = -1;

		cv::Mat mat;

		Image image;
	};

	class VideoReader::VideoReaderDetail
	{
	private:

		std::mutex m_mutex;

		std::condition_variable m_cv;

		AsyncTask<void> m_task;

		/////
		// m_mutex で管理するデータ
		struct Shared
		{
			cv::VideoCapture capture;

			int32 readPos = 0;

			bool reachedEnd = false;

			bool stop = false;

			MatFrame frame;

			bool ready = false;

		} m_shared;
		//
		/////

		struct Info
		{
			FilePath fullPath;

			Size resolution = Size{ 0, 0 };

			double fps = 30.0;

			int32 readPos = 0;

			size_t frameCount = 0;

			bool isOpen = false;

		} m_info;

		void run();

	public:

		VideoReaderDetail();

		~VideoReaderDetail();

		bool open(FilePathView path);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		bool readFrame(Image& image);

		[[nodiscard]]
		const Size& getSize() const noexcept;

		[[nodiscard]]
		double getFPS() const noexcept;

		[[nodiscard]]
		double getLengthSec() const;

		void setCurrentFrameIndex(size_t index);

		[[nodiscard]]
		size_t getCurrentFrameIndex() const noexcept;

		[[nodiscard]]
		double getPosSec() const;

		[[nodiscard]]
		size_t getFrameCount() const noexcept;

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
