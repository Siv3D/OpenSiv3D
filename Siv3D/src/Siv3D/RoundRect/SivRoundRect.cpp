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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CaluculateFanQuality(const double r) noexcept
		{
			return r <= 1.0 ? 3
				: r <= 6.0 ? 5
				: r <= 12.0 ? 8
				: static_cast<Vertex2D::IndexType>(Min(64.0, r * 0.2 + 6));
		}

		[[nodiscard]]
		static Array<Vec2> GetOuterVertices(const RoundRect& rect, const double offset, const Optional<float>& scalingFactor)
		{
			const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), Max(0.0, rect.r) }) + offset;
			const float scale = scalingFactor ? *scalingFactor : SIV3D_ENGINE(Renderer2D)->getMaxScaling();
			const int32 quality = detail::CaluculateFanQuality(rr * scale);
			const double radDelta = (Math::HalfPi / (quality - 1));

			Array<Vec2> fanPositions(quality);

			for (int32 i = 0; i < quality; ++i)
			{
				fanPositions[i] = Circular{ rr, (radDelta * i) }.fastToVec2();
			}

			const bool uniteV = (rect.h * 0.5 == rr);
			const bool uniteH = (rect.w * 0.5 == rr);
			const std::array<Vec2, 4> centers =
			{ {
				{ rect.x + rect.w - rr + offset, rect.y + rr - offset },
				{ rect.x + rect.w - rr + offset, rect.y + rect.h - rr + offset },
				{ rect.x + rr - offset, rect.y + rect.h - rr + offset },
				{ rect.x + rr - offset, rect.y + rr - offset },
			} };

			const uint32 vertexSize = (quality - uniteV + quality - uniteH) * 2;

			Array<Vec2> vertices(vertexSize);
			{
				Vec2* pVertex = vertices.data();

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					*pVertex++ = centers[0] + fanPositions[i];
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					*pVertex++ = centers[1] + Float2{ fanPositions[quality - i - 1].x, -fanPositions[quality - i - 1].y };
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					*pVertex++ = centers[2] - fanPositions[i];
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					*pVertex++ = centers[3] + Float2{ -fanPositions[quality - i - 1].x, fanPositions[quality - i - 1].y };
				}
			}

			return vertices;
		}
	}

	Array<Vec2> RoundRect::outerVertices(const uint32 quality) const
	{
		const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), r });

		if (rr <= 0.0)
		{
			return{};
		}

		const uint32 n = Max(quality, 3u);
		return detail::GetOuterVertices(*this, 0.0, (n / 24.0f));
	}

	Polygon RoundRect::asPolygon(const uint32 quality) const
	{
		const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), r });

		if (rr <= 0.0)
		{
			return{};
		}

		const uint32 n = Max(quality, 3u);
		const Array<Vec2> vertices = detail::GetOuterVertices(*this, 0.0, (n / 24.0f));

		Array<TriangleIndex> indices(vertices.size() - 2);
		TriangleIndex* pDst = indices.data();

		for (Vertex2D::IndexType i = 0; i < indices.size(); ++i)
		{
			pDst->i0 = 0;
			pDst->i1 = (i + 1);
			pDst->i2 = (i + 2);
			++pDst;
		}

		return Polygon{ vertices, indices, rect, SkipValidation::Yes };
	}

	bool RoundRect::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool RoundRect::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool RoundRect::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool RoundRect::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool RoundRect::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool RoundRect::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool RoundRect::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const RoundRect& RoundRect::paint(Image& dst, const Color& color) const
	{
		asPolygon().paint(dst, color);

		return *this;
	}

	const RoundRect& RoundRect::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		asPolygon().overwrite(dst, color, antialiased);

		return *this;
	}

	const RoundRect& RoundRect::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		LineString(detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5, none)).paintClosed(dst, (outerThickness + innerThickness), color);

		return *this;
	}

	const RoundRect& RoundRect::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color, const Antialiased antialiased) const
	{
		LineString(detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5, none)).overwriteClosed(dst, (outerThickness + innerThickness), color, antialiased);

		return *this;
	}

	const RoundRect& RoundRect::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addRoundRect(
			FloatRect{ x, y, (x + w), (y + h) },
			static_cast<float>(w),
			static_cast<float>(h),
			static_cast<float>(r),
			color.toFloat4()
		);

		return *this;
	}

	const RoundRect& RoundRect::draw(const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		const Float4 color0 = topColor->toFloat4();
		const Float4 color1 = bottomColor->toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRoundRect(FloatRect{ x, y, (x + w), (y + h) },
			static_cast<float>(w),
			static_cast<float>(h),
			static_cast<float>(r),
			color0, color1);

		return *this;
	}

	const RoundRect& RoundRect::drawFrame(const double thickness, const ColorF& color) const
	{
		return drawFrame((thickness * 0.5), (thickness * 0.5), color);
	}

	const RoundRect& RoundRect::drawFrame(const double thickness, const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return drawFrame((thickness * 0.5), (thickness * 0.5), topColor, bottomColor);
	}

	const RoundRect& RoundRect::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		if ((rect.w <= 0.0) || (rect.h <= 0.0)
			|| (innerThickness < 0.0) || (outerThickness < 0.0)
			|| ((innerThickness == 0.0) && (outerThickness == 0.0)))
		{
			return *this;
		}

		if (r <= 0.0)
		{
			rect.drawFrame(innerThickness, outerThickness, color);
			return *this;
		}

		const RectF outerRect = rect.stretched(outerThickness);
		const RoundRect outerRoundRect{ outerRect, Min((r + outerThickness), (Min(outerRect.w, outerRect.h) * 0.5)) };
		const RectF innerRect = rect.stretched(-innerThickness);

		if ((innerRect.w <= 0.0) || (innerRect.h <= 0.0))
		{
			outerRoundRect.draw(color);
			return *this;
		}

		const RoundRect innerRoundRect{ innerRect, Clamp((r - innerThickness), 0.0, (Min(innerRect.w, innerRect.h) * 0.5)) };

		SIV3D_ENGINE(Renderer2D)->addRoundRectFrame(
			outerRoundRect,
			innerRoundRect,
			color.toFloat4()
		);

		return *this;
	}

	const RoundRect& RoundRect::drawFrame(const double innerThickness, const double outerThickness, const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		if ((rect.w <= 0.0) || (rect.h <= 0.0)
			|| (innerThickness < 0.0) || (outerThickness < 0.0)
			|| ((innerThickness == 0.0) && (outerThickness == 0.0)))
		{
			return *this;
		}

		if (r <= 0.0)
		{
			rect.drawFrame(innerThickness, outerThickness, topColor, bottomColor);
			return *this;
		}

		const RectF outerRect = rect.stretched(outerThickness);
		const RoundRect outerRoundRect{ outerRect, Min((r + outerThickness), (Min(outerRect.w, outerRect.h) * 0.5)) };
		const RectF innerRect = rect.stretched(-innerThickness);

		if ((innerRect.w <= 0.0) || (innerRect.h <= 0.0))
		{
			outerRoundRect.draw(topColor, bottomColor);
			return *this;
		}

		const RoundRect innerRoundRect{ innerRect, Clamp((r - innerThickness), 0.0, (Min(innerRect.w, innerRect.h) * 0.5)) };

		SIV3D_ENGINE(Renderer2D)->addRoundRectFrame(
			outerRoundRect,
			innerRoundRect,
			topColor->toFloat4(),
			bottomColor->toFloat4()
		);

		return *this;
	}

	const RoundRect& RoundRect::drawShadow(const Vec2& offset, double blur, const double spread, const ColorF& color, const bool fill) const
	{
		// ブラー半径が 0 未満なら描画しない
		if (blur < 0.0)
		{
			return *this;
		}

		// 角丸でなければ長方形へ
		if (r == 0.0)
		{
			rect.drawShadow(offset, blur, spread, color);
			return *this;
		}

		RoundRect baseRoundRect = movedBy(offset).stretched(spread);
		baseRoundRect.r += spread;
		baseRoundRect.r = Min(baseRoundRect.r, (baseRoundRect.rect.size.minComponent() * 0.5));
		const double blurClamped = Min({ baseRoundRect.w, baseRoundRect.h, blur });

		SIV3D_ENGINE(Renderer2D)->addRoundRectShadow(baseRoundRect, static_cast<float>(blurClamped), color.toFloat4(), fill);

		return *this;
	}

	TexturedRoundRect RoundRect::operator ()(const Texture& texture) const
	{
		return{ texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this };
	}

	TexturedRoundRect RoundRect::operator ()(const TextureRegion& textureRegion) const
	{
		return{ textureRegion.texture,
			textureRegion.uvRect,
			*this };
	}

	void Formatter(FormatData& formatData, const RoundRect& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.w, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.h, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.r, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}
}
