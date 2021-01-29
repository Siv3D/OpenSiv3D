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
# include "Array.hpp"
# include "Image.hpp"

namespace s3d
{
	namespace ImageProcessing
	{
		[[nodiscard]]
		inline constexpr size_t CalculateMipCount(uint32 width, uint32 height) noexcept;

		[[nodiscard]]
		Array<Image> GenerateMips(const Image& src);
	}
}

# include "detail/ImageProcessing.ipp"
