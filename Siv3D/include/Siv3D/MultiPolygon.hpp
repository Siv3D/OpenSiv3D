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

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "Polygon.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	class MultiPolygon : protected Array<Polygon>
	{
	private:

		using base_type = Array<Polygon>;

	public:

		using typename base_type::value_type;
		using typename base_type::pointer;
		using typename base_type::const_pointer;
		using typename base_type::reference;
		using typename base_type::const_reference;
		using typename base_type::iterator;
		using typename base_type::const_iterator;
		using typename base_type::reverse_iterator;
		using typename base_type::const_reverse_iterator;
		using typename base_type::size_type;
		using typename base_type::difference_type;
		using typename base_type::allocator_type;

		using base_type::Array;
		using base_type::assign;
		using base_type::get_allocator;
		using base_type::at;
		using base_type::operator[];
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::crend;
		using base_type::empty;
		using base_type::size;
		using base_type::max_size;
		using base_type::reserve;
		using base_type::capacity;
		using base_type::shrink_to_fit;
		using base_type::clear;
		using base_type::insert;
		using base_type::emplace;
		using base_type::erase;
		using base_type::push_back;
		using base_type::emplace_back;
		using base_type::pop_back;
		using base_type::resize;

		using base_type::count;
		using base_type::count_if;
		using base_type::isEmpty;
		using base_type::operator bool;
		using base_type::release;
		using base_type::size_bytes;
		using base_type::push_front;
		using base_type::pop_front;
		using base_type::choice;
		using base_type::fill;
		using base_type::join;
		using base_type::remove;

		MultiPolygon() = default;

		MultiPolygon(const MultiPolygon& polygons)
			: base_type(polygons.begin(), polygons.end())
		{

		}

		MultiPolygon(MultiPolygon&& polygons)
			: base_type(std::move(polygons))
		{

		}

		explicit MultiPolygon(const Array<Polygon>& polygons)
			: base_type(polygons.begin(), polygons.end())
		{

		}

		explicit MultiPolygon(Array<Polygon>&& polygons)
			: base_type(std::move(polygons))
		{

		}

		MultiPolygon& operator =(const Array<Polygon>& other)
		{
			base_type::operator=(other);

			return *this;
		}

		MultiPolygon& operator =(Array<Polygon>&& other) noexcept
		{
			base_type::operator=(std::move(other));

			return *this;
		}

		MultiPolygon& operator =(const MultiPolygon& other)
		{
			base_type::operator=(other);

			return *this;
		}

		MultiPolygon& operator =(MultiPolygon&& other) noexcept
		{
			base_type::operator=(std::move(other));

			return *this;
		}

		void assign(const MultiPolygon& other)
		{
			base_type::operator=(other);
		}

		void assign(MultiPolygon&& other) noexcept
		{
			base_type::operator=(std::move(other));
		}

		MultiPolygon& operator <<(const Polygon& polygon)
		{
			base_type::push_back(polygon);

			return *this;
		}

		void swap(MultiPolygon& other) noexcept
		{
			base_type::swap(other);
		}

		MultiPolygon& append(const Array<Polygon>& other)
		{
			base_type::insert(end(), other.begin(), other.end());

			return *this;
		}

		MultiPolygon& append(const MultiPolygon& other)
		{
			base_type::insert(end(), other.begin(), other.end());

			return *this;
		}

		MultiPolygon& remove_at(const size_t index)
		{
			base_type::remove_at(index);

			return *this;
		}

		template <class Fty>
		MultiPolygon& remove_if(Fty f)
		{
			base_type::remove_if(f);

			return *this;
		}

		MultiPolygon& reverse()
		{
			base_type::reverse();

			return *this;
		}

		MultiPolygon& rotate(std::ptrdiff_t count = 1)
		{
			base_type::rotate(count);

			return *this;
		}

		MultiPolygon& shuffle()
		{
			base_type::shuffle();

			return *this;
		}

		template <class URBG>
		MultiPolygon& shuffle(URBG&& rbg)
		{
			base_type::shuffle(std::forward<URBG>(rbg));

			return *this;
		}

		MultiPolygon slice(const size_t index) const
		{
			return MultiPolygon(base_type::slice(index));
		}

		MultiPolygon slice(const size_t index, const size_t length) const
		{
			return MultiPolygon(base_type::slice(index, length));
		}

		MultiPolygon& moveBy(double x, double y) noexcept
		{
			for (auto& polygon : *this)
			{
				polygon.moveBy(x, y);
			}

			return *this;
		}

		MultiPolygon& moveBy(const Vec2& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		[[nodiscard]] MultiPolygon movedBy(double x, double y) const
		{
			return MultiPolygon(*this).moveBy(x, y);
		}

		[[nodiscard]] MultiPolygon movedBy(const Vec2& v) const
		{
			return movedBy(v.x, v.y);
		}

		[[nodiscard]] MultiPolygon rotated(double angle) const;

		[[nodiscard]] MultiPolygon rotatedAt(const Vec2& pos, double angle) const;

		MultiPolygon& rotate(double angle);

		MultiPolygon& rotateAt(const Vec2& pos, double angle);

		[[nodiscard]] MultiPolygon transformed(double s, double c, const Vec2& pos) const;

		MultiPolygon& transform(double s, double c, const Vec2& pos);

		[[nodiscard]] MultiPolygon scaled(double s) const;

		MultiPolygon& scale(double s);

		[[nodiscard]] RectF calculateBoundingRect() const noexcept;

		[[nodiscard]] MultiPolygon simplified(double maxDistance = 2.0) const;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		[[nodiscard]] bool contains(const Shape2DType& shape) const
		{
			return Geometry2D::Contains(*this, shape);
		}

		[[nodiscard]] bool leftClicked() const;

		[[nodiscard]] bool leftPressed() const;

		[[nodiscard]] bool leftReleased() const;

		[[nodiscard]] bool rightClicked() const;

		[[nodiscard]] bool rightPressed() const;

		[[nodiscard]] bool rightReleased() const;

		[[nodiscard]] bool mouseOver() const;

		const MultiPolygon& draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, const ColorF& color = Palette::White) const;

		void draw(const Vec2& pos, const ColorF& color = Palette::White) const;

		const MultiPolygon& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		const MultiPolygon& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color = Palette::White) const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	inline void Formatter(FormatData& formatData, const MultiPolygon& value)
	{
		formatData.string.append(value.join(U",", U"(", U")"));
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const MultiPolygon& value)
	{
		output << CharType('(');

		bool b = false;

		for (const auto& polygon : value)
		{
			if (std::exchange(b, true))
			{
				output << CharType(',');
			}

			output << polygon;
		}

		return output << CharType(')');
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{

}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	inline void swap(s3d::MultiPolygon& a, s3d::MultiPolygon& b) noexcept
	{
		a.swap(b);
	}
}
