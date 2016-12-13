//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <atomic>
# include <Siv3D/System.hpp>
# include "ISystem.hpp"

namespace s3d
{
	class CSystem : public ISiv3DSystem
	{
	private:

		std::atomic_uint32_t m_event = 0;

		uint32 m_previousEvent = 0;

		uint32 m_exitEvent = WindowEvent::Default;

	public:

		CSystem();

		~CSystem() override;

		bool init() override;

		void exit() override;

		bool update() override;

		void reportEvent(uint32 windowEventFlag) override;
	};
}
