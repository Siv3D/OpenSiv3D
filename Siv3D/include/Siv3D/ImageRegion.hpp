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
# include "Rectangle.hpp"

namespace s3d
{
	class ImageRegion
	{
	private:

		friend class Image;

		const Image& m_imageRef;

		const Rect m_rect;

		ImageRegion(const ImageRegion&) = default;

		ImageRegion& operator = (const ImageRegion&) = delete;

		ImageRegion(const Image& image, const Rect& rect)
			: m_imageRef(image)
			, m_rect(rect) {}

	public:

		void paint(Image& image, int32 x, int32 y, const Color& color = Palette::White) const;

		void paint(Image& image, const Point& pos, const Color& color = Palette::White) const;

		void overwrite(Image& image, int32 x, int32 y, const Color& color = Palette::White) const;

		void overwrite(Image& image, const Point& pos, const Color& color = Palette::White) const;
	};
}
