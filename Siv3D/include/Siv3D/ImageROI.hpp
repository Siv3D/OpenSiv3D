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
# include "2DShapes.hpp"
# include "BorderType.hpp"

namespace s3d
{
	class Image;

	struct ImageROI
	{
		Image& imageRef;

		Rect region;

		SIV3D_NODISCARD_CXX20
		ImageROI(Image& image, const Rect& rect) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		ImageROI& negate();

		ImageROI& grayscale();

		ImageROI& sepia();

		ImageROI& posterize(int32 level);

		ImageROI& brighten(int32 level);

		ImageROI& mirror();

		ImageROI& flip();

		ImageROI& rotate180();

		ImageROI& gammaCorrect(double gamma);

		ImageROI& threshold(uint8 threshold, InvertColor invertColor = InvertColor::No);

		//ImageROI& threshold_Otsu(InvertColor invertColor = InvertColor::No);

		//ImageROI& adaptiveThreshold(AdaptiveThresholdMethod method, int32 blockSize, double c, InvertColor invertColor = InvertColor::No);

		ImageROI& mosaic(int32 size);

		ImageROI& mosaic(int32 horizontal, int32 vertical);

		ImageROI& spread(int32 size);

		ImageROI& spread(int32 horizontal, int32 vertical);

		ImageROI& blur(int32 size, BorderType borderType = BorderType::Reflect_101);

		ImageROI& blur(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101);

		ImageROI& medianBlur(int32 apertureSize);

		ImageROI& gaussianBlur(int32 size, BorderType borderType = BorderType::Reflect_101);

		ImageROI& gaussianBlur(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Reflect_101);

		//ImageROI& bilateralFilter(int32 d, double sigmaColor, double sigmaSpace, BorderType borderType = BorderType::Reflect_101);

		ImageROI& dilate(int32 iterations = 1);

		ImageROI& erode(int32 iterations = 1);

		void paint(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paint(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void stamp(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void stamp(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwrite(Image& dst, int32 x, int32 y) const;

		void overwrite(Image& dst, Point pos) const;

		void paintAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paintAt(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void stampAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void stampAt(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwriteAt(Image& dst, int32 x, int32 y) const;

		void overwriteAt(Image& dst, Point pos) const;
	};

	struct ImageConstROI
	{
		const Image& imageRef;

		Rect region;

		SIV3D_NODISCARD_CXX20
		explicit ImageConstROI(const ImageROI& imageROI) noexcept;

		SIV3D_NODISCARD_CXX20
		ImageConstROI(const Image& image, const Rect& rect) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		void paint(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paint(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void stamp(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void stamp(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwrite(Image& dst, int32 x, int32 y) const;

		void overwrite(Image& dst, Point pos) const;

		void paintAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paintAt(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void stampAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void stampAt(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwriteAt(Image& dst, int32 x, int32 y) const;

		void overwriteAt(Image& dst, Point pos) const;
	};
}
