//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CTexture_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_D3D11::CTexture_D3D11()
	{

	}

	CTexture_D3D11::~CTexture_D3D11()
	{
		LOG_SCOPED_TRACE(U"CTexture_D3D11::~CTexture_D3D11()");
	}

	void CTexture_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CTexture_D3D11::init()");

	}

	bool CTexture_D3D11::update()
	{
		return true;
	}
}
