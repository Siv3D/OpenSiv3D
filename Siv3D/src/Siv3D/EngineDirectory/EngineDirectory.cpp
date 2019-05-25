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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Version.hpp>
# include "EngineDirectory.hpp"

namespace s3d
{
	namespace EngineDirectory
	{
		FilePath CurrectVersionCommon()
		{
			return FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData) + U"Siv3D/" SIV3D_VERSION U"/";
		}

		FilePath DefaultLicensePath()
		{
			return FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData) + U"Siv3D/" SIV3D_VERSION U"/Licenses.html";
		}

		FilePath ApplicationLicensePath(const String& uniqueID)
		{
			return FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData) + U"Siv3DApps/" + uniqueID + U"/Licenses.html";
		}
	}
}
