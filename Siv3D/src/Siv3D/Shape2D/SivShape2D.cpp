//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Shape2D.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/MathConstants.hpp>
# include "../Siv3DEngine.hpp"
//# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	Shape2D::Shape2D(const uint32 vSize, const uint32 iSize)
		: m_vertices(vSize)
		, m_indices(iSize)
	{
	
	}

	Shape2D::Shape2D(const uint32 vSize, const uint32 iSize, const Float2& offset, const uint32 baseIndex)
		: m_vertices(vSize, offset)
		, m_indices(iSize, baseIndex)
	{

	}

	Shape2D Shape2D::Cross(const double r, const double width, const Vec2& center, const double angle)
	{
		return Plus(r, width, center, angle + Math::QuarterPi);
	}

	Shape2D Shape2D::Plus(const double r, const double width, const Vec2& center, const double angle)
	{
		Shape2D shape(12, 18, center, 0);

		const float w = static_cast<float>(width) * 0.5f;
		const float af = static_cast<float>(angle);
		const Float2 n = Float2(w, w).rotate(af), a = Float2(r, w).rotate(af), b = Float2(w, r).rotate(af);
		
		Float2* pPos = shape.m_vertices.data();
		(pPos++)->moveBy(a.x, a.y);
		(pPos++)->moveBy(n.x, n.y);
		(pPos++)->moveBy(b.x, b.y);
		(pPos++)->moveBy(-a.y, a.x);
		(pPos++)->moveBy(-n.y, n.x);
		(pPos++)->moveBy(-b.y, b.x);
		(pPos++)->moveBy(-a.x, -a.y);
		(pPos++)->moveBy(-n.x, -n.y);
		(pPos++)->moveBy(-b.x, -b.y);
		(pPos++)->moveBy(a.y, -a.x);
		(pPos++)->moveBy(n.y, -n.x);
		(pPos++)->moveBy(b.y, -b.x);

		shape.m_indices = { 6, 11, 5, 5, 11, 0, 8, 9, 7, 7, 9, 10, 4, 1, 3, 3, 1, 2 };

		return shape;
	}

	Shape2D Shape2D::Ngon(const uint32 n, const double r, const Vec2& center, const double angle)
	{
		if (n < 3)
		{
			return Shape2D();
		}

		Shape2D shape(n, 3 * (n - 2), center, 0);

		const Float2 offset(center);
		Float2* pPos = shape.m_vertices.data();

		for (uint32 i = 0; i < n; ++i)
		{
			*pPos++ += Circular(r, angle + i * (Math::TwoPi / n)).toFloat2();
		}

		uint32* pIndex = shape.m_indices.data();

		for (uint32 i = 0; i < n - 2; ++i)
		{
			++pIndex;
			(*pIndex++) = i + 1;
			(*pIndex++) = i + 2;
		}

		return shape;
	}

	Shape2D Shape2D::Star(const double r, const Vec2& center, const double angle)
	{
		const double innerScale = 0.38196601125010515; // 2 / (3 + sqrt(5)) 

		return NStar(5, r, r * innerScale, center, angle);
	}

	Shape2D Shape2D::NStar(const uint32 n, const double rOuter, const double rInner, const Vec2& center, const double angle)
	{
		if (n < 2)
		{
			return Shape2D();
		}

		Shape2D shape(n * 2, n * 3 + (n - 2) * 3, center, 1);
		Float2* pPos = shape.m_vertices.data();

		for (uint32 i = 0; i < n * 2; ++i)
		{
			(*pPos++) += Circular(i % 2 ? rInner : rOuter, angle + i * (Math::Pi / n)).toFloat2();
		}

		uint32* pIndex = shape.m_indices.data();

		for (uint32 i = 0; i < n; ++i)
		{
			(*pIndex++) = i * 2 + 1;
			(*pIndex++) = (i * 2 + 2) % (n * 2);
			(*pIndex++) = (i * 2 + 3) % (n * 2);
		}

		for (uint32 i = 0; i < n - 2; ++i)
		{
			++pIndex;
			(*pIndex++) = i * 2 + 3;
			(*pIndex++) = i * 2 + 5;
		}

		return shape;
	}

	Shape2D Shape2D::Arrow(const Vec2& from, const Vec2& to, const double width, const Vec2& headSize)
	{
		const double length = to.distanceFrom(from);

		if (length == 0.0f || width <= 0.0 || headSize.x <= 0.0 || headSize.y <= 0.0)
		{
			return Shape2D();
		}

		const double clampedRatio = std::min(headSize.y, length) / headSize.y;
		const Float2 direction = (to - from) / length;
		const Float2 normalDirection{ direction.y, -direction.x };
		const Float2 leftOffset = normalDirection * static_cast<float>(width) * 0.5f;
		const Float2 clampedHeadSize = clampedRatio * headSize;
		const Float2 gutterOffset = direction * clampedHeadSize.y;
		const Float2 edgeOffset = normalDirection * clampedHeadSize.x * 0.5f;

		Shape2D shape(7, 9, to, 0);

		shape.m_vertices[0] = from + leftOffset;
		shape.m_vertices[1] += leftOffset - gutterOffset;
		shape.m_vertices[2] += leftOffset - gutterOffset + edgeOffset;
		shape.m_vertices[4] += -leftOffset - gutterOffset - edgeOffset;
		shape.m_vertices[5] += -leftOffset - gutterOffset;
		shape.m_vertices[6] = from - leftOffset;

		shape.m_indices = { 1, 5, 0, 0, 5, 6, 3, 4, 2 };

		return shape;
	}

	Shape2D Shape2D::Rhombus(const double w, const double h, const Vec2& center, const double angle)
	{
		Shape2D shape(4, 6, center, 0);

		const float halfW = static_cast<float>(w) * 0.5f;
		const float halfH = static_cast<float>(h) * 0.5f;
		const float angleF = static_cast<float>(angle);
		const float s = std::sin(angleF);
		const float c = std::cos(angleF);

		Float2* pPos = shape.m_vertices.data();
		(pPos++)->moveBy(halfH * s, -halfH * c);
		(pPos++)->moveBy(halfW * c, halfW * s);
		(pPos++)->moveBy(-halfH * s, halfH * c);
		(pPos++)->moveBy(-halfW * c, -halfW * s);

		shape.m_indices = { 0, 1, 3, 2, 3, 1 };

		return shape;
	}

	Shape2D Shape2D::RectBalloon(const RectF& rect, const Vec2& target, const double _pointingRootRatio)
	{
		const Float2 center = rect.center();

		Shape2D shape(7, 9, center, 0);
		const float h = static_cast<float>(rect.h);
		const float w = static_cast<float>(rect.w);
		const float prf = static_cast<float>(_pointingRootRatio);

		constexpr std::array<int32, 2> sign{ 1, -1 };
		const float firstAngle = std::atan2(h, w);
		const Float2 direction = target - center;
		const float flagAngle = std::fmod(std::atan2(direction.y, direction.x) + Math::TwoPiF, Math::TwoPiF);
		const float remainderAngle = std::fmod(flagAngle + Math::HalfPiF, Math::HalfPiF);
		const int32 dividedAngleIndex = static_cast<int32>(flagAngle / Math::HalfPiF);
		const int32 a = ((dividedAngleIndex % 2 == 0) ? (remainderAngle > firstAngle) : (remainderAngle > Math::HalfPiF - firstAngle)) + dividedAngleIndex * 2;
		const Float2 pointingRootCenter(sign[((a + 2) / 4) % 2] * w * 0.25f * (1.0f + ((a + 3) / 2) % 2), sign[((a) / 4) % 2] * h * 0.25f * (1.0f + ((a + 1) / 2) % 2));
		const Float2 offset = sign[(((a + 3) % 8) / 4) % 2] * ((((a + 1) / 2) % 2) ? Float2(w * 0.25f * prf, 0.0f) : Float2(0.0f, h * 0.25f * prf));
		const uint32 indexOffset = ((a + 1) / 2) % 4;

		shape.m_vertices[0 + indexOffset] += pointingRootCenter - offset;
		shape.m_vertices[1 + indexOffset] = target;
		shape.m_vertices[2 + indexOffset] += pointingRootCenter + offset;

		std::array<uint32, 4> rectIndices;
		uint32 i = 0;

		for (size_t rectIndex = 0; rectIndex < 4; ++rectIndex)
		{
			if (indexOffset == rectIndex)
			{
				i += 3;
			}

			rectIndices[rectIndex] = i;

			shape.m_vertices[i++] += Float2(sign[((rectIndex + 1) / 2) % 2] * w * 0.5f, sign[((rectIndex) / 2) % 2] * h * 0.5f);
		}

		uint32* pIndex = shape.m_indices.data();
		(*pIndex++) = 0 + indexOffset;
		(*pIndex++) = 1 + indexOffset;
		(*pIndex++) = 2 + indexOffset;
		(*pIndex++) = rectIndices[0];
		(*pIndex++) = rectIndices[1];
		(*pIndex++) = rectIndices[2];
		(*pIndex++) = rectIndices[0];
		(*pIndex++) = rectIndices[2];
		(*pIndex++) = rectIndices[3];

		return shape;
	}

	Shape2D Shape2D::Stairs(const Vec2& base, const double w, const double h, const int32 steps, const bool upStairs)
	{
		if (steps <= 0)
		{
			return Shape2D();
		}

		Shape2D shape(2 + 2 * steps, 3 * 2 * steps);

		const float offsetX = static_cast<float>(w / steps);
		const float offsetY = static_cast<float>(h / steps);

		shape.m_vertices[0] = base;
		shape.m_vertices[1] = base + Float2(upStairs ? -w : w, 0);

		for (int32 i = 0; i < steps; ++i)
		{
			const int32 offsetIndex = i + 1;

			shape.m_vertices[offsetIndex * 2] = shape.m_vertices[1] + Float2(upStairs ? offsetX * i : -offsetX * i, -offsetY * offsetIndex);
			shape.m_vertices[offsetIndex * 2 + 1] = shape.m_vertices[1] + Float2(upStairs ? offsetX * offsetIndex : -offsetX * offsetIndex, -offsetY * offsetIndex);

			shape.m_indices[6 * i] = 0;
			shape.m_indices[6 * i + 1] = 1 + 2 * i;
			shape.m_indices[6 * i + 2] = 2 + 2 * i;
			shape.m_indices[6 * i + 3] = 0;
			shape.m_indices[6 * i + 4] = 2 + 2 * i;
			shape.m_indices[6 * i + 5] = 3 + 2 * i;
		}

		return shape;
	}

	//Shape2D Shape2D::DoubleArrow(const Vec2& a, const Vec2& b, double width, const Vec2& headSize)
	//{
	//	return Shape2D();
	//}

	//const Shape2D& Shape2D::draw(const ColorF& color) const
	//{
	//	Siv3DEngine::GetRenderer2D()->addShape2D(m_vertices, m_indices, color.toFloat4());

	//	return *this;
	//}

	//const Shape2D& Shape2D::drawFrame(const double thickness, const ColorF& color) const
	//{
	//	Siv3DEngine::GetRenderer2D()->addShape2DFrame(m_vertices.data(), static_cast<uint32>(m_vertices.size()),
	//		static_cast<float>(thickness), color.toFloat4());

	//	return *this;
	//}
}
