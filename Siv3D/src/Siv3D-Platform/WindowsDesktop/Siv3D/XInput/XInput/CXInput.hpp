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
# include <Siv3D/DLL.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/XInput/IXInput.hpp>
# include <Siv3D/XInput/XInputState.hpp>
# include <XInput.h>

namespace s3d
{
	class CXInput final : public ISiv3DXInput
	{
	public:

		CXInput();

		~CXInput() override;

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

		LibraryHandle m_xInput = nullptr;

		decltype(XInputGetState)* p_XInputGetState = nullptr;

		decltype(XInputSetState)* p_XInputSetState = nullptr;

		bool m_initialized = false;

		std::array<XInputState, XInput.MaxPlayerCount> m_states;

		std::array<detail::XInput_impl, XInput.MaxPlayerCount> m_inputs;
	};
}
