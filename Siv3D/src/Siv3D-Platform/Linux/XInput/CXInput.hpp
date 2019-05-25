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

# pragma once
# include <XInput/IXInput.hpp>
# include <Key/InputState.hpp>

namespace s3d
{
	class CXInput : public ISiv3DXInput
	{
	private:

		std::array<detail::XInput_impl, 4> m_inputs;

	public:

		CXInput();

		~CXInput() override;

		void init() override;

		void update(bool deviceChanged) override;

		bool isConnected(size_t userIndex) const override;

		void setDeadZone(size_t userIndex, DeadZoneIndex inputIndex, const DeadZone& deadZone) override;

		void setVibration(size_t userIndex, double leftMotorSpeed, double rightMotorSpeed) override;

		std::pair<double, double> getVibration(size_t userIndex) const override;

		void pauseVibration(size_t userIndex) override;

		void resumeVibration(size_t userIndex) override;

		bool down(size_t userIndex, uint32 index) const override;

		bool pressed(size_t userIndex, uint32 index) const override;

		bool up(size_t userIndex, uint32 index) const override;

		Duration pressedDuration(size_t userIndex, uint32 index) const override;

		const detail::XInput_impl& getInput(size_t userIndex) const override;
	};
}
