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

# include "GlyphRenderer.hpp"
# include "SDFGlyphRenderer.hpp"
# include "../FreeType.hpp"

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include "mapbox/glyph_foundry_impl.hpp"
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		Image RenderSDF(const std::vector<uint8>& bitmap, const size_t imageWidth, const size_t imageHeight)
		{
			Image image(imageWidth, imageHeight, Color{ 255, 255, 255, 255 });
			const uint8* pSrc = bitmap.data();
			const uint8* const pSrcEnd = (pSrc + bitmap.size());
			Color* pDst = image.data();

			while (pSrc != pSrcEnd)
			{
				const uint8 gray = *pSrc;
				pDst->r = gray;
				pDst->g = gray;
				pDst->b = gray;
				++pDst;
				++pSrc;
			}

			return image;
		}
	}

	SDFGlyph RenderSDFGlyph(FT_Face face, const GlyphIndex glyphIndex, int32 buffer, const FontFaceProperty& prop)
	{
		if (not LoadGlyph(face, glyphIndex, prop.style))
		{
			return{};
		}

		buffer = Max(buffer, 0);

		const FT_Outline_Funcs func_interface = {
			.move_to	= &sdf_glyph_foundry::MoveTo,
			.line_to	= &sdf_glyph_foundry::LineTo,
			.conic_to	= &sdf_glyph_foundry::ConicTo,
			.cubic_to	= &sdf_glyph_foundry::CubicTo,
			.shift		= 0,
			.delta		= 0
		};

		sdf_glyph_foundry::User user;

		if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
		{
			if (::FT_Outline_Decompose(&face->glyph->outline, &func_interface, &user))
			{
				return{};
			}

			if (!user.ring.empty())
			{
				sdf_glyph_foundry::CloseRing(user.ring);
				user.rings.push_back(user.ring);
			}

			if (user.rings.empty())
			{
				return{};
			}
		}
		else
		{
			return{};
		}

		// Calculate the real glyph bbox.
		double bbox_xmin = Math::Inf;
		double bbox_ymin = Math::Inf;
		double bbox_xmax = -Math::Inf;
		double bbox_ymax = -Math::Inf;

		for (const auto& ring : user.rings)
		{
			for (const auto& point : ring)
			{
				if (point.get<0>() > bbox_xmax) bbox_xmax = point.get<0>();
				if (point.get<0>() < bbox_xmin) bbox_xmin = point.get<0>();
				if (point.get<1>() > bbox_ymax) bbox_ymax = point.get<1>();
				if (point.get<1>() < bbox_ymin) bbox_ymin = point.get<1>();
			}
		}

		bbox_xmin = std::round(bbox_xmin);
		bbox_ymin = std::round(bbox_ymin);
		bbox_xmax = std::round(bbox_xmax);
		bbox_ymax = std::round(bbox_ymax);

		// Offset so that glyph outlines are in the bounding box.
		for (auto& ring : user.rings)
		{
			for (auto& point : ring)
			{
				point.set<0>(point.get<0>() + -bbox_xmin + buffer);
				point.set<1>(point.get<1>() + -bbox_ymin + buffer);
			}
		}

		if ((bbox_xmax - bbox_xmin == 0)
			|| (bbox_ymax - bbox_ymin == 0))
		{
			return{};
		}

		::Tree tree;

		for (const auto& ring : user.rings)
		{
			auto p1 = ring.begin();
			auto p2 = p1 + 1;

			for (; p2 != ring.end(); p1++, p2++)
			{
				const int32 segment_x1 = static_cast<int32>(Min(p1->get<0>(), p2->get<0>()));
				const int32 segment_x2 = static_cast<int32>(Max(p1->get<0>(), p2->get<0>()));
				const int32 segment_y1 = static_cast<int32>(Min(p1->get<1>(), p2->get<1>()));
				const int32 segment_y2 = static_cast<int32>(Max(p1->get<1>(), p2->get<1>()));

				tree.insert(::SegmentValue{
					::Box{ ::Point(segment_x1, segment_y1), ::Point(segment_x2, segment_y2) },
					::SegmentPair{ ::Point(p1->get<0>(), p1->get<1>()), ::Point(p2->get<0>(), p2->get<1>()) }
				});
			}
		}

		// Loop over every pixel and determine the positive/negative distance to the outline.
		constexpr double offset			= 0.5;
		constexpr double cutoff			= 0.5;
		constexpr int32 radius			= 8;
		constexpr int32 radius_by_256	= (256 / radius);

		const int32 glyphWidth		= static_cast<int32>(bbox_xmax - bbox_xmin);
		const int32 glyphHeight		= static_cast<int32>(bbox_ymax - bbox_ymin);
		const size_t imageWidth		= (glyphWidth + 2 * buffer);
		const size_t imageHeight	= (glyphHeight + 2 * buffer);
		const size_t bitmap_size	= (imageWidth * imageHeight);
		
		std::vector<uint8> bitmap(bitmap_size);
		uint8* const pDst = bitmap.data();

		for (size_t y = 0; y < imageHeight; ++y)
		{
			const size_t ypos = imageHeight - y - 1;
			const size_t lineIndex = ypos * imageWidth;
			uint8_t* pDstLine = pDst + lineIndex;

			for (size_t x = 0; x < imageWidth; ++x)
			{
				const ::Point pt{ x + offset, y + offset };
				double d = (sdf_glyph_foundry::MinDistanceToLineSegment(tree, pt, radius) * radius_by_256);

				if (sdf_glyph_foundry::PolyContainsPoint(user.rings, pt))
				{
					d = -d;
				}

				// Shift the 0 so that we can fit a few negative values
				// into our 8 bits.
				d += (cutoff * 256);

				// Clamp to 0-255 to prevent overflows or underflows.
				int n = d > 255 ? 255 : static_cast<int>(d);
				n = n < 0 ? 0 : n;
				*pDstLine++ = static_cast<uint8_t>(255 - n);
			}
		}

		SDFGlyph result;
		result.glyphIndex	= glyphIndex;
		result.buffer		= buffer;
		result.left			= static_cast<int16>(bbox_xmin);
		result.top			= static_cast<int16>(bbox_ymax);
		result.width		= static_cast<int16>(bbox_xmax - bbox_xmin);
		result.height		= static_cast<int16>(bbox_ymax - bbox_ymin);
		result.ascender		= prop.ascender;
		result.descender	= prop.descender;
		result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
		result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);
		result.image		= detail::RenderSDF(bitmap, imageWidth, imageHeight);
		return result;
	}
}
