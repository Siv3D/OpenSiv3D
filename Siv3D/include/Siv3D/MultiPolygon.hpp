//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Polygon.hpp"

namespace s3d
{
	/// @brief Polygon の集合
	class MultiPolygon
	{
	public:

		using base_type					= Array<Polygon>;
		using allocator_type			= base_type::allocator_type;
		using value_type				= base_type::value_type;
		using size_type					= base_type::size_type;
		using difference_type			= base_type::difference_type;
		using pointer					= base_type::pointer;
		using const_pointer				= base_type::const_pointer;
		using reference					= base_type::reference;
		using const_reference			= base_type::const_reference;
		using iterator					= base_type::iterator;
		using const_iterator			= base_type::const_iterator;
		using reverse_iterator			= base_type::reverse_iterator;
		using const_reverse_iterator	= base_type::const_reverse_iterator;

		SIV3D_NODISCARD_CXX20
		MultiPolygon() = default;

		SIV3D_NODISCARD_CXX20
		explicit MultiPolygon(const allocator_type& alloc) noexcept;

		SIV3D_NODISCARD_CXX20
		MultiPolygon(size_t count, const value_type& value, const allocator_type& alloc = allocator_type{});

		SIV3D_NODISCARD_CXX20
		explicit MultiPolygon(size_t count, const allocator_type& alloc = allocator_type{});

		template <class Iterator>
		MultiPolygon(Iterator first, Iterator last, const allocator_type& alloc = allocator_type{});

		SIV3D_NODISCARD_CXX20
		MultiPolygon(const MultiPolygon& polygons);

		SIV3D_NODISCARD_CXX20
		MultiPolygon(const MultiPolygon& polygons, const allocator_type& alloc);

		SIV3D_NODISCARD_CXX20
		MultiPolygon(MultiPolygon&& polygons) noexcept;

		SIV3D_NODISCARD_CXX20
		MultiPolygon(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type{});

		SIV3D_NODISCARD_CXX20
		explicit MultiPolygon(const Array<Polygon>& polygons);

		SIV3D_NODISCARD_CXX20
		explicit MultiPolygon(Array<Polygon>&& polygons) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit MultiPolygon(Arg::reserve_<size_type> size);

		MultiPolygon& operator =(const Array<value_type>& other);

		MultiPolygon& operator =(Array<value_type>&& other) noexcept;

		MultiPolygon& operator =(const MultiPolygon& other);

		MultiPolygon& operator =(MultiPolygon&& other) noexcept;

		[[nodiscard]]
		const Array<value_type>& asArray() const noexcept;

		[[nodiscard]]
		operator const Array<value_type>& () const noexcept;

		template <class Iterator>
		void assign(Iterator first, Iterator last);

		void assign(size_type n, const value_type& value);

		void assign(std::initializer_list<value_type> il);

		void assign(const Array<Polygon>& other);

		void assign(Array<Polygon>&& other);

		void assign(const MultiPolygon& other);

		void assign(MultiPolygon&& other) noexcept;

		[[nodiscard]]
		allocator_type get_allocator() const noexcept;

		[[nodiscard]]
		value_type& at(size_t index)&;

		[[nodiscard]]
		const value_type& at(size_t index) const&;

		[[nodiscard]]
		value_type at(size_t index)&&;

		[[nodiscard]]
		value_type& operator [](size_t index) & noexcept;

		[[nodiscard]]
		const value_type& operator [](size_t index) const& noexcept;

		[[nodiscard]]
		value_type operator [](size_t index) && noexcept;

		void push_front(const value_type& value);

		void push_front(value_type&& value);

		void push_back(const value_type& value);

		void push_back(value_type&& value);

		void pop_front();

		void pop_front_N(size_t n);

		void pop_back() noexcept;

		void pop_back_N(size_t n);

		MultiPolygon& operator <<(const value_type& polygon);

		MultiPolygon& operator <<(value_type&& polygon);

		template <class... Args>
		iterator emplace(const_iterator position, Args&&... args);

		template <class... Args>
		decltype(auto) emplace_back(Args&&... args);

		[[nodiscard]]
		value_type& front() noexcept;

		[[nodiscard]]
		const value_type& front() const noexcept;

		[[nodiscard]]
		value_type& back() noexcept;

		[[nodiscard]]
		const value_type& back() const noexcept;

		void swap(MultiPolygon& other) noexcept;

		[[nodiscard]]
		const value_type* data() const noexcept;

		[[nodiscard]]
		value_type* data() noexcept;

		[[nodiscard]]
		iterator begin() noexcept;

		[[nodiscard]]
		iterator end() noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		[[nodiscard]]
		reverse_iterator rend() noexcept;

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		[[nodiscard]]
		bool empty() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		size_t size_bytes() const noexcept;

		[[nodiscard]]
		size_t size() const noexcept;

		[[nodiscard]]
		size_t max_size() const noexcept;

		void reserve(size_t newCapacity);

		[[nodiscard]]
		size_t capacity() const noexcept;

		void shrink_to_fit();

		void clear() noexcept;

		void release();

		iterator insert(const_iterator where, const value_type& value);

		iterator insert(const_iterator where, value_type&& value);

		iterator insert(const_iterator where, size_t count, const value_type& value);

		template <class Iterator>
		iterator insert(const_iterator where, Iterator first, Iterator last);

		iterator insert(const_iterator where, std::initializer_list<value_type> il);

		iterator erase(const_iterator where) noexcept;

		iterator erase(const_iterator first, const_iterator last) noexcept;

		void resize(size_t newSize);

		void resize(size_t newSize, const value_type& value);

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, value_type>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, value_type>>* = nullptr>
		[[nodiscard]]
		bool any(Fty f = Identity) const;

		[[nodiscard]]
		value_type& choice();

		[[nodiscard]]
		const value_type& choice() const;

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		value_type& choice(URBG&& rbg);

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		const value_type& choice(URBG&& rbg) const;

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		MultiPolygon choice(Int n) const;

	# if __cpp_lib_concepts
		template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
	# else
		template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr,
			std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# endif
		[[nodiscard]]
		MultiPolygon choice(Size_t n, URBG&& rbg) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, value_type>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		[[nodiscard]]
		String join(StringView sep = U", "_sv, StringView begin = U"{"_sv, StringView end = U"}"_sv) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, value_type>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

		MultiPolygon& append(const Array<value_type>& other);

		MultiPolygon& append(const MultiPolygon& other);

		MultiPolygon& remove_at(size_t index);

		template <class Fty>
		MultiPolygon& remove_if(Fty f);

		MultiPolygon& reverse();

		[[nodiscard]]
		MultiPolygon reversed() const;

		MultiPolygon& shuffle();

		SIV3D_CONCEPT_URBG
		MultiPolygon& shuffle(URBG&& rbg);

		MultiPolygon slice(size_t index) const;

		MultiPolygon slice(size_t index, size_t length) const;

		[[nodiscard]]
		MultiPolygon movedBy(double x, double y) const;

		[[nodiscard]]
		MultiPolygon movedBy(Vec2 v) const;

		MultiPolygon& moveBy(double x, double y) noexcept;

		MultiPolygon& moveBy(Vec2 v) noexcept;

		[[nodiscard]]
		MultiPolygon rotated(double angle) const;

		[[nodiscard]]
		MultiPolygon rotatedAt(const Vec2& pos, double angle) const;

		MultiPolygon& rotate(double angle);

		MultiPolygon& rotateAt(const Vec2& pos, double angle);

		[[nodiscard]]
		MultiPolygon transformed(double s, double c, const Vec2& pos) const;

		MultiPolygon& transform(double s, double c, const Vec2& pos);

		[[nodiscard]]
		MultiPolygon scaled(double s) const;

		[[nodiscard]]
		MultiPolygon scaled(double sx, double sy) const;

		[[nodiscard]]
		MultiPolygon scaled(Vec2 s) const;

		MultiPolygon& scale(double s);

		MultiPolygon& scale(double sx, double sy);

		MultiPolygon& scale(Vec2 s);

		[[nodiscard]]
		MultiPolygon scaledAt(Vec2 pos, double s) const;

		[[nodiscard]]
		MultiPolygon scaledAt(Vec2 pos, double sx, double sy) const;

		[[nodiscard]]
		MultiPolygon scaledAt(Vec2 pos, Vec2 s) const;

		MultiPolygon& scaleAt(Vec2 pos, double s);

		MultiPolygon& scaleAt(Vec2 pos, double sx, double sy);

		MultiPolygon& scaleAt(Vec2 pos, Vec2 s);

		[[nodiscard]]
		RectF computeBoundingRect() const noexcept;

		[[nodiscard]]
		MultiPolygon simplified(double maxDistance = 2.0) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		bool contains(const Shape2DType& other) const;

		[[nodiscard]]
		bool leftClicked() const noexcept;

		[[nodiscard]]
		bool leftPressed() const noexcept;

		[[nodiscard]]
		bool leftReleased() const noexcept;

		[[nodiscard]]
		bool rightClicked() const noexcept;

		[[nodiscard]]
		bool rightPressed() const noexcept;

		[[nodiscard]]
		bool rightReleased() const noexcept;

		[[nodiscard]]
		bool mouseOver() const noexcept;

		const MultiPolygon& paint(Image& dst, const Color& color) const;

		const MultiPolygon& paint(Image& dst, double x, double y, const Color& color) const;

		const MultiPolygon& paint(Image& dst, const Vec2& pos, const Color& color) const;

		const MultiPolygon& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const MultiPolygon& overwrite(Image& dst, double x, double y, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const MultiPolygon& overwrite(Image& dst, const Vec2& pos, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const MultiPolygon& draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, const ColorF& color = Palette::White) const;

		void draw(const Vec2& pos, const ColorF& color = Palette::White) const;

		const MultiPolygon& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		const MultiPolygon& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawTransformed(double angle, const Vec2& pos, const ColorF& color = Palette::White) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color = Palette::White) const;

	private:

		base_type m_data;
	};
}

template <>
inline void std::swap(s3d::MultiPolygon& a, s3d::MultiPolygon& b) noexcept;

# include "detail/MultiPolygon.ipp"
