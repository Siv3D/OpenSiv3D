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

# include <Siv3D/MultiPolygon.hpp>

namespace s3d
{
	MultiPolygon::MultiPolygon(const MultiPolygon& polygons)
		: base_type(polygons.begin(), polygons.end())
	{

	}

	MultiPolygon::MultiPolygon(MultiPolygon&& polygons)
		: base_type(std::move(polygons))
	{

	}

	MultiPolygon::MultiPolygon(const Array<Polygon>& polygons)
		: base_type(polygons.begin(), polygons.end())
	{

	}

	MultiPolygon::MultiPolygon(Array<Polygon>&& polygons)
		: base_type(std::move(polygons))
	{

	}

	MultiPolygon& MultiPolygon::operator =(const Array<Polygon>& other)
	{
		base_type::operator=(other);

		return *this;
	}

	MultiPolygon& MultiPolygon::operator =(Array<Polygon>&& other) noexcept
	{
		base_type::operator=(std::move(other));

		return *this;
	}

	MultiPolygon& MultiPolygon::operator =(const MultiPolygon& other)
	{
		base_type::operator=(other);

		return *this;
	}

	MultiPolygon& MultiPolygon::operator =(MultiPolygon&& other) noexcept
	{
		base_type::operator=(std::move(other));

		return *this;
	}

	void MultiPolygon::assign(const MultiPolygon& other)
	{
		base_type::operator=(other);
	}

	void MultiPolygon::assign(MultiPolygon&& other) noexcept
	{
		base_type::operator=(std::move(other));
	}

	MultiPolygon& MultiPolygon::operator <<(const Polygon& polygon)
	{
		base_type::push_back(polygon);

		return *this;
	}

	void MultiPolygon::swap(MultiPolygon& other) noexcept
	{
		base_type::swap(other);
	}

	MultiPolygon& MultiPolygon::append(const Array<Polygon>& other)
	{
		base_type::insert(end(), other.begin(), other.end());

		return *this;
	}

	MultiPolygon& MultiPolygon::append(const MultiPolygon& other)
	{
		base_type::insert(end(), other.begin(), other.end());

		return *this;
	}

	MultiPolygon& MultiPolygon::remove_at(const size_t index)
	{
		base_type::remove_at(index);

		return *this;
	}

	MultiPolygon& MultiPolygon::reverse()
	{
		base_type::reverse();

		return *this;
	}

	MultiPolygon& MultiPolygon::rotate(const std::ptrdiff_t count)
	{
		base_type::rotate(count);

		return *this;
	}

	MultiPolygon& MultiPolygon::shuffle()
	{
		base_type::shuffle();

		return *this;
	}

	MultiPolygon MultiPolygon::slice(const size_t index) const
	{
		return MultiPolygon(base_type::slice(index));
	}

	MultiPolygon MultiPolygon::slice(const size_t index, const size_t length) const
	{
		return MultiPolygon(base_type::slice(index, length));
	}

	MultiPolygon& MultiPolygon::moveBy(const double x, const double y) noexcept
	{
		for (auto& polygon : *this)
		{
			polygon.moveBy(x, y);
		}

		return *this;
	}

	MultiPolygon& MultiPolygon::moveBy(const Vec2& v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	MultiPolygon MultiPolygon::movedBy(const double x, const double y) const
	{
		return MultiPolygon(*this).moveBy(x, y);
	}

	MultiPolygon MultiPolygon::movedBy(const Vec2& v) const
	{
		return movedBy(v.x, v.y);
	}

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

	void Formatter(FormatData& formatData, const MultiPolygon& value)
	{
		formatData.string.append(value.join(U", "_sv, U"("_sv, U")"_sv));
	}
}
