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
	inline Error::Error(const char32* what)
		: m_what{ what } {}

	inline Error::Error(StringView what)
		: m_what{ what } {}

	inline Error::Error(const String& what)
		: m_what{ what } {}

	inline Error::Error(String&& what) noexcept
		: m_what{ std::move(what) } {}

	inline const String& Error::what() const noexcept
	{
		return m_what;
	}

	inline StringView Error::type() const noexcept
	{
		return StringView{ U"Error" };
	}

	inline StringView ParseError::type() const noexcept
	{
		return StringView{ U"ParseError" };
	}

	inline StringView BadOptionalAccess::type() const noexcept
	{
		return StringView{ U"Bad optional access" };
	}

	inline StringView NotImplementedError::type() const noexcept
	{
		return StringView{ U"NotImplementedError" };
	}

	inline StringView EngineError::type() const noexcept
	{
		return StringView{ U"EngineError" };
	}
}
