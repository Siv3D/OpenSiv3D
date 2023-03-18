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
# include <Siv3D/XInput.hpp>

namespace s3d
{
	enum class DeadZoneIndex : uint8
	{
		LefTrigger,

		RightTrigger,

		LeftThumb,

		RightThumb
	};

	class SIV3D_NOVTABLE ISiv3DXInput
	{
	public:

		static ISiv3DXInput* Create();

		virtual ~ISiv3DXInput() = default;

		virtual void init() = 0;

		virtual void update(bool deviceChanged) = 0;

		virtual bool isConnected(uint32 playerIndex) const = 0;

		virtual void setDeadZone(uint32 playerIndex, DeadZoneIndex inputIndex, const DeadZone& deadZone) = 0;

		virtual void setVibration(uint32 playerIndex, const XInputVibration& vibration) = 0;

		virtual const XInputVibration& getVibration(uint32 playerIndex) const = 0;

		virtual void pauseVibration(uint32 playerIndex) = 0;

		virtual void resumeVibration(uint32 playerIndex) = 0;

		virtual bool down(uint32 playerIndex, uint32 index) const = 0;

		virtual bool pressed(uint32 playerIndex, uint32 index) const = 0;

		virtual bool up(uint32 playerIndex, uint32 index) const = 0;

		virtual void clearInput(uint32 playerIndex, uint32 index) = 0;

		virtual bool cleared(uint32 playerIndex, uint32 index) const = 0;

		virtual Duration pressedDuration(uint32 playerIndex, uint32 index) const = 0;

		virtual const detail::XInput_impl& getInput(uint32 playerIndex) const = 0;
	};
}
