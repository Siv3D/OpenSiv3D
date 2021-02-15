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
	struct TextStyle
	{
		struct Parameters
		{
			bool customShader;
		};

		bool customShader = false;

		constexpr TextStyle() = default;

		SIV3D_NODISCARD_CXX20
		constexpr TextStyle(const Parameters& params) noexcept;

		static constexpr Parameters Default{ false };

		static constexpr Parameters CustomShader{ true };
	};
}

# include "detail/TextStyle.ipp"
