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

# include <Siv3D/Circle.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	Circle::Circle(const position_type& p0, const position_type& p1, const position_type& p2) noexcept
	{
		if (p0 == p1)
		{
			*this = Circle(p0, p2);
			return;
		}
		else if (p0 == p2 || p1 == p2)
		{
			*this = Circle(p0, p1);
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
		*this = Circle(cx, cy, p0.distanceFrom(cx, cy));
	}

	bool Circle::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Circle::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Circle::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Circle::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Circle::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Circle::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Circle::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Circle& Circle::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCircle(
			center,
			static_cast<float>(r),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCircleFrame(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		Siv3DEngine::GetRenderer2D()->addCircleFrame(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawPie(double startAngle, double angle, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCirclePie(
			center,
			static_cast<float>(r),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawArc(double startAngle, double angle, double innerThickness, double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCircleArc(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
		);

		return *this;
	}
}
