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

		LineString(const LineString& lines);

		LineString(LineString&& lines);
		
		explicit LineString(const Array<Vec2>& points);

		explicit LineString(Array<Vec2>&& points);

		LineString& operator =(const Array<Vec2>& other);

		LineString& operator =(Array<Vec2>&& other) noexcept;

		LineString& operator =(const LineString& other);

		LineString& operator =(LineString&& other) noexcept;

		void assign(const LineString& other);

		void assign(LineString&& other) noexcept;

		LineString& operator <<(const Vec2& value);

		void swap(LineString& other) noexcept;

		LineString& append(const Array<Vec2>& other);

		LineString& append(const LineString& other);

		LineString& remove(const Vec2& value);

		LineString& remove_at(size_t index);

		template <class Fty>
		LineString& remove_if(Fty f)
		{
			base_type::remove_if(f);

			return *this;
		}

		LineString& reverse();

		LineString& rotate(std::ptrdiff_t count = 1);

		LineString& shuffle();

		template <class URBG>
		LineString& shuffle(URBG&& rbg)
		{
			base_type::shuffle(std::forward<URBG>(rbg));

			return *this;
		}

		[[nodiscard]] LineString slice(size_t index) const;

		[[nodiscard]] LineString slice(size_t index, size_t length) const;

		[[nodiscard]] size_t num_lines() const noexcept;

		[[nodiscard]] Line line(size_t index) const;

		[[nodiscard]] LineString movedBy(double x, double y) const;

		[[nodiscard]] LineString movedBy(const Vec2& v) const;

		LineString& moveBy(double x, double y) noexcept;

		LineString& moveBy(const Vec2& v) noexcept;

		[[nodiscard]] RectF calculateBoundingRect() const noexcept;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		[[nodiscard]] LineString densified(double maxDistance) const;

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
	void Formatter(FormatData& formatData, const LineString& value);

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
			return s3d::Hash::FNV1a(value.data(), value.size_bytes());
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
