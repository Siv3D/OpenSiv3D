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

# include "../Siv3DEngine.hpp"
# include "IScreenCapture.hpp"
# include <Siv3D/ScreenCapture.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace ScreenCapture
	{
		void SaveCurrentFrame()
		{
			const FilePath path = FileSystem::InitialPath() + L"/Screenshot/" + DateTime::Now().format(L"yyyyMMdd-HHmmss-SSS") + L".png";

			SaveCurrentFrame(path);
		}

		void SaveCurrentFrame(const FilePath& path)
		{
			if (!path)
			{
				return;
			}

			Siv3DEngine::GetScreenCapture()->requestScreenCapture(path);
		}
	}
}
