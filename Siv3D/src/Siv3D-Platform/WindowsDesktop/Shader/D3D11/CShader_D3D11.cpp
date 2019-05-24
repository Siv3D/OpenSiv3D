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

# include <Siv3D/Windows.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CShader_D3D11.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr std::array<uint8, 4> DXBC_FourCC = { 'D', 'X', 'B', 'C' };

		bool LookaheadFourCC(const IReader& reader, std::array<uint8, 4>& fourcc)
		{
			if (!reader.isOpened() || reader.size() == 0 || !reader.supportsLookahead())
			{
				return false;
			}

			return reader.lookahead(fourcc);
		}

		bool CompileHLSL(decltype(D3DCompile2)* pD3DCompile2, IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target)
		{
			LOG_TRACE(U"CompileHLSL(filePath = {}, entryPoint = {}, target = {})"_fmt(
				Unicode::Widen(filePath), Unicode::Widen(entryPoint), Unicode::Widen(target)));

			if (!pD3DCompile2)
			{
				return false;
			}

			Array<Byte> shaderData(static_cast<size_t>(reader.size()));
			reader.read(shaderData.data(), shaderData.size());

			const bool preferFlow = false;
			const uint32 flags =
				D3DCOMPILE_ENABLE_STRICTNESS
				| D3DCOMPILE_OPTIMIZATION_LEVEL3
				| D3DCOMPILE_WARNINGS_ARE_ERRORS
				| (preferFlow ? D3DCOMPILE_PREFER_FLOW_CONTROL : 0);

			ComPtr<ID3DBlob> blob, error;
			const HRESULT hr = pD3DCompile2(shaderData.data(), shaderData.size(), filePath, nullptr, nullptr,
				entryPoint, target, flags, 0, 0, nullptr, 0, &blob, &error);

			if (error)
			{
				::OutputDebugStringA((const char*)error->GetBufferPointer());
			}

			if (FAILED(hr))
			{
				LOG_FAIL(U"✖ D3DCompile2() failed");
				return false;
			}

			return to.create(blob->GetBufferPointer(), blob->GetBufferSize());
		}
	}

	CShader_D3D11::CShader_D3D11()
	{

	}

	CShader_D3D11::~CShader_D3D11()
	{
		LOG_TRACE(U"CShader_D3D11::~CShader_D3D11()");

		m_pixelShaders.destroy();
		m_vertexShaders.destroy();
	}

	void CShader_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		LOG_TRACE(U"CShader_D3D11::init()");

		m_device = device;
		m_context = context;

		m_d3dcompiler = DLL::LoadSystemLibrary(L"d3dcompiler_47.dll");

		if (m_d3dcompiler)
		{
			p_D3DCompile2 = DLL::GetFunctionNoThrow(m_d3dcompiler, "D3DCompile2");
		}

	# if 0

		compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/sprite.vs", "VS", "vs_4_0");
		compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/shape.ps", "PS_Shape", "ps_4_0");
		compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/texture.ps", "PS_Texture", "ps_4_0");
		compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/square_dot.ps", "PS_SquareDot", "ps_4_0");
		compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/round_dot.ps", "PS_RoundDot", "ps_4_0");
		compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/sdf.ps", "PS_SDF", "ps_4_0");
		compileHLSLToFile(U"engine/shader/fullscreen_triangle.hlsl", U"engine/shader/fullscreen_triangle_resolve.vs", "VS_Resolve", "vs_4_0");
		compileHLSLToFile(U"engine/shader/fullscreen_triangle.hlsl", U"engine/shader/fullscreen_triangle_draw.vs", "VS_Draw", "vs_4_0");
		compileHLSLToFile(U"engine/shader/fullscreen_triangle_resolve.hlsl", U"engine/shader/fullscreen_triangle_resolve.ps", "PS", "ps_4_0");
		compileHLSLToFile(U"engine/shader/fullscreen_triangle_draw.hlsl", U"engine/shader/fullscreen_triangle_draw.ps", "PS", "ps_4_0");
		compileHLSLToFile(U"engine/shader/fullscreen_triangle_draw.hlsl", U"engine/shader/fullscreen_triangle_draw.ps", "PS", "ps_4_0");

	# endif

		{
			auto nullVertexShader = std::make_unique<VertexShader_D3D11>(VertexShader_D3D11::Null{});

			if (!nullVertexShader->isInitialized())
			{
				throw EngineError(U"Null VertexShader initialization failed");
			}

			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}

		{
			auto nullPixelShader = std::make_unique<PixelShader_D3D11>(PixelShader_D3D11::Null{});

			if (!nullPixelShader->isInitialized())
			{
				throw EngineError(U"Null PixelShader initialization failed");
			}

			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}

		LOG_INFO(U"ℹ️ CShader_D3D11 initialized");
	}

	VertexShaderID CShader_D3D11::createVS(ByteArray&& binary, const Array<BindingPoint>&)
	{
		auto vertexShader = std::make_unique<VertexShader_D3D11>(std::move(binary), m_device);

		if (!vertexShader->isInitialized())
		{
			return VertexShaderID::NullAsset();
		}

		return m_vertexShaders.add(std::move(vertexShader));
	}

	VertexShaderID CShader_D3D11::createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints)
	{
		BinaryReader reader(path);
		{
			std::array<uint8, 4> fourcc;

			if (!detail::LookaheadFourCC(reader, fourcc))
			{
				return VertexShaderID::NullAsset();
			}

			const bool isBinary = (fourcc == detail::DXBC_FourCC);

			if (isBinary)// compiled HLSL shader
			{
				return createVS(reader.readAll(), bindingPoints);
			}
		}

		ByteArray memory;

		if (!detail::CompileHLSL(p_D3DCompile2, reader, memory, reader.path().narrow().c_str(), "VS", "vs_4_0"))
		{
			return VertexShaderID::NullAsset();
		}

		return createVS(std::move(memory), bindingPoints);
	}

	PixelShaderID CShader_D3D11::createPS(ByteArray&& binary, const Array<BindingPoint>&)
	{
		auto pixelShader = std::make_unique<PixelShader_D3D11>(std::move(binary), m_device);

		if (!pixelShader->isInitialized())
		{
			return PixelShaderID::NullAsset();
		}

		return m_pixelShaders.add(std::move(pixelShader));
	}

	PixelShaderID CShader_D3D11::createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints)
	{
		BinaryReader reader(path);
		{
			std::array<uint8, 4> fourcc;

			if (!detail::LookaheadFourCC(reader, fourcc))
			{
				return PixelShaderID::NullAsset();
			}

			const bool isBinary = (fourcc == detail::DXBC_FourCC);

			if (isBinary)// compiled HLSL shader
			{
				return createPS(reader.readAll(), bindingPoints);
			}
		}

		ByteArray memory;

		if (!detail::CompileHLSL(p_D3DCompile2, reader, memory, reader.path().narrow().c_str(), "PS", "ps_4_0"))
		{
			return PixelShaderID::NullAsset();
		}

		return createPS(std::move(memory), bindingPoints);
	}

	//PixelShaderID CShader_D3D11::createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints)
	//{

	//}

	void CShader_D3D11::release(const VertexShaderID handleID)
	{
		m_vertexShaders.erase(handleID);
	}

	void CShader_D3D11::release(const PixelShaderID handleID)
	{
		m_pixelShaders.erase(handleID);
	}

	ByteArrayView CShader_D3D11::getBinaryView(const VertexShaderID handleID)
	{
		return m_vertexShaders[handleID]->getView();
	}

	ByteArrayView CShader_D3D11::getBinaryView(const PixelShaderID handleID)
	{
		return m_pixelShaders[handleID]->getView();
	}

	void CShader_D3D11::setVS(const VertexShaderID handleID)
	{
		m_context->VSSetShader(m_vertexShaders[handleID]->getShader(), nullptr, 0);
	}

	void CShader_D3D11::setPS(const PixelShaderID handleID)
	{
		m_context->PSSetShader(m_pixelShaders[handleID]->getShader(), nullptr, 0);
	}

	void CShader_D3D11::compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target)
	{
		if (!p_D3DCompile2)
		{
			throw EngineError(U"CShader_D3D11::compileHLSL() failed: p_D3DCompile2 is null");
		}

		Array<Byte> shaderData(static_cast<size_t>(reader.size()));

		reader.read(shaderData.data(), shaderData.size());

		const bool preferFlow = false;
		const uint32 flags =
			  D3DCOMPILE_ENABLE_STRICTNESS
			| D3DCOMPILE_OPTIMIZATION_LEVEL3
			| D3DCOMPILE_WARNINGS_ARE_ERRORS
			| (preferFlow ? D3DCOMPILE_PREFER_FLOW_CONTROL : 0);

		ComPtr<ID3DBlob> blob, error;
		const HRESULT hr = p_D3DCompile2(shaderData.data(), shaderData.size(), filePath, nullptr, nullptr,
			entryPoint, target, flags, 0, 0, nullptr, 0, &blob, &error);

		if (error)
		{
			::OutputDebugStringA((const char*)error->GetBufferPointer());
		}

		if (FAILED(hr))
		{
			throw EngineError(U"CShader_D3D11::compileHLSL() failed");
		}

		to.create(blob->GetBufferPointer(), blob->GetBufferSize());
	}

	void CShader_D3D11::compileHLSLToFile(const FilePath& hlsl, const FilePath& to, const char* entryPoint, const char* target)
	{
		BinaryReader reader(hlsl);

		if (!reader)
		{
			throw EngineError(U"CShader_D3D11::compileHLSLToFile() failed to open {}"_fmt(hlsl));
		}

		ByteArray binary;
		
		compileHLSL(reader, binary, hlsl.narrow().c_str(), entryPoint, target);

		if (!binary.save(to))
		{
			throw EngineError(U"CShader_D3D11::compileHLSLToFile() BinaryReader::save({}) failed"_fmt(to));
		}
	}
}
