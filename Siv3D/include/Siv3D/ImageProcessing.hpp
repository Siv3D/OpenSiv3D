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
	}
}
