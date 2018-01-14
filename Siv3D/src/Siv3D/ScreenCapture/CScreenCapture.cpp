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
# include "../Graphics/IGraphics.hpp"
# include "CScreenCapture.hpp"
# include <Siv3D/Image.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/KeyConjunction.hpp>
# include <Siv3D/ScreenCapture.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CScreenCapture::CScreenCapture()
	{

	}

	CScreenCapture::~CScreenCapture()
	{

	}

	bool CScreenCapture::init()
	{
	# if defined(SIV3D_TARGET_MACOS)
		
		const String appName = FileSystem::BaseName(FileSystem::ModulePath());
		
		if (FileSystem::IsSandBoxed())
		{
			m_defaultScreenshotDirectory = FileSystem::SpecialFolderPath(SpecialFolder::Pictures) + U"Screenshot/" + appName + U"/";
		}
		else
		{
			m_defaultScreenshotDirectory = FileSystem::InitialPath() + U"Screenshot/";
		}

	# else
		
		m_defaultScreenshotDirectory = FileSystem::InitialPath() + U"Screenshot/";
		
	# endif

		return true;
	}

	bool CScreenCapture::update()
	{
		if (m_hasRequest)
		{
			const Image& image = Siv3DEngine::GetGraphics()->getScreenCapture();

			for (const auto& path : m_requestedPaths)
			{
				image.save(path);

				LOG_INFO(U"📷 Screen capture saved (path: \"{0}\")"_fmt(path));
			}

			m_requestedPaths.clear();

			m_hasRequest = false;
		}

		if (KeyPrintScreen.down())
		{
			ScreenCapture::SaveCurrentFrame();
		}

	# if defined(SIV3D_TARGET_MACOS)

		if (!m_hasRequest && ((KeyCommand + KeyControl).pressed() && Key4.down()))
		{
			ScreenCapture::SaveCurrentFrame();
		}

	# endif

		return true;
	}

	const FilePath& CScreenCapture::getDefaultScreenshotDirectory() const
	{
		return m_defaultScreenshotDirectory;
	}

	void CScreenCapture::requestScreenCapture(const FilePath& path)
	{
		m_requestedPaths.push_back(path);

		if (!m_hasRequest)
		{
			m_hasRequest = true;

			Siv3DEngine::GetGraphics()->requestScreenCapture();
		}	
	}
}