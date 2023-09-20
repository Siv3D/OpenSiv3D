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

# include "CScreenCapture.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CScreenCapture::CScreenCapture() {}

	CScreenCapture::~CScreenCapture()
	{
		LOG_SCOPED_TRACE(U"CScreenCapture::~CScreenCapture()");
	}

	void CScreenCapture::init()
	{
		LOG_SCOPED_TRACE(U"CScreenCapture::init()");

	# if SIV3D_PLATFORM(MACOS)

		m_screenshotDirectory = FileSystem::GetFolderPath(SpecialFolder::Pictures) + U"Screenshot/";

	# else

		m_screenshotDirectory = FileSystem::InitialDirectory() + U"Screenshot/";

	# endif

		LOG_INFO(U"Default Screenshot directory: \"{}\""_fmt(m_screenshotDirectory));
	}

	void CScreenCapture::update()
	{
		m_hasNewFrame = false;

		// スクリーンショットのショートカットに対応
		if (not m_requestedPaths)
		{
			bool captureKeyDown = false;

			for (const auto& inputGroup : m_screenshotShortcutKeys)
			{
				if (inputGroup.down())
				{
					captureKeyDown = true;
					break;
				}
			}

			if (captureKeyDown)
			{
				ScreenCapture::SaveCurrentFrame();
			}
		}

		if (m_requestedPaths)
		{
			SIV3D_ENGINE(Renderer)->captureScreenshot();

			const Image& image = SIV3D_ENGINE(Renderer)->getScreenCapture();

			if (not image)
			{
				LOG_FAIL(U"✖ failed to capture a screen shot");
			}
			else
			{
				for (const auto& requestedPath : m_requestedPaths)
				{
					if (requestedPath)
					{
						const FilePath path = (m_screenshotDirectory + requestedPath);
						image.save(path);
						LOG_INFO(U"📷 Screen capture saved (path: \"{0}\")"_fmt(path));
					}
				}
			}

			m_requestedPaths.clear();
			m_hasNewFrame = true;
		}
	}

	const FilePath& CScreenCapture::getScreenshotDirectory() const
	{
		return m_screenshotDirectory;
	}

	void CScreenCapture::setScreenshotDirectory(const FilePathView path)
	{
		m_screenshotDirectory = path;
	}

	void CScreenCapture::requestScreenCapture(const FilePathView path)
	{
		m_requestedPaths.emplace_back(path);
	}

	bool CScreenCapture::hasNewFrame() const
	{
		return m_hasNewFrame;
	}

	const Image& CScreenCapture::receiveScreenCapture() const
	{
		return SIV3D_ENGINE(Renderer)->getScreenCapture();
	}

	void CScreenCapture::setScreenshotShortcutKeys(const Array<InputGroup>& screenshotShortcutKeys)
	{
		m_screenshotShortcutKeys = screenshotShortcutKeys;
	}
}
