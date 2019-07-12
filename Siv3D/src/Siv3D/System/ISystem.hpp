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
# include <Siv3D/Fwd.hpp>
# include "FrameDelta.hpp"

namespace s3d
{
	class ISiv3DSystem
	{
	public:

		static ISiv3DSystem* Create();

		virtual ~ISiv3DSystem() = default;

		virtual void init() = 0;

		virtual bool update() = 0;

		virtual void setTerminationTriggers(uint32 userActionFlags) = 0;

		virtual uint32 getTerminationTriggers() = 0;

		virtual uint32 getUserActions() = 0;

		virtual void reportUserActions(uint32 userActions) = 0;

		virtual uint64 getSystemFrameCount() const noexcept = 0;

		virtual int32 getUserFrameCount() const noexcept = 0;

		virtual void setUserFrameCount(int32 count) noexcept = 0;

		virtual FrameDelta& getFrameDelta() noexcept = 0;
	};
}
