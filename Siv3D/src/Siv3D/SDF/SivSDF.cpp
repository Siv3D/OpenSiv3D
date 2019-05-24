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

# include <Siv3D/SDF.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3DEngine.hpp>
# include <Font/CFont.hpp>
# include <msdf/msdfgen.h>
# include <msdf/ext/import-font.h>

namespace s3d
{
	namespace SDF
	{
		Image GenerateMSDF(const FilePath& fontFile, const char32 codePoint, const double scale)
		{
			Image result;

			if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype())
			{
				if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, fontFile.narrow().c_str()))
				{
					msdfgen::Shape shape;

					if (loadGlyph(shape, font, codePoint))
					{
						shape.normalize();
						double l = 0.0, b = 0.0, r = 0.0, t = 0.0;
						shape.bounds(l, b, r, t);

						const int32 margin = 1;
						const int32 width = static_cast<int32>((std::ceil(r - l) + (margin * 2)) * scale);
						const int32 height = static_cast<int32>((std::ceil(t - b) + (margin * 2)) * scale);
						const Vec2 offset(-l + margin, -b + margin);

						edgeColoringSimple(shape, 3.0);

						msdfgen::Bitmap<msdfgen::FloatRGB> bitmap(width, height);
						msdfgen::generateMSDF(bitmap, shape, 4.0, scale, msdfgen::Vector2(offset.x, offset.y));

						result.resize(width, height, Color(0, 255));
						Color * pDst = result.data();

						for (int32 y = height - 1; y >= 0; --y)
						{
							for (int32 x = 0; x < width; ++x)
							{
								const auto& pixel = bitmap(x, y);
								pDst->r = msdfgen::clamp(int32(pixel.r * 0x100), 0xff);
								pDst->g = msdfgen::clamp(int32(pixel.g * 0x100), 0xff);
								pDst->b = msdfgen::clamp(int32(pixel.b * 0x100), 0xff);
								++pDst;
							}
						}
					}

					msdfgen::destroyFont(font);
				}

				msdfgen::deinitializeFreetype(ft);
			}

			return result;
		}

		Image GenerateMSDFIcon(const uint32 codePoint, const double scale)
		{
			Image result;

			const Optional<const FontFace&> fontFace = Siv3DEngine::Get<ISiv3DFont>()->getAwesomeIconFontFaceFotCode(static_cast<uint16>(codePoint));

			if (!fontFace)
			{
				return result;
			}

			msdfgen::Shape shape;

			msdfgen::FontHandle font;
			font.face = fontFace->face;

			if (!loadGlyph(shape, &font, codePoint))
			{
				return result;
			}

			shape.normalize();
			double l = 0.0, b = 0.0, r = 0.0, t = 0.0;
			shape.bounds(l, b, r, t);

			const int32 margin = 1;
			const int32 width = static_cast<int32>((std::ceil(r - l) + (margin * 2)) * scale);
			const int32 height = static_cast<int32>((std::ceil(t - b) + (margin * 2)) * scale);
			const Vec2 offset(-l + margin, -b + margin);

			edgeColoringSimple(shape, 3.0);

			msdfgen::Bitmap<msdfgen::FloatRGB> bitmap(width, height);
			msdfgen::generateMSDF(bitmap, shape, 4.0, scale, msdfgen::Vector2(offset.x, offset.y));

			result.resize(width, height, Color(0, 255));
			Color * pDst = result.data();

			for (int32 y = height - 1; y >= 0; --y)
			{
				for (int32 x = 0; x < width; ++x)
				{
					const auto& pixel = bitmap(x, y);
					pDst->r = msdfgen::clamp(int32(pixel.r * 0x100), 0xff);
					pDst->g = msdfgen::clamp(int32(pixel.g * 0x100), 0xff);
					pDst->b = msdfgen::clamp(int32(pixel.b * 0x100), 0xff);
					++pDst;
				}
			}

			return result;
		}
	}
}
