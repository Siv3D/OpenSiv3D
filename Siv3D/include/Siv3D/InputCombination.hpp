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
# include "Input.hpp"

namespace s3d
{
	class InputGroup;

	class InputCombination
	{
	public:

		SIV3D_NODISCARD_CXX20
		InputCombination() = default;

		SIV3D_NODISCARD_CXX20
		constexpr InputCombination(Input input1, Input input2) noexcept;

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
		constexpr const Input& input1() const noexcept;

		[[nodiscard]]
		constexpr const Input& input2() const noexcept;

		[[nodiscard]]
		InputGroup operator |(Input other) const;

		[[nodiscard]]
		InputGroup operator |(const InputCombination& other) const;

		[[nodiscard]]
		InputGroup operator |(const InputGroup& other) const;

		[[nodiscard]]
		constexpr uint64 asUint64() const noexcept;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		friend constexpr bool operator ==(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() == rhs.asUint64());
		}

		[[nodiscard]]
		friend constexpr auto operator <=>(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() <=> rhs.asUint64());
		}

	# else

		[[nodiscard]]
		friend constexpr bool operator ==(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() == rhs.asUint64());
		}

		[[nodiscard]]
		friend constexpr bool operator !=(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() != rhs.asUint64());
		}

		[[nodiscard]]
		friend constexpr bool operator <(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() < rhs.asUint64());
		}

		[[nodiscard]]
		friend constexpr bool operator <=(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() <= rhs.asUint64());
		}

		[[nodiscard]]
		friend constexpr bool operator >(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() > rhs.asUint64());
		}

		[[nodiscard]]
		friend constexpr bool operator >=(InputCombination lhs, InputCombination rhs) noexcept
		{
			return (lhs.asUint64() >= rhs.asUint64());
		}

	# endif

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const InputCombination& value)
		{
			return output << value.name();
		}

		friend void Formatter(FormatData& formatData, const InputCombination& value);

	private:

		Input m_input1, m_input2;
	};
}
