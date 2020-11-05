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
# include "Common.hpp"
# include "InputDevice.hpp"
# include "Duration.hpp"

namespace s3d
{
	class Input
	{
	public:

		Input() = default;

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

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		constexpr bool operator ==(const Input& other) const;

		[[nodiscard]]
		constexpr auto operator <=>(const Input& other) const;

	# else

		[[nodiscard]]
		constexpr bool operator ==(const Input& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator !=(const Input& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator <(const Input& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator <=(const Input& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator >(const Input& other) const noexcept;

		[[nodiscard]]
		constexpr bool operator >=(const Input& other) const noexcept;

	# endif

	private:

		InputDeviceType m_deviceType = InputDeviceType::Undefined;

		uint8 m_code = 0;

		uint8 m_userIndex = 0;

		[[maybe_unused]] uint8 m_reserved = 0;

		[[nodiscard]]
		constexpr uint32 asUint32() const noexcept;
	};
}

# include "detail/Input.ipp"
