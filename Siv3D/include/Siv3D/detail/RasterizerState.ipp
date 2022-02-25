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
	inline constexpr RasterizerState::RasterizerState(
		const FillMode _fillMode,
		const CullMode _cullMode,
		const bool _scissorEnable,
		const bool _antialiasedLine3D,
		const int32 _depthBias
	)
		: fillMode{ _fillMode }
		, cullMode{ _cullMode }
		, scissorEnable{ _scissorEnable }
		, antialiasedLine3D{ _antialiasedLine3D }
		, depthBias{ _depthBias } {}

	inline RasterizerState::storage_type RasterizerState::asValue() const noexcept
	{
	# if __cpp_lib_bit_cast
		return std::bit_cast<storage_type>(*this);
	# else
		storage_type t;
		std::memcpy(&t, this, sizeof(storage_type));
		return t;
	# endif
	}

	inline bool RasterizerState::operator ==(const RasterizerState& other) const noexcept
	{
		return (asValue() == other.asValue());
	}

	inline bool RasterizerState::operator !=(const RasterizerState& other) const noexcept
	{
		return (asValue() != other.asValue());
	}

	inline constexpr RasterizerState::RasterizerState(const Predefined predefined) noexcept
	{
		constexpr RasterizerState PredefinedStates[14] =
		{
			RasterizerState{ FillMode::Solid,		CullMode::Back },	// SolidCullBack
			RasterizerState{ FillMode::Solid,		CullMode::Front },	// SolidCullFront
			RasterizerState{ FillMode::Solid,		CullMode::Off },	// SolidCullNone
			RasterizerState{ FillMode::Wireframe,	CullMode::Back },	// WireframeCullBack
			RasterizerState{ FillMode::Wireframe,	CullMode::Front },	// WireframeCullFront
			RasterizerState{ FillMode::Wireframe,	CullMode::Off },	// WireframeCullNone
			RasterizerState{ FillMode::Solid,		CullMode::Off, false, true },	// AntialiasedLine3D
			RasterizerState{ FillMode::Solid,		CullMode::Back, true },			// SolidCullBackScissor
			RasterizerState{ FillMode::Solid,		CullMode::Front, true },		// SolidCullFrontScissor
			RasterizerState{ FillMode::Solid,		CullMode::Off, true },			// SolidCullNoneScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Back, true },			// WireframeCullBackScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Front, true },		// WireframeCullFrontScissor
			RasterizerState{ FillMode::Wireframe,	CullMode::Off, true },			// WireframeCullNoneScissor
			RasterizerState{ FillMode::Solid,		CullMode::Off, true, true },	// AntialiasedLine3DScissor
		};

		*this = PredefinedStates[FromEnum(predefined)];
	}
}
