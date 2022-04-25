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
# include "Common.hpp"

# if __has_include(<opencv2/core.hpp>)

# include "Image.hpp"
# include "2DShapes.hpp"

# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wdeprecated-anon-enum-enum-conversion"
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)

# include <opencv2/core.hpp>

# if  __has_include(<opencv2/imgproc.hpp>)
#	include <opencv2/imgproc.hpp>
# endif

# if  __has_include(<opencv2/photo.hpp>)
#	include <opencv2/photo.hpp>
# endif

# if  __has_include(<opencv2/videoio.hpp>)
#	include <opencv2/videoio.hpp>
# endif

# if  __has_include(<opencv2/objdetect.hpp>)
#	include <opencv2/objdetect.hpp>
# endif

SIV3D_DISABLE_MSVC_WARNINGS_POP()
# ifdef __clang__
#	pragma clang diagnostic pop
# endif

namespace s3d
{
	namespace OpenCV_Bridge
	{
		[[nodiscard]]
		inline cv::Rect ToCVRect(const Rect& rect);

		[[nodiscard]]
		inline cv::Mat GetMatView(Image& image);

		[[nodiscard]]
		inline constexpr int32 ConvertBorderType(const BorderType borderType) noexcept;

		[[nodiscard]]
		cv::Mat_<uint8> ToGrayScale(const Image& image);

		void ToGrayScale(const Image& image, cv::Mat_<uint8>& to);

		[[nodiscard]]
		cv::Mat_<cv::Vec3b> ToMatVec3bBGR(const Image& image);

		void FromGrayScale(const cv::Mat_<uint8>& from, Image& to, OverwriteAlpha overwriteAlpha);

		void FromMatVec3b(const cv::Mat_<cv::Vec3b>& from, Image& to, OverwriteAlpha overwriteAlpha);

		void FromMatVec4bRGBA(const cv::Mat_<cv::Vec4b>& from, Image& to);

		void MaskByColor(const Image& from, cv::Mat_<uint8>& to, const Color& maskColor);

		void RedToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void AlphaToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void ToMatVec3bBGR(const Image& from, cv::Mat_<cv::Vec3b>& to);

		void ToMatVec3f255(const Image& from, cv::Mat_<cv::Vec3f>& to);
	}
}

# include "detail/OpenCV_Bridge.ipp"

# endif
