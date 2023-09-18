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
# include "SDFGlyphRenderer.hpp"
# include "../FreeType.hpp"
# include <ThirdParty/msdfgen/msdfgen.h>
# include <ThirdParty/msdfgen/ext/resolve-shape-geometry.h>

namespace s3d
{
	namespace detail
	{
		struct FtContext
		{
			msdfgen::Point2 position = msdfgen::Point2{};
			msdfgen::Shape* shape = nullptr;
			msdfgen::Contour* contour = nullptr;
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

		[[nodiscard]]
		static GlyphBBox GetBound(const msdfgen::Shape& shape)
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

		[[nodiscard]]
		static bool GetShape(FT_Face face, msdfgen::Shape& shape)
		{
			const FT_Outline_Funcs func_interface = {
				.move_to	= &detail::ftMoveTo,
				.line_to	= &detail::ftLineTo,
				.conic_to	= &detail::ftConicTo,
				.cubic_to	= &detail::ftCubicTo,
				.shift = 0,
				.delta = 0
			};

			detail::FtContext context;
			context.shape = &shape;

			if (::FT_Outline_Decompose(&face->glyph->outline, &func_interface, &context))
			{
				return false;
			}

			resolveShapeGeometry(shape);

			shape.normalize();

			edgeColoringSimple(shape, 3.0);

			return true;
		}

		[[nodiscard]]
		static Image RenderMSDF(const msdfgen::Bitmap<float, 1>& bitmap)
		{
			const int32 imageWidth	= bitmap.width();
			const int32 imageHeight	= bitmap.height();

			Image image(imageWidth, imageHeight, Color{ 255, 255 });
			Color* pDst = image.data();

			const float* pLine = bitmap(0, imageHeight - 1);
			const size_t stride = imageWidth;

			for (int32 y = (imageHeight - 1); y >= 0; --y)
			{
				const float* pSrc = pLine;

				for (int32 x = 0; x < imageWidth; ++x)
				{
					pDst->a = static_cast<uint8>(Clamp(int32(*pSrc++ * 0x100), 0, 255));
					++pDst;
				}

				pLine -= stride;
			}

			return image;
		}
	}

	SDFGlyph RenderSDFGlyph(FT_Face face, const GlyphIndex glyphIndex, int32 buffer, const FontFaceProperty& prop)
	{
		if (not LoadOutlineGlyph(face, glyphIndex, prop.style))
		{
			return{};
		}

		buffer = Max(buffer, 0);

		msdfgen::Shape shape;	
		if (not detail::GetShape(face, shape))
		{
			return{};
		}

		const GlyphBBox bbox = detail::GetBound(shape);

		if (std::isinf(bbox.xMin) || std::isinf(bbox.xMax) || std::isinf(bbox.yMin) || std::isinf(bbox.yMax))
		{
			SDFGlyph result;
			result.glyphIndex	= glyphIndex;
			result.buffer		= buffer;
			result.left			= 0;
			result.top			= 0;
			result.width		= 0;
			result.height		= 0;
			result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
			result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);
			result.ascender		= prop.ascender;
			result.descender	= prop.descender;
			result.image		= {};
			return result;
		}
		else
		{
			const int32 width		= static_cast<int32>(bbox.xMax - bbox.xMin);
			const int32 height		= static_cast<int32>(bbox.yMax - bbox.yMin);
			const Vec2 offset{ (-bbox.xMin+ buffer), (-bbox.yMin + buffer) };
			const msdfgen::Projection projection{ 1.0, msdfgen::Vector2{ offset.x, offset.y } };
			msdfgen::GeneratorConfig generatorConfig;
			generatorConfig.overlapSupport = false;

			msdfgen::Bitmap<float, 1> bitmap{ (width + (2 * buffer)), (height + (2 * buffer)) };
			msdfgen::generateSDF(bitmap, shape, projection, 8.0, generatorConfig);

			SDFGlyph result;
			result.glyphIndex	= glyphIndex;
			result.buffer		= buffer;
			result.left			= static_cast<int16>(bbox.xMin);
			result.top			= static_cast<int16>(bbox.yMax);
			result.width		= static_cast<int16>(width);
			result.height		= static_cast<int16>(height);
			result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
			result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);
			result.ascender		= prop.ascender;
			result.descender	= prop.descender;
			result.image		= detail::RenderMSDF(bitmap);
			return result;
		}
	}
}
