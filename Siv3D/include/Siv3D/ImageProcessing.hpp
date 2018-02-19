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
# include "Fwd.hpp"
# include "Array.hpp"
# include "Image.hpp"
# include "Polygon.hpp"

namespace s3d
{
	namespace ImageProcessing
	{
		[[nodiscard]] inline constexpr uint32 CalculateMipCount(uint32 width, uint32 height)
		{
			uint32 numLevels = 1u;

			while (width > 1u && height > 1u)
			{
				width = std::max(width / 2, 1u);

				height = std::max(height / 2, 1u);

				++numLevels;
			}

			return numLevels;
		}

		[[nodiscard]] Array<Image> GenerateMips(const Image& src);

		[[nodiscard]] Image GenerateSDF(const Image& image, const uint32 scale, const double spread = 16.0);

		/// <summary>
		/// 画像から最大の輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された Polygon
		/// </returns>
		Polygon FindExternalContour(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		/// <summary>
		/// 画像から輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された Polygon の Array
		/// </returns>
		Array<Polygon> FindExternalContours(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		/// <summary>
		/// 画像から穴を含む最大の輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された Polygon
		/// </returns>
		Polygon FindContour(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		/// <summary>
		/// 画像から穴を含む輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された Polygon の Array
		/// </returns>
		Array<Polygon> FindContours(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		void Sobel(const Image& src, Image& dst, int32 dx = 1, int32 dy = 1, int32 apertureSize = 3);

		void Laplacian(const Image& src, Image& dst, int32 apertureSize = 3);

		void Canny(const Image& src, Image& dst, uint8 lowThreshold, uint8 highThreshold, int32 apertureSize = 3, bool useL2Gradient = false);

		//void EdgePreservingFilter(const Image& src, Image& dst, EdgePreservingFilterType filterType = EdgePreservingFilterType::Recursive, _Field_range_(0.0, 200.0) double sigma_s = 60, _Field_range_(0.0, 1.0) double sigma_r = 0.4);

		//void DetailEnhance(const Image& src, Image& dst, _Field_range_(0.0, 200.0) double sigma_s = 10, _Field_range_(0.0, 1.0) double sigma_r = 0.15);

		//void Stylization(const Image& src, Image& dst, _Field_range_(0.0, 200.0) double sigma_s = 60, _Field_range_(0.0, 1.0) double sigma_r = 0.07);

		//ColorF SSIM(const Image& image1, const Image& image2);

		//Array<Rect> DetectFaces(const Image& image, CascadeType cascadeType = CascadeType::Photo, int32 minNeighbors = 3, const Point& minSize = { 30, 30 }, const Point& maxSize = { 0, 0 });

		//void Inpaint(const Image& image, const Image& maskImage, Image& result, int32 radius = 2);

		//void Inpaint(const Image& image, const Grid<uint8>& maskImage, Image& result, int32 radius = 2);
	}
}
