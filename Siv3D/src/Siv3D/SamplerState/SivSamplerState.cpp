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

# include <Siv3D/SamplerState.hpp>

namespace s3d
{
	SamplerState::SamplerState(const Predefined predefined)
	{
		static const SamplerState predefinedStates[12] =
		{
			SamplerState{ TextureAddressMode::Repeat, TextureAddressMode::Repeat, TextureAddressMode::Repeat,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Repeat, TextureAddressMode::Repeat, TextureAddressMode::Repeat,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Repeat, TextureAddressMode::Repeat, TextureAddressMode::Repeat,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, 16 },


			SamplerState{ TextureAddressMode::Mirror, TextureAddressMode::Mirror, TextureAddressMode::Mirror,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Mirror, TextureAddressMode::Mirror, TextureAddressMode::Mirror,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Mirror, TextureAddressMode::Mirror, TextureAddressMode::Mirror,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, 16 },


			SamplerState{ TextureAddressMode::Clamp, TextureAddressMode::Clamp, TextureAddressMode::Clamp,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Clamp, TextureAddressMode::Clamp, TextureAddressMode::Clamp,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Clamp, TextureAddressMode::Clamp, TextureAddressMode::Clamp,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, 16 },


			SamplerState{ TextureAddressMode::Border, TextureAddressMode::Border, TextureAddressMode::Border,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Border, TextureAddressMode::Border, TextureAddressMode::Border,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Border, TextureAddressMode::Border, TextureAddressMode::Border,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, 16 },
		};
		
		*this = predefinedStates[static_cast<size_t>(predefined)];
	}
}
