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
# include <Siv3D/EngineLog.hpp>
# include "CScreenCapture.hpp"

namespace s3d
{
	CScreenCapture::CScreenCapture()
	{

	}

	CScreenCapture::~CScreenCapture()
	{
		LOG_TRACE(U"CScreenCapture::~CScreenCapture()");
	}

	const FilePath& CScreenCapture::getDefaultScreenshotDirectory() const
	{
		return m_defaultScreenshotDirectory;
	}

	void CScreenCapture::requestScreenCapture(const FilePath& path)
	{
		if (path)
		{
			m_requestedPaths.push_back(path);
		}

		if (!m_hasRequest)
		{
			m_hasRequest = true;

			Siv3DEngine::Get<ISiv3DGraphics>()->requestScreenCapture();
		}	
	}

	bool CScreenCapture::hasNewFrame() const
	{
		return m_hasNewFrame;
	}

	const Image& CScreenCapture::receiveScreenCapture() const
	{
		return Siv3DEngine::Get<ISiv3DGraphics>()->getScreenCapture();
	}
}
