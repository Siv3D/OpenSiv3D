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
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DProfiler
	{
	public:

		static ISiv3DProfiler* Create();

		virtual ~ISiv3DProfiler() = default;

		virtual bool init() = 0;

		virtual void beginFrame() = 0;

		virtual void endFrame() = 0;

		virtual int32 getFPS() const = 0;
	};
}
