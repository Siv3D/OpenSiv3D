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

# include "CXInput_Null.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CXInput_Null::CXInput_Null()
		: m_inputs{ { detail::XInput_impl{ 0 },
					  detail::XInput_impl{ 1 },
					  detail::XInput_impl{ 2 },
					  detail::XInput_impl{ 3 }} } {}

	CXInput_Null::~CXInput_Null()
	{
		LOG_SCOPED_TRACE(U"CXInput_Null::~CXInput_Null()");
	}

	void CXInput_Null::init()
	{
		LOG_SCOPED_TRACE(U"CXInput_Null::init()");
	}

	void CXInput_Null::update(bool)
	{
		for (auto& state : m_states)
		{
			for (auto& button : state.buttons)
			{
				button.update(false);
			}
		}
	}

	bool CXInput_Null::isConnected([[maybe_unused]] const uint32 playerIndex) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return false;
	}

	void CXInput_Null::setDeadZone([[maybe_unused]] const uint32 playerIndex, DeadZoneIndex, const DeadZone&)
	{
		assert(playerIndex < XInput.MaxPlayerCount);
	}

	void CXInput_Null::setVibration([[maybe_unused]] const uint32 playerIndex, const XInputVibration&)
	{
		assert(playerIndex < XInput.MaxPlayerCount);
	}

	const XInputVibration& CXInput_Null::getVibration([[maybe_unused]] const uint32 playerIndex) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].vibration;
	}

	void CXInput_Null::pauseVibration([[maybe_unused]] const uint32 playerIndex)
	{
		assert(playerIndex < XInput.MaxPlayerCount);
	}

	void CXInput_Null::resumeVibration([[maybe_unused]] const uint32 playerIndex)
	{
		assert(playerIndex < XInput.MaxPlayerCount);
	}

	bool CXInput_Null::down([[maybe_unused]] const uint32 playerIndex, uint32) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return false;
	}

	bool CXInput_Null::pressed([[maybe_unused]] const uint32 playerIndex, uint32) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return false;
	}

	bool CXInput_Null::up([[maybe_unused]] const uint32 playerIndex, uint32) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return false;
	}

	void CXInput_Null::clearInput(const uint32 playerIndex, const uint32 index)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].clearInput();
	}

	bool CXInput_Null::cleared(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].cleared();
	}

	Duration CXInput_Null::pressedDuration([[maybe_unused]] const uint32 playerIndex, uint32) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return Duration{ 0.0 };
	}

	const detail::XInput_impl& CXInput_Null::getInput(const uint32 playerIndex) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_inputs[playerIndex];
	}
}
