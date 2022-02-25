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
	inline XMLReader::XMLReader(Reader&& reader, const PreserveWhitespace preserveWhitespace)
		: XMLReader{}
	{
		open(std::make_unique<Reader>(std::forward<Reader>(reader)), preserveWhitespace);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool XMLReader::open(Reader&& reader, const PreserveWhitespace preserveWhitespace)
	{
		return open(std::make_unique<Reader>(std::forward<Reader>(reader)), preserveWhitespace);
	}
}
