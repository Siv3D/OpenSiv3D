//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline float CalculateMaxScaling(const Mat3x2& mat)
		{
			return (Float2{ mat._11 + mat._21, mat._12 + mat._22 }.length() / Math::Sqrt2_v<float>);
		}
	}

	template <class Enum>
	class CurrentBatchStateChanges
	{
	private:

		uint64 m_states = 0;

	public:

		[[nodiscard]]
		bool has(const Enum command) const noexcept
		{
			return ((m_states & (0x1ull << FromEnum(command))) != 0);
		}

		[[nodiscard]]
		bool hasStateChange() const noexcept
		{
			return (m_states > 1);
		}

		void set(const Enum command) noexcept
		{
			m_states |= (0x1ull << FromEnum(command));
		}

		void clear(const Enum command) noexcept
		{
			m_states &= ~(0x1ull << FromEnum(command));
		}

		void clear() noexcept
		{
			m_states = 0;
		}
	};
}
