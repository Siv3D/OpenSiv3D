//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr NinePatch::Style NinePatch::Style::Default() noexcept
	{
		return{};
	}

	inline constexpr NinePatch::Style NinePatch::Style::TileTopBottom() noexcept
	{
		return{
			.tileTopBottom = true,
			.tileLeftRight = false,
			.tileCenter = false
		};
	}

	inline constexpr NinePatch::Style NinePatch::Style::TileLeftRight() noexcept
	{
		return{
			.tileTopBottom = false,
			.tileLeftRight = true,
			.tileCenter = false
		};
	}

	inline constexpr NinePatch::Style NinePatch::Style::TileCenter() noexcept
	{
		return{
			.tileTopBottom = false,
			.tileLeftRight = false,
			.tileCenter = true
		};
	}

	inline constexpr NinePatch::Style NinePatch::Style::Tile4() noexcept
	{
		return{
			.tileTopBottom = true,
			.tileLeftRight = true,
			.tileCenter = false
		};
	}

	inline constexpr NinePatch::Style NinePatch::Style::TileAll() noexcept
	{
		return{
			.tileTopBottom = true,
			.tileLeftRight = true,
			.tileCenter = true
		};
	}
}
