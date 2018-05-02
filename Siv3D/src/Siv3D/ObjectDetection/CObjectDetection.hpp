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
# include <array>
# include <opencv2/objdetect/objdetect.hpp>
# include "IObjectDetection.hpp"

namespace s3d
{
	class CObjectDetection : public ISiv3DObjectDetection
	{
	private:

		bool m_initialized = false;

		std::array<cv::CascadeClassifier, 5> m_cascades;

		std::array<bool, 5> m_unavailable;

		cv::Mat_<uint8> m_mat;

		bool load(size_t cascadeIndex);

	public:

		CObjectDetection();

		~CObjectDetection() override;

		bool init() override;

		Array<Rect> detect(const Image& image, HaarCascade cascade, int32 minNeighbors, const Size& minSize, const Size& maxSize) override;

		Array<Rect> detect(const Image& image, HaarCascade cascade, const Array<Rect>& regions, int32 minNeighbors, const Size& minSize, const Size& maxSize) override;
	};
}
