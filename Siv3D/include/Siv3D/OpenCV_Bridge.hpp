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
# include "Common.hpp"

# if __has_include(<opencv2/core.hpp>)

# include "Image.hpp"
# include "2DShapes.hpp"

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include <opencv2/core.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace OpenCV_Bridge
	{
		[[nodiscard]]
		inline cv::Rect ToCVRect(const Rect& rect);

		[[nodiscard]]
		inline cv::Mat_<cv::Vec4b> GetMatView(Image& image);

		[[nodiscard]]
		inline constexpr int32 ConvertBorderType(const BorderType borderType) noexcept;

		[[nodiscard]]
		cv::Mat_<uint8> ToGrayScale(const Image& image);

		[[nodiscard]]
		cv::Mat_<cv::Vec3b> ToMatVec3bBGR(const Image& image);

		void FromGrayScale(const cv::Mat_<uint8>& from, Image& to, OverwriteAlpha overwriteAlpha = OverwriteAlpha::Yes);

		void FromMatVec3b(const cv::Mat_<cv::Vec3b>& from, Image& to, OverwriteAlpha overwriteAlpha = OverwriteAlpha::Yes);

		void FromMatVec4bRGBA(const cv::Mat_<cv::Vec4b>& from, Image& to);



		void RedToBinary(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void RedToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void AlphaToBinary(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void AlphaToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void ToGrayScale(const Image& from, cv::Mat_<uint8>& to);

		void ToMatVec3b(const Image& from, cv::Mat_<cv::Vec3b>& to);

		void ToMatVec3f255(const Image& from, cv::Mat_<cv::Vec3f>& to);

		void FromMat(const cv::Mat_<cv::Vec3b>& from, Image& to, bool preserveAlpha = false);



		[[nodiscard]]
		cv::Mat_<uint8> ImRead_GrayScale(const FilePath& path);

		[[nodiscard]]
		cv::Mat_<uint8> ImRead_GrayScale(const Image& image);

		[[nodiscard]]
		cv::Mat_<cv::Vec3b> ImRead_BGR(const FilePath& path);

		[[nodiscard]]
		cv::Mat_<cv::Vec3b> ImRead_BGR(const Image& image);
	}
}

# include "detail/OpenCV_Bridge.ipp"

# endif
