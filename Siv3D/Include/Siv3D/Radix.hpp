//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	class Radix
	{
	private:

		uint32 m_value = 10;

		struct unspecified_t {};

	public:

		static constexpr unspecified_t Unspecified{};

		constexpr Radix(uint32 value = 10) noexcept
			: m_value(value) {}

        constexpr Radix(unspecified_t) noexcept
			: m_value(0) {}

		constexpr uint32 value() const noexcept
		{
			return m_value;
		}

		constexpr bool is2() const noexcept
		{
			return m_value == 2;
		}

		constexpr bool is8() const noexcept
		{
			return m_value == 8;
		}

		constexpr bool is10() const noexcept
		{
			return m_value == 10;
		}

		constexpr bool is16() const noexcept
		{
			return m_value == 16;
		}
	};
}
