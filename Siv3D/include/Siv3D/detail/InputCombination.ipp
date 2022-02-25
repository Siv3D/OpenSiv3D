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

	inline String InputCombination::name() const
	{
		return (m_input1.name() + U'+' + m_input2.name());
	}

	inline bool InputCombination::down() const
	{
		return (m_input1.pressed() && m_input2.down());
	}

	inline bool InputCombination::pressed() const
	{
		if (m_input1.pressedDuration() < m_input2.pressedDuration())
		{
			return false;
		}

		return (m_input1.pressed() && m_input2.pressed());
	}

	inline bool InputCombination::up() const
	{
		return (m_input1.pressed() && m_input2.up());
	}

	inline Duration InputCombination::pressedDuration() const
	{
		const auto t1 = m_input1.pressedDuration();
		const auto t2 = m_input2.pressedDuration();
		const bool pr = (m_input1.pressed() && m_input2.pressed());

		if ((not pr) || (t1 < t2))
		{
			return Duration{ 0 };
		}

		return t2;
	}

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
