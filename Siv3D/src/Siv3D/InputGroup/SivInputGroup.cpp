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

# include <Siv3D/InputGroups.hpp>

namespace s3d
{
	String InputGroup::name() const
	{
		return (m_inputs.join(U"|") + m_inputCombinations.join(U"|"));
	}

	bool InputGroup::down() const
	{
		return (m_inputs.any([](const Input& i) { return i.down(); })
			|| m_inputCombinations.any([](const InputCombination& c) { return c.down(); }));
	}

	bool InputGroup::pressed() const
	{
		return (m_inputs.any([](const Input& i) { return i.pressed(); })
			|| m_inputCombinations.any([](const InputCombination& c) { return c.pressed(); }));
	}

	bool InputGroup::up() const
	{
		return (m_inputs.any([](const Input& i) { return i.up(); })
			|| m_inputCombinations.any([](const InputCombination& c) { return c.up(); }));
	}

	Duration InputGroup::pressedDuration() const
	{
		Duration duration{ 0 };

		for (const auto& input : m_inputs)
		{
			duration = Max(input.pressedDuration(), duration);
		}

		for (const auto& inputCombination : m_inputCombinations)
		{
			duration = Max(inputCombination.pressedDuration(), duration);
		}

		return duration;
	}

	int32 InputGroup::num_pressed() const
	{
		int32 num = 0;

		for (const auto& input : m_inputs)
		{
			num += input.pressed();
		}

		for (const auto& inputCombination : m_inputCombinations)
		{
			num += inputCombination.pressed();
		}

		return num;
	}
}
