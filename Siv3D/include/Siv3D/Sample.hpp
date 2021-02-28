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
# include "Array.hpp"
# include "Random.hpp"

namespace s3d
{
	template <class Iterator, class URBG>
	[[nodiscard]]
	inline auto Sample(Iterator begin, Iterator end, URBG&& urbg);

	template <class Iterator>
	[[nodiscard]]
	inline auto Sample(Iterator begin, Iterator end);

	template <class Iterator, class URBG>
	[[nodiscard]]
	inline auto Sample(size_t n, Iterator begin, Iterator end, URBG&& urbg);

	template <class Iterator>
	[[nodiscard]]
	inline auto Sample(size_t n, Iterator begin, Iterator end);

	template <class Container, class URBG>
	[[nodiscard]]
	inline auto Sample(const Container& c, URBG&& urbg);

	template <class Container>
	[[nodiscard]]
	inline auto Sample(const Container& c);

	template <class Container, class URBG>
	[[nodiscard]]
	inline auto Sample(size_t n, const Container& c, URBG&& urbg);

	template <class Container>
	[[nodiscard]]
	inline auto Sample(size_t n, const Container& c);

	template <class Type, class URBG>
	[[nodiscard]]
	inline auto Sample(std::initializer_list<Type> ilist, URBG&& urbg);

	template <class Type>
	[[nodiscard]]
	inline auto Sample(std::initializer_list<Type> ilist);

	template <class Type, class URBG>
	[[nodiscard]]
	inline auto Sample(size_t n, std::initializer_list<Type> ilist, URBG&& urbg);

	template <class Type>
	[[nodiscard]]
	inline auto Sample(size_t n, std::initializer_list<Type> ilist);
}

# include "detail/Sample.ipp"
