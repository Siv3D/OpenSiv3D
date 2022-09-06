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

# include <Siv3D/InputGroups.hpp>

namespace s3d
{
	String InputCombination::name() const
	{
		return (m_input1.name() + U'+' + m_input2.name());
	}

	bool InputCombination::down() const
	{
		return (m_input1.pressed() && m_input2.down());
	}

	bool InputCombination::pressed() const
	{
		if (m_input1.pressedDuration() < m_input2.pressedDuration())
		{
			return false;
		}

		return (m_input1.pressed() && m_input2.pressed());
	}

	bool InputCombination::up() const
	{
		return (m_input1.pressed() && m_input2.up());
	}

	Duration InputCombination::pressedDuration() const
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

	InputGroup InputCombination::operator |(const Input other) const
	{
		return InputGroup{ *this, other };
	}

	InputGroup InputCombination::operator |(const InputCombination& other) const
	{
		return InputGroup{ *this, other };
	}

	InputGroup InputCombination::operator |(const InputGroup& other) const
	{
		return InputGroup{ *this, other };
	}

	void Formatter(FormatData& formatData, const InputCombination& value)
	{
		Formatter(formatData, value.name());
	}
}
