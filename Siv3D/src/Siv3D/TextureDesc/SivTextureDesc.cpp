//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextureDesc.hpp>

namespace s3d
{
	namespace detail
	{
		bool IsMipped(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::Mipped)
				|| (desc == TextureDesc::MippedSRGB);
		}

		bool IsSRGB(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::UnmippedSRGB)
				|| (desc == TextureDesc::MippedSRGB);
		}
	}
}
