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

# include <Siv3D/LineString.hpp>
# include "GlyphRenderer.hpp"

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include "agg/agg_curves.h"
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		namespace Bound
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

		namespace MSDF
		{
			struct FtContext
			{
				msdfgen::Point2 position;
				msdfgen::Shape* shape;
				msdfgen::Contour* contour;
			};

			inline msdfgen::Point2 ftPoint2(const FT_Vector& vector) noexcept
			{
				return msdfgen::Point2(vector.x / 64., vector.y / 64.);
			}

			static int ftMoveTo(const FT_Vector* to, void* user)
			{
				FtContext* context = reinterpret_cast<FtContext*>(user);
				context->contour = &context->shape->addContour();
				context->position = ftPoint2(*to);
				return 0;
			}

			static int ftLineTo(const FT_Vector* to, void* user)
			{
				FtContext* context = reinterpret_cast<FtContext*>(user);
				context->contour->addEdge(new msdfgen::LinearSegment(context->position, ftPoint2(*to)));
				context->position = ftPoint2(*to);
				return 0;
			}

			static int ftConicTo(const FT_Vector* control, const FT_Vector* to, void* user)
			{
				FtContext* context = reinterpret_cast<FtContext*>(user);
				context->contour->addEdge(new msdfgen::QuadraticSegment(context->position, ftPoint2(*control), ftPoint2(*to)));
				context->position = ftPoint2(*to);
				return 0;
			}

			static int ftCubicTo(const FT_Vector* control1, const FT_Vector* control2, const FT_Vector* to, void* user)
			{
				FtContext* context = reinterpret_cast<FtContext*>(user);
				context->contour->addEdge(new msdfgen::CubicSegment(context->position, ftPoint2(*control1), ftPoint2(*control2), ftPoint2(*to)));
				context->position = ftPoint2(*to);
				return 0;
			}
		}

		namespace Outline
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
		}
	}

	bool LoadGlyph(FT_Face face, GlyphIndex glyphIndex, const FontStyle style)
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

	GlyphBBox GetGlyphBound(FT_Face face)
	{
		detail::Bound::UserData userData;
		{
			const FT_Outline_Funcs func_interface = {
				.move_to	= &detail::Bound::MoveTo,
				.line_to	= &detail::Bound::LineTo,
				.conic_to	= &detail::Bound::ConicTo,
				.cubic_to	= &detail::Bound::CubicTo,
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

	GlyphBBox GetGlyphBound(const msdfgen::Shape& shape)
	{
		double l = Math::Inf;
		double b = Math::Inf;
		double r = -Math::Inf;
		double t = -Math::Inf;
		shape.bound(l, b, r, t);

		return GlyphBBox{
			.xMin = std::round(l),
			.yMin = std::round(b),
			.xMax = std::round(r),
			.yMax = std::round(t)
		};
	}

	Array<LineString> GetGlyphOutline(FT_Face face, GlyphBBox& bbox, const CloseRing closeRing)
	{
		const FT_Outline_Funcs outlineFuncs = {
			.move_to	= &detail::Outline::MoveTo,
			.line_to	= &detail::Outline::LineTo,
			.conic_to	= &detail::Outline::ConicTo,
			.cubic_to	= &detail::Outline::CubicTo,
			.shift = 0,
			.delta = 0
		};

		detail::Outline::OutlineData userData;

		if (const FT_Error error = FT_Outline_Decompose(&face->glyph->outline, &outlineFuncs, &userData))
		{
			return{};
		}

		if (userData.ring)
		{
			detail::Outline::CloseRing(userData.ring);
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

	Image RenderSDF(const std::vector<uint8>& bitmap, const int32 imageWidth, const int32 imageHeight)
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

	bool GetShape(FT_Face face, msdfgen::Shape& shape)
	{
		const FT_Outline_Funcs func_interface = {
			.move_to	= &detail::MSDF::ftMoveTo,
			.line_to	= &detail::MSDF::ftLineTo,
			.conic_to	= &detail::MSDF::ftConicTo,
			.cubic_to	= &detail::MSDF::ftCubicTo,
			.shift = 0,
			.delta = 0
		};

		detail::MSDF::FtContext context = { .shape = &shape };

		if (::FT_Outline_Decompose(&face->glyph->outline, &func_interface, &context))
		{
			return false;
		}

		shape.normalize();
		
		edgeColoringSimple(shape, 3.0);

		return true;
	}

	Image RenderMSDF(const msdfgen::Bitmap<float, 3>& bitmap)
	{
		const int32 imageWidth	= bitmap.width();
		const int32 imageHeight	= bitmap.height();

		Image image(imageWidth, imageHeight, Color{ 0, 0, 0, 255 });
		Color* pDst = image.data();

		for (int32 y = (imageHeight - 1); y >= 0; --y)
		{
			for (int32 x = 0; x < imageWidth; ++x)
			{
				const auto& pixel = bitmap(x, y);
				pDst->r = Clamp(int32(pixel[0] * 0x100), 0, 255);
				pDst->g = Clamp(int32(pixel[1] * 0x100), 0, 255);
				pDst->b = Clamp(int32(pixel[2] * 0x100), 0, 255);
				++pDst;
			}
		}

		return image;
	}
}
