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
	inline constexpr InputCombination::InputCombination(const Input input1, const Input input2) noexcept
		: m_input1{ input1 }
		, m_input2{ input2 } {}

	inline constexpr const Input& InputCombination::input1() const noexcept
	{
		return m_input1;
	}

	inline constexpr const Input& InputCombination::input2() const noexcept
	{
		return m_input2;
	}

	inline constexpr uint64 InputCombination::asUint64() const noexcept
	{
	# if __cpp_lib_bit_cast
		return std::bit_cast<uint64>(*this);
	# else
		return ((uint64(m_input1.asUint32()) << 32) | m_input2.asUint32());
	# endif
	}
}
