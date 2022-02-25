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
	namespace ImageProcessing
	{
		inline constexpr size_t CalculateMipCount(uint32 width, uint32 height) noexcept
		{
			size_t numLevels = 1;

			while ((1u < width) && (1u < height))
			{
				width	= Max(width / 2, 1u);
				height	= Max(height / 2, 1u);
				++numLevels;
			}

			return numLevels;
		}
	}
}
