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
# include <System/ISystem.hpp>
# include <System/UserActionManager.hpp>
# include <System/FrameCounter.hpp>
# include <System/FrameDelta.hpp>

namespace s3d
{
	class CSystem : public ISiv3DSystem
	{
	private:

		UserActionManager m_terminationTrigger;

		FrameCounter m_frameCounter;

		FrameDelta m_frameDelta;

		enum class SetupState
		{
			Uninitialized,
			Initialized,
			Displayed,
			DisplayedWaitKey,
		} m_setupState = SetupState::Uninitialized;

		bool m_updateSucceeded = true;

		std::atomic<bool> m_onDeviceChange = { false };

	public:

		CSystem();

		~CSystem() override;

		void init() override;

		bool update() override;

		void setTerminationTriggers(uint32 userActionFlags) override;

		uint32 getTerminationTriggers() override;

		uint32 getUserActions() override;

		void reportUserActions(uint32 userActions) override;

		uint64 getSystemFrameCount() const noexcept override;

		int32 getUserFrameCount() const noexcept override;

		void setUserFrameCount(int32 count) noexcept override;

		FrameDelta& getFrameDelta() noexcept override;

		void onDeviceChange();
	};
}
