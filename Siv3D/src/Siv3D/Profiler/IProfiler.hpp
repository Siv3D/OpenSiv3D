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
	class ISiv3DProfiler
	{
	public:

		static ISiv3DProfiler* Create();

		virtual ~ISiv3DProfiler() = default;

		virtual bool init() = 0;

		virtual bool beginFrame() = 0;

		virtual void endFrame() = 0;

		virtual int32 getFPS() const = 0;


		virtual void setAssetCreationWarningEnabled(bool enabled) = 0;

		virtual void reportAssetCreation() = 0;

		virtual void reportAssetRelease() = 0;
	};
}

# define ASSET_CREATION()	s3d::Siv3DEngine::GetProfiler()->reportAssetCreation()
# define ASSET_RELEASE()	s3d::Siv3DEngine::GetProfiler()->reportAssetRelease() 
