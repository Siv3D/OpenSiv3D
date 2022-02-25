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
# include <ostream>
# include <optional>
# include "Common.hpp"
# include "FormatData.hpp"

namespace s3d
{
	/// @brief 無効値の型
	using None_t = std::nullopt_t;

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const None_t&)
	{
		const CharType no[] = { 'n','o','n','e','\0' };
		return output << no;
	}

	inline void Formatter(FormatData& formatData, None_t)
	{
		formatData.string.append(U"none"_sv);
	}

	/// @brief 無効値
	inline constexpr None_t none = std::nullopt;
}
