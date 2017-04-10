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

# include "CShader_D3D11.hpp"
# include "../../EngineUtility.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CShader_D3D11::CShader_D3D11()
	{

	}

	CShader_D3D11::~CShader_D3D11()
	{

	}

	bool CShader_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		m_device = device;
		m_context = context;

	# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

		m_d3dcompiler = ::LoadLibraryW(L"dll(x64)/D3D/d3dcompiler_47.dll");

	# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

		m_d3dcompiler = ::LoadLibraryW(L"dll(x86)/D3D/d3dcompiler_47.dll");

	# endif

		if (!m_d3dcompiler)
		{
			::LoadLibraryW(L"d3dcompiler_47.dll");
		}

		if (m_d3dcompiler)
		{
			p_D3DCompile2 = FunctionPointer(m_d3dcompiler, "D3DCompile2");
		}

		const auto nullVertexShader = std::make_shared<VertexShader_D3D11>(VertexShader_D3D11::Null{});

		if (!nullVertexShader->isInitialized())
		{
			return false;
		}

		m_vertexShaders.setNullData(nullVertexShader);

		return true;
	}

	bool CShader_D3D11::compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target)
	{
		if (!p_D3DCompile2)
		{
			return false;
		}

		Array<Byte> data(static_cast<size_t>(reader.size()));

		reader.read(data.data(), data.size());

		const bool preferFlow = false;
		const uint32 flags =
			D3DCOMPILE_ENABLE_STRICTNESS
			| D3DCOMPILE_OPTIMIZATION_LEVEL3
			| D3DCOMPILE_WARNINGS_ARE_ERRORS
			| (preferFlow ? D3DCOMPILE_PREFER_FLOW_CONTROL : 0);

		ID3DBlob* pBlobOut = nullptr;
		ID3DBlob* pErrorBlob = nullptr;
		const HRESULT hr = p_D3DCompile2(data.data(), data.size(), filePath, nullptr, nullptr,
			entryPoint, target, flags, 0, 0, nullptr, 0, &pBlobOut, &pErrorBlob);

		if (pErrorBlob)
		{
			::OutputDebugStringA((const char*)pErrorBlob->GetBufferPointer());

			pErrorBlob->Release();
		}

		if (FAILED(hr))
		{
			if (pBlobOut)
			{
				pBlobOut->Release();
			}

			return false;
		}

		to.create(pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize());

		pBlobOut->Release();

		return true;
	}

	VertexShader::IDType CShader_D3D11::createVS(ByteArray&& binary)
	{
		const auto vertexShader = std::make_shared<VertexShader_D3D11>(std::move(binary), m_device);

		if (!vertexShader->isInitialized())
		{
			return VertexShader::IDType(0);
		}

		return m_vertexShaders.add(vertexShader);
	}
}

# endif
