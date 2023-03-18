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
# include <Siv3D/CascadeClassifier.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	class CascadeClassifier::CascadeClassifierDetail
	{
	public:

		CascadeClassifierDetail();

		~CascadeClassifierDetail();

		bool open(FilePathView path);

		void close();

		bool isOpen() const;

		[[nodiscard]]
		Array<Rect> detectObjects(const Image& image, const Array<Rect>& regions, int32 minNeighbors, const Size& minSize, const Size& maxSize);

	private:

		cv::CascadeClassifier m_cascade;

		cv::Mat_<uint8> m_mat;
	};
}
