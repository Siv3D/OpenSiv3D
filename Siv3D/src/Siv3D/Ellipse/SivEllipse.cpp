//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Polygon.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

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
		Siv3DEngine::GetRenderer2D()->addEllipse(
			center,
			static_cast<float>(a),
			static_cast<float>(b),
			color.toFloat4()
		);

		return *this;
	}

	const Ellipse& Ellipse::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addEllipseFrame(
			center,
			static_cast<float>(a - innerThickness),
			static_cast<float>(b - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
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
		const double d = (Math::TwoPi / n);
		
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
		
		Array<uint32> indices(3 * (n - 2));
		uint32* pIndex = indices.data();

		for (uint32 i = 0; i < n - 2; ++i)
		{
			++pIndex;
			(*pIndex++) = i + 1;
			(*pIndex++) = i + 2;
		}

		return Polygon(vertices, indices, RectF(xMin, yMin, xMax - xMin, yMax - yMin));
	}
}
