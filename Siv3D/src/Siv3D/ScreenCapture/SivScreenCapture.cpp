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

# include <Siv3D/ScreenCapture.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/ScreenCapture/IScreenCapture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace ScreenCapture
	{
		FilePath GetScreenshotDirectory()
		{
			return SIV3D_ENGINE(ScreenCapture)->getScreenshotDirectory();
		}

		void SetScreenshotDirectory(const FilePathView path)
		{
			SIV3D_ENGINE(ScreenCapture)->setScreenshotDirectory(path);
		}

		void SaveCurrentFrame(const FilePathView path)
		{
			SIV3D_ENGINE(ScreenCapture)->requestScreenCapture(path);
		}

		void RequestCurrentFrame()
		{
			SIV3D_ENGINE(ScreenCapture)->requestScreenCapture({});
		}

		bool HasNewFrame()
		{
			return SIV3D_ENGINE(ScreenCapture)->hasNewFrame();
		}

		const Image& GetFrame()
		{
			return SIV3D_ENGINE(ScreenCapture)->receiveScreenCapture();
		}

		bool GetFrame(Image& image)
		{
			image = SIV3D_ENGINE(ScreenCapture)->receiveScreenCapture();

			return !!image;
		}

		bool GetFrame(DynamicTexture& texture)
		{
			return texture.fill(SIV3D_ENGINE(ScreenCapture)->receiveScreenCapture());
		}

		void SetShortcutKeys(const Array<InputGroup>& screenshotShortcutKeys)
		{
			SIV3D_ENGINE(ScreenCapture)->setScreenshotShortcutKeys(screenshotShortcutKeys);
		}
	}
}
