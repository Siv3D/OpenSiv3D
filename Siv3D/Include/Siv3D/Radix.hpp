//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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

		constexpr Radix() = default;

		explicit constexpr Radix(uint32 value)
			: m_value(value) {}

		explicit constexpr Radix(unspecified_t)
			: m_value(0) {}

		constexpr uint32 value() const
		{
			return m_value;
		}

		constexpr bool is2() const
		{
			return m_value == 2;
		}

		constexpr bool is8() const
		{
			return m_value == 8;
		}

		constexpr bool is10() const
		{
			return m_value == 10;
		}

		constexpr bool is16() const
		{
			return m_value == 16;
		}
	};
}
