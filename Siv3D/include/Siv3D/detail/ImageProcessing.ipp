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
	namespace ImageProcessing
	{
		inline constexpr size_t CalculateMipCount(size_t width, size_t height) noexcept
		{
			size_t numLevels = 1;

			while ((1 < width) && (1 < height))
			{
				width	= Max<size_t>((width / 2), 1);
				height	= Max<size_t>((height / 2), 1);
				++numLevels;
			}

			return numLevels;
		}
	}
}
