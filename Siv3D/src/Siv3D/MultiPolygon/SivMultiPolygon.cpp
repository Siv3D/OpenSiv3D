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

# include <Siv3D/MultiPolygon.hpp>

namespace s3d
{
	MultiPolygon MultiPolygon::rotated(const double angle) const
	{
		return MultiPolygon(map([=](const Polygon& p) { return p.rotated(angle); }));
	}

	MultiPolygon MultiPolygon::rotatedAt(const Vec2& pos, const double angle) const
	{
		return MultiPolygon(map([=](const Polygon& p) { return p.rotatedAt(pos, angle); }));
	}

	MultiPolygon& MultiPolygon::rotate(const double angle)
	{
		for (auto& polygon : *this)
		{
			polygon.rotate(angle);
		}

		return *this;
	}

	MultiPolygon& MultiPolygon::rotateAt(const Vec2& pos, const double angle)
	{
		for (auto& polygon : *this)
		{
			polygon.rotateAt(pos, angle);
		}

		return *this;
	}

	MultiPolygon MultiPolygon::transformed(const double s, double c, const Vec2& pos) const
	{
		return MultiPolygon(map([=](const Polygon& p) { return p.transformed(s, c, pos); }));
	}

	MultiPolygon& MultiPolygon::transform(const double s, const double c, const Vec2& pos)
	{
		for (auto& polygon : *this)
		{
			polygon.transform(s, c, pos);
		}

		return *this;
	}

	MultiPolygon MultiPolygon::scaled(const double s) const
	{
		return MultiPolygon(map([=](const Polygon& p) { return p.scaled(s); }));
	}

	MultiPolygon& MultiPolygon::scale(const double s)
	{
		for (auto& polygon : *this)
		{
			polygon.scale(s);
		}

		return *this;
	}

	RectF MultiPolygon::calculateBoundingRect() const noexcept
	{
		if (isEmpty())
		{
			return RectF(0);
		}

		auto it = begin();
		const auto itEnd = end();

		const RectF rect = it->boundingRect();
		double left		= rect.x;
		double top		= rect.y;
		double right	= rect.x + rect.w;
		double bottom	= rect.y + rect.h;

		++it;

		while (it != itEnd)
		{
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

		return RectF(left, top, right - left, bottom - top);
	}

	MultiPolygon MultiPolygon::simplified(const double maxDistance) const
	{
		return MultiPolygon(map([=](const Polygon& p) { return p.simplified(maxDistance); }));
	}

	bool MultiPolygon::leftClicked() const
	{
		return any([](const Polygon& p) { return p.leftClicked(); });
	}

	bool MultiPolygon::leftPressed() const
	{
		return any([](const Polygon& p) { return p.leftPressed(); });
	}

	bool MultiPolygon::leftReleased() const
	{
		return any([](const Polygon& p) { return p.leftReleased(); });
	}

	bool MultiPolygon::rightClicked() const
	{
		return any([](const Polygon& p) { return p.rightClicked(); });
	}

	bool MultiPolygon::rightPressed() const
	{
		return any([](const Polygon& p) { return p.rightPressed(); });
	}

	bool MultiPolygon::rightReleased() const
	{
		return any([](const Polygon& p) { return p.rightReleased(); });
	}

	bool MultiPolygon::mouseOver() const
	{
		return any([](const Polygon& p) { return p.mouseOver(); });
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

	void MultiPolygon::drawTransformed(const double s, const double c, const Vec2& pos, const ColorF& color) const
	{
		for (const auto& polygon : *this)
		{
			polygon.drawTransformed(s, c, pos, color);
		}
	}
}
