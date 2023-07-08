//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "GlyphRenderer.hpp"
# include "OutlineGlyphRenderer.hpp"
# include "../FreeType.hpp"

# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wdeprecated-enum-enum-conversion"
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include "agg/agg_curves.h"
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# ifdef __clang__
#	pragma clang diagnostic pop
# endif

namespace s3d
{
	namespace detail
	{
		struct OutlineData
		{
			Array<LineString> rings;

			LineString ring;
		};

		static void CloseRing(LineString& ring)
		{
			const Vec2& first = ring.front();
			const Vec2& last = ring.back();

			if (first != last)
			{
				ring.push_back(first);
			}
		}

		static int MoveTo(const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);

			if (user->ring)
			{
				CloseRing(user->ring);
				user->rings.push_back(user->ring);
				user->ring.clear();
			}

			user->ring.emplace_back((to->x / 64.0), (to->y / 64.0));
			return 0;
		}

		static int LineTo(const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);
			user->ring.emplace_back((to->x / 64.0), (to->y / 64.0));
			return 0;
		}

		static int ConicTo(const FT_Vector* control, const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);

			if (user->ring)
			{
				const Vec2 prev = user->ring.back();
				user->ring.pop_back();

				agg_fontnik::curve3_div curve{ prev.x, prev.y,
					(control->x / 64.0), (control->y / 64.0),
					(to->x / 64.0), (to->y / 64.0) };
				curve.rewind(0);

				double x, y;
				unsigned cmd;

				while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y)))
				{
					user->ring.emplace_back(x, y);
				}
			}

			return 0;
		}

		static int CubicTo(const FT_Vector* c1, const FT_Vector* c2, const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);

			if (user->ring)
			{
				const Vec2 prev = user->ring.back();
				user->ring.pop_back();

				agg_fontnik::curve4_div curve{ prev.x, prev.y,
					(c1->x / 64.0), (c1->y / 64.0),
					(c2->x / 64.0), (c2->y / 64.0),
					(to->x / 64.0), (to->y / 64.0) };
				curve.rewind(0);

				double x, y;
				unsigned cmd;

				while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y)))
				{
					user->ring.emplace_back(x, y);
				}
			}

			return 0;
		}

		[[nodiscard]]
		static Array<LineString> GetGlyphOutline(FT_Face face, GlyphBBox& bbox, const s3d::CloseRing closeRing)
		{
			const FT_Outline_Funcs outlineFuncs = {
				.move_to	= &detail::MoveTo,
				.line_to	= &detail::LineTo,
				.conic_to	= &detail::ConicTo,
				.cubic_to	= &detail::CubicTo,
				.shift = 0,
				.delta = 0
			};

			detail::OutlineData userData;

			if (const FT_Error error = FT_Outline_Decompose(&face->glyph->outline, &outlineFuncs, &userData))
			{
				return{};
			}

			if (userData.ring)
			{
				detail::CloseRing(userData.ring);
				userData.rings.push_back(userData.ring);
			}

			if (not userData.rings)
			{
				return{};
			}

			for (auto& ring : userData.rings)
			{
				ring.unique_consecutive();
			}

			const auto orientation = FT_Outline_Get_Orientation(&face->glyph->outline);
			if (orientation == FT_ORIENTATION_POSTSCRIPT)
			{
				for (auto& ring : userData.rings)
				{
					ring.reverse();
				}
			}

			if (not closeRing)
			{
				for (auto& ring : userData.rings)
				{
					if (ring.front() == ring.back())
					{
						ring.pop_back();
					}
				}
			}

			GlyphBBox t;
			{
				for (const auto& ring : userData.rings)
				{
					for (const auto& point : ring)
					{
						if (t.xMax < point.x)
						{
							t.xMax = point.x;
						}

						if (point.x < t.xMin)
						{
							t.xMin = point.x;
						}

						if (t.yMax < point.y)
						{
							t.yMax = point.y;
						}

						if (point.y < t.yMin)
						{
							t.yMin = point.y;
						}
					}
				}
			}

			for (auto& ring : userData.rings)
			{
				for (auto& point : ring)
				{
					point.x -= t.xMin;
					point.y = -point.y;
					point.y += t.yMax;
				}
			}

			bbox.xMin = std::round(t.xMin);
			bbox.yMin = std::round(t.yMin);
			bbox.xMax = std::round(t.xMax);
			bbox.yMax = std::round(t.yMax);

			return userData.rings;
		}
	}

	OutlineGlyph RenderOutlineGlyph(FT_Face face, const GlyphIndex glyphIndex, const CloseRing closeRing, const FontFaceProperty& prop)
	{
		if (not LoadOutlineGlyph(face, glyphIndex, prop.style))
		{
			return{};
		}

		GlyphBBox bbox;
		Array<LineString> rings = detail::GetGlyphOutline(face, bbox, closeRing);

		OutlineGlyph result;
		result.glyphIndex	= glyphIndex;
		result.left			= static_cast<int16>(bbox.xMin);
		result.top			= static_cast<int16>(bbox.yMax);
		result.width		= static_cast<int16>(bbox.xMax - bbox.xMin);
		result.height		= static_cast<int16>(bbox.yMax - bbox.yMin);
		result.ascender		= prop.ascender;
		result.descender	= prop.descender;
		result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
		result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);
		result.rings		= std::move(rings);
		return result;
	}
}
