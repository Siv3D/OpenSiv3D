//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# if __has_include(<opencv2/core.hpp>)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include <opencv2/core.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# include "Image.hpp"

namespace s3d
{
	namespace OpenCV_Bridge
	{
		void RedToBinary(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void RedToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void AlphaToBinary(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void AlphaToBinary2x(const Image& from, cv::Mat_<uint8>& to, uint32 threshold);

		void ToGrayScale(const Image& from, cv::Mat_<uint8>& to);

		void ToMatVec3b(const Image& from, cv::Mat_<cv::Vec3b>& to);

		void ToMatVec3f255(const Image& from, cv::Mat_<cv::Vec3f>& to);

		void FromMat(const cv::Mat_<cv::Vec3b>& from, Image& to, bool preserveAlpha = false);

		void FromGrayScale(const cv::Mat_<uint8>& from, Image& to, bool preserveAlpha = false);

		cv::Mat_<uint8> ImRead_GrayScale(const FilePath& path);

		cv::Mat_<uint8> ImRead_GrayScale(const Image& image);

		cv::Mat_<cv::Vec3b> ImRead_BGR(const FilePath& path);

		cv::Mat_<cv::Vec3b> ImRead_BGR(const Image& image);
	}
}

# endif
