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

# include <Siv3D/Gamepad.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Gamepad/IGamepad.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
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

		Gamepad_impl::Gamepad_impl(const size_t _playerIndex)
			: playerIndex{ static_cast<uint32>(_playerIndex) }
			, povUp{ InputDeviceType::Gamepad, 0x80, static_cast<uint8>(_playerIndex) }
			, povDown{ InputDeviceType::Gamepad, 0x82, static_cast<uint8>(_playerIndex) }
			, povLeft{ InputDeviceType::Gamepad, 0x83, static_cast<uint8>(_playerIndex) }
			, povRight{ InputDeviceType::Gamepad, 0x81, static_cast<uint8>(_playerIndex) } {}

		bool Gamepad_impl::isConnected() const
		{
			return SIV3D_ENGINE(Gamepad)->isConnected(playerIndex);
		}

		Gamepad_impl::operator bool() const
		{
			return isConnected();
		}

		const GamepadInfo& Gamepad_impl::getInfo() const
		{
			return SIV3D_ENGINE(Gamepad)->getInfo(playerIndex);
		}

		Optional<int32> Gamepad_impl::povD8() const
		{
			if (const Optional<int32> povDegree = SIV3D_ENGINE(Gamepad)->povDegree(playerIndex))
			{
				return detail::Get8Direction(*povDegree);
			}

			return none;
		}

		const Gamepad_impl& Gamepad_helper::operator()(const size_t playerIndex) const
		{
			return SIV3D_ENGINE(Gamepad)->getInput(playerIndex);
		}
	}
}
