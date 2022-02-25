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

namespace s3d
{
	inline MatchResults::MatchResults(container&& matches) noexcept
		: m_matches{ std::move(matches) } {}

	inline MatchResults::size_type MatchResults::size() const noexcept
	{
		return m_matches.size();
	}

	inline bool MatchResults::empty() const noexcept
	{
		return m_matches.empty();
	}

	inline bool MatchResults::isEmpty() const noexcept
	{
		return m_matches.isEmpty();
	}

	inline MatchResults::operator bool() const noexcept
	{
		return (not empty());
	}

	inline MatchResults::const_reference MatchResults::operator [](const size_type index) const noexcept
	{
		return m_matches[index];
	}

	inline MatchResults::const_iterator MatchResults::begin() const noexcept
	{
		return m_matches.begin();
	}

	inline MatchResults::const_iterator MatchResults::end() const noexcept
	{
		return m_matches.end();
	}

	inline MatchResults::const_iterator MatchResults::cbegin() const noexcept
	{
		return m_matches.begin();
	}

	inline MatchResults::const_iterator MatchResults::cend() const noexcept
	{
		return m_matches.end();
	}
}
