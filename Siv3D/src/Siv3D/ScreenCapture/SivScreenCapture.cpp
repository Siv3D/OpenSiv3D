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
# include <Siv3D/DateTime.hpp>

namespace s3d
{
	namespace ScreenCapture
	{
		void SaveCurrentFrame()
		{
			const FilePath path = Siv3DEngine::GetScreenCapture()->getDefaultScreenshotDirectory() + DateTime::Now().format(U"yyyyMMdd-HHmmss-SSS") + U".png";

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
