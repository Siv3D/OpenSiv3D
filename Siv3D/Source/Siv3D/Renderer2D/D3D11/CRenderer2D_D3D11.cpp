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

# include "../../Siv3DEngine.hpp"
# include "../../Shader/IShader.hpp"
# include "CRenderer2D_D3D11.hpp"

#include <Siv3D/Logger.hpp>

namespace s3d
{
	CRenderer2D_D3D11::CRenderer2D_D3D11()
	{

	}

	CRenderer2D_D3D11::~CRenderer2D_D3D11()
	{

	}

	bool CRenderer2D_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		m_device = device;
		m_context = context;

		D3D11_INPUT_ELEMENT_DESC layout[3] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,       0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		const VertexShader& spriteVS = Siv3DEngine::GetShader()->getStandardVS(0);
		const ByteArrayView vsView = spriteVS.getBinaryView();

		Log << vsView.size();

		if (FAILED(m_device->CreateInputLayout(layout, 3, vsView.data(), vsView.size(), &m_inputLayout)))
		{
			return false;
		}

		m_context->IASetInputLayout(m_inputLayout.Get());


		if (!m_spriteBatch.init(m_device, m_context))
		{
			return false;
		}

		return true;
	}

	void CRenderer2D_D3D11::flush()
	{
		// set buffer
		m_spriteBatch.setBuffers();

		// setCB

		// setVS

		// setPS

		// draw

		m_spriteBatch.clear();
	}
}

# endif
