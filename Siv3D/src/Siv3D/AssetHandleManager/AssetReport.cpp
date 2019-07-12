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

# include <Siv3DEngine.hpp>
# include <Profiler/IProfiler.hpp>
# include "AssetReport.hpp"

namespace s3d
{
	void ReportAssetCreation()
	{
		Siv3DEngine::Get<ISiv3DProfiler>()->reportAssetCreation();
	}

	void ReportAssetRelease()
	{
		Siv3DEngine::Get<ISiv3DProfiler>()->reportAssetRelease();
	}
}
