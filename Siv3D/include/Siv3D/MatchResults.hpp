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
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	class MatchResults
	{
	public:

		using container			= Array<StringView>;
		using value_type		= StringView;
		using const_reference	= const value_type&;
		using reference			= value_type&;
		using const_iterator	= typename container::const_iterator;
		using iterator			= const_iterator;
		using difference_type	= StringView::difference_type;
		using size_type			= typename container::size_type;
		using allocator_type	= typename container::allocator_type;
		using char_type			= StringView::value_type;
		using string_type		= String;

		SIV3D_NODISCARD_CXX20
		MatchResults() = default;

		SIV3D_NODISCARD_CXX20
		explicit MatchResults(container&& matches) noexcept;

		[[nodiscard]]
		size_type size() const noexcept;

		[[nodiscard]]
		bool empty() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		const_reference operator [](size_type index) const noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

	private:

		container m_matches;
	};
}

# include "detail/MatchResults.ipp"
