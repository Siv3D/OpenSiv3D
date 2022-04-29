//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace OpenCV_Bridge
	{
		inline cv::Rect ToCVRect(const Rect& rect)
		{
			return{ rect.x, rect.y, rect.w, rect.h };
		}

		inline cv::Mat GetMatView(Image& image)
		{
			return{ cv::Size{ image.width(), image.height() }, CV_8UC4, image.dataAsUint8(), image.stride() };
		}

		inline constexpr int32 ConvertBorderType(const BorderType borderType) noexcept
		{
			switch (borderType)
			{
			case BorderType::Replicate:
				return cv::BORDER_REPLICATE;
			//case BorderType::Wrap:
			//	return cv::BORDER_WRAP;
			case BorderType::Reflect:
				return cv::BORDER_REFLECT;
			case BorderType::Reflect_101:
				return cv::BORDER_REFLECT101;
			default:
				return cv::BORDER_DEFAULT;
			}
		}
	}
}
