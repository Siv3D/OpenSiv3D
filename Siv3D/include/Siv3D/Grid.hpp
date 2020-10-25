//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

	/// <summary>
	/// 可変長二次元配列
	/// </summary>
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

	private:

		container_type m_data;

		size_type m_width = 0;

		size_type m_height = 0;

	public:

		Grid() = default;

		Grid(const Grid&) = default;

		Grid(Grid&&) = default;

		Grid(size_type w, size_type h);

		Grid(size_type w, size_type h, const value_type& value);

		explicit Grid(Size size);

		Grid(Size size, const value_type& value);

		Grid(size_type w, size_type h, const Array<value_type>& data);

		Grid(size_type w, size_type h, Array<value_type>&& data);

		Grid(Size size, const Array<value_type>& data);

		Grid(Size size, Array<value_type>&& data);

		Grid(const std::initializer_list<std::initializer_list<value_type>>& set);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		Grid(size_type w, size_type h, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		Grid(Size size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		Grid(size_type w, size_type h, Arg::indexedGenerator_<Fty> indexedGenerator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
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
		value_type* operator[](size_t index);

		[[nodiscard]]
		const value_type* operator[](size_t index) const;

		[[nodiscard]]
		value_type& operator[](Point pos)&;

		[[nodiscard]]
		const value_type& operator[](Point pos) const&;

		[[nodiscard]]
		value_type operator[](Point pos)&&;

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
		size_type size_elements() const noexcept;

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
		auto map(Fty f) const;





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
					formatData.string.push_back(U',');

					formatData.string.push_back(U'\n');
				}

				Formatter(formatData, value[y], value[y] + value.width());
			}

			formatData.string.push_back(U'}');
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		static Grid Generate(size_type w, size_type h, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		static Grid Generate(Size size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		static Grid IndexedGenerate(size_type w, size_type h, Arg::indexedGenerator_<Fty> indexedGenerator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		static Grid IndexedGenerate(Size size, Arg::indexedGenerator_<Fty> indexedGenerator);
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
		if (tag.empty())
		{
			const s3d::String s = s3d::Format(value).replace(U"{", U"{{").replace(U"}", U"}}");
			const basic_string_view<s3d::char32> sv(s.data(), s.size());
			return format_to(ctx.out(), sv);
		}
		else
		{
			const s3d::String format = U"{:" + tag + U'}';
			const auto formatHelper = s3d::Fmt(format);
			const s3d::String s = s3d::Format(value.map([&formatHelper](const auto& e) { return formatHelper(e); })).replace(U"{", U"{{").replace(U"}", U"}}");
			const basic_string_view<s3d::char32> sv(s.data(), s.size());
			return format_to(ctx.out(), sv);
		}
	}
};

# include "detail/Grid.ipp"
