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
	inline constexpr SamplerState::SamplerState(
		const TextureAddressMode address,
		const TextureFilter filter,
		const uint8 _maxAnisotropy,
		const float _lodBias,
		const Float4 _borderColor) noexcept
		: addressU{ address }
		, addressV{ address }
		, addressW{ address }
		, min{ filter }
		, mag{ filter }
		, mip{ filter }
		, maxAnisotropy{ _maxAnisotropy }
		, lodBias{ _lodBias }
		, borderColor{ _borderColor.x, _borderColor.y, _borderColor.z, _borderColor.w } {}

	inline constexpr SamplerState::SamplerState(
		const TextureAddressMode _addressU,
		const TextureAddressMode _addressV,
		const TextureAddressMode _addressW,
		const TextureFilter _min,
		const TextureFilter _mag,
		const TextureFilter _mip,
		const uint8 _maxAnisotropy,
		const float _lodBias,
		const Float4 _borderColor) noexcept
		: addressU{ _addressU }
		, addressV{ _addressV }
		, addressW{ _addressW }
		, min{ _min }
		, mag{ _mag }
		, mip{ _mip }
		, maxAnisotropy{ _maxAnisotropy }
		, lodBias{ _lodBias }
		, borderColor{ _borderColor.x, _borderColor.y, _borderColor.z, _borderColor.w } {}

	inline SamplerState::storage_type SamplerState::asValue() const noexcept
	{
		storage_type t;
		std::memcpy(&t, this, sizeof(storage_type));
		return t;
	}

	inline bool SamplerState::operator ==(const SamplerState& other) const noexcept
	{
		return (asValue() == other.asValue());
	}

	inline bool SamplerState::operator !=(const SamplerState& other) const noexcept
	{
		return (asValue() != other.asValue());
	}

	inline constexpr SamplerState::SamplerState(const Predefined predefined) noexcept
	{
		constexpr SamplerState PredefinedStates[12] =
		{
			SamplerState{ TextureAddressMode::Repeat, TextureAddressMode::Repeat, TextureAddressMode::Repeat,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Repeat, TextureAddressMode::Repeat, TextureAddressMode::Repeat,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Repeat, TextureAddressMode::Repeat, TextureAddressMode::Repeat,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, DefaultMaxAnisotropy },


			SamplerState{ TextureAddressMode::Mirror, TextureAddressMode::Mirror, TextureAddressMode::Mirror,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Mirror, TextureAddressMode::Mirror, TextureAddressMode::Mirror,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Mirror, TextureAddressMode::Mirror, TextureAddressMode::Mirror,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, DefaultMaxAnisotropy },


			SamplerState{ TextureAddressMode::Clamp, TextureAddressMode::Clamp, TextureAddressMode::Clamp,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Clamp, TextureAddressMode::Clamp, TextureAddressMode::Clamp,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Clamp, TextureAddressMode::Clamp, TextureAddressMode::Clamp,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, DefaultMaxAnisotropy },


			SamplerState{ TextureAddressMode::Border, TextureAddressMode::Border, TextureAddressMode::Border,
							TextureFilter::Nearest, TextureFilter::Nearest, TextureFilter::Nearest },

			SamplerState{ TextureAddressMode::Border, TextureAddressMode::Border, TextureAddressMode::Border,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear },

			SamplerState{ TextureAddressMode::Border, TextureAddressMode::Border, TextureAddressMode::Border,
							TextureFilter::Linear, TextureFilter::Linear, TextureFilter::Linear, DefaultMaxAnisotropy },
		};

		*this = PredefinedStates[FromEnum(predefined)];
	}
}
