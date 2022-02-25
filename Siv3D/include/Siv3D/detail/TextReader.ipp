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
	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline TextReader::TextReader(Reader&& reader, const Optional<TextEncoding>& encoding)
		: TextReader{}
	{
		open(std::forward<Reader>(reader), encoding);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool TextReader::open(Reader&& reader, const Optional<TextEncoding>& encoding)
	{
		return open(std::make_unique<Reader>(std::forward<Reader>(reader)), encoding);
	}

	inline TextReader::operator bool() const noexcept
	{
		return isOpen();
	}
}
