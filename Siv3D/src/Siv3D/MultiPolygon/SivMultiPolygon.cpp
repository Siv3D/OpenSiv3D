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

# include <Siv3D/MultiPolygon.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>

namespace s3d
{
	MultiPolygon::value_type& MultiPolygon::choice()
	{
		return choice(GetDefaultRNG());
	}

	const MultiPolygon::value_type& MultiPolygon::choice() const
	{
		return choice(GetDefaultRNG());
	}

	String MultiPolygon::join(const StringView sep, const StringView begin, const StringView end) const
	{
		return m_data.join(sep, begin, end);
	}

	MultiPolygon& MultiPolygon::append(const Array<value_type>& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	MultiPolygon& MultiPolygon::append(const MultiPolygon& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	MultiPolygon& MultiPolygon::remove_at(const size_t index)
	{
		m_data.remove_at(index);

		return *this;
	}

	MultiPolygon& MultiPolygon::reverse()
	{
		m_data.reverse();

		return *this;
	}

	MultiPolygon MultiPolygon::reversed() const&
	{
		return MultiPolygon(rbegin(), rend());
	}

	MultiPolygon MultiPolygon::reversed() &&
	{
		return std::move(reverse());
	}

	MultiPolygon& MultiPolygon::shuffle()
	{
		m_data.shuffle();

		return *this;
	}

	MultiPolygon MultiPolygon::slice(const size_t index) const
	{
		if (index >= size())
		{
			return{};
		}

		return MultiPolygon(begin() + index, end());
	}

	MultiPolygon MultiPolygon::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return{};
		}

		return MultiPolygon(begin() + index, begin() + Min(index + length, size()));
	}

	MultiPolygon MultiPolygon::movedBy(const double x, const double y) const&
	{
		MultiPolygon polygons{ *this };

		polygons.moveBy(x, y);

		return polygons;
	}

	MultiPolygon MultiPolygon::movedBy(const double x, const double y) && noexcept
	{
		return std::move(moveBy(x, y));
	}

	MultiPolygon MultiPolygon::movedBy(const Vec2 v) const&
	{
		return movedBy(v.x, v.y);
	}

	MultiPolygon MultiPolygon::movedBy(const Vec2 v) && noexcept
	{
		return std::move(moveBy(v));
	}

	MultiPolygon& MultiPolygon::moveBy(const double x, const double y) noexcept
	{
		for (auto& polygon : m_data)
		{
			polygon.moveBy(x, y);
		}

		return *this;
	}

	MultiPolygon& MultiPolygon::moveBy(const Vec2 v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	MultiPolygon MultiPolygon::rotated(const double angle) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.rotated(angle); }) };
	}

	MultiPolygon MultiPolygon::rotated(const double angle) &&
	{
		return std::move(rotate(angle));
	}

	MultiPolygon MultiPolygon::rotatedAt(const Vec2& pos, const double angle) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.rotatedAt(pos, angle); }) };
	}

	MultiPolygon MultiPolygon::rotatedAt(const Vec2& pos, const double angle) &&
	{
		return std::move(rotateAt(pos, angle));
	}

	MultiPolygon& MultiPolygon::rotate(const double angle)
	{
		for (auto& polygon : m_data)
		{
			polygon.rotate(angle);
		}

		return *this;
	}

	MultiPolygon& MultiPolygon::rotateAt(const Vec2& pos, const double angle)
	{
		for (auto& polygon : m_data)
		{
			polygon.rotateAt(pos, angle);
		}

		return *this;
	}

	MultiPolygon MultiPolygon::transformed(const double s, double c, const Vec2& pos) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.transformed(s, c, pos); }) };
	}

	MultiPolygon MultiPolygon::transformed(const double s, double c, const Vec2& pos) &&
	{
		return std::move(transform(s, c, pos));
	}

	MultiPolygon& MultiPolygon::transform(const double s, const double c, const Vec2& pos)
	{
		for (auto& polygon : m_data)
		{
			polygon.transform(s, c, pos);
		}

		return *this;
	}

	MultiPolygon MultiPolygon::scaled(const double s) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.scaled(s); }) };
	}

	MultiPolygon MultiPolygon::scaled(const double s) &&
	{
		return std::move(scale(s));
	}

	MultiPolygon MultiPolygon::scaled(const double sx, const double sy) const&
	{
		return scaled(Vec2{ sx, sy });
	}

	MultiPolygon MultiPolygon::scaled(const double sx, const double sy) &&
	{
		return std::move(scale(sx, sy));
	}

	MultiPolygon MultiPolygon::scaled(const Vec2 s) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.scaled(s); }) };
	}

	MultiPolygon MultiPolygon::scaled(const Vec2 s) &&
	{
		return std::move(scale(s));
	}

	MultiPolygon& MultiPolygon::scale(const double s)
	{
		for (auto& polygon : m_data)
		{
			polygon.scale(s);
		}

		return *this;
	}

	MultiPolygon& MultiPolygon::scale(const double sx, const double sy)
	{
		return scale(Vec2{ sx, sy });
	}

	MultiPolygon& MultiPolygon::scale(const Vec2 s)
	{
		for (auto& polygon : m_data)
		{
			polygon.scale(s);
		}

		return *this;
	}

	MultiPolygon MultiPolygon::scaledAt(const Vec2 pos, const double s) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.scaledAt(pos, s); }) };
	}

	MultiPolygon MultiPolygon::scaledAt(const Vec2 pos, const double s) &&
	{
		return std::move(scaleAt(pos, s));
	}

	MultiPolygon& MultiPolygon::scaleAt(const Vec2 pos, const double s)
	{
		for (auto& polygon : m_data)
		{
			polygon.scaleAt(pos, s);
		}

		return *this;
	}

	MultiPolygon MultiPolygon::scaledAt(const Vec2 pos, const double sx, const double sy) const&
	{
		return scaledAt(pos, Vec2{ sx, sy });
	}

	MultiPolygon MultiPolygon::scaledAt(const Vec2 pos, const double sx, const double sy) &&
	{
		return std::move(scaleAt(pos, sx, sy));
	}

	MultiPolygon MultiPolygon::scaledAt(const Vec2 pos, const Vec2 s) const&
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.scaledAt(pos, s); }) };
	}

	MultiPolygon MultiPolygon::scaledAt(const Vec2 pos, const Vec2 s) &&
	{
		return std::move(scaleAt(pos, s));
	}

	MultiPolygon& MultiPolygon::scaleAt(const Vec2 pos, const double sx, const double sy)
	{
		return scaleAt(pos, Vec2{ sx, sy });
	}

	MultiPolygon& MultiPolygon::scaleAt(const Vec2 pos, const Vec2 s)
	{
		for (auto& polygon : m_data)
		{
			polygon.scaleAt(pos, s);
		}

		return *this;
	}

	double MultiPolygon::area() const noexcept
	{
		double total = 0.0;
		
		for (const auto& polygon : m_data)
		{
			total += polygon.area();
		}
		
		return total;
	}

	double MultiPolygon::perimeter() const noexcept
	{
		double total = 0.0;
		
		for (const auto& polygon : m_data)
		{
			total += polygon.perimeter();
		}
		
		return total;
	}

	Vec2 MultiPolygon::centroid() const
	{
		if (m_data.empty())
		{
			return Vec2{ 0, 0 };
		}
		
		Vec2 weightedCoordsTotal{ 0, 0 };
		double areaTotal = 0.0;
		
		for (const auto& polygon : m_data)
		{
			const double polygonArea = polygon.area();
			weightedCoordsTotal += polygonArea * polygon.centroid();
			areaTotal += polygonArea;
		}
		
		return weightedCoordsTotal / areaTotal;
	}

	Polygon MultiPolygon::computeConvexHull() const
	{
		Array<Vec2> points;

		for (const auto& polygon : m_data)
		{
			points.append(polygon.outer());
		}

		return Geometry2D::ConvexHull(points);
	}

	RectF MultiPolygon::computeBoundingRect() const noexcept
	{
		if (isEmpty())
		{
			return RectF::Empty();
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

	MultiPolygon MultiPolygon::simplified(const double maxDistance) const
	{
		return MultiPolygon{ m_data.map([=](const Polygon& p) { return p.simplified(maxDistance); }) };
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
		for (const auto& polygon : m_data)
		{
			polygon.paint(dst, color);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::paint(Image& dst, const double x, const double y, const Color& color) const
	{
		const Vec2 pos{ x, y };

		for (const auto& polygon : m_data)
		{
			polygon.paint(dst, pos, color);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::paint(Image& dst, const Vec2& pos, const Color& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.paint(dst, pos, color);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.overwrite(dst, color, antialiased);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::overwrite(Image& dst, const double x, const double y, const Color& color, const Antialiased antialiased) const
	{
		const Vec2 pos{ x, y };

		for (const auto& polygon : m_data)
		{
			polygon.overwrite(dst, pos, color, antialiased);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::overwrite(Image& dst, const Vec2& pos, const Color& color, const Antialiased antialiased) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.overwrite(dst, pos, color, antialiased);
		}

		return *this;
	}

	const MultiPolygon& MultiPolygon::draw(const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.draw(color);
		}

		return *this;
	}

	void MultiPolygon::draw(const double x, const double y, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.draw(x, y, color);
		}
	}

	void MultiPolygon::draw(const Vec2& pos, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.draw(pos, color);
		}
	}

	const MultiPolygon& MultiPolygon::drawFrame(const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawFrame(thickness, color);
		}

		return *this;
	}

	void MultiPolygon::drawFrame(const double x, const double y, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawFrame(x, y, thickness, color);
		}
	}

	void MultiPolygon::drawFrame(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawFrame(pos, thickness, color);
		}
	}

	const MultiPolygon& MultiPolygon::drawWireframe(const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawWireframe(thickness, color);
		}

		return *this;
	}

	void MultiPolygon::drawWireframe(const double x, const double y, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawWireframe(x, y, thickness, color);
		}
	}

	void MultiPolygon::drawWireframe(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawWireframe(pos, thickness, color);
		}
	}

	void MultiPolygon::drawTransformed(const double angle, const Vec2& pos, const ColorF& color) const
	{
		const auto [s, c] = FastMath::SinCos(angle);

		for (const auto& polygon : m_data)
		{
			polygon.drawTransformed(s, c, pos, color);
		}
	}

	void MultiPolygon::drawTransformed(const double s, const double c, const Vec2& pos, const ColorF& color) const
	{
		for (const auto& polygon : m_data)
		{
			polygon.drawTransformed(s, c, pos, color);
		}
	}
}
