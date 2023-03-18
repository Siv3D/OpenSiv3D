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

# include <Siv3D/XInput.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/XInput/IXInput.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr int32 Get4Direction(const double angle) noexcept
		{
			const double deg = Math::ToDegrees(angle);

			if (deg <= -145.0)
				return 2;
			else if (deg <= -45.0)
				return 3;
			else if (deg <= 45.0)
				return 0;
			else if (deg <= 135.0)
				return 1;
			else
				return 2;
		}

		static constexpr int32 Get8Direction(const double angle) noexcept
		{
			const double deg = Math::ToDegrees(angle);

			if (deg <= -157.5)
				return 4;
			else if (deg <= -112.5)
				return 5;
			else if (deg <= -67.5)
				return 6;
			else if (deg <= -22.5)
				return 7;
			else if (deg <= 22.5)
				return 0;
			else if (deg <= 67.5)
				return 1;
			else if (deg <= 112.5)
				return 2;
			else if (deg <= 157.5)
				return 3;
			else
				return 4;
		}

		XInput_impl::XInput_impl(const size_t _playerIndex) noexcept
			: playerIndex{ static_cast<uint32>(_playerIndex) }
			, buttonUp{ InputDeviceType::XInput, 0, static_cast<uint8>(_playerIndex) }
			, buttonDown{ InputDeviceType::XInput, 1, static_cast<uint8>(_playerIndex) }
			, buttonLeft{ InputDeviceType::XInput, 2, static_cast<uint8>(_playerIndex) }
			, buttonRight{ InputDeviceType::XInput, 3, static_cast<uint8>(_playerIndex) }
			, buttonStart{ InputDeviceType::XInput, 4, static_cast<uint8>(_playerIndex) }
			, buttonMenu{ InputDeviceType::XInput, 4, static_cast<uint8>(_playerIndex) }
			, buttonBack{ InputDeviceType::XInput, 5, static_cast<uint8>(_playerIndex) }
			, buttonView{ InputDeviceType::XInput, 5, static_cast<uint8>(_playerIndex) }
			, buttonLThumb{ InputDeviceType::XInput, 6, static_cast<uint8>(_playerIndex) }
			, buttonRThumb{ InputDeviceType::XInput, 7, static_cast<uint8>(_playerIndex) }
			, buttonLB{ InputDeviceType::XInput, 8, static_cast<uint8>(_playerIndex) }
			, buttonRB{ InputDeviceType::XInput, 9, static_cast<uint8>(_playerIndex) }
			, buttonA{ InputDeviceType::XInput, 12, static_cast<uint8>(_playerIndex) }
			, buttonB{ InputDeviceType::XInput, 13, static_cast<uint8>(_playerIndex) }
			, buttonX{ InputDeviceType::XInput, 14, static_cast<uint8>(_playerIndex) }
			, buttonY{ InputDeviceType::XInput, 15, static_cast<uint8>(_playerIndex) }
			, leftTrigger{ 0.0 }
			, rightTrigger{ 0.0 }
			, leftThumbX{ 0.0 }
			, leftThumbY{ 0.0 }
			, rightThumbX{ 0.0 }
			, rightThumbY{ 0.0 } {}

		bool XInput_impl::isConnected() const
		{
			return SIV3D_ENGINE(XInput)->isConnected(playerIndex);
		}

		XInput_impl::operator bool() const
		{
			return isConnected();
		}

		void XInput_impl::setLeftTriggerDeadZone(const DeadZone& deadZone)
		{
			SIV3D_ENGINE(XInput)->setDeadZone(playerIndex, DeadZoneIndex::LefTrigger, deadZone);
		}

		void XInput_impl::setRightTriggerDeadZone(const DeadZone& deadZone)
		{
			SIV3D_ENGINE(XInput)->setDeadZone(playerIndex, DeadZoneIndex::RightTrigger, deadZone);
		}

		void XInput_impl::setLeftThumbDeadZone(const DeadZone& deadZone)
		{
			SIV3D_ENGINE(XInput)->setDeadZone(playerIndex, DeadZoneIndex::LeftThumb, deadZone);
		}

		void XInput_impl::setRightThumbDeadZone(const DeadZone& deadZone)
		{
			SIV3D_ENGINE(XInput)->setDeadZone(playerIndex, DeadZoneIndex::RightThumb, deadZone);
		}

		Optional<int32> XInput_impl::leftThumbD4(const double threshold) const
		{
			const Circular circular{ Vec2{ leftThumbX, -leftThumbY} };

			if (circular.r < threshold)
			{
				return none;
			}

			return Get4Direction(circular.theta);
		}

		Optional<int32> XInput_impl::leftThumbD8(const double threshold) const
		{
			const Circular circular{ Vec2{ leftThumbX, -leftThumbY} };

			if (circular.r < threshold)
			{
				return none;
			}

			return Get8Direction(circular.theta);
		}

		Optional<int32> XInput_impl::rightThumbD4(const double threshold) const
		{
			const Circular circular{ Vec2{ rightThumbX, -rightThumbY} };

			if (circular.r < threshold)
			{
				return none;
			}

			return Get4Direction(circular.theta);
		}

		Optional<int32> XInput_impl::rightThumbD8(const double threshold) const
		{
			const Circular circular{ Vec2{ rightThumbX, -rightThumbY} };

			if (circular.r < threshold)
			{
				return none;
			}

			return Get8Direction(circular.theta);
		}

		void XInput_impl::setVibration(const XInputVibration& vibration) const
		{
			SIV3D_ENGINE(XInput)->setVibration(playerIndex, vibration);
		}

		const XInputVibration& XInput_impl::getVibration() const
		{
			return SIV3D_ENGINE(XInput)->getVibration(playerIndex);
		}

		void XInput_impl::stopVibration() const
		{
			SIV3D_ENGINE(XInput)->setVibration(playerIndex, XInputVibration{});
		}

		void XInput_impl::pauseVibration() const
		{
			SIV3D_ENGINE(XInput)->pauseVibration(playerIndex);
		}

		void XInput_impl::resumeVibration() const
		{
			SIV3D_ENGINE(XInput)->resumeVibration(playerIndex);
		}

		const XInput_impl& XInput_helper::operator()(const size_t playerIndex) const
		{
			return SIV3D_ENGINE(XInput)->getInput(static_cast<uint32>(playerIndex));
		}
	}
}
