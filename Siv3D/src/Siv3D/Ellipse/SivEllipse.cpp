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

# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
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
}
