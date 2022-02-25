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
	inline const Array<Input>& InputGroup::inputs() const
	{
		return m_inputs;
	}

	inline const Array<InputCombination>& InputGroup::inputCombinations() const
	{
		return m_inputCombinations;
	}

	inline InputGroup InputGroup::operator |(const Input other) const noexcept
	{
		return InputGroup{ *this, other };
	}

	inline InputGroup InputGroup::operator |(const InputCombination& other) const noexcept
	{
		return InputGroup{ *this, other };
	}

	inline InputGroup InputGroup::operator |(const InputGroup& other) const noexcept
	{
		return InputGroup{ *this, other };
	}

	inline bool InputGroup::operator ==(const InputGroup& other) const
	{
		return (m_inputs == other.m_inputs)
			&& (m_inputCombinations == other.m_inputCombinations);
	}

	inline bool InputGroup::operator !=(const InputGroup& other) const
	{
		return (m_inputs != other.m_inputs)
			|| (m_inputCombinations != other.m_inputCombinations);
	}

	template <class Type, class ...Args>
	inline void InputGroup::append(const Type& input, const Args&... args)
	{
		append(input);
		append(args...);
	}

	inline void InputGroup::append()
	{
		// do nothing
	}

	inline void InputGroup::append(const Input other)
	{
		(m_inputs << other).sort_and_unique();
	}

	inline void InputGroup::append(const InputCombination& other)
	{
		(m_inputCombinations << other).sort_and_unique();
	}

	inline void InputGroup::append(const InputGroup& other)
	{
		m_inputs.append(other.m_inputs).sort_and_unique();
		m_inputCombinations.append(other.m_inputCombinations).sort_and_unique();
	}
}
