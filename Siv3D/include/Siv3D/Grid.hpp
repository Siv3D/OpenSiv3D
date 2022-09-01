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
# include "PointVector.hpp"

namespace s3d
{
	template <class Type, class Allocator>
	class Grid;

	template <class Type, class Allocator>
	inline void Formatter(FormatData& formatData, const Grid<Type, Allocator>& value);

	/// @brief 二次元配列クラス
	/// @tparam Type 要素の型
	/// @tparam Allocator アロケータの型
	template <class Type, class Allocator = std::allocator<Type>>
	class Grid
	{
	public:

		using container_type			= Array<Type, Allocator>;
		using value_type				= typename container_type::value_type;
		using pointer					= typename container_type::pointer;
		using const_pointer				= typename container_type::const_pointer;
		using reference					= typename container_type::reference;
		using const_reference			= typename container_type::const_reference;
		using iterator					= typename container_type::iterator;
		using const_iterator			= typename container_type::const_iterator;
		using reverse_iterator			= typename container_type::reverse_iterator;
		using const_reverse_iterator	= typename container_type::const_reverse_iterator;
		using size_type					= typename container_type::size_type;
		using difference_type			= typename container_type::difference_type;
		using allocator_type			= typename container_type::allocator_type;

		SIV3D_NODISCARD_CXX20
		Grid() = default;

		SIV3D_NODISCARD_CXX20
		Grid(const Grid&) = default;

		SIV3D_NODISCARD_CXX20
		Grid(Grid&&) = default;

		SIV3D_NODISCARD_CXX20
		Grid(size_type w, size_type h);

		SIV3D_NODISCARD_CXX20
		Grid(size_type w, size_type h, const value_type& value);

		SIV3D_NODISCARD_CXX20
		explicit Grid(Size size);

		SIV3D_NODISCARD_CXX20
		Grid(Size size, const value_type& value);

		SIV3D_NODISCARD_CXX20
		Grid(size_type w, size_type h, const Array<value_type>& data);

		SIV3D_NODISCARD_CXX20
		Grid(size_type w, size_type h, Array<value_type>&& data);

		SIV3D_NODISCARD_CXX20
		Grid(Size size, const Array<value_type>& data);

		SIV3D_NODISCARD_CXX20
		Grid(Size size, Array<value_type>&& data);

		SIV3D_NODISCARD_CXX20
		Grid(const std::initializer_list<std::initializer_list<value_type>>& set);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Grid(size_type w, size_type h, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Grid(Size size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Grid(size_type w, size_type h, Arg::indexedGenerator_<Fty> indexedGenerator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Grid(Size size, Arg::indexedGenerator_<Fty> indexedGenerator);

		Grid& operator =(const Grid&) = default;

		/// @brief ムーブ代入演算子
		/// @param other ムーブする配列
		/// @return *this
		Grid& operator =(Grid&&) = default;

		/// @brief 他の配列と要素を入れ替えます。
		/// @param other 入れ替える配列
		void swap(Grid& other) noexcept;

		[[nodiscard]]
		allocator_type get_allocator() const noexcept;

		void assign(size_type w, size_type h, const value_type& value);

		void assign(Size size, const value_type& value);

		void assign(const std::initializer_list<std::initializer_list<value_type>>& set);

		value_type& at(size_type y, size_type x)&;

		const value_type& at(size_type y, size_type x) const&;

		value_type at(size_type y, size_type x)&&;

		value_type& at(Point pos)&;

		const value_type& at(Point pos) const&;

		value_type at(Point pos)&&;

		[[nodiscard]]
		value_type* operator [](size_t index);

		[[nodiscard]]
		const value_type* operator [](size_t index) const;

		[[nodiscard]]
		value_type& operator [](Point pos)&;

		[[nodiscard]]
		const value_type& operator [](Point pos) const&;

		[[nodiscard]]
		value_type operator [](Point pos)&&;

		[[nodiscard]]
		bool inBounds(int64 y, int64 x) const noexcept;

		[[nodiscard]]
		bool inBounds(Point pos) const noexcept;

		[[nodiscard]] pointer data() noexcept;

		[[nodiscard]] const_pointer data() const noexcept;

		/// @brief 配列が空であるかを返します。
		/// @return 配列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool empty() const noexcept;

		/// @brief 配列が空であるかを返します。
		/// @return 配列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 配列が要素を持っているかを返します。
		/// @return 配列が要素を持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		size_type width() const noexcept;

		[[nodiscard]]
		size_type height() const noexcept;

		[[nodiscard]]
		Size size() const noexcept;

		[[nodiscard]]
		size_type num_elements() const noexcept;

		/// @brief 配列の要素の合計サイズ（バイト）を返します。
		/// @return 配列の要素の合計サイズ（バイト）
		[[nodiscard]]
		size_t size_bytes() const noexcept;

		[[nodiscard]]
		const container_type& asArray() const noexcept;

		void reserve(size_type w, size_type h);

		void reserve(Size size);

		[[nodiscard]]
		size_type capacity() const noexcept;

		void shrink_to_fit();

		void clear() noexcept;

		/// @brief 配列の要素を全て消去し、メモリも解放します。
		void release();

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

		void push_back_row(const value_type& value);

		void pop_back_row();

		void pop_back_row_N(size_t n);

		void push_back_column(const value_type& value);

		void pop_back_column();

		void pop_back_column_N(size_t n);

		void insert_row(size_type pos, const value_type& value);

		void insert_rows(size_type pos, size_type rows, const value_type& value);

		void insert_column(size_type pos, const value_type& value);

		void insert_columns(size_type pos, size_type columns, const value_type& value);

		void remove_row(size_type pos);

		void remove_rows(size_type pos, size_type count);

		void remove_column(size_type pos);

		void remove_columns(size_type pos, size_type count);

		void resize(size_type w, size_type h);

		void resize(Size size);

		void resize(size_type w, size_type h, const value_type& value);

		void resize(Size size, const value_type& value);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto operator >>(Fty f) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
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
		Array<Type> choice(Int n) const;

	# if __cpp_lib_concepts
		template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
	# else
		template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr,
			std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# endif
		[[nodiscard]]
		Array<Type> choice(Size_t n, URBG&& rbg) const;

		[[nodiscard]]
		size_t count(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		Grid& each(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		const Grid& each(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Point, Type&>>* = nullptr>
		Grid& each_index(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Point, Type>>* = nullptr>
		const Grid& each_index(Fty f) const;

		[[nodiscard]]
		const value_type& fetch(size_type y, size_type x, const value_type& defaultValue) const;

		[[nodiscard]]
		const value_type& fetch(Point pos, const value_type& defaultValue) const;

		Grid& fill(const value_type& value);

		[[nodiscard]]
		bool includes(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool includes_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto map(Fty f) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, Type, Type>>>
		auto reduce(Fty f, R init) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type, Type>>* = nullptr>
		auto reduce1(Fty f) const;

		Grid& replace(const value_type& oldValue, const value_type& newValue);

		[[nodiscard]]
		Grid replaced(const value_type& oldValue, const value_type& newValue) const&;

		[[nodiscard]]
		Grid replaced(const value_type& oldValue, const value_type& newValue)&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		Grid& replace_if(Fty f, const value_type& newValue);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Grid replaced_if(Fty f, const value_type& newValue) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Grid replaced_if(Fty f, const value_type& newValue)&&;

		Grid& reverse();

		Grid& reverse_columns();

		Grid& reverse_rows();

		[[nodiscard]]
		Grid reversed() const&;

		[[nodiscard]]
		Grid reversed()&&;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		Grid& reverse_each(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		const Grid& reverse_each(Fty f) const;

		Grid& rotate(std::ptrdiff_t count = 1);

		[[nodiscard]]
		Grid rotated(std::ptrdiff_t count = 1) const&;

		[[nodiscard]]
		Grid rotated(std::ptrdiff_t count = 1)&&;

		Grid& rotate_rows(std::ptrdiff_t count = 1);

		[[nodiscard]]
		Grid rotated_rows(std::ptrdiff_t count = 1) const&;

		[[nodiscard]]
		Grid rotated_rows(std::ptrdiff_t count = 1)&&;

		Grid& shuffle();

		SIV3D_CONCEPT_URBG
		Grid& shuffle(URBG&& rbg);

		[[nodiscard]]
		Grid shuffled() const&;

		[[nodiscard]]
		Grid shuffled()&&;

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Grid shuffled(URBG&& rbg) const&;

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Grid shuffled(URBG&& rbg)&&;

		[[nodiscard]]
		Array<Type> slice(size_type y, size_type x) const;

		[[nodiscard]]
		Array<Type> slice(Point pos) const;

		[[nodiscard]]
		Array<Type> slice(size_type y, size_type x, size_t length) const;

		[[nodiscard]]
		Array<Type> slice(Point pos, size_t length) const;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		Grid& sort();

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		Grid& stable_sort();

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		Grid& sort_by(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		Grid& stable_sort_by(Fty f);

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Grid sorted() const&;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Grid stable_sorted() const&;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Grid sorted()&&;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Grid stable_sorted()&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Grid sorted_by(Fty f) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Grid stable_sorted_by(Fty f) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Grid sorted_by(Fty f)&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Grid stable_sorted_by(Fty f)&&;

		template <class T = Type, std::enable_if_t<Meta::HasPlus_v<T>>* = nullptr>
		[[nodiscard]]
		auto sum() const;

		template <class T = Type, std::enable_if_t<not Meta::HasPlus_v<T>>* = nullptr>
		void sum() const = delete;

		template <class T = Type, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
		[[nodiscard]]
		auto sumF() const;

		template <class T = Type, std::enable_if_t<not std::is_floating_point_v<T>>* = nullptr>
		[[nodiscard]]
		auto sumF() const = delete;

		Grid& swap_columns(size_t a, size_t b);

		Grid& swap_rows(size_t a, size_t b);

		[[nodiscard]]
		Array<Type> values_at(std::initializer_list<Point> indices) const;

		[[nodiscard]]
		friend bool operator ==(const Grid& lhs, const Grid& rhs)
		{
			return (lhs.asArray() == rhs.asArray());
		}

		[[nodiscard]]
		friend bool operator !=(const Grid& lhs, const Grid& rhs)
		{
			return (lhs.asArray() != rhs.asArray());
		}

		friend std::ostream& operator <<(std::ostream& output, const Grid& value)
		{
			return (output << Format(value).narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const Grid& value)
		{
			return (output << Format(value).toWstr());
		}

		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const Grid& value)
		{
			const String s = Format(value);
			return output.write(s.data(), s.size());
		}

		friend void Formatter(FormatData& formatData, const Grid& value)
		{
			formatData.string.push_back(U'{');

			bool isFirst = true;

			for (size_t y = 0; y < value.height(); ++y)
			{
				if (isFirst)
				{
					isFirst = false;
				}
				else
				{
					formatData.string.append(U",\n");
				}

				Formatter(formatData, value[y], value[y] + value.width());
			}

			formatData.string.push_back(U'}');
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		[[nodiscard]]
		static Grid Generate(size_type w, size_type h, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		[[nodiscard]]
		static Grid Generate(Size size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>* = nullptr>
		[[nodiscard]]
		static Grid IndexedGenerate(size_type w, size_type h, Fty indexedGenerator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>* = nullptr>
		[[nodiscard]]
		static Grid IndexedGenerate(Size size, Fty indexedGenerator);

	private:

		container_type m_data;

		size_type m_width = 0;

		size_type m_height = 0;
	};

	// deduction guide
	template <class Type>
	Grid(std::initializer_list<std::initializer_list<Type>>) -> Grid<Type>;

	template <class Type>
	Grid(typename Grid<Type>::size_type, typename Grid<Type>::size_type, const Array<Type>&) -> Grid<Type>;

	template <class Type>
	Grid(typename Grid<Type>::size_type, typename Grid<Type>::size_type, Array<Type>&&) -> Grid<Type>;

	template <class Type>
	Grid(Size, const Array<Type>&) -> Grid<Type>;

	template <class Type>
	Grid(Size, Array<Type>&&) -> Grid<Type>;

	template <class Type, class Allocator>
	inline void swap(Grid<Type, Allocator>& a, Grid<Type, Allocator>& b) noexcept;
}

template <class Type, class Allocator>
struct SIV3D_HIDDEN fmt::formatter<s3d::Grid<Type, Allocator>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Grid<Type, Allocator>& value, FormatContext& ctx)
	{
		if (value.empty())
		{
			return format_to(ctx.out(), U"{{}}");
		}

		const std::u32string firstTag = (tag.empty() ? U"{{{}" : (U"{{{:" + tag + U"}"));
		const std::u32string secondTag = (tag.empty() ? U", {}" : (U", {:" + tag + U"}"));

		auto it = format_to(ctx.out(), U"{{");
		
		for (size_t y = 0; y < value.height(); ++y)
		{
			if (y != 0)
			{
				it = format_to(it, U",\n");
			}

			it = format_to(it, firstTag, value[y][0]);

			for (size_t x = 1; x < value.width(); ++x)
			{
				it = format_to(it, secondTag, value[y][x]);
			}

			it = format_to(it, U"}}");
		}
		
		it = format_to(it, U"}}");

		return it;
	}
};

# include "detail/Grid.ipp"
