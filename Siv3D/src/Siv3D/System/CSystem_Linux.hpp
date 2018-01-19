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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <Siv3D/System.hpp>
# include "ISystem.hpp"
# include "SystemUtility.hpp"

namespace s3d
{
	class CSystem_Linux : public ISiv3DSystem
	{
	private:

		ExitEventManager m_exitEventManager;
		
		FrameCounter m_frameCounter;

		FrameDelta m_frameDelta;

		bool m_updateSucceeded = true;

	public:

		CSystem_Linux();

		~CSystem_Linux() override;

		bool init() override;

		bool update(bool clearGraphics) override;

		void reportEvent(uint32 windowEventFlag) override;

		void setExitEvent(uint32 windowEventFlag) override;

		uint32 getPreviousEvent() const override;

		uint64 getSystemFrameCount() const noexcept override;

		int32 getUserFrameCount() const noexcept override;

		void setUserFrameCount(int32 count) noexcept override;

		double getDeltaTime() const noexcept override;
	};
}

# endif
