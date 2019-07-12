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

		MultiPolygon(const MultiPolygon& polygons);

		MultiPolygon(MultiPolygon&& polygons);

		explicit MultiPolygon(const Array<Polygon>& polygons);

		explicit MultiPolygon(Array<Polygon>&& polygons);

		MultiPolygon& operator =(const Array<Polygon>& other);

		MultiPolygon& operator =(Array<Polygon>&& other) noexcept;

		MultiPolygon& operator =(const MultiPolygon& other);

		MultiPolygon& operator =(MultiPolygon&& other) noexcept;

		void assign(const MultiPolygon& other);

		void assign(MultiPolygon&& other) noexcept;

		MultiPolygon& operator <<(const Polygon& polygon);

		void swap(MultiPolygon& other) noexcept;

		MultiPolygon& append(const Array<Polygon>& other);

		MultiPolygon& append(const MultiPolygon& other);

		MultiPolygon& remove_at(size_t index);

		template <class Fty>
		MultiPolygon& remove_if(Fty f)
		{
			base_type::remove_if(f);

			return *this;
		}

		MultiPolygon& reverse();

		MultiPolygon& rotate(std::ptrdiff_t count = 1);

		MultiPolygon& shuffle();

		template <class URBG>
		MultiPolygon& shuffle(URBG&& rbg)
		{
			base_type::shuffle(std::forward<URBG>(rbg));

			return *this;
		}

		MultiPolygon slice(const size_t index) const;

		MultiPolygon slice(size_t index, size_t length) const;

		MultiPolygon& moveBy(double x, double y) noexcept;

		MultiPolygon& moveBy(const Vec2& v) noexcept;

		[[nodiscard]] MultiPolygon movedBy(double x, double y) const;

		[[nodiscard]] MultiPolygon movedBy(const Vec2& v) const;

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
	void Formatter(FormatData& formatData, const MultiPolygon& value);

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
