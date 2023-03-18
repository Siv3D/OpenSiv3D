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
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Polygon Ellipse::asPolygon(const uint32 quality) const
	{
		if ((a == 0.0) || (b == 0.0))
		{
			return{};
		}

		const uint32 n = Max(quality, 3u);

		Array<Vec2> vertices(n, center);
		Vec2* pPos = vertices.data();

		double xMin = center.x;
		double xMax = center.x;
		const double yMin = (center.y - b);
		double yMax = center.y;
		const double d = (Math::TwoPi / n);

		for (uint32 i = 0; i < n; ++i)
		{
			const double rad = (i * d);
			const auto [s, c] = FastMath::SinCos(rad);
			pPos->moveBy(a * c, b * s);

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

	bool Ellipse::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool Ellipse::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool Ellipse::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool Ellipse::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool Ellipse::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool Ellipse::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool Ellipse::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Ellipse& Ellipse::draw(const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addEllipse(
			center,
			static_cast<float>(a),
			static_cast<float>(b),
			color0,
			color0
		);

		return *this;
	}

	const Ellipse& Ellipse::draw(const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addEllipse(
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
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addEllipseFrame(
			center,
			static_cast<float>(a - innerThickness),
			static_cast<float>(b - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color0,
			color0
		);

		return *this;
	}

	void Formatter(FormatData& formatData, const Ellipse& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.a, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.b, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}
}
