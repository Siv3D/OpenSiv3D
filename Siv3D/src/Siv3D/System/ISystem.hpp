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
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DSystem
	{
	public:

		static ISiv3DSystem* Create();

		virtual ~ISiv3DSystem() = default;

		virtual bool init() = 0;

		virtual bool update(bool clearGraphics) = 0;

		virtual void reportEvent(uint32 windowEventFlag) = 0;

		virtual void setExitEvent(uint32 windowEventFlag) = 0;

		virtual uint32 getPreviousEvent() const = 0;

		virtual uint64 getSystemFrameCount() const noexcept = 0;

		virtual int32 getUserFrameCount() const noexcept = 0;

		virtual void setUserFrameCount(int32 count) noexcept = 0;

		virtual double getDeltaTime() const noexcept = 0;
	};
}
