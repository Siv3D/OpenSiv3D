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
# include <Siv3D/VideoReader.hpp>
# include <Siv3D/VideoCapture/VideoCapture.hpp>
# include <Siv3D/VideoCapture/FrameBufferUnpacker.hpp>
# include <Siv3D/PseudoThread/PseudoThread.hpp>
# include <GLES3/gl3.h>

namespace s3d
{
	struct MatFrame
	{
		int32 index = -1;

		FrameBufferUnpacker unpacker;

		bool ready = false;
	};

	class VideoReader::VideoReaderDetail
	{
	private:

		std::mutex m_mutex;

		std::condition_variable m_cv;

		std::future<void> m_task;

		PseudoThread m_thread;

		/////
		// m_mutex で管理するデータ
		struct Shared
		{
			WebCameraCapture capture;

			int32 readPos = 0;

			bool reachedEnd = false;

			bool stop = false;

			Array<MatFrame> frame;

			static constexpr uint32 bufferedFramesNum = 3;

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

			bool isReady = false;

		} m_info;

		int32 m_ReadFrames = 0;

		bool run();

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
