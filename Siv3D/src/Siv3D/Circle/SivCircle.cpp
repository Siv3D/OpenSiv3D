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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
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

		double xMin = center.x;
		double xMax = center.x;
		const double yMin = (center.y - r);
		double yMax = center.y;
		const double d = (Math::TwoPi / n);

		for (uint32 i = 0; i < n; ++i)
		{
			*pPos += Circular{ r, i * d }.fastToVec2();

			if (pPos->x < xMin)
			{
				xMin = pPos->x;
			}
			else if (xMax < pPos->x)
			{
				xMax = pPos->x;
			}

			if (yMax < pPos->y)
			{
				yMax = pPos->y;
			}

			++pPos;
		}

		Array<TriangleIndex> indices(n - 2);
		TriangleIndex* pIndex = indices.data();

		for (Vertex2D::IndexType i = 0; i < n - 2; ++i)
		{
			pIndex->i0 = 0;
			pIndex->i1 = (i + 1);
			pIndex->i2 = (i + 2);
			++pIndex;
		}

		return Polygon{ vertices, indices, RectF{ xMin, yMin, (xMax - xMin), (yMax - yMin) }, SkipValidation::Yes };
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

	void Circle::_Formatter(FormatData& formatData, const Circle& value)
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
