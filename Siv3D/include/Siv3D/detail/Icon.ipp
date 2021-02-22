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

namespace s3d
{
	inline constexpr Icon::Icon(const uint32 _code) noexcept
		: type{ Type::Awesome }
		, code{ _code } {}

	inline constexpr Icon::Icon(const Type _type, const uint32 _code) noexcept
		: type{ _type }
		, code{ _code } {}
}
