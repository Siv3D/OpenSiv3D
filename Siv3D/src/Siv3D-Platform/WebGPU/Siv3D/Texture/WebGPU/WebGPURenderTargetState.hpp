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

# include <Siv3D/Common.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
    struct WebGPURenderTargetState
    {
        using storage_type = uint32;

        uint8 renderTargetFormat : 8 = FromEnum(wgpu::TextureFormat::RGBA8Unorm);

        uint8 sampleCount : 8 = 1;

        bool hasDepth : 1 = false;

        bool hasAlpha : 1 = true;

        [[nodiscard]]
		storage_type asValue() const noexcept;

        [[nodiscard]]
		bool operator ==(const WebGPURenderTargetState& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const WebGPURenderTargetState& other) const noexcept;
    };

    inline WebGPURenderTargetState::storage_type WebGPURenderTargetState::asValue() const noexcept
	{
	# if __cpp_lib_bit_cast
		return std::bit_cast<storage_type>(*this);
	# else
		storage_type t;
		std::memcpy(&t, this, sizeof(storage_type));
		return t;
	# endif
	}

	inline bool WebGPURenderTargetState::operator ==(const WebGPURenderTargetState& other) const noexcept
	{
		return (asValue() == other.asValue());
	}

	inline bool WebGPURenderTargetState::operator !=(const WebGPURenderTargetState& other) const noexcept
	{
		return (asValue() != other.asValue());
	}
}

template <>
struct std::hash<s3d::WebGPURenderTargetState>
{
	[[nodiscard]]
	size_t operator()(const s3d::WebGPURenderTargetState& value) const noexcept
	{
		return hash<s3d::WebGPURenderTargetState::storage_type>()(value.asValue());
	}
};
