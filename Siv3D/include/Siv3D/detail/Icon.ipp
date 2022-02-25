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
	namespace detail
	{
		[[nodiscard]]
		inline constexpr Icon::Type GetIconType(const uint32 code) noexcept
		{
			if (code < 0x10000)
			{
				return Icon::Type::Awesome;
			}
			else
			{
				return Icon::Type::MaterialDesign;
			}
		}
	}

	inline constexpr Icon::Icon(const uint32 _code) noexcept
		: type{ detail::GetIconType(_code) }
		, code{ _code } {}

	inline constexpr Icon::Icon(const Type _type, const uint32 _code) noexcept
		: type{ _type }
		, code{ _code } {}

	inline namespace Literals
	{
		inline namespace IconLiterals
		{
			inline constexpr Icon operator ""_icon(unsigned long long codePoint) noexcept
			{
				return Icon{ static_cast<uint32>(codePoint) };
			}
		}
	}
}
