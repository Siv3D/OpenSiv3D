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

		Type type = Type::Awesome;

		uint32 code = 0;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Icon(uint32 _code) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Icon(Type _type, uint32 _code) noexcept;
	};
}

# include "detail/Icon.ipp"
