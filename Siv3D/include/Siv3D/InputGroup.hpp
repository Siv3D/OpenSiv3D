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
# include "Common.hpp"
# include "Array.hpp"
# include "Input.hpp"
# include "InputCombination.hpp"

namespace s3d
{
	class InputGroup
	{
	public:

		SIV3D_NODISCARD_CXX20
		InputGroup() = default;

		template <class ...Args>
		SIV3D_NODISCARD_CXX20
		InputGroup(const Args&... args)
		{
			append(args...);
		}

		[[nodiscard]]
		String name() const;

		[[nodiscard]]
		bool down() const;

		[[nodiscard]]
		bool pressed() const;

		[[nodiscard]]
		bool up() const;

		[[nodiscard]]
		Duration pressedDuration() const;

		[[nodiscard]]
		int32 num_pressed() const;

		[[nodiscard]]
		const Array<Input>& inputs() const;

		[[nodiscard]]
		const Array<InputCombination>& inputCombinations() const;

		[[nodiscard]]
		InputGroup operator |(Input other) const noexcept;

		[[nodiscard]]
		InputGroup operator |(const InputCombination& other) const noexcept;

		[[nodiscard]]
		InputGroup operator |(const InputGroup& other) const noexcept;

		[[nodiscard]]
		bool operator ==(const InputGroup& other) const;

		[[nodiscard]]
		bool operator !=(const InputGroup& other) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const InputGroup& value)
		{
			return output << value.name();
		}

		friend void Formatter(FormatData& formatData, const InputGroup& value);

	private:

		Array<Input> m_inputs;

		Array<InputCombination> m_inputCombinations;

		template <class Type, class ...Args>
		void append(const Type& input, const Args&... args);

		void append();

		void append(const Input other);

		void append(const InputCombination& other);

		void append(const InputGroup& other);
	};
}
