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
# include <Siv3D/ProfilerStat.hpp>

namespace s3d
{
	class String;

	class SIV3D_NOVTABLE ISiv3DProfiler
	{
	public:

		static ISiv3DProfiler* Create();

		virtual ~ISiv3DProfiler() = default;

		virtual void init() = 0;

		virtual void beginFrame() = 0;

		virtual void endFrame() = 0;

		virtual int32 getFPS() const noexcept = 0;

		virtual String getSimpleStatistics() const = 0;

		virtual const ProfilerStat& getStat() const = 0;
	};
}
