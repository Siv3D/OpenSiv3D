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

namespace s3d
{
	namespace UserAction
	{
		inline constexpr uint32 SystemExitCalled = 0x10000000u;
	}

	class SIV3D_NOVTABLE ISiv3DUserAction
	{
	public:

		static ISiv3DUserAction* Create();

		virtual ~ISiv3DUserAction() = default;

		virtual void setTerminationTriggers(uint32 userActionFlags) noexcept = 0;

		virtual uint32 getTerminationTriggers() noexcept = 0;

		virtual uint32 getPreviousUserActions() noexcept = 0;

		virtual void reportUserActions(uint32 userActions) noexcept = 0;

		virtual bool terminationTriggered() noexcept = 0;
	};
}
