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
# include <Siv3D/XInput/IXInput.hpp>
# include <Siv3D/XInput/XInputState.hpp>

namespace s3d
{
	class CXInput_Null final : public ISiv3DXInput
	{
	public:

		CXInput_Null();

		~CXInput_Null() override;

		void init() override;

		void update(bool deviceChanged) override;

		bool isConnected(uint32 playerIndex) const override;

		void setDeadZone(uint32 playerIndex, DeadZoneIndex inputIndex, const DeadZone& deadZone) override;

		void setVibration(uint32 playerIndex, const XInputVibration& vibration) override;

		const XInputVibration& getVibration(uint32 playerIndex) const override;

		void pauseVibration(uint32 playerIndex) override;

		void resumeVibration(uint32 playerIndex) override;

		bool down(uint32 playerIndex, uint32 index) const override;

		bool pressed(uint32 playerIndex, uint32 index) const override;

		bool up(uint32 playerIndex, uint32 index) const override;

		void clearInput(uint32 playerIndex, uint32 index) override;

		bool cleared(uint32 playerIndex, uint32 index) const override;

		Duration pressedDuration(uint32 playerIndex, uint32 index) const override;

		const detail::XInput_impl& getInput(uint32 playerIndex) const override;

	private:

		std::array<XInputState, XInput.MaxPlayerCount> m_states;

		std::array<detail::XInput_impl, XInput.MaxPlayerCount> m_inputs;
	};
}
