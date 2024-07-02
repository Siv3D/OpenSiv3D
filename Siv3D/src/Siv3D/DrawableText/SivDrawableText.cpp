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

# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/BitmapGlyph.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		void RenderToImage(const size_t mode, const DrawableText& drawableText, Image& dst, const Vec2& pos, const Color& color)
		{
			const Font& font = drawableText.font;
			const auto& clusters = drawableText.clusters;
			const auto& text = drawableText.text;

			const double spaceWidth = font.spaceWidth();
			const int32 height = font.height();
			const double lineHeightScale = 1.0;
			const double scale = 1.0;
			const Vec2 basePos{ pos };
			Vec2 penPos{ basePos };
			int32 lineCount = 1;

			for (const auto& cluster : clusters)
			{
				const char32 ch = text[cluster.pos];

				if (IsControl(ch))
				{
					switch (ch)
					{
					case U'\t':
						penPos.x += (spaceWidth * scale * 4);
						break;
					case U'\n':
						penPos.x = basePos.x;
						penPos.y += (height * scale * lineHeightScale);
						++lineCount;
						break;
					default:
						break;
					}

					continue;
				}

				if (cluster.fontIndex != 0)
				{
					//const size_t fallbackIndex = (cluster.fontIndex - 1);
					//RectF rect;
					//
					//if (usebasePos)
					//{
					//	rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
					//		cluster, penPos, size, textStyle, color, lineHeightScale);
					//}
					//else
					//{
					//	rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
					//		cluster, penPos.movedBy(0, prop.ascender * scale), size, textStyle, color, lineHeightScale);
					//}
					//
					//penPos.x += rect.w;
					continue;
				}

				BitmapGlyph glyph = font.renderBitmapByGlyphIndex(cluster.glyphIndex);
				{
					const Vec2 posOffset = glyph.getOffset(scale);
					const Vec2 drawPos = (penPos + posOffset);

					if (mode == 0) // paint
					{
						glyph.image.paint(dst, Math::Round(drawPos).asPoint(), color);
					}
					else if (mode == 1) // stamp
					{
						glyph.image.stamp(dst, Math::Round(drawPos).asPoint(), color);
					}
					else // overwrite
					{
						glyph.image.overwrite(dst, Math::Round(drawPos).asPoint());
					}
				}

				penPos.x += (glyph.xAdvance * scale);
			}
		}
	}

	DrawableText::DrawableText(const Font& _font, const String& _text)
		: font{ _font }
		, text{ _text }
		, clusters{ font.getGlyphClusters(text) } {}

	DrawableText::DrawableText(const Font& _font, String&& _text)
		: font{ _font }
		, text{ std::move(_text) }
		, clusters{ font.getGlyphClusters(text) } {}

	Array<double> DrawableText::getXAdvances() const
	{
		return getXAdvances(font.fontSize());
	}

	Array<double> DrawableText::getXAdvances(const double size) const
	{
		return SIV3D_ENGINE(Font)->getXAdvances(font.id(), text, clusters, size);
	}

	RectF DrawableText::region(const double x, const double y) const
	{
		return region(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::region(const Vec2 pos) const
	{
		return region(font.fontSize(), pos);
	}

	RectF DrawableText::region(const double size, const double x, const double y) const
	{
		return region(size, Vec2{ x, y });
	}

	RectF DrawableText::region(const Arg::topLeft_<Vec2> topLeft) const
	{
		return region(font.fontSize(), topLeft);
	}

	RectF DrawableText::region(const Arg::topCenter_<Vec2> topCenter) const
	{
		return region(font.fontSize(), topCenter);
	}

	RectF DrawableText::region(const Arg::topRight_<Vec2> topRight) const
	{
		return region(font.fontSize(), topRight);
	}

	RectF DrawableText::region(const Arg::rightCenter_<Vec2> rightCenter) const
	{
		return region(font.fontSize(), rightCenter);
	}

	RectF DrawableText::region(const Arg::bottomRight_<Vec2> bottomRight) const
	{
		return region(font.fontSize(), bottomRight);
	}

	RectF DrawableText::region(const Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return region(font.fontSize(), bottomCenter);
	}

	RectF DrawableText::region(const Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return region(font.fontSize(), bottomLeft);
	}

	RectF DrawableText::region(const Arg::leftCenter_<Vec2> leftCenter) const
	{
		return region(font.fontSize(), leftCenter);
	}

	RectF DrawableText::region(const Arg::center_<Vec2> center) const
	{
		return region(font.fontSize(), center);
	}

	RectF DrawableText::region(const double size, const Vec2 pos) const
	{
		return SIV3D_ENGINE(Font)->region(font.id(), text, clusters, pos, size, 1.0);
	}

	RectF DrawableText::region(const double size, const Arg::topLeft_<Vec2> topLeft) const
	{
		return region(size, *topLeft);
	}

	RectF DrawableText::region(const double size, const Arg::topCenter_<Vec2> topCenter) const
	{
		return region(size, topCenter->movedBy(-region(size).w * 0.5, 0));
	}

	RectF DrawableText::region(const double size, const Arg::topRight_<Vec2> topRight) const
	{
		return region(size, topRight->movedBy(-region(size).w, 0));
	}

	RectF DrawableText::region(const double size, const Arg::rightCenter_<Vec2> rightCenter) const
	{
		const RectF textRegion = region(size);

		return region(size, rightCenter->movedBy(-textRegion.w, -textRegion.h * 0.5));
	}

	RectF DrawableText::region(const double size, const Arg::bottomRight_<Vec2> bottomRight) const
	{
		return region(size, bottomRight->movedBy(-region(size).size));
	}

	RectF DrawableText::region(const double size, const Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		const RectF textRegion = region(size);

		return region(size, bottomCenter->movedBy(-textRegion.w * 0.5, -textRegion.h));
	}

	RectF DrawableText::region(const double size, const Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return region(size, bottomLeft->movedBy(0, -region(size).h));
	}

	RectF DrawableText::region(const double size, const Arg::leftCenter_<Vec2> leftCenter) const
	{
		return region(size, leftCenter->movedBy(0, -region(size).h * 0.5));
	}

	RectF DrawableText::region(const double size, const Arg::center_<Vec2> center) const
	{
		return regionAt(size, *center);
	}

	RectF DrawableText::regionBase(const double x, const double y) const
	{
		return regionBase(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionBase(const Vec2 pos) const
	{
		return regionBase(font.fontSize(), pos);
	}

	RectF DrawableText::regionBase(const Arg::left_<Vec2> left) const
	{
		return regionBase(font.fontSize(), left);
	}

	RectF DrawableText::regionBase(const Arg::center_<Vec2> center) const
	{
		return regionBase(font.fontSize(), center);
	}

	RectF DrawableText::regionBase(const Arg::right_<Vec2> right) const
	{
		return regionBase(font.fontSize(), right);
	}

	RectF DrawableText::regionBase(const double size, const double x, const double y) const
	{
		return regionBase(size, Vec2{ x, y });
	}

	RectF DrawableText::regionBase(const double size, const Vec2 pos) const
	{
		return SIV3D_ENGINE(Font)->regionBase(font.id(), text, clusters, pos, size, 1.0);
	}

	RectF DrawableText::regionBase(const double size, const Arg::left_<Vec2> left) const
	{
		return regionBase(size, *left);
	}

	RectF DrawableText::regionBase(const double size, const Arg::center_<Vec2> center) const
	{
		return regionBase(size, center->movedBy(-region(size).w * 0.5, 0));
	}

	RectF DrawableText::regionBase(const double size, const Arg::right_<Vec2> right) const
	{
		return regionBase(size, right->movedBy(-region(size).w, 0));
	}

	RectF DrawableText::regionAt(const double x, const double y) const
	{
		return regionAt(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionAt(const Vec2 pos) const
	{
		return regionAt(font.fontSize(), pos);
	}

	RectF DrawableText::regionAt(const double size, const double x, const double y) const
	{
		return regionAt(size, Vec2{ x, y });
	}

	RectF DrawableText::regionAt(const double size, const Vec2 pos) const
	{
		const RectF rect = region(size, Vec2{ 0, 0 });

		return rect.movedBy(pos - rect.center());
	}

	RectF DrawableText::regionBaseAt(const double x, const double y) const
	{
		return regionBaseAt(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionBaseAt(const Vec2 pos) const
	{
		return regionBaseAt(font.fontSize(), pos);
	}

	RectF DrawableText::regionBaseAt(const double size, const double x, const double y) const
	{
		return regionBaseAt(size, Vec2{ x, y });
	}

	RectF DrawableText::regionBaseAt(const double size, const Vec2 pos) const
	{
		const RectF rect = regionBase(size, Vec2{ 0, 0 });

		return rect.movedBy(pos.x - (rect.w * 0.5), pos.y);
	}

	bool DrawableText::fits(const RectF& area) const
	{
		return fits(font.fontSize(), area);
	}

	bool DrawableText::fits(const double size, const RectF& area) const
	{
		return SIV3D_ENGINE(Font)->fits(font.id(), text, clusters, area, size, 1.0);
	}

	RectF DrawableText::draw(const double x, const double y, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), Vec2{x, y}, color);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), pos, color);
	}

	RectF DrawableText::draw(const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), topLeft, color);
	}

	RectF DrawableText::draw(const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), topCenter, color);
	}

	RectF DrawableText::draw(const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), topRight, color);
	}

	RectF DrawableText::draw(const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), rightCenter, color);
	}

	RectF DrawableText::draw(const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), bottomRight, color);
	}

	RectF DrawableText::draw(const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), bottomCenter, color);
	}

	RectF DrawableText::draw(const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), bottomLeft, color);
	}

	RectF DrawableText::draw(const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), leftCenter, color);
	}

	RectF DrawableText::draw(const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), center, color);
	}

	bool DrawableText::draw(const RectF& area, const ColorF& color) const
	{
		return draw(TextStyle::Default(), font.fontSize(), area, color);
	}

	RectF DrawableText::draw(const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const double size, const Vec2& pos, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, pos, color);
	}

	RectF DrawableText::draw(const double size, const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, topLeft, color);
	}

	RectF DrawableText::draw(const double size, const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, topCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, topRight, color);
	}

	RectF DrawableText::draw(const double size, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, rightCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, bottomRight, color);
	}

	RectF DrawableText::draw(const double size, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, bottomCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, bottomLeft, color);
	}

	RectF DrawableText::draw(const double size, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, leftCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, center, color);
	}

	bool DrawableText::draw(const double size, const RectF& area, const ColorF& color) const
	{
		return draw(TextStyle::Default(), size, area, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), topLeft, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), topCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), topRight, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), rightCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), bottomRight, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), bottomCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), bottomLeft, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), leftCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), center, color);
	}

	bool DrawableText::draw(const TextStyle& textStyle, const RectF& area, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), area, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, clusters, pos, size, textStyle, color, 1.0);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(textStyle, size, *topLeft, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(textStyle, size, topCenter->movedBy(-region(size).w * 0.5, 0), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(textStyle, size, topRight->movedBy(-region(size).w, 0), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		const RectF textRegion = region(size);

		return draw(textStyle, size, rightCenter->movedBy(-textRegion.w, -textRegion.h * 0.5), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(textStyle, size, bottomRight->movedBy(-region(size).size), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		const RectF textRegion = region(size);

		return draw(textStyle, size, bottomCenter->movedBy(-textRegion.w * 0.5, -textRegion.h), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(textStyle, size, bottomLeft->movedBy(0, -region(size).h), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(textStyle, size, leftCenter->movedBy(0, -region(size).h * 0.5), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawAt(textStyle, size, *center, color);
	}

	bool DrawableText::draw(const TextStyle& textStyle, const double size, const RectF& area, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, clusters, area, size, textStyle, color, 1.0);
	}

	RectF DrawableText::drawBase(const double x, const double y, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const Vec2& pos, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), font.fontSize(), left, color);
	}

	RectF DrawableText::drawBase(const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), font.fontSize(), center, color);
	}

	RectF DrawableText::drawBase(const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), font.fontSize(), right, color);
	}

	RectF DrawableText::drawBase(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), size, pos, color);
	}

	RectF DrawableText::drawBase(const double size, const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), size, left, color);
	}

	RectF DrawableText::drawBase(const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), size, center, color);
	}

	RectF DrawableText::drawBase(const double size, const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(TextStyle::Default(), size, right, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), left, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), center, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), right, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->drawBase(font.id(), text, clusters, pos, size, textStyle, color, 1.0);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(textStyle, size, *left, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(textStyle, size, center->movedBy(-region(size).w * 0.5, 0), color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(textStyle, size, right->movedBy(-region(size).w, 0), color);
	}

	RectF DrawableText::drawAt(const double x, const double y, const ColorF& color) const
	{
		return drawAt(TextStyle::Default(), font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const Vec2& pos, const ColorF& color) const
	{
		return drawAt(TextStyle::Default(), font.fontSize(), pos, color);
	}

	RectF DrawableText::drawAt(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawAt(TextStyle::Default(), size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawAt(TextStyle::Default(), size, pos, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawAt(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawAt(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawAt(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		const RectF rect = region(size, Vec2{ 0, 0 });

		const Vec2 drawPos = (pos - rect.center());

		return draw(textStyle, size, drawPos, color);
	}

	RectF DrawableText::drawBaseAt(const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default(), font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default(), font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBaseAt(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default(), size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default(), size, pos, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		const RectF rect = regionBase(size, Vec2{ 0, 0 });

		const double drawPosX = (pos.x - (rect.w * 0.5));

		return drawBase(textStyle, size, Vec2{ drawPosX, pos.y }, color);
	}

	void DrawableText::paint(Image& dst, const double x, const double y, const Color& color) const
	{
		paint(dst, Vec2{ x, y }, color);
	}

	void DrawableText::paint(Image& dst, const Vec2& pos, const Color& color) const
	{
		detail::RenderToImage(0, *this, dst, pos, color);
	}

	void DrawableText::stamp(Image& dst, const double x, const double y, const Color& color) const
	{
		stamp(dst, Vec2{ x, y }, color);
	}

	void DrawableText::stamp(Image& dst, const Vec2& pos, const Color& color) const
	{
		detail::RenderToImage(1, *this, dst, pos, color);
	}

	void DrawableText::overwrite(Image& dst, const double x, const double y) const
	{
		overwrite(dst, Vec2{ x, y });
	}

	void DrawableText::overwrite(Image& dst, const Vec2& pos) const
	{
		detail::RenderToImage(2, *this, dst, pos, Palette::White);
	}

	void DrawableText::paintAt(Image& dst, const double x, const double y, const Color& color) const
	{
		paintAt(dst, Vec2{ x, y }, color);
	}

	void DrawableText::paintAt(Image& dst, const Vec2& pos, const Color& color) const
	{
		const RectF rect = region(font.fontSize(), Vec2{ 0, 0 });

		const Vec2 drawPos = (pos - rect.center());

		detail::RenderToImage(0, *this, dst, drawPos, color);
	}

	void DrawableText::stampAt(Image& dst, const double x, const double y, const Color& color) const
	{
		stampAt(dst, Vec2{ x, y }, color);
	}

	void DrawableText::stampAt(Image& dst, const Vec2& pos, const Color& color) const
	{
		const RectF rect = region(font.fontSize(), Vec2{ 0, 0 });

		const Vec2 drawPos = (pos - rect.center());

		detail::RenderToImage(1, *this, dst, drawPos, color);
	}

	void DrawableText::overwriteAt(Image& dst, const double x, const double y) const
	{
		overwriteAt(dst, Vec2{ x, y });
	}

	void DrawableText::overwriteAt(Image& dst, const Vec2& pos) const
	{
		const RectF rect = region(font.fontSize(), Vec2{ 0, 0 });

		const Vec2 drawPos = (pos - rect.center());

		detail::RenderToImage(2, *this, dst, drawPos, Palette::White);
	}
}
