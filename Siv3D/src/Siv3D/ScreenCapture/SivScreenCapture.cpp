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

# include "../Siv3DEngine.hpp"
# include "IScreenCapture.hpp"
# include <Siv3D/ScreenCapture.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/DynamicTexture.hpp>

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

		void RequestCurrentFrame()
		{
			Siv3DEngine::GetScreenCapture()->requestScreenCapture(FilePath());
		}

		bool HasNewFrame()
		{
			return Siv3DEngine::GetScreenCapture()->hasNewFrame();
		}

		const Image& GetFrame()
		{
			return Siv3DEngine::GetScreenCapture()->receiveScreenCapture();
		}

		bool GetFrame(Image& image)
		{
			image = Siv3DEngine::GetScreenCapture()->receiveScreenCapture();

			return !!image;
		}

		bool GetFrame(DynamicTexture& texture)
		{
			return texture.fill(Siv3DEngine::GetScreenCapture()->receiveScreenCapture());
		}
	}
}
