//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr TriangleIndex TriangleIndex::Zero() noexcept
	{
		return{ 0, 0, 0 };
	}

	inline constexpr TriangleIndex32 TriangleIndex32::Zero() noexcept
	{
		return{ 0, 0, 0 };
	}
}
