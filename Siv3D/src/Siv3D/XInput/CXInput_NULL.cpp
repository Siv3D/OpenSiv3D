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

# include "CXInput.hpp"

namespace s3d
{
	CXInput::CXInput()
		: m_inputs{ detail::XInput_impl(0), detail::XInput_impl(1),
					detail::XInput_impl(2), detail::XInput_impl(3) }
	{

	}

	CXInput::~CXInput()
	{
	
	}

	bool CXInput::init()
	{
		return true;
	}

	void CXInput::update(const bool)
	{

	}

	bool CXInput::isConnected([[maybe_unused]] const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return false;
	}

	void CXInput::setDeadZone([[maybe_unused]] const size_t userIndex, const DeadZoneIndex, const DeadZone&)
	{
		assert(userIndex < XInput.MaxUserCount);
	}

	void CXInput::setVibration([[maybe_unused]] const size_t userIndex, const double, const double)
	{
		assert(userIndex < XInput.MaxUserCount);
	}

	std::pair<double, double> CXInput::getVibration([[maybe_unused]] const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return{ 0.0, 0.0 };
	}

	void CXInput::pauseVibration([[maybe_unused]] const size_t userIndex)
	{
		assert(userIndex < XInput.MaxUserCount);
	}

	void CXInput::resumeVibration([[maybe_unused]] const size_t userIndex)
	{
		assert(userIndex < XInput.MaxUserCount);
	}

	bool CXInput::down([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return false;
	}

	bool CXInput::pressed([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return false;
	}

	bool CXInput::up([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return false;
	}

	MillisecondsF CXInput::pressedDuration([[maybe_unused]] const size_t userIndex, const uint32) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return MillisecondsF(0.0);
	}

	const detail::XInput_impl& CXInput::getInput(const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_inputs[userIndex];
	}
}

# endif
