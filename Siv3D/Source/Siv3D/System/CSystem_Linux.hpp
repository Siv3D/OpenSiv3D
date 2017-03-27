//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <atomic>
# include <Siv3D/System.hpp>
# include "ISystem.hpp"

namespace s3d
{
	class CSystem_Linux : public ISiv3DSystem
	{
	private:

		std::atomic<uint32> m_event = {0};

		uint32 m_previousEvent = 0;

		uint32 m_exitEvent = WindowEvent::Default;

	public:

		CSystem_Linux();

		~CSystem_Linux() override;

		bool init() override;

		void exit() override;

		bool update() override;

		void reportEvent(uint32 windowEventFlag) override;
	};
}

# endif
