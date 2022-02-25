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
	inline SVG::SVG(Reader&& reader)
		: SVG{}
	{
		load(std::forward<Reader>(reader));
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool SVG::load(Reader&& reader)
	{
		return load(std::make_unique<Reader>(std::forward<Reader>(reader)));
	}

	inline SVG::operator bool() const noexcept
	{
		return (not isEmpty());
	}
}
