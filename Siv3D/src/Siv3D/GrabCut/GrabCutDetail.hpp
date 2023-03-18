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
# include <Siv3D/GrabCut.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	class GrabCut::GrabCutDetail
	{
	private:

		cv::Mat_<cv::Vec3b> m_originalImage;

		cv::Mat_<uint8> m_maskImage;

		cv::Mat m_backgroundModel;

		cv::Mat m_foregroundModel;

		bool m_hasForegroundPixel = false;

		bool m_hasBackgroundPixel = false;
	public:

		GrabCutDetail();

		~GrabCutDetail();

		void init(const Image& image, GrabCutClass defaultMask);

		void initWithRect(const Image& image, const Rect& rect, size_t iterations);

		void update(const Image& maskImage, const Color& foreground, const Color& background, size_t iterations);

		void getResult(Grid<GrabCutClass>& result);
	};
}
