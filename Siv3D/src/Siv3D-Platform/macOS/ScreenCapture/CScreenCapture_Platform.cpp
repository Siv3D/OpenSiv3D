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
# include <Graphics/IGraphics.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/KeyConjunction.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScreenCapture.hpp>
# include <ScreenCapture/CScreenCapture.hpp>

namespace s3d
{
	void CScreenCapture::init()
	{
		LOG_TRACE(U"CScreenCapture::init()");

		const String appName = FileSystem::BaseName(FileSystem::ModulePath());
		
		if (FileSystem::IsSandBoxed())
		{
			m_defaultScreenshotDirectory = FileSystem::SpecialFolderPath(SpecialFolder::Pictures) + U"Screenshot/" + appName + U"/";
		}
		else
		{
			m_defaultScreenshotDirectory = FileSystem::InitialDirectory() + U"Screenshot/";
		}

		LOG_DEBUG(U"Default Screenshot directory: \"{}\""_fmt(m_defaultScreenshotDirectory));
		LOG_INFO(U"ℹ️ CScreenCapture initialized");
	}

	void CScreenCapture::update()
	{
		m_hasNewFrame = false;

		if (m_hasRequest)
		{
			const Image& image = Siv3DEngine::Get<ISiv3DGraphics>()->getScreenCapture();

			for (const auto& path : m_requestedPaths)
			{
				if (image.save(path))
				{
					LOG_INFO(U"📷 Screen capture saved (path: \"{0}\")"_fmt(path));
				}
			}

			m_requestedPaths.clear();

			m_hasRequest = false;

			m_hasNewFrame = true;
		}

		if (KeyPrintScreen.down())
		{
			ScreenCapture::SaveCurrentFrame();
		}
		
		if (!m_hasRequest && ((KeyCommand + KeyControl).pressed() && Key4.down()))
		{
			ScreenCapture::SaveCurrentFrame();
		}
	}
}
