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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CGraphics_D3D11.hpp"

namespace s3d
{
	CGraphics_D3D11::CGraphics_D3D11()
	{

	}

	CGraphics_D3D11::~CGraphics_D3D11()
	{

	}

	bool CGraphics_D3D11::init()
	{
		//////////////////////////////////////////////////////
		//
		//	 D3D11Device
		//
		m_device = std::make_unique<D3D11Device>();

		if (!m_device->init())
		{
			return false;
		}

		//////////////////////////////////////////////////////
		//
		//	 D3D11SwapChain
		//
		m_swapChain = std::make_unique<D3D11SwapChain>(m_device->getDevice(), m_device->getContext(), m_device->getAdapter());

		if (!m_swapChain->init())
		{
			return false;
		}

		return true;
	}
}

# endif
