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
		struct UserData
		{
			double xMin = Math::Inf;
			double yMin = Math::Inf;
			double xMax = -Math::Inf;
			double yMax = -Math::Inf;

			Vec2 last = { Math::NaN, Math::NaN };

			void update(double x, double y) noexcept
			{
				if (xMax < x)
				{
					xMax = x;
				}

				if (x < xMin)
				{
					xMin = x;
				}

				if (yMax < y)
				{
					yMax = y;
				}

				if (y < yMin)
				{
					yMin = y;
				}

				last.set(x, y);
			}
		};

		static int MoveTo(const FT_Vector* to, void* ptr)
		{
			UserData* user = static_cast<UserData*>(ptr);
			user->update(to->x, to->y);
			return 0;
		}

		static int LineTo(const FT_Vector* to, void* ptr)
		{
			UserData* user = static_cast<UserData*>(ptr);
			user->update(to->x, to->y);
			return 0;
		}

		static int ConicTo(const FT_Vector* control, const FT_Vector* to, void* ptr)
		{
			UserData* user = static_cast<UserData*>(ptr);

			if (not user->last.hasNaN())
			{
				const Vec2 prev = user->last;

				agg_fontnik::curve3_div curve(prev.x, prev.y, control->x, control->y, to->x, to->y);
				curve.rewind(0);

				double x, y;
				unsigned cmd;
				while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y)))
				{
					user->update(x, y);
				}
			}

			return 0;
		}

		static int CubicTo(const FT_Vector* c1, const FT_Vector* c2, const FT_Vector* to, void* ptr)
		{
			UserData* user = static_cast<UserData*>(ptr);

			if (not user->last.hasNaN())
			{
				const Vec2 prev = user->last;

				agg_fontnik::curve4_div curve(prev.x, prev.y, c1->x, c1->y, c2->x, c2->y, to->x, to->y);
				curve.rewind(0);

				double x, y;
				unsigned cmd;
				while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y)))
				{
					user->update(x, y);
				}
			}

			return 0;
		}
	}

	bool LoadOutlineGlyph(FT_Face face, const GlyphIndex glyphIndex, const FontStyle style)
	{
		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex,
			(FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP)))
		{
			return false;
		}

		if (style & FontStyle::Bold)
		{
			::FT_GlyphSlot_Embolden(face->glyph);
		}

		if (style & FontStyle::Italic)
		{
			::FT_GlyphSlot_Oblique(face->glyph);
		}

		return true;
	}

	GlyphBBox GetOutlineGlyphBound(FT_Face face)
	{
		detail::UserData userData;
		{
			const FT_Outline_Funcs func_interface = {
				.move_to	= &detail::MoveTo,
				.line_to	= &detail::LineTo,
				.conic_to	= &detail::ConicTo,
				.cubic_to	= &detail::CubicTo,
				.shift = 0,
				.delta = 0
			};

			if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
			{
				if (::FT_Outline_Decompose(&face->glyph->outline, &func_interface, &userData))
				{
					return{};
				}

				if (userData.last.hasNaN())
				{
					return{};
				}
			}
			else
			{
				return{};
			}
		}

		userData.xMin /= 64.0;
		userData.yMin /= 64.0;
		userData.xMax /= 64.0;
		userData.yMax /= 64.0;

		const double xMin = std::round(userData.xMin);
		const double yMin = std::round(userData.yMin);
		const double xMax = std::round(userData.xMax);
		const double yMax = std::round(userData.yMax);

		if (((xMax - xMin) == 0)
			|| ((yMax - yMin) == 0))
		{
			return{};
		}

		return GlyphBBox{
			.xMin = xMin,
			.yMin = yMin,
			.xMax = xMax,
			.yMax = yMax,
		};
	}

	GlyphInfo GetGlyphInfo(FT_Face face, const GlyphIndex glyphIndex, const FontFaceProperty& prop, const FontMethod method)
	{
		const bool hasColor = prop.hasColor;

		if (hasColor)
		{
			if (not ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_COLOR))
			{
				GlyphInfo result;
				result.glyphIndex	= glyphIndex;
				result.left			= static_cast<int16>(face->glyph->bitmap_left);
				result.top			= static_cast<int16>(face->glyph->bitmap_top);
				result.width		= static_cast<int16>(face->glyph->bitmap.width);
				result.height		= static_cast<int16>(face->glyph->bitmap.rows);
				result.ascender		= prop.ascender;
				result.descender	= prop.descender;
				result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
				result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);

				if (result.yAdvance == 0)
				{
					result.yAdvance = result.xAdvance;
				}

				return result;
			}
		}

		if (method == FontMethod::Bitmap)
		{
			FT_Int32 flag = (FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING);

			if (!(prop.style & FontStyle::Bitmap))
			{
				flag |= FT_LOAD_NO_BITMAP;
			}

			if (::FT_Load_Glyph(face, glyphIndex, flag))
			{
				return{};
			}

			if (prop.style & FontStyle::Bold)
			{
				::FT_GlyphSlot_Embolden(face->glyph);
			}

			if (prop.style & FontStyle::Italic)
			{
				::FT_GlyphSlot_Oblique(face->glyph);
			}

			GlyphInfo result;
			result.glyphIndex	= glyphIndex;
			result.left			= static_cast<int16>(face->glyph->bitmap_left);
			result.top			= static_cast<int16>(face->glyph->bitmap_top);
			result.width		= static_cast<int16>(face->glyph->bitmap.width);
			result.height		= static_cast<int16>(face->glyph->bitmap.rows);
			result.ascender		= prop.ascender;
			result.descender	= prop.descender;
			result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
			result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);

			return result;
		}
	
		if (not LoadOutlineGlyph(face, glyphIndex, prop.style))
		{
			return{};
		}

		const GlyphBBox bbox = GetOutlineGlyphBound(face);

		return GlyphInfo{
			.glyphIndex	= glyphIndex,
			.buffer		= 0,
			.left		= static_cast<int16>(bbox.xMin),
			.top		= static_cast<int16>(bbox.yMax),
			.width		= static_cast<int16>(bbox.xMax - bbox.xMin),
			.height		= static_cast<int16>(bbox.yMax - bbox.yMin),
			.ascender	= prop.ascender,
			.descender	= prop.descender,
			.xAdvance	= (face->glyph->metrics.horiAdvance / 64.0),
			.yAdvance	= (face->glyph->metrics.vertAdvance / 64.0),
		};
	}
}
