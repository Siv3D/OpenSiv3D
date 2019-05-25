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
			const FilePath path = Siv3DEngine::Get<ISiv3DScreenCapture>()->getDefaultScreenshotDirectory() + DateTime::Now().format(U"yyyyMMdd-HHmmss-SSS") + U".png";

			SaveCurrentFrame(path);
		}

		void SaveCurrentFrame(const FilePath& path)
		{
			if (!path)
			{
				return;
			}

			Siv3DEngine::Get<ISiv3DScreenCapture>()->requestScreenCapture(path);
		}

		void RequestCurrentFrame()
		{
			Siv3DEngine::Get<ISiv3DScreenCapture>()->requestScreenCapture(FilePath());
		}

		bool HasNewFrame()
		{
			return Siv3DEngine::Get<ISiv3DScreenCapture>()->hasNewFrame();
		}

		const Image& GetFrame()
		{
			return Siv3DEngine::Get<ISiv3DScreenCapture>()->receiveScreenCapture();
		}

		bool GetFrame(Image& image)
		{
			image = Siv3DEngine::Get<ISiv3DScreenCapture>()->receiveScreenCapture();

			return !!image;
		}

		bool GetFrame(DynamicTexture& texture)
		{
			return texture.fill(Siv3DEngine::Get<ISiv3DScreenCapture>()->receiveScreenCapture());
		}
	}
}
