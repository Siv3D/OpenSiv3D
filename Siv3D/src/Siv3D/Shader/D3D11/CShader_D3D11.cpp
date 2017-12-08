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
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CShader_D3D11::CShader_D3D11()
	{

	}

	CShader_D3D11::~CShader_D3D11()
	{
		m_standardVSs.clear();

		m_standardPSs.clear();

		m_vertexShaders.destroy();

		m_pixelShaders.destroy();

		if (m_d3dcompiler)
		{
			::FreeLibrary(m_d3dcompiler);
		}
	}

	bool CShader_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		m_device = device;
		m_context = context;

	# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

		m_d3dcompiler = ::LoadLibraryW(L"dll_x64/d3d/d3dcompiler_47.dll");

	# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

		m_d3dcompiler = ::LoadLibraryW(L"dll_x86/d3d/d3dcompiler_47.dll");

	# endif

		if (!m_d3dcompiler)
		{
			m_d3dcompiler = ::LoadLibraryW(L"d3dcompiler_47.dll");
		}

		if (m_d3dcompiler)
		{
			p_D3DCompile2 = FunctionPointer(m_d3dcompiler, "D3DCompile2");
		}

		{
			const auto nullVertexShader = std::make_shared<VertexShader_D3D11>(VertexShader_D3D11::Null{});

			if (!nullVertexShader->isInitialized())
			{
				return false;
			}

			m_vertexShaders.setNullData(nullVertexShader);
		}

		{
			const auto nullPixelShader = std::make_shared<PixelShader_D3D11>(PixelShader_D3D11::Null{});

			if (!nullPixelShader->isInitialized())
			{
				return false;
			}

			m_pixelShaders.setNullData(nullPixelShader);
		}

		///*	
		//compileHLSLToFile(S3DSTR("engine/shader/sprite.hlsl"), S3DSTR("engine/shader/sprite.vs"), "VS", "vs_4_0");
		//compileHLSLToFile(S3DSTR("engine/shader/sprite.hlsl"), S3DSTR("engine/shader/shape.ps"), "PS_Shape", "ps_4_0");
		//compileHLSLToFile(S3DSTR("engine/shader/sprite.hlsl"), S3DSTR("engine/shader/line_dot.ps"), "PS_LineDot", "ps_4_0");
		//compileHLSLToFile(S3DSTR("engine/shader/sprite.hlsl"), S3DSTR("engine/shader/line_round_dot.ps"), "PS_LineRoundDot", "ps_4_0");
		//compileHLSLToFile(S3DSTR("engine/shader/sprite.hlsl"), S3DSTR("engine/shader/sprite.ps"), "PS_Sprite", "ps_4_0");
		//compileHLSLToFile(S3DSTR("engine/shader/sprite.hlsl"), S3DSTR("engine/shader/sprite_sdf.ps"), "PS_SDF", "ps_4_0");
		//*/

# define RSC(path) Resource(path)
//# define RSC(path) path

		m_standardVSs.push_back(VertexShader(RSC(U"engine/shader/sprite.vs")));
		m_standardPSs.push_back(PixelShader(RSC(U"engine/shader/shape.ps")));
		m_standardPSs.push_back(PixelShader(RSC(U"engine/shader/line_dot.ps")));
		m_standardPSs.push_back(PixelShader(RSC(U"engine/shader/line_round_dot.ps")));
		m_standardPSs.push_back(PixelShader(RSC(U"engine/shader/sprite.ps")));
		m_standardPSs.push_back(PixelShader(RSC(U"engine/shader/sprite_sdf.ps")));

		return true;
	}

	VertexShaderID CShader_D3D11::createVS(ByteArray&& binary)
	{
		const auto vertexShader = std::make_shared<VertexShader_D3D11>(std::move(binary), m_device);

		if (!vertexShader->isInitialized())
		{
			return VertexShaderID::NullAsset();
		}

		return m_vertexShaders.add(vertexShader);
	}

	VertexShaderID CShader_D3D11::createVSFromFile(const FilePath& path, const Array<BindingPoint>&)
	{
		BinaryReader reader(path);

		if (!reader.isOpened() || reader.size() == 0 || !reader.supportsLookahead())
		{
			return VertexShaderID::NullAsset();
		}

		static constexpr uint8 dxbc[4] = { 'D', 'X', 'B', 'C' };
		uint8 fourcc[4];

		if (!reader.lookahead(fourcc))
		{
			return VertexShaderID::NullAsset();
		}

		const bool isBinary = (::memcmp(dxbc, fourcc, 4) == 0);

		ByteArray memory;

		if (isBinary)
		{
			memory = reader.readAll();
		}
		else if (!compileHLSL(reader, memory, reader.path().narrow().c_str(), "VS", "vs_4_0"))
		{
			return VertexShaderID::NullAsset();
		}

		return createVS(std::move(memory));
	}

	PixelShaderID CShader_D3D11::createPS(ByteArray&& binary)
	{
		const auto pixelShader = std::make_shared<PixelShader_D3D11>(std::move(binary), m_device);

		if (!pixelShader->isInitialized())
		{
			return PixelShaderID::NullAsset();
		}

		return m_pixelShaders.add(pixelShader);
	}

	PixelShaderID CShader_D3D11::createPSFromFile(const FilePath& path, const Array<BindingPoint>&)
	{
		BinaryReader reader(path);

		if (!reader.isOpened() || reader.size() == 0 || !reader.supportsLookahead())
		{
			return PixelShaderID::NullAsset();
		}

		static constexpr uint8 dxbc[4] = { 'D', 'X', 'B', 'C' };
		uint8 fourcc[4];

		if (!reader.lookahead(fourcc))
		{
			return PixelShaderID::NullAsset();
		}

		const bool isBinary = (::memcmp(dxbc, fourcc, 4) == 0);

		ByteArray memory;

		if (isBinary)
		{
			memory = reader.readAll();
		}
		else if (!compileHLSL(reader, memory, reader.path().narrow().c_str(), "PS", "ps_4_0"))
		{
			return PixelShaderID::NullAsset();
		}

		return createPS(std::move(memory));
	}

	void CShader_D3D11::releaseVS(const VertexShaderID handleID)
	{
		m_vertexShaders.erase(handleID);
	}

	void CShader_D3D11::releasePS(const PixelShaderID handleID)
	{
		m_pixelShaders.erase(handleID);
	}

	ByteArrayView CShader_D3D11::getBinaryViewVS(const VertexShaderID handleID)
	{
		return m_vertexShaders[handleID]->getView();
	}

	ByteArrayView CShader_D3D11::getBinaryViewPS(const PixelShaderID handleID)
	{
		return m_pixelShaders[handleID]->getView();
	}

	const VertexShader& CShader_D3D11::getStandardVS(const size_t index) const
	{
		return m_standardVSs[index];
	}

	const PixelShader& CShader_D3D11::getStandardPS(const size_t index) const
	{
		return m_standardPSs[index];
	}

	void CShader_D3D11::setVS(const VertexShaderID handleID)
	{
		if (handleID == m_currentVS)
		{
			return;
		}

		m_context->VSSetShader(m_vertexShaders[handleID]->getShader(), nullptr, 0);

		m_currentVS = handleID;
	}

	void CShader_D3D11::setPS(const PixelShaderID handleID)
	{
		if (m_currentPS == handleID)
		{
			return;
		}

		m_context->PSSetShader(m_pixelShaders[handleID]->getShader(), nullptr, 0);

		m_currentPS = handleID;
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

	bool CShader_D3D11::compileHLSLToFile(const FilePath& hlsl, const FilePath& to, const char* entryPoint, const char* target)
	{
		BinaryReader reader(hlsl);
		ByteArray binary;

		if (!compileHLSL(reader, binary, hlsl.narrow().c_str(), entryPoint, target))
		{
			return false;
		}

		return binary.save(to);
	}
}

# endif
