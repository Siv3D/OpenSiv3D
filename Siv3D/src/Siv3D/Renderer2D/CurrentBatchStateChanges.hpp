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
# include <Siv3D/Common.hpp>

namespace s3d
{
	template <class Enum>
	class CurrentBatchStateChanges
	{
	private:

		uint32 m_states = 0;

	public:

		[[nodiscard]]
		bool has(const Enum command) const noexcept
		{
			return ((m_states & (0x1 << FromEnum(command))) != 0);
		}

		[[nodiscard]]
		bool hasStateChange() const noexcept
		{
			return (m_states > 1);
		}

		void set(const Enum command) noexcept
		{
			m_states |= (0x1u << FromEnum(command));
		}

		void clear(const Enum command) noexcept
		{
			m_states &= ~(0x1u << FromEnum(command));
		}

		void clear() noexcept
		{
			m_states = 0;
		}
	};
}
