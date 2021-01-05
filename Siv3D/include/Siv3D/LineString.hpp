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

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "Array.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	/// @brief 点の集合（とそれをつないで表現される線分）
	class LineString : protected Array<Vec2>
	{
	public:

		using base_type = Array<Vec2>;
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
		using base_type::pop_front_N;
		using base_type::pop_back_N;
		using base_type::all;
		using base_type::any;
		using base_type::choice;
		using base_type::fill;
		using base_type::join;
		using base_type::none;
		using base_type::remove;

		SIV3D_NODISCARD_CXX20
		LineString() = default;

		SIV3D_NODISCARD_CXX20
		LineString(const LineString& lines);

		SIV3D_NODISCARD_CXX20
		LineString(LineString&& lines) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit LineString(const Array<Point>& points);

		SIV3D_NODISCARD_CXX20
		explicit LineString(const Array<Vec2>& points);

		SIV3D_NODISCARD_CXX20
		explicit LineString(Array<Vec2>&& points) noexcept;

		LineString& operator =(const Array<Point>& other);

		LineString& operator =(const Array<Vec2>& other);

		LineString& operator =(Array<Vec2>&& other) noexcept;

		LineString& operator =(const LineString& other);

		LineString& operator =(LineString&& other) noexcept;

		void assign(const Array<Point>& other);

		void assign(const LineString& other);

		void assign(LineString&& other) noexcept;

		LineString& operator <<(const Vec2& value);

		void swap(LineString& other) noexcept;

		LineString& append(const Array<Vec2>&other);

		LineString& append(const LineString& other);

		LineString& remove(const Vec2& value);

		LineString& remove_at(size_t index);

		template <class Fty>
		LineString& remove_if(Fty f);

		LineString& reverse();

		[[nodiscard]]
		LineString reversed() const;

		LineString& shuffle();

		SIV3D_CONCEPT_URBG
		LineString& shuffle(URBG&& rbg);

		[[nodiscard]]
		LineString slice(size_t index) const;

		[[nodiscard]]
		LineString slice(size_t index, size_t length) const;

		[[nodiscard]]
		size_t num_lines() const noexcept;

		[[nodiscard]]
		Line line(size_t index) const;

		[[nodiscard]]
		LineString movedBy(double x, double y) const;

		[[nodiscard]]
		LineString movedBy(Vec2 v) const;

		LineString& moveBy(double x, double y) noexcept;

		LineString& moveBy(Vec2 v) noexcept;

		[[nodiscard]]
		RectF calculateBoundingRect() const noexcept;
		

		[[nodiscard]]
		LineString densified(double maxDistance) const;

		[[nodiscard]]
		LineString catmullRom(int32 interpolation = 24) const;

		[[nodiscard]]
		LineString catmullRomClosed(int32 interpolation = 24) const;

		[[nodiscard]]
		Polygon calculateBuffer(double distance, int32 quality = 24) const;

		[[nodiscard]]
		Polygon calculateBufferClosed(double distance, int32 quality = 24) const;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;


		//const LineString& paint(Image& dst, const Color& color) const;

		//const LineString& paint(Image& dst, int32 thickness, const Color& color) const;

		//const LineString& paintClosed(Image& dst, const Color& color) const;

		//const LineString& paintClosed(Image& dst, int32 thickness, const Color& color) const;

		//const LineString& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		//const LineString& overwrite(Image& dst, int32 thickness, const Color& color, bool antialiased = true) const;

		//const LineString& overwriteClosed(Image& dst, const Color& color, bool antialiased = true) const;

		//const LineString& overwriteClosed(Image& dst, int32 thickness, const Color& color, bool antialiased = true) const;


		const LineString& draw(const ColorF& color = Palette::White) const;

		const LineString& draw(double thickness, const ColorF& color = Palette::White) const;

		const LineString& draw(double thickness, const Array<ColorF>& colors) const;

		//const LineString& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		const LineString& drawClosed(const ColorF& color = Palette::White) const;

		const LineString& drawClosed(double thickness, const ColorF & color = Palette::White) const;

		//const LineString& drawClosed(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		//void drawCatmullRom(const ColorF& color = Palette::White, int32 interpolation = 24) const;

		//void drawCatmullRom(double thickness, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		//void drawCatmullRom(const LineStyle& style, double thickness = 1.0, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		//void drawCatmullRomClosed(const ColorF& color = Palette::White, int32 interpolation = 24) const;

		//void drawCatmullRomClosed(double thickness, const ColorF& color = Palette::White, int32 interpolation = 24) const;

		//void drawCatmullRomClosed(const LineStyle& style, double thickness = 1.0, const ColorF& color = Palette::White, int32 interpolation = 24) const;

	private:

	};
}

template <>
inline void std::swap(s3d::LineString& a, s3d::LineString& b) noexcept;

# include "detail/LineString.ipp"
