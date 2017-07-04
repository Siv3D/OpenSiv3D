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

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Array.hpp"
# include "Line.hpp"

namespace s3d
{
	class LineString : protected Array<Vec2>
	{
	private:

		using base_type = Array<Vec2>;

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
		using base_type::operator=;
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

		LineString() = default;

		LineString(const Array<Vec2>& points)
			: base_type(points)
		{

		}

		LineString(Array<Vec2>&& points)
			: base_type(std::move(points))
		{

		}

		LineString& operator <<(const Vec2& value)
		{
			base_type::push_back(value);

			return *this;
		}

		void swap(LineString& other)
		{
			base_type::swap(other);
		}

		LineString& append(const Array<Vec2>& other)
		{
			base_type::insert(end(), other.begin(), other.end());

			return *this;
		}

		LineString& append(const LineString& other)
		{
			base_type::insert(end(), other.begin(), other.end());

			return *this;
		}

		LineString& remove(const Vec2& value)
		{
			base_type::remove(value);

			return *this;
		}

		LineString& remove_at(const size_t index)
		{
			base_type::remove_at(index);

			return *this;
		}

		template <class Fty>
		LineString& remove_if(Fty f)
		{
			base_type::remove_if(f);

			return *this;
		}

		LineString& reverse()
		{
			base_type::reverse();

			return *this;
		}

		LineString& rotate(std::ptrdiff_t count = 1)
		{
			base_type::rotate(count);

			return *this;
		}

		LineString& shuffle()
		{
			base_type::shuffle();

			return *this;
		}

		template <class URBG>
		LineString& shuffle(URBG&& rbg)
		{
			base_type::shuffle(std::forward<URBG>(rbg));

			return *this;
		}

		LineString slice(const size_t index) const
		{
			return base_type::slice(index);
		}

		LineString slice(const size_t index, const size_t length) const
		{
			return base_type::slice(index, length);
		}

		size_t num_lines() const noexcept
		{
			return size() < 2 ? 0 : size() - 1;
		}

		Line line(size_t index) const
		{
			return{ base_type::operator[](index), base_type::operator[](index + 1) };
		}

		LineString& moveBy(double x, double y) noexcept
		{
			for (auto& point : *this)
			{
				point.moveBy(x, y);
			}

			return *this;
		}

		LineString& moveBy(const Vec2& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		LineString movedBy(double x, double y) const
		{
			return LineString(*this).moveBy(x, y);
		}

		LineString movedBy(const Vec2& v) const
		{
			return movedBy(v.x, v.y);
		}

		RectF calculateBoundingRect() const noexcept;

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}

		LineString catmullRom(bool isClosed = false, int32 interpolation = 24) const;

		// paint

		// overpaint

		const LineString& draw(const ColorF& color = Palette::White, bool isClosed = false) const
		{
			return draw(LineStyle::SquareCap, 1.0, color, isClosed);
		}

		const LineString& draw(double thickness, const ColorF& color = Palette::White, bool isClosed = false) const
		{
			return draw(LineStyle::SquareCap, thickness, color, isClosed);
		}

		const LineString& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White, bool isClosed = false) const;

		void drawCatmullRom(double thickness = 1.0, const ColorF& color = Palette::White, bool isClosed = false, int32 interpolation = 24) const
		{
			drawCatmullRom(LineStyle::SquareCap, thickness, color, isClosed, interpolation);
		}

		void drawCatmullRom(const LineStyle& style, double thickness = 1.0, const ColorF& color = Palette::White, bool isClosed = false, int32 interpolation = 24) const;


		// drawArray

		// asPolygon
	};
}

namespace std
{
	inline void swap(s3d::LineString& a, s3d::LineString& b)
	{
		a.swap(b);
	}
}


//////////////////////////////////////////////////////////////////////////////
//
//	Formatting LineString
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const LineString& value)
	{
		formatData.string.append(value.join(L",", L"(", L")"));
	}

	/// <summary>
	/// 出力ストリームに線を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="lines">
	/// 線
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const LineString& lines)
	{
		os << CharType('(');

		bool b = false;

		for (const auto& point : lines)
		{
			if (std::exchange(b, true))
			{
				os << CharType(',');
			}

			os << point;
		}

		return os << CharType(')');
	}
}
//
//////////////////////////////////////////////////////////////////////////////
