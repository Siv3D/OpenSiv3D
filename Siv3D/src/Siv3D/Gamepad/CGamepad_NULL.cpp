//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CGamepad_NULL.hpp"

namespace s3d
{
	CGamepad::CGamepad()
		: m_inputs{{detail::Gamepad_impl(0), detail::Gamepad_impl(1),
					detail::Gamepad_impl(2), detail::Gamepad_impl(3),
					detail::Gamepad_impl(4), detail::Gamepad_impl(5),
					detail::Gamepad_impl(6), detail::Gamepad_impl(7),
					detail::Gamepad_impl(8), detail::Gamepad_impl(9),
					detail::Gamepad_impl(10), detail::Gamepad_impl(11),
					detail::Gamepad_impl(12), detail::Gamepad_impl(13),
					detail::Gamepad_impl(14), detail::Gamepad_impl(15) }}
	{

	}

	CGamepad::~CGamepad()
	{
	
	}

	bool CGamepad::init()
	{
		LOG_INFO(U"ℹ️ Gamepad initialized");

		update(true);

		return true;
	}

	void CGamepad::update(const bool)
	{

	}

	bool CGamepad::isConnected([[maybe_unused]] const size_t userIndex) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return false;
	}

	bool CGamepad::down([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return false;
	}

	bool CGamepad::pressed([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return false;
	}

	bool CGamepad::up([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return false;
	}

	MillisecondsF CGamepad::pressedDuration([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return MillisecondsF(0.0);
	}

	Optional<int32> CGamepad::povDegree([[maybe_unused]] const size_t userIndex) const
	{
		return none;
	}

	const detail::Gamepad_impl& CGamepad::getInput(const size_t userIndex) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return m_inputs[userIndex];
	}
}

# endif
