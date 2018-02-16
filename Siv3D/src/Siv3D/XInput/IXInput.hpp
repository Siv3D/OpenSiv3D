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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/XInput.hpp>

namespace s3d
{
	enum class DeadZoneIndex
	{
		LefTrigger,

		RightTrigger,

		LeftThumb,

		RightThumb
	};

	class ISiv3DXInput
	{
	public:

		static ISiv3DXInput* Create();

		virtual ~ISiv3DXInput() = default;

		virtual bool init() = 0;

		virtual void update(bool deviceChanged) = 0;

		virtual bool isConnected(size_t userIndex) const = 0;

		virtual void setDeadZone(size_t userIndex, DeadZoneIndex inputIndex, const DeadZone& deadZone) = 0;

		virtual void setVibration(size_t userIndex, double leftMotorSpeed, double rightMotorSpeed) = 0;

		virtual std::pair<double, double> getVibration(size_t userIndex) const = 0;

		virtual void pauseVibration(size_t userIndex) = 0;

		virtual void resumeVibration(size_t userIndex) = 0;

		virtual bool down(size_t userIndex, uint32 index) const = 0;

		virtual bool pressed(size_t userIndex, uint32 index) const = 0;

		virtual bool up(size_t userIndex, uint32 index) const = 0;

		virtual MillisecondsF pressedDuration(size_t userIndex, uint32 index) const = 0;

		virtual const detail::XInput_impl& getInput(size_t userIndex) const = 0;
	};
}
