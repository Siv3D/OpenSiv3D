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
# include "../Graphics/IGraphics.hpp"
# include "CScreenCapture.hpp"
# include <Siv3D/Image.hpp>

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

		return true;
	}

	bool CScreenCapture::update()
	{
		if (!m_hasRequest)
		{
			return true;
		}

		const Image& image = Siv3DEngine::GetGraphics()->getScreenCapture();

		for (const auto& path : m_requestedPaths)
		{
			image.save(path);
		}

		m_requestedPaths.clear();

		m_hasRequest = false;

		return true;
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