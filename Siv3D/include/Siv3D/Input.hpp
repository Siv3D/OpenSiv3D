//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# if  __has_include(<bit>)
#	include <bit>
# endif
# include "Common.hpp"
# include "InputDevice.hpp"
# include "Duration.hpp"
# include "Formatter.hpp"

namespace s3d
{
	class InputCombination;
	class InputGroup;

	class Input
	{
	public:

		SIV3D_NODISCARD_CXX20
		Input() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Input(InputDeviceType deviceType, uint8 code, uint8 userIndex = 0) noexcept;

		[[nodiscard]]
		constexpr InputDeviceType deviceType() const noexcept;

		[[nodiscard]]
		constexpr uint8 code() const noexcept;

		[[nodiscard]]
		constexpr uint8 userIndex() const noexcept;

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
		constexpr InputCombination operator +(Input other) const noexcept;

		[[nodiscard]]
		InputGroup operator |(Input other) const;
		
		[[nodiscard]]
		InputGroup operator |(const InputCombination& other) const;

		[[nodiscard]]
		InputGroup operator |(const InputGroup& other) const;

		[[nodiscard]]
		constexpr uint32 asUint32() const noexcept;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		friend constexpr bool operator ==(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() == rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr auto operator <=>(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() <=> rhs.asUint32());
		}

	# else

		[[nodiscard]]
		friend constexpr bool operator ==(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() == rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() != rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator <(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() < rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator <=(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() <= rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator >(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() > rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator >=(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() >= rhs.asUint32());
		}

	# endif

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Input& value)
		{
			return output << value.name();
		}

		friend void Formatter(FormatData& formatData, const Input& value)
		{
			Formatter(formatData, value.name());
		}

	private:

		InputDeviceType m_deviceType = InputDeviceType::Undefined;

		uint8 m_code = 0;

		uint8 m_userIndex = 0;

		SIV3D_MAYBE_UNUSED_NSDM uint8 m_reserved = 0;
	};
}
