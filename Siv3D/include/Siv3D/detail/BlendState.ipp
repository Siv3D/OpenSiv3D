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

namespace s3d
{
	inline constexpr BlendState::BlendState(
		const bool _enable,
		const Blend _src,
		const Blend _dst,
		const BlendOp _op,
		const Blend _srcAlpha,
		const Blend _dstAlpha,
		const BlendOp _opAlpha,
		const bool _alphaToCoverageEnable,
		const bool _writeR,
		const bool _writeG,
		const bool _writeB,
		const bool _writeA
	) noexcept
		: enable(_enable)
		, writeR(_writeR)
		, writeG(_writeG)
		, src(_src)
		, dst(_dst)
		, op(_op)
		, alphaToCoverageEnable(_alphaToCoverageEnable)
		, writeB(_writeB)
		, writeA(_writeA)
		, srcAlpha(_srcAlpha)
		, dstAlpha(_dstAlpha)
		, opAlpha(_opAlpha) {}

	inline constexpr BlendState::BlendState(const Predefined predefined) noexcept
	{
		constexpr BlendState PredefinedStates[7] =
		{
			BlendState{ true },																// NonPremultiplied
			BlendState{ true, Blend::One },													// Premultiplied
			BlendState{ false },															// Opaque
			BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::Add },			// Additive
			BlendState{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::RevSubtract },	// Subtractive
			BlendState{ true, Blend::Zero,		Blend::SrcColor,	BlendOp::Add },			// Multiplicative
			BlendState{ true, Blend::DestColor,	Blend::SrcColor,	BlendOp::Add },			// Multiplicative2X
		};

		*this = PredefinedStates[FromEnum(predefined)];
	}

	inline BlendState::storage_type BlendState::asValue() const noexcept
	{
	# if __cpp_lib_bit_cast
		return std::bit_cast<storage_type>(*this);
	# else
		storage_type t;
		std::memcpy(&t, this, sizeof(storage_type));
		return t;
	# endif
	}

	inline bool BlendState::operator ==(const BlendState& other) const noexcept
	{
		return (asValue() == other.asValue());
	}

	inline bool BlendState::operator !=(const BlendState& other) const noexcept
	{
		return (asValue() != other.asValue());
	}
}
