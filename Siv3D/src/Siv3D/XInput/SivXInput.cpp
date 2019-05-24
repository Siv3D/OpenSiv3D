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

# include <Siv3D/XInput.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3DEngine.hpp>
# include "IXInput.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr int32 Get4Direction(const double angle)
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

		static constexpr int32 Get8Direction(const double angle)
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

		XInput_impl::XInput_impl(const size_t _userIndex)
			: userIndex(static_cast<uint32>(_userIndex))
			, buttonUp(InputDevice::XInput, 0, static_cast<uint8>(userIndex))
			, buttonDown(InputDevice::XInput, 1, static_cast<uint8>(userIndex))
			, buttonLeft(InputDevice::XInput, 2, static_cast<uint8>(userIndex))
			, buttonRight(InputDevice::XInput, 3, static_cast<uint8>(userIndex))
			, buttonStart(InputDevice::XInput, 4, static_cast<uint8>(userIndex))
			, buttonBack(InputDevice::XInput, 5, static_cast<uint8>(userIndex))
			, buttonLThumb(InputDevice::XInput, 6, static_cast<uint8>(userIndex))
			, buttonRThumb(InputDevice::XInput, 7, static_cast<uint8>(userIndex))
			, buttonLB(InputDevice::XInput, 8, static_cast<uint8>(userIndex))
			, buttonRB(InputDevice::XInput, 9, static_cast<uint8>(userIndex))
			, buttonA(InputDevice::XInput, 12, static_cast<uint8>(userIndex))
			, buttonB(InputDevice::XInput, 13, static_cast<uint8>(userIndex))
			, buttonX(InputDevice::XInput, 14, static_cast<uint8>(userIndex))
			, buttonY(InputDevice::XInput, 15, static_cast<uint8>(userIndex))
			, leftTrigger(0.0)
			, rightTrigger(0.0)
			, leftThumbX(0.0)
			, leftThumbY(0.0)
			, rightThumbX(0.0)
			, rightThumbY(0.0)
		{

		}

		bool XInput_impl::isConnected() const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->isConnected(userIndex);
		}

		XInput_impl::operator bool() const
		{
			return isConnected();
		}

		void XInput_impl::setLeftTriggerDeadZone(const DeadZone& deadZone)
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->setDeadZone(userIndex, DeadZoneIndex::LefTrigger, deadZone);
		}

		void XInput_impl::setRightTriggerDeadZone(const DeadZone& deadZone)
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->setDeadZone(userIndex, DeadZoneIndex::RightTrigger, deadZone);
		}

		void XInput_impl::setLeftThumbDeadZone(const DeadZone& deadZone)
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->setDeadZone(userIndex, DeadZoneIndex::LeftThumb, deadZone);
		}

		void XInput_impl::setRightThumbDeadZone(const DeadZone& deadZone)
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->setDeadZone(userIndex, DeadZoneIndex::RightThumb, deadZone);
		}

		Optional<int32> XInput_impl::leftThumbD4(const double threshold) const
		{
			const Circular circular(Vec2(leftThumbX, -leftThumbY));

			if (circular.r < threshold)
			{
				return none;
			}

			return Get4Direction(circular.theta);
		}

		Optional<int32> XInput_impl::leftThumbD8(const double threshold) const
		{
			const Circular circular(Vec2(leftThumbX, -leftThumbY));

			if (circular.r < threshold)
			{
				return none;
			}

			return Get8Direction(circular.theta);
		}

		Optional<int32> XInput_impl::rightThumbD4(const double threshold) const
		{
			const Circular circular(Vec2(rightThumbX, -rightThumbY));

			if (circular.r < threshold)
			{
				return none;
			}

			return Get4Direction(circular.theta);
		}

		Optional<int32> XInput_impl::rightThumbD8(const double threshold) const
		{
			const Circular circular(Vec2(rightThumbX, -rightThumbY));

			if (circular.r < threshold)
			{
				return none;
			}

			return Get8Direction(circular.theta);
		}

		void XInput_impl::setVibration(const double leftMotorSpeed, const double rightMotorSpeed) const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->setVibration(userIndex, leftMotorSpeed, rightMotorSpeed);
		}

		std::pair<double, double> XInput_impl::getVibration() const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->getVibration(userIndex);
		}

		void XInput_impl::stopVibration() const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->setVibration(userIndex, 0.0, 0.0);
		}

		void XInput_impl::pauseVibration() const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->pauseVibration(userIndex);
		}

		void XInput_impl::resumeVibration() const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->resumeVibration(userIndex);
		}

		const XInput_impl& XInput_helper::operator()(const size_t userIndex) const
		{
			return Siv3DEngine::Get<ISiv3DXInput>()->getInput(userIndex);
		}
	}
}
