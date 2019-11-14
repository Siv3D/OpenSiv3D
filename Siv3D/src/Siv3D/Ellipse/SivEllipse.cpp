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

# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	bool Ellipse::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Ellipse::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Ellipse::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Ellipse::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Ellipse::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Ellipse::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Ellipse::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Ellipse& Ellipse::draw(const ColorF& color) const
	{
		const Float4 colors = color.toFloat4();

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addEllipse(
			center,
			static_cast<float>(a),
			static_cast<float>(b),
			colors,
			colors
		);

		return *this;
	}

	const Ellipse& Ellipse::draw(const ColorF& innerColor, const ColorF& outerColor) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addEllipse(
			center,
			static_cast<float>(a),
			static_cast<float>(b),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Ellipse& Ellipse::drawFrame(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness * 0.5, thickness * 0.5, color);
	}

	const Ellipse& Ellipse::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		const Float4 colorF = color.toFloat4();

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addEllipseFrame(
			center,
			static_cast<float>(a - innerThickness),
			static_cast<float>(b - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			colorF,
			colorF
		);

		return *this;
	}

	Polygon Ellipse::asPolygon(const uint32 quality) const
	{
		const uint32 n = std::max(quality, 3u);
		
		Array<Vec2> vertices(n, center);
		Vec2* pPos = vertices.data();

		double xMin = center.x, xMax = center.x;
		const double yMin = center.y - b;
		double yMax = center.y;
		const double d = (Math::Constants::TwoPi / n);
		
		for (uint32 i = 0; i < n; ++i)
		{
			const double rad = i * d;
			pPos->moveBy(a * std::cos(rad), b * std::sin(rad));

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
		
		Array<uint16> indices(3 * (n - 2));
		uint16* pIndex = indices.data();

		for (uint16 i = 0; i < n - 2; ++i)
		{
			++pIndex;
			(*pIndex++) = i + 1;
			(*pIndex++) = i + 2;
		}

		return Polygon(vertices, indices, RectF(xMin, yMin, xMax - xMin, yMax - yMin));
	}

	void Formatter(FormatData& formatData, const Ellipse& value)
	{
		Formatter(formatData, Vec4(value.x, value.y, value.a, value.b));
	}
}
