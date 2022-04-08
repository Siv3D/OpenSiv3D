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
# include "Array.hpp"
# include "Image.hpp"
# include "EdgePreservingFilterType.hpp"

namespace s3d
{
	namespace ImageProcessing
	{
		/// @brief 何枚のミップマップ画像が作成されるかを返します。
		/// @param width 元の画像の幅（ピクセル）
		/// @param height 元の画像の高さ（ピクセル）
		/// @return 作成されるミップマップ画像の枚数
		[[nodiscard]]
		inline constexpr size_t CalculateMipCount(uint32 width, uint32 height) noexcept;

		/// @brief 画像からミップマップ画像を作成します。
		/// @param src 画像
		/// @return ミップマップ画像
		[[nodiscard]] 
		Array<Image> GenerateMips(const Image& src);

		/// @brief 画像からミップマップ画像を作成します。
		/// @param src 画像
		/// @param maxLevel ミップマップの最大個数（この値が 2 の場合、一辺の大きさが 1/2 と 1/4 のミップマップが生成される）
		/// @return ミップマップ画像
		[[nodiscard]]
		Array<Image> GenerateMips(const Image& src, size_t maxLevel);

		void Sobel(const Image& src, Image& dst, int32 dx = 1, int32 dy = 1, int32 apertureSize = 3);

		void Laplacian(const Image& src, Image& dst, int32 apertureSize = 3);

		void Canny(const Image& src, Image& dst, uint8 lowThreshold, uint8 highThreshold, int32 apertureSize = 3, bool useL2Gradient = false);

		// _Field_range_(0.0, 200.0) sigma_s, _Field_range_(0.0, 1.0) double sigma_r
		void EdgePreservingFilter(const Image& src, Image& dst, EdgePreservingFilterType filter = EdgePreservingFilterType::Recursive, double sigma_s = 60, double sigma_r = 0.4);

		// _Field_range_(0.0, 200.0) sigma_s, _Field_range_(0.0, 1.0) double sigma_r
		void DetailEnhance(const Image& src, Image& dst, double sigma_s = 10, double sigma_r = 0.15);

		// _Field_range_(0.0, 200.0) sigma_s, _Field_range_(0.0, 1.0) double sigma_r
		void Stylization(const Image& src, Image& dst, double sigma_s = 60, double sigma_r = 0.45);

		[[nodiscard]]
		ColorF SSIM(const Image& image1, const Image& image2);

		void Inpaint(const Image& image, const Image& maskImage, const Color& maskColor, Image& result, int32 radius = 2);

		void Inpaint(const Image& image, const Grid<uint8>& maskImage, Image& result, int32 radius = 2);
	}
}

# include "detail/ImageProcessing.ipp"
