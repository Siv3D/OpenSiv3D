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

namespace s3d
{
	class ISiv3DProfiler
	{
	public:

		static ISiv3DProfiler* Create();

		virtual ~ISiv3DProfiler() = default;

		virtual void init() = 0;

		virtual bool beginFrame() = 0;

		virtual void endFrame() = 0;

		virtual int32 getFPS() const = 0;

		virtual String getSimpleStatistics() const = 0;

		virtual void reportDrawcalls(size_t drawcalls, size_t triangles) = 0;

		virtual Statistics getStatistics() const noexcept = 0;

		virtual void setAssetCreationWarningEnabled(bool enabled) = 0;

		virtual void reportAssetCreation() = 0;

		virtual void reportAssetRelease() = 0;
	};
}
