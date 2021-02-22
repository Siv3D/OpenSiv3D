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

namespace s3d
{
	struct Icon
	{
		enum class Type : uint32
		{
			Awesome,

			MaterialDesign,
		};

		Type type;

		uint32 code;

		explicit constexpr Icon(uint32 _code) noexcept
			: type{ Type::Awesome }
			, code{ _code } {}

		constexpr Icon(Type _type, uint32 _code) noexcept
			: type{ _type }
			, code{ _code } {}
	};
}
