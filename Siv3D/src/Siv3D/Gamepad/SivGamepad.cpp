//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Gamepad.hpp>
# include <Siv3D/Point.hpp>
# include <Siv3DEngine.hpp>
# include "IGamepad.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr int32 Get8Direction(const double deg)
		{
			if (deg <= 22.5)
				return 0;
			else if (deg <= 67.5)
				return 1;
			else if (deg <= 112.5)
				return 2;
			else if (deg <= 157.5)
				return 3;
			else if (deg <= 202.5)
				return 4;
			else if (deg <= 247.5)
				return 5;
			else if (deg <= 292.5)
				return 6;
			else if (deg <= 337.5)
				return 7;
			else
				return 0;
		}

		Gamepad_impl::Gamepad_impl(const size_t _userIndex)
			: userIndex(static_cast<uint32>(_userIndex))
			, axes(2, 0.0)
			, povUp(InputDevice::Gamepad, 0x80, static_cast<uint8>(userIndex))
			, povDown(InputDevice::Gamepad, 0x82, static_cast<uint8>(userIndex))
			, povLeft(InputDevice::Gamepad, 0x83, static_cast<uint8>(userIndex))
			, povRight(InputDevice::Gamepad, 0x81, static_cast<uint8>(userIndex))
		{

		}

		bool Gamepad_impl::isConnected() const
		{
			return Siv3DEngine::Get<ISiv3DGamepad>()->isConnected(userIndex);
		}

		Gamepad_impl::operator bool() const
		{
			return isConnected();
		}

		const GamepadInfo& Gamepad_impl::getInfo() const
		{
			return Siv3DEngine::Get<ISiv3DGamepad>()->getInfo(userIndex);
		}

		Optional<int32> Gamepad_impl::povD8() const
		{
			if (const Optional<int32> povDegree = Siv3DEngine::Get<ISiv3DGamepad>()->povDegree(userIndex))
			{
				return detail::Get8Direction(povDegree.value());
			}

			return none;
		}

		const Gamepad_impl& Gamepad_helper::operator()(const size_t userIndex) const
		{
			return Siv3DEngine::Get<ISiv3DGamepad>()->getInput(userIndex);
		}
	}
}
