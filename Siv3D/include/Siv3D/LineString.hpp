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
# include "PointVector.hpp"
# include "Array.hpp"
# include "Line.hpp"

namespace s3d
{
	class LineString : protected Array<Vec2>
	{
	private:

		using base_type = Array<Vec2>;

		[[nodiscard]] LineString _catmullRom(int32 interpolation, bool isClosed) const;

		[[nodiscard]] Polygon _calculateBuffer(double distance, int32 quality, bool isClosed) const;

		const LineString& _paint(Image& dst, int32 thickness, const Color& color, bool isClosed) const;

		const LineString& _overwrite(Image& dst, int32 thickness, const Color& color, bool antialiased, bool isClosed) const;

		const LineString& _draw(const LineStyle& style, double thickness, const ColorF& color, bool isClosed) const;

		void _drawCatmullRom(const LineStyle& style, double thickness, const ColorF& color, int32 interpolation, bool isClosed) const;

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

		LineString() = default;

		LineString(const LineString& lines)
			: base_type(lines.begin(), lines.end())
		{

		}

		LineString(LineString&& lines)
			: base_type(std::move(lines))
		{

		}
		
		explicit LineString(const Array<Vec2>& points)
			: base_type(points.begin(), points.end())
		{

		}

		explicit LineString(Array<Vec2>&& points)
			: base_type(std::move(points))
		{

		}

		LineString& operator =(const Array<Vec2>& other)
		{
			base_type::operator=(other);

			return *this;
		}

		LineString& operator =(Array<Vec2>&& other) noexcept
		{
			base_type::operator=(std::move(other));

			return *this;
		}

		LineString& operator =(const LineString& other)
		{
			base_type::operator=(other);

			return *this;
		}

		LineString& operator =(LineString&& other) noexcept
		{
			base_type::operator=(std::move(other));

			return *this;
		}

		void assign(const LineString& other)
		{
			base_type::operator=(other);
		}

		void assign(LineString&& other) noexcept
		{
			base_type::operator=(std::move(other));
		}

		LineString& operator <<(const Vec2& value)
		{
			base_type::push_back(value);

			return *this;
		}

		void swap(LineString& other) noexcept
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

		[[nodiscard]] LineString slice(const size_t index) const
		{
			return LineString(base_type::slice(index));
		}

		[[nodiscard]] LineString slice(const size_t index, const size_t length) const
		{
			return LineString(base_type::slice(index, length));
		}

		[[nodiscard]] size_t num_lines() const noexcept
		{
			return size() < 2 ? 0 : size() - 1;
		}

		[[nodiscard]] Line line(size_t index) const
		{
			return{ base_type::operator[](index), base_type::operator[](index + 1) };
		}

		[[nodiscard]] LineString movedBy(double x, double y) const
		{
			return LineString(*this).moveBy(x, y);
		}

		[[nodiscard]] LineString movedBy(const Vec2& v) const
		{
			return movedBy(v.x, v.y);
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

		[[nodiscard]] RectF calculateBoundingRect() const noexcept;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		[[nodiscard]] LineString catmullRom(int32 interpolation = 24) const;

		[[nodiscard]] LineString catmullRomClosed(int32 interpolation = 24) const;

		[[nodiscard]] Polygon calculateBuffer(double distance, int32 quality = 24) const;

		[[nodiscard]] Polygon calculateBufferClosed(double distance, int32 quality = 24) const;

		const LineString& paint(Image& dst, const Color& color) const;

		const LineString& paint(Image& dst, int32 thickness, const Color& color) const;

		const LineString& paintClosed(Image& dst, const Color& color) const;

		const LineString& paintClosed(Image& dst, int32 thickness, const Color& color) const;

		const LineString& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		const LineString& overwrite(Image& dst, int32 thickness, const Color& color, bool antialiased = true) const;

		const LineString& overwriteClosed(Image& dst, const Color& color, bool antialiased = true) const;

		const LineString& overwriteClosed(Image& dst, int32 thickness, const Color& color, bool antialiased = true) const;

		const LineString& draw(const ColorF& color = Palette::White) const;

		const LineString& draw(double thickness, const ColorF& color = Palette::White) const;

		const LineString& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		const LineString& drawClosed(const ColorF& color = Palette::White) const;

		const LineString& drawClosed(double thickness, const ColorF& color = Palette::White) const;

		const LineString& drawClosed(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		void drawCatmullRom(const ColorF& color = Palette::White, int32 interpolation = 24) const;

		void drawCatmullRom(double thickness, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		void drawCatmullRom(const LineStyle& style, double thickness = 1.0, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		void drawCatmullRomClosed(const ColorF& color = Palette::White, int32 interpolation = 24) const;

		void drawCatmullRomClosed(double thickness, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		void drawCatmullRomClosed(const LineStyle& style, double thickness = 1.0, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		// drawArray
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	inline void Formatter(FormatData& formatData, const LineString& value)
	{
		formatData.string.append(value.join(U", ", U"(", U")"));
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const LineString& value)
	{
		output << CharType('(');

		bool b = false;

		for (const auto& point : value)
		{
			if (std::exchange(b, true))
			{
				output << CharType(',');
			}

			output << point;
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
	template <>
	struct hash<s3d::LineString>
	{
		[[nodiscard]] size_t operator ()(const s3d::LineString& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	inline void swap(s3d::LineString& a, s3d::LineString& b) noexcept
	{
		a.swap(b);
	}
}
