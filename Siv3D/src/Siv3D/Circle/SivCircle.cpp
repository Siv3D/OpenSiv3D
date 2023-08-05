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
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedCircle.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CalculateCirclePieQuality(const float size, const float angle)
		{
			const float rate = Min(Abs(angle) / (Math::TwoPiF) * 2.0f, 1.0f);

			Vertex2D::IndexType quality = 0;

			if (size <= 1.0f)
			{
				quality = 4;
			}
			else if (size <= 6.0f)
			{
				quality = 7;
			}
			else if (size <= 8.0f)
			{
				quality = 11;
			}
			else
			{
				quality = static_cast<Vertex2D::IndexType>(Min(size * 0.225f + 18.0f, 255.0f));
			}

			return static_cast<Vertex2D::IndexType>(Max(quality * rate, 3.0f));
		}
	}

	Circle::Circle(const position_type& p0, const position_type& p1, const position_type& p2) noexcept
	{
		if (p0 == p1)
		{
			*this = Circle{ p0, p2 };
			return;
		}
		else if ((p0 == p2) || (p1 == p2))
		{
			*this = Circle{ p0, p1 };
			return;
		}

		const double a02 = 2 * (p0.x - p2.x);
		const double b02 = 2 * (p0.y - p2.y);
		const double c02 = (p0.y * p0.y - p2.y * p2.y) + (p0.x * p0.x - p2.x * p2.x);
		const double a12 = 2 * (p1.x - p2.x);
		const double b12 = 2 * (p1.y - p2.y);
		const double c12 = (p1.y * p1.y - p2.y * p2.y) + (p1.x * p1.x - p2.x * p2.x);
		const double cy = (a02 * c12 - a12 * c02) / (a02 * b12 - a12 * b02);
		const double cx = std::abs(a02) < std::abs(a12) ? ((c12 - b12 * cy) / a12) : ((c02 - b02 * cy) / a02);
		*this = Circle{ cx, cy, p0.distanceFrom(cx, cy) };
	}

	Polygon Circle::asPolygon(const uint32 quality) const
	{
		if (r == 0.0)
		{
			return{};
		}

		const uint32 n = Max(quality, 3u);

		Array<Vec2> vertices(n, center);
		Vec2* pPos = vertices.data();

		const double d = (Math::TwoPi / n);

		for (uint32 i = 0; i < n; ++i)
		{
			*pPos += Circular{ r, i * d }.fastToVec2();
			++pPos;
		}

		const RectF boundingRect = Geometry2D::BoundingRect(vertices);

		Array<TriangleIndex> indices(n - 2);
		TriangleIndex* pIndex = indices.data();

		for (Vertex2D::IndexType i = 0; i < n - 2; ++i)
		{
			pIndex->i0 = 0;
			pIndex->i1 = (i + 1);
			pIndex->i2 = (i + 2);
			++pIndex;
		}

		return Polygon{ vertices, indices, boundingRect, SkipValidation::Yes };
	}

	Polygon Circle::pieAsPolygon(const double startAngle, const double _angle, const uint32 _quality) const
	{
		if ((r == 0.0) || (_angle == 0.0))
		{
			return{};
		}

		const uint32 n = Max(_quality, 3u);
		const float scaleFactor = (n / 24.0f);
		const float angle = Clamp(static_cast<float>(_angle), -Math::TwoPiF, Math::TwoPiF);
		const Vertex2D::IndexType quality = detail::CalculateCirclePieQuality(static_cast<float>(r) * scaleFactor, angle);
		const Vertex2D::IndexType vertexSize = (quality + 1);

		Array<Vec2> vertices(vertexSize, center);
		{
			// 周
			{
				const float start = (static_cast<float>(startAngle) + ((angle < 0.0f) ? angle : 0.0f));
				const float radDelta = (Abs(angle) / (quality - 1));
				Vec2* pDst = &vertices[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (start + (radDelta * i));
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->moveBy(r * s, -r * c);
				}
			}
		}

		const RectF boundingRect = Geometry2D::BoundingRect(vertices);

		Array<TriangleIndex> indices(vertexSize - 2);
		{
			TriangleIndex* pIndex = indices.data();

			for (Vertex2D::IndexType i = 0; i < indices.size(); ++i)
			{
				pIndex->i0 = 0;
				pIndex->i1 = (i + 1);
				pIndex->i2 = (i + 2);
				++pIndex;
			}
		}

		return Polygon{ vertices, indices, boundingRect, SkipValidation::Yes };
	}

	Polygon Circle::arcAsPolygon(const double startAngle, const double _angle, const double innerThickness, const double outerThickness, const uint32 _quality) const
	{
		if ((r == 0.0) || (_angle == 0.0))
		{
			return{};
		}

		const uint32 n = Max(_quality, 3u);
		const float scaleFactor = (n / 24.0f);
		const float angle = Clamp(static_cast<float>(_angle), -Math::TwoPiF, Math::TwoPiF);
		const Vertex2D::IndexType quality = detail::CalculateCirclePieQuality(static_cast<float>(r) * scaleFactor, angle);
		const Vertex2D::IndexType vertexSize = (quality * 2);

		const double thickness = (innerThickness + outerThickness);
		const double rInner = (r - innerThickness);
		const double rOuter = (rInner + thickness);

		Array<Vec2> vertices(vertexSize, center);
		{
			const float start = (static_cast<float>(startAngle) + ((angle < 0.0f) ? angle : 0.0f));
			const float radDelta = (Abs(angle) / (quality - 1));

			Vec2* pHead = vertices.data();
			Vec2* pTail = &vertices.back();

			for (uint32 i = 0; i < quality; ++i)
			{
				const float rad = (start + (radDelta * i));
				const auto [s, c] = FastMath::SinCos(rad);
				pHead->moveBy(rOuter * s, -rOuter * c);
				pTail->moveBy(rInner * s, -rInner * c);
				++pHead;
				--pTail;
			}
		}

		const RectF boundingRect = Geometry2D::BoundingRect(vertices);

		Array<TriangleIndex> indices((quality - 1) * 2);
		TriangleIndex* pIndex = indices.data();

		for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
		{
			pIndex->i0 = i;
			pIndex->i1 = (i + 1);
			pIndex->i2 = ((2 * quality - 1) - i);
			++pIndex;

			pIndex->i0 = ((2 * quality - 1) - i);
			pIndex->i1 = (i + 1);
			pIndex->i2 = ((2 * quality - 2) - i);
			++pIndex;
		}

		return Polygon{ vertices, indices, boundingRect, SkipValidation::Yes };
	}

	bool Circle::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool Circle::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool Circle::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool Circle::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool Circle::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool Circle::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool Circle::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Circle& Circle::draw(const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addCircle(
			center,
			static_cast<float>(r),
			color0,
			color0
		);

		return *this;
	}

	const Circle& Circle::draw(const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addCircle(
			center,
			static_cast<float>(r),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawFrame(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness * 0.5, thickness * 0.5, color);
	}

	const Circle& Circle::drawFrame(const double thickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		return drawFrame(thickness * 0.5, thickness * 0.5, innerColor, outerColor);
	}

	const Circle& Circle::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addCircleFrame(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color0,
			color0
		);

		return *this;
	}

	const Circle& Circle::drawFrame(const double innerThickness, const double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addCircleFrame(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawPie(const double startAngle, const double angle, const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addCirclePie(
			center,
			static_cast<float>(r),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			color0,
			color0
		);

		return *this;
	}

	const Circle& Circle::drawPie(const double startAngle, const double angle, const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addCirclePie(
			center,
			static_cast<float>(r),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawArc(const double startAngle, const double angle, const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addCircleArc(
			LineStyle::Default,
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			color0,
			color0
		);

		return *this;
	}

	const Circle& Circle::drawArc(const double startAngle, const double angle, const double innerThickness, const double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addCircleArc(
			LineStyle::Default,
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawArc(const LineStyle& style, const double startAngle, const double angle, const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addCircleArc(
			style,
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			color0,
			color0
		);

		return *this;
	}

	const Circle& Circle::drawArc(const LineStyle& style, const double startAngle, const double angle, const double innerThickness, const double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addCircleArc(
			style,
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawSegment(const double arcMidpointAngle, const double height, const ColorF& color) const
	{
		if ((height <= 0.0) || (r <= 0.0))
		{
			return *this;
		}

		if ((r * 2.0) <= height)
		{
			return draw(color);
		}

		const float arcAngleHalf = std::acos(1.0f - (static_cast<float>(height) / static_cast<float>(r)));

		SIV3D_ENGINE(Renderer2D)->addCircleSegment(
			center,
			static_cast<float>(r),
			static_cast<float>(arcMidpointAngle - arcAngleHalf),
			static_cast<float>(arcAngleHalf * 2.0f),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawSegmentFromAngles(const double startAngle, const double angle, const ColorF& color) const
	{
		// 面積が 0 の場合は描画しない
		if (angle == 0.0)
		{
			return *this;
		}

		// angle が 2π 以上の場合は円全体を描画する
		if (Math::TwoPi <= angle)
		{
			return draw(color);
		}

		SIV3D_ENGINE(Renderer2D)->addCircleSegment(
			center,
			static_cast<float>(r),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawShadow(const Vec2& offset, double blur, const double spread, const ColorF& color) const
	{
		// ブラー半径が 0 未満なら描画しない
		if (blur < 0.0)
		{
			return *this;
		}

		const Circle baseCircle{ (center + offset), (r + spread) };

		// 非ぼかし部分がない場合は直接描画へ
		if (((r + spread) * 2.0) <= blur)
		{
			SIV3D_ENGINE(Renderer2D)->addTexturedQuad(SIV3D_ENGINE(Renderer2D)->getBoxShadowTexture(),
				FloatQuad{ baseCircle.stretched(blur * 0.5).boundingRect().asQuad() }, FloatRect{ 0.0f, 0.0f, 1.0f, 1.0f }, color.toFloat4());
			return *this;
		}

		const double blurClamped = Min(blur, (baseCircle.r * 2.0));

		SIV3D_ENGINE(Renderer2D)->addCircleShadow(baseCircle, static_cast<float>(blurClamped), color.toFloat4());
		
		return *this;
	}

	TexturedCircle Circle::operator ()(const Texture& texture) const
	{
		return{ texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this };
	}

	TexturedCircle Circle::operator ()(const TextureRegion& textureRegion) const
	{
		return{ textureRegion.texture,
			textureRegion.uvRect,
			*this };
	}

	void Formatter(FormatData& formatData, const Circle& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.r, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}
}
