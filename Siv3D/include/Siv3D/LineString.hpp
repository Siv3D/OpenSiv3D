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
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "Array.hpp"
# include "2DShapes.hpp"
# include "Polygon.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief 点の集合（とそれをつないで表現される、連続する線分）
	class LineString
	{
	public:

		using base_type					= Array<Vec2>;
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
		LineString() = default;

		SIV3D_NODISCARD_CXX20
		explicit LineString(const allocator_type& alloc) noexcept;

		SIV3D_NODISCARD_CXX20
		LineString(size_t count, const value_type& value, const allocator_type& alloc = allocator_type{});

		SIV3D_NODISCARD_CXX20
		explicit LineString(size_t count, const allocator_type& alloc = allocator_type{});

		template <class Iterator>
		LineString(Iterator first, Iterator last, const allocator_type& alloc = allocator_type{});

		SIV3D_NODISCARD_CXX20
		LineString(const LineString& lines);

		SIV3D_NODISCARD_CXX20
		LineString(const LineString& lines, const allocator_type& alloc);

		SIV3D_NODISCARD_CXX20
		LineString(LineString&& lines) noexcept;

		SIV3D_NODISCARD_CXX20
		LineString(std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type{});

		SIV3D_NODISCARD_CXX20
		explicit LineString(const Array<Point>& points);

		SIV3D_NODISCARD_CXX20
		explicit LineString(const Array<Vec2>& points);

		SIV3D_NODISCARD_CXX20
		explicit LineString(Array<Vec2>&& points) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit LineString(Arg::reserve_<size_type> size);

		LineString& operator =(const Array<Point>& other);

		LineString& operator =(const Array<Vec2>& other);

		LineString& operator =(Array<Vec2>&& other) noexcept;

		LineString& operator =(const LineString& other);

		LineString& operator =(LineString&& other) noexcept;

		[[nodiscard]]
		const Array<value_type>& asArray() const noexcept;
		
		[[nodiscard]]
		operator const Array<value_type>& () const noexcept;

		template <class Iterator>
		void assign(Iterator first, Iterator last);

		void assign(size_type n, const value_type& value);

		void assign(std::initializer_list<value_type> il);

		void assign(const Array<Point>& other);

		void assign(const Array<Vec2>& other);

		void assign(Array<Vec2>&& other) noexcept;

		void assign(const LineString& other);

		void assign(LineString&& other) noexcept;

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

		void push_front(const value_type & value);

		void push_back(const value_type & value);

		void pop_front();

		void pop_front_N(size_t n);

		void pop_back() noexcept;

		void pop_back_N(size_t n);

		LineString& operator <<(const value_type& value);

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

		void swap(LineString& other) noexcept;

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
		LineString choice(Int n) const;

	# if __cpp_lib_concepts
		template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
	# else
		template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr,
			std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# endif
		[[nodiscard]]
		LineString choice(Size_t n, URBG&& rbg) const;

		[[nodiscard]]
		size_t count(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, value_type>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		LineString& fill(const value_type& value);

		[[nodiscard]]
		String join(StringView sep = U", "_sv, StringView begin = U"{"_sv, StringView end = U"}"_sv) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, value_type>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

		LineString& append(const Array<value_type>&other);

		LineString& append(const LineString& other);

		LineString& remove(const value_type& value);

		LineString& remove_at(size_t index);

		template <class Fty>
		LineString& remove_if(Fty f);

		LineString& reverse();

		/// @brief 連続する線分の向きを反転した新しい LineString を返します。
		/// @return 連続する線分の向きを反転した新しい LineString
		[[nodiscard]]
		LineString reversed() const;

		LineString& shuffle();

		SIV3D_CONCEPT_URBG
		LineString& shuffle(URBG&& rbg);

		[[nodiscard]]
		LineString slice(size_t index) const;

		[[nodiscard]]
		LineString slice(size_t index, size_t length) const;

		LineString& unique_consecutive();

		[[nodiscard]]
		LineString uniqued_consecutive() const&;

		[[nodiscard]]
		LineString uniqued_consecutive()&&;

		/// @brief LineString を構成する頂点の数を返します。
		/// @remark `size()` と同じです。
		/// @return LineString を構成する頂点の数
		[[nodiscard]]
		size_t num_points() const noexcept;

		/// @brief LineString を構成する線分の数を返します。
		/// @param closeRing 終点と始点を結ぶか
		/// @return LineString を構成する線分の数
		[[nodiscard]]
		size_t num_lines(CloseRing closeRing = CloseRing::No) const noexcept;

		/// @brief LineString を構成する線分を返します。
		/// @param index 線分のインデックス
		/// @param closeRing 終点と始点を結ぶか
		/// @return LineString を構成する線分
		[[nodiscard]]
		Line line(size_t index, CloseRing closeRing = CloseRing::No) const;

		/// @brief 指定した頂点における進行方向左手の単位ベクトルを返します。
		/// @param index 頂点のインデックス
		/// @param closeRing 終点と始点を結ぶか
		/// @return 指定した頂点における進行方向左手の単位ベクトル
		[[nodiscard]]
		Vec2 normalAtPoint(size_t index, CloseRing closeRing = CloseRing::No) const;

		/// @brief 指定した線分における進行方向左手の単位ベクトルを返します。
		/// @param index 線分のインデックス
		/// @param closeRing 終点と始点を結ぶか
		/// @return  指定した線分における進行方向左手の単位ベクトル
		[[nodiscard]]
		Vec2 normalAtLine(size_t index, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		LineString movedBy(double x, double y) const;

		[[nodiscard]]
		LineString movedBy(Vec2 v) const;

		LineString& moveBy(double x, double y) noexcept;

		LineString& moveBy(Vec2 v) noexcept;

		[[nodiscard]]
		LineString scaled(double s) const;

		[[nodiscard]]
		LineString scaled(double sx, double sy) const;

		[[nodiscard]]
		LineString scaled(Vec2 s) const;

		LineString& scale(double s);

		LineString& scale(double sx, double sy);

		LineString& scale(Vec2 s);

		[[nodiscard]]
		LineString scaledAt(Vec2 pos, double s) const;

		[[nodiscard]]
		LineString scaledAt(Vec2 pos, double sx, double sy) const;

		[[nodiscard]]
		LineString scaledAt(Vec2 pos, Vec2 s) const;

		LineString& scaleAt(Vec2 pos, double s);

		LineString& scaleAt(Vec2 pos, double sx, double sy);

		LineString& scaleAt(Vec2 pos, Vec2 s);

		[[nodiscard]]
		RectF computeBoundingRect() const noexcept;

		/// @brief 連続する線分を単純化した LineString を返します。
		/// @param maxDistance 単純化の大きさ
		/// @param closeRing 終点と始点を結ぶか
		/// @return 単純化した LineString
		[[nodiscard]]
		LineString simplified(double maxDistance = 2.0, CloseRing closeRing = CloseRing::No) const;

		/// @brief 点と点の間の距離が `maxDistance` より大きくならないよう、区間ごとに最小回数で均等に分割した結果を返します。
		/// @param maxDistance 点と点の間の最大距離
		/// @param closeRing 終点と始点を結ぶか
		/// @return 分割した結果
		[[nodiscard]]
		LineString densified(double maxDistance, CloseRing closeRing = CloseRing::No) const;

		/// @brief Catmull-Rom スプライン曲線を返します。
		/// @param interpolation 分割の品質
		/// @return Catmull-Rom スプライン曲線
		[[nodiscard]]
		LineString catmullRom(int32 interpolation = 24) const;

		/// @brief Catmull-Rom スプライン曲線を返します。
		/// @param closeRing 終点と始点を結ぶか
		/// @param interpolation 分割の品質
		/// @return Catmull-Rom スプライン曲線
		[[nodiscard]]
		LineString catmullRom(CloseRing closeRing, int32 interpolation = 24) const;

		/// @brief 連続する線分全体の長さを返します。
		/// @param closeRing 終点と始点を結ぶか
		/// @return 連続する線分全体の長さ
		[[nodiscard]]
		double calculateLength(CloseRing closeRing = CloseRing::No) const noexcept;

		/// @brief 始点から指定した距離にある、線分上の点を返します
		/// @param distanceFromOrigin 始点からの距離
		/// @param closeRing 終点と始点を結ぶか
		/// @return 始点から指定した距離にある線分上の点
		[[nodiscard]]
		Vec2 calculatePointFromOrigin(double distanceFromOrigin, CloseRing closeRing = CloseRing::No) const;

		/// @brief 部分 LineString を返します。
		/// @param distanceFromOrigin 始点からの距離
		/// @param closeRing 終点と始点を結ぶか
		/// @return 部分 LineString
		[[nodiscard]]
		LineString extractLineString(double distanceFromOrigin, CloseRing closeRing = CloseRing::No) const;

		/// @brief 部分 LineString を返します。
		/// @param distanceFromOrigin 始点からの距離
		/// @param length 長さ
		/// @param closeRing 終点と始点を結ぶか
		/// @return 部分 LineString
		[[nodiscard]]
		LineString extractLineString(double distanceFromOrigin, double length, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		Array<Vec2> computeNormals(CloseRing closeRing = CloseRing::No) const;

		/// @brief 太らせた多角形を作成します。
		/// @param distance 太らせる距離（ピクセル）
		/// @param bufferQuality 品質
		/// @return 太らせた多角形
		[[nodiscard]]
		Polygon calculateBuffer(double distance, int32 bufferQuality = 24) const;

		/// @brief 終点と始点を結んだうえで、太らせた多角形を作成します。
		/// @param distance 太らせる距離（ピクセル）
		/// @param bufferQuality 品質
		/// @return 太らせた多角形
		[[nodiscard]]
		Polygon calculateBufferClosed(double distance, int32 bufferQuality = 24) const;

		/// @brief 丸く太らせた多角形を作成します。
		/// @param distance 太らせる距離（ピクセル）
		/// @param bufferQuality 品質
		/// @return 丸く太らせた多角形
		[[nodiscard]]
		Polygon calculateRoundBuffer(double distance, int32 bufferQuality = 24) const;

		/// @brief 終点と始点を結んだうえで、丸く太らせた多角形を作成します。
		/// @param distance 太らせる距離（ピクセル）
		/// @param bufferQuality 品質
		/// @return 丸く太らせた多角形
		[[nodiscard]]
		Polygon calculateRoundBufferClosed(double distance, int32 bufferQuality = 24) const;

		[[nodiscard]]
		Spline2D asSpline(CloseRing closeRing = CloseRing::No) const;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		const LineString& paint(Image& dst, const Color& color) const;

		const LineString& paint(Image& dst, int32 thickness, const Color& color) const;

		const LineString& paintClosed(Image& dst, const Color& color) const;

		const LineString& paintClosed(Image& dst, int32 thickness, const Color& color) const;

		const LineString& overwrite(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const LineString& overwrite(Image& dst, int32 thickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const LineString& overwriteClosed(Image& dst, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const LineString& overwriteClosed(Image& dst, int32 thickness, const Color& color, Antialiased antialiased = Antialiased::Yes) const;

		const LineString& draw(const ColorF& color = Palette::White) const;

		/// @brief 連続する線分を描画します。
		/// @param thickness 線の太さ（ピクセル）
		/// @param color 色
		/// @return *this
		const LineString& draw(double thickness, const ColorF& color = Palette::White) const;

		/// @brief 連続する線分を描画します。
		/// @param thickness 線の太さ（ピクセル）
		/// @param colors 各頂点に割り当てる色
		/// @return *this
		const LineString& draw(double thickness, const Array<ColorF>& colors) const;

		const LineString& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		/// @brief 終点と始点を結んだうえで、連続する線分を描画します。
		/// @param color 色
		/// @return *this
		const LineString& drawClosed(const ColorF& color = Palette::White) const;

		/// @brief 終点と始点を結んだうえで、連続する線分を描画します。
		/// @param thickness 線の太さ（ピクセル）
		/// @param color 色
		/// @return *this
		const LineString& drawClosed(double thickness, const ColorF & color = Palette::White) const;

		const LineString& drawClosed(double thickness, const Array<ColorF>& colors) const;

		const LineString& drawClosed(const LineStyle& style, double thickness, const ColorF& color = Palette::White) const;

		friend void Formatter(FormatData& formatData, const LineString& value);

	private:

		base_type m_data;
	};
}

template <>
inline void std::swap(s3d::LineString& a, s3d::LineString& b) noexcept;

# include "detail/LineString.ipp"
