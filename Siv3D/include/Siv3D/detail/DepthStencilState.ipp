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
	inline constexpr DepthStencilState::DepthStencilState(
		const bool _depthEnable,
		const bool _depthWriteEnable,
		const DepthFunc _depthFunc
	)
		: depthEnable{ _depthEnable }
		, depthWriteEnable{ _depthWriteEnable }
		, depthFunc{ _depthFunc } {}

	inline DepthStencilState::storage_type DepthStencilState::asValue() const noexcept
	{
	# if __cpp_lib_bit_cast
		return std::bit_cast<storage_type>(*this);
	# else
		storage_type t;
		std::memcpy(&t, this, sizeof(storage_type));
		return t;
	# endif
	}

	inline bool DepthStencilState::operator ==(const DepthStencilState& other) const noexcept
	{
		return (asValue() == other.asValue());
	}

	inline bool DepthStencilState::operator !=(const DepthStencilState& other) const noexcept
	{
		return (asValue() != other.asValue());
	}

	inline constexpr DepthStencilState::DepthStencilState(const Predefined predefined) noexcept
	{
		constexpr DepthStencilState PredefinedStates[3] =
		{
			DepthStencilState{ false, false, DepthFunc::Always },	// Disbaled
			DepthStencilState{ true, false, DepthFunc::GreaterEqual },	// DepthTest
			DepthStencilState{ true, true, DepthFunc::GreaterEqual },	// DepthTestWrite
		};

		*this = PredefinedStates[FromEnum(predefined)];
	}
}
