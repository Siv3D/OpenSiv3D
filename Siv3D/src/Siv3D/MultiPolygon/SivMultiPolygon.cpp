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

# include <Siv3D/MultiPolygon.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>

namespace s3d
{
	RectF MultiPolygon::calculateBoundingRect() const noexcept
	{
		if (isEmpty())
		{
			return RectF{ 0 };
		}

		auto it				= begin();
		const auto itEnd	= end();

		RectF rect = it->boundingRect();
		double left		= rect.x;
		double top		= rect.y;
		double right	= (rect.x + rect.w);
		double bottom	= (rect.y + rect.h);

		++it;

		while (it != itEnd)
		{
			rect = it->boundingRect();

			if (rect.x < left)
			{
				left = rect.x;
			}

			if (right < (rect.x + rect.w))
			{
				right = (rect.x + rect.w);
			}

			if (rect.y < top)
			{
				top = rect.y;
			}

			if (bottom < (rect.y + rect.h))
			{
				bottom = (rect.y + rect.h);
			}

			++it;
		}

		return{ left, top, (right - left), (bottom - top) };
	}

	bool MultiPolygon::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool MultiPolygon::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool MultiPolygon::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool MultiPolygon::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool MultiPolygon::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool MultiPolygon::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool MultiPolygon::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const MultiPolygon& MultiPolygon::paint(Image& dst, const Color& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.paint(dst, color);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::paint(Image& dst, const double x, const double y, const Color& color) const
	{
		const Vec2 pos{ x, y };

		for (const auto& polygon : *this)
		{
			polygon.paint(dst, pos, color);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::paint(Image& dst, const Vec2& pos, const Color& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.paint(dst, pos, color);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		for (const auto& polygon : *this)
		{
			polygon.overwrite(dst, color, antialiased);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::overwrite(Image& dst, const double x, const double y, const Color& color, const Antialiased antialiased) const
	{
		const Vec2 pos{ x, y };

		for (const auto& polygon : *this)
		{
			polygon.overwrite(dst, pos, color, antialiased);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::overwrite(Image& dst, const Vec2& pos, const Color& color, const Antialiased antialiased) const
	{
		for (const auto& polygon : *this)
		{
			polygon.overwrite(dst, pos, color, antialiased);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::draw(const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.draw(color);
		}

		return *this;
	}

	void MultiPolygon::draw(const double x, const double y, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.draw(x, y, color);
		}
	}

	void MultiPolygon::draw(const Vec2& pos, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.draw(pos, color);
		}
	}

	const MultiPolygon& MultiPolygon::drawFrame(const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawFrame(thickness, color);
		}

		return *this;
	}

	void MultiPolygon::drawFrame(const double x, const double y, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawFrame(x, y, thickness, color);
		}
	}

	void MultiPolygon::drawFrame(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawFrame(pos, thickness, color);
		}
	}

	const MultiPolygon& MultiPolygon::drawWireframe(const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawWireframe(thickness, color);
		}

		return *this;
	}

	void MultiPolygon::drawWireframe(const double x, const double y, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawWireframe(x, y, thickness, color);
		}
	}

	void MultiPolygon::drawWireframe(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawWireframe(pos, thickness, color);
		}
	}

	void MultiPolygon::drawTransformed(const double angle, const Vec2& pos, const ColorF& color) const
	{
		const auto [s, c] = FastMath::SinCos(angle);

		for (const auto& polygon : *this)
		{
			polygon.drawTransformed(s, c, pos, color);
		}
	}

	void MultiPolygon::drawTransformed(const double s, const double c, const Vec2& pos, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawTransformed(s, c, pos, color);
		}
	}
}
