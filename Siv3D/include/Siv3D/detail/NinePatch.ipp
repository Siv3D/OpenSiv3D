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

	inline constexpr Rect NinePatch::PatchSize::topLeftRect() const noexcept
	{
		return{ 0, 0, left, top };
	}

	inline constexpr Rect NinePatch::PatchSize::topRect() const noexcept
	{
		return{ left, 0, (textureSize.x - left - right), top};
	}

	inline constexpr Rect NinePatch::PatchSize::topRightRect() const noexcept
	{
		return{ (textureSize.x - right), 0, right, top };
	}

	inline constexpr Rect NinePatch::PatchSize::leftRect() const noexcept
	{
		return{ 0, top, left, (textureSize.y - top - bottom) };
	}

	inline constexpr Rect NinePatch::PatchSize::centerRect() const noexcept
	{
		return{ left, top, (textureSize.x - left - right), (textureSize.y - top - bottom) };
	}

	inline constexpr Rect NinePatch::PatchSize::rightRect() const noexcept
	{
		return{ (textureSize.x - right), top, right, (textureSize.y - top - bottom) };
	}

	inline constexpr Rect NinePatch::PatchSize::bottomLeftRect() const noexcept
	{
		return{ 0, (textureSize.y - bottom), left, bottom };
	}

	inline constexpr Rect NinePatch::PatchSize::bottomRect() const noexcept
	{
		return{ left, (textureSize.y - bottom), (textureSize.x - left - right), bottom };
	}

	inline constexpr Rect NinePatch::PatchSize::bottomRightRect() const noexcept
	{
		return{ (textureSize.x - right), (textureSize.y - bottom), right, bottom };
	}
}
