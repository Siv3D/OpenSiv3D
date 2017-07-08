//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "Image.hpp"
# include "Texture.hpp"

namespace s3d
{
	namespace ImageProcessing
	{
		inline constexpr uint32 CalculateMipCount(uint32 width, uint32 height)
		{
			uint32 numLevels = 1u;

			while (width > 1u && height > 1u)
			{
				width = std::max(width / 2, 1u);

				height = std::max(height / 2, 1u);

				++numLevels;
			}

			return numLevels;
		}

		inline constexpr bool IsMipped(const TextureDesc desc)
		{
			return (desc == TextureDesc::Mipped) || (desc == TextureDesc::MippedSRGB);
		}

		Array<Image> GenerateMips(const Image& src);

		Image GenerateSDF(const Image& image, const uint32 scale, const double spread = 16.0);
	}
}
