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

# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/Sprite.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/OffsetCircular.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr uint16 CaluculateFanQuality(const double r) noexcept
		{
			return r <= 1.0 ? 3
				: r <= 6.0 ? 5
				: r <= 12.0 ? 8
				: static_cast<uint16>(std::min(64.0, r * 0.2 + 6));
		}
	}

	template <class SizeType>
	RoundRect Rectangle<SizeType>::rounded(const double r) const noexcept
	{
		return RoundRect(*this, r);
	}

	template <class SizeType>
	Polygon Rectangle<SizeType>::rounded(double tl, double tr, double br, double bl) const noexcept
	{
		constexpr double epsilon = 0.001;

		tl = std::max(tl, 0.0);
		tr = std::max(tr, 0.0);
		br = std::max(br, 0.0);
		bl = std::max(bl, 0.0);

		if (const double t = (tl + tr); t > w)
		{
			const double s = w / t;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		if (const double r = (tr + br); r > h)
		{
			const double s = h / r;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		if (const double b = (bl + br); b > w)
		{
			const double s = w / b;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		if (const double l = (tl + bl); l > h)
		{
			const double s = h / l;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		const Vec2 tlCenter = this->tl() + Vec2(tl, tl);
		const Vec2 trCenter = this->tr() + Vec2(-tr, tr);
		const Vec2 brCenter = this->br() + Vec2(-br, -br);
		const Vec2 blCenter = this->bl() + Vec2(bl, -bl);

		const float scale = Siv3DEngine::Get<ISiv3DRenderer2D>()->getMaxScaling();

		Array<Vec2> vertices;

		if (tl)
		{
			const int32 quality = detail::CaluculateFanQuality(tl * scale);
			const double radDelta = Math::Constants::HalfPi / (quality - 1);

			for (int32 i = 0; i < quality; ++i)
			{
				vertices << OffsetCircular9(tlCenter, tl, radDelta * i);
			}
		}
		else
		{
			vertices << tlCenter;
		}

		if (tr)
		{
			const int32 quality = detail::CaluculateFanQuality(tr * scale);
			const double radDelta = Math::Constants::HalfPi / (quality - 1);

			for (int32 i = 0; i < quality; ++i)
			{
				vertices << OffsetCircular0(trCenter, tr, radDelta * i);
			}
		}
		else
		{
			vertices << trCenter;
		}

		if (br)
		{
			const int32 quality = detail::CaluculateFanQuality(br * scale);
			const double radDelta = Math::Constants::HalfPi / (quality - 1);

			for (int32 i = 0; i < quality; ++i)
			{
				vertices << OffsetCircular3(brCenter, br, radDelta * i);
			}
		}
		else
		{
			vertices << brCenter;
		}

		if (bl)
		{
			const int32 quality = detail::CaluculateFanQuality(bl * scale);
			const double radDelta = Math::Constants::HalfPi / (quality - 1);

			for (int32 i = 0; i < quality; ++i)
			{
				vertices << OffsetCircular6(blCenter, bl, radDelta * i);
			}
		}
		else
		{
			vertices << blCenter;
		}

		for (auto it = vertices.begin() + 1; it != vertices.end();)
		{
			if (it->distanceFromSq(*(it - 1)) < epsilon)
			{
				it = vertices.erase(it);
			}
			else
			{
				++it;
			}
		}

		if (vertices.size() > 3
			&& (vertices.front().distanceFromSq(vertices.back()) < epsilon))
		{
			vertices.pop_back();
		}

		return Polygon(vertices);
	}

	template <class SizeType>
	bool Rectangle<SizeType>::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	template <>
	const Rectangle<Point>& Rectangle<Point>::paint(Image& dst, const Color& color) const
	{
		const int32 xBegin = std::max(x, 0);
		const int32 xEnd = std::min(x + w, dst.width());
		const int32 yBegin = std::max(y, 0);
		const int32 yEnd = std::min(y + h, dst.height());
		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stride = dst.width();
		const int32 stepOffset = stride - fillWidth;

		const uint32 srcBlend = color.a;

		if (srcBlend == 255)
		{
			for (int32 _y = 0; _y < fillHeight; ++_y)
			{
				for (int32 _x = 0; _x < fillWidth; ++_x)
				{
					const uint8 a = pDst->a;
					*pDst = color;
					pDst->a = a;

					++pDst;
				}

				pDst += stepOffset;
			}
		}
		else
		{
			const uint32 premulSrcR = srcBlend * color.r;
			const uint32 premulSrcG = srcBlend * color.g;
			const uint32 premulSrcB = srcBlend * color.b;
			const uint32 dstBlend = 255 - srcBlend;

			for (int32 _y = 0; _y < fillHeight; ++_y)
			{
				for (int32 _x = 0; _x < fillWidth; ++_x)
				{
					pDst->r = (pDst->r * dstBlend + premulSrcR) / 255;
					pDst->g = (pDst->g * dstBlend + premulSrcG) / 255;
					pDst->b = (pDst->b * dstBlend + premulSrcB) / 255;

					++pDst;
				}

				pDst += stepOffset;
			}
		}

		return *this;
	}

	template <>
	const Rectangle<Point>& Rectangle<Point>::overwrite(Image& dst, const Color& color) const
	{
		const int32 xBegin = std::max(x, 0);
		const int32 xEnd = std::min(x + w, dst.width());
		const int32 yBegin = std::max(y, 0);
		const int32 yEnd = std::min(y + h, dst.height());
		const int32 fillWidth = xEnd - xBegin;
		const int32 fillHeight = yEnd - yBegin;

		if (fillWidth <= 0 || fillHeight <= 0)
		{
			return *this;
		}

		Color* pDst = dst.data() + yBegin * dst.width() + xBegin;
		const int32 stride = dst.width();
		const int32 stepOffset = stride - fillWidth;

		for (int32 _y = 0; _y < fillHeight; ++_y)
		{
			for (int32 _x = 0; _x < fillWidth; ++_x)
			{
				*pDst = color;

				++pDst;
			}

			pDst += stepOffset;
		}

		return *this;
	}

	template <>
	const Rectangle<Vec2>& Rectangle<Vec2>::paint(Image& dst, const Color& color) const
	{
		Rect(*this).paint(dst, color);

		return *this;
	}

	template <>
	const Rectangle<Vec2>& Rectangle<Vec2>::overwrite(Image& dst, const Color& color) const
	{
		Rect(*this).overwrite(dst, color);

		return *this;
	}

	template <>
	const Rectangle<Point>& Rectangle<Point>::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		if (w <= 0 || h <= 0)
		{
			return *this;
		}

		const int32 x0 = x - outerThickness;
		const int32 x1 = x + innerThickness;
		const int32 x2 = x + w - innerThickness;
		const int32 x3 = x + w + outerThickness;

		const int32 y0 = y - outerThickness;
		const int32 y1 = y + innerThickness;
		const int32 y2 = y + h - innerThickness;
		const int32 y3 = y + h + outerThickness;

		Rect(x0, y0, x3 - x0, y1 - y0).paint(dst, color);
		Rect(x0, y1, x1 - x0, y2 - y1).paint(dst, color);
		Rect(x2, y1, x3 - x2, y2 - y1).paint(dst, color);
		Rect(x0, y2, x3 - x0, y3 - y2).paint(dst, color);

		return *this;
	}

	template <>
	const Rectangle<Point>& Rectangle<Point>::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		if (w <= 0 || h <= 0)
		{
			return *this;
		}

		const int32 x0 = x - outerThickness;
		const int32 x1 = x + innerThickness;
		const int32 x2 = x + w - innerThickness;
		const int32 x3 = x + w + outerThickness;

		const int32 y0 = y - outerThickness;
		const int32 y1 = y + innerThickness;
		const int32 y2 = y + h - innerThickness;
		const int32 y3 = y + h + outerThickness;

		Rect(x0, y0, x3 - x0, y1 - y0).overwrite(dst, color);
		Rect(x0, y1, x1 - x0, y2 - y1).overwrite(dst, color);
		Rect(x2, y1, x3 - x2, y2 - y1).overwrite(dst, color);
		Rect(x0, y2, x3 - x0, y3 - y2).overwrite(dst, color);

		return *this;
	}

	template <>
	const Rectangle<Vec2>& Rectangle<Vec2>::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		Rect(*this).paintFrame(dst, innerThickness, outerThickness, color);

		return *this;
	}

	template <>
	const Rectangle<Vec2>& Rectangle<Vec2>::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		Rect(*this).overwriteFrame(dst, innerThickness, outerThickness, color);

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF& color) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addRect(FloatRect(x, y, x + w, y + h), color.toFloat4());

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF(&colors)[4]) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addRect(FloatRect(x, y, x + w, y + h),
			{ colors[0].toFloat4(), colors[1].toFloat4(), colors[2].toFloat4(), colors[3].toFloat4() });

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addRectFrame(
			FloatRect(x + innerThickness, y + innerThickness, x + w - innerThickness, y + h - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
		);

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawShadow(const Vec2& offset, double blurRadius, double spread, const ColorF& color) const
	{
		if (blurRadius < 0.0)
		{
			return *this;
		}

		const RectF rect = RectF(pos + offset, size).stretched(spread + blurRadius * 0.5);
		const Float4 colorF = color.toFloat4();

		const double rr = Min({ rect.w * 0.5, rect.h * 0.5, blurRadius });
		const float xs[4] =
		{
			static_cast<float>(rect.x),
			static_cast<float>(rect.x + rr),
			static_cast<float>(rect.x + rect.w - rr),
			static_cast<float>(rect.x + rect.w)
		};

		const float ys[4] =
		{
			static_cast<float>(rect.y),
			static_cast<float>(rect.y + rr),
			static_cast<float>(rect.y + rect.h - rr),
			static_cast<float>(rect.y + rect.h)
		};

		const float uvs[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

		Sprite sprite(16, 54);

		Vertex2D* pVertex = sprite.vertices.data();

		for (int32 i = 0; i < 16; ++i)
		{
			pVertex->pos.set(xs[i % 4], ys[i / 4]);
			pVertex->tex.set(uvs[i % 4], uvs[i / 4]);
			pVertex->color = colorF;
			++pVertex;
		}

		static const uint16 rectIndexTable[6] = { 0, 1, 4, 4, 1, 5 };

		for (uint16 ty = 0; ty < 3; ++ty)
		{
			for (uint16 tx = 0; tx < 3; ++tx)
			{
				for (uint16 k = 0; k < 6; ++k)
				{
					sprite.indices[(ty * 3 + tx) * 6 + k] = (ty * 4) + tx + rectIndexTable[k];
				}
			}
		}

		sprite.draw(Siv3DEngine::Get<ISiv3DRenderer2D>()->getBoxShadowTexture());

		return *this;
	}

	template <class SizeType>
	TexturedQuad Rectangle<SizeType>::operator ()(const Texture& texture) const
	{
		return TexturedQuad(texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			{ pos,{ x + w, y },{ x + w, y + h },{ x, y + h } },
			center());
	}

	template <class SizeType>
	TexturedQuad Rectangle<SizeType>::operator ()(const TextureRegion& textureRegion) const
	{
		return TexturedQuad(textureRegion.texture,
			textureRegion.uvRect,
			{ pos,{ x + w, y },{ x + w, y + h },{ x, y + h } },
			center());
	}

	template <class SizeType>
	Polygon Rectangle<SizeType>::asPolygon() const
	{
		return Polygon({ { x, y },{ x + w, y },{ x + w, y + h },{ x, y + h } }, { 0, 1, 3, 3, 1, 2 }, *this);
	}

	void Formatter(FormatData& formatData, const Rect& value)
	{
		const size_t bufferSize = 12 * 4 + 9;
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt(&p, value.x);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.y);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.w);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.h);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}

	void Formatter(FormatData& formatData, const RectF& value)
	{
		Formatter(formatData, Vec4(value.x, value.y, value.w, value.h));
	}

	template struct Rectangle<Point>;
	
	template struct Rectangle<Vec2>;
}
