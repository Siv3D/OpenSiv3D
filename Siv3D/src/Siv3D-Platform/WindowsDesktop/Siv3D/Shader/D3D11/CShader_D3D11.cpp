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

# include "CShader_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/ConstantBuffer/D3D11/ConstantBufferDetail_D3D11.hpp>

namespace s3d
{
	namespace detail
	{
		// 4 バイトの FourCC が、コンパイル済みシェーダ "DXBC" かを調べる
		[[nodiscard]]
		static bool IsDXBC(const Blob& blob) noexcept
		{
			if (blob.size() < 4)
			{
				return false;
			}

			return (blob[0] == Byte{ 'D' })
				&& (blob[1] == Byte{ 'X' })
				&& (blob[2] == Byte{ 'B' })
				&& (blob[3] == Byte{ 'C' });
		}

		// ShaderStage から Target 名への変換
		constexpr const char* StageToTarget(ShaderStage stage) noexcept
		{
			switch (stage)
			{
			case ShaderStage::Vertex:
				return "vs_4_0";
			case ShaderStage::Pixel:
				return "ps_4_0";
			default:
				return "";
			}
		}
	}

	CShader_D3D11::CShader_D3D11()
	{

	}

	CShader_D3D11::~CShader_D3D11()
	{
		LOG_SCOPED_TRACE(U"CShader_D3D11::~CShader_D3D11()");
		m_pixelShaders.destroy();
		m_vertexShaders.destroy();
	}

	void CShader_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CShader_D3D11::init()");

		pRenderer	= dynamic_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer));
		m_device	= pRenderer->getDevice();
		m_context	= pRenderer->getContext();

		// HLSL コンパイラをロード
		{
			// HLSL コンパイラ用の DLL をロード
			m_d3dcompiler = DLL::LoadSystemLibrary(L"d3dcompiler_47.dll");

			if (m_d3dcompiler) // ロードに成功 (Windows 8.1 以降か、最新の D3D ランタイムをインストールした Windows 7 ならここ）
			{
				LOG_INFO(U"`d3dcompiler_47.dll` found");

				// D3DCompile2() 関数を見つける
				p_D3DCompile2 = DLL::GetFunctionNoThrow(m_d3dcompiler, "D3DCompile2");

				if (p_D3DCompile2) // もし D3DCompile2() 関数が見つかったら
				{
					LOG_INFO(U"HLSL compiler is available");
				}
				else // もし見つからなかったら
				{
					LOG_WARNING(U"HLSL compiler is not available");
				}
			}
			else // ロードに失敗
			{
				LOG_INFO(U"`d3dcompiler_47.dll` not found. HLSL compiler is not available");
			}
		}

	# if 0

		// エンジン用 HLSL シェーダをコンパイル
		{
			compileHLSL(U"engine/shader/d3d11/fullscreen_triangle.hlsl", ShaderStage::Vertex, U"VS")
				.save(U"engine/shader/d3d11/fullscreen_triangle.vs");

			compileHLSL(U"engine/shader/d3d11/fullscreen_triangle.hlsl", ShaderStage::Pixel, U"PS")
				.save(U"engine/shader/d3d11/fullscreen_triangle.ps");

			compileHLSL(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Vertex, U"VS")
				.save(U"engine/shader/d3d11/sprite.vs");

			compileHLSL(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_Shape")
				.save(U"engine/shader/d3d11/shape.ps");

			throw EngineError(U"Engine shaders have compiled. Please rebuild the project.");
		}

	# endif

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<D3D11VertexShader>(D3D11VertexShader::Null{});

			if (!nullVertexShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null VertexShader initialization failed");
			}

			// 管理に登録
			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}

		// null PS を管理に登録
		{
			// null PS を作成
			auto nullPixelShader = std::make_unique<D3D11PixelShader>(D3D11PixelShader::Null{});

			if (!nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null PixelShader initialization failed");
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}
	}

	VertexShader::IDType CShader_D3D11::createVSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		Blob blob{ path };

		if (not blob)
		{
			LOG_FAIL(U"CShader_D3D11::createVS(): failed to load data from `{}`"_fmt(path));
			return VertexShader::IDType::NullAsset();
		}

		if (detail::IsDXBC(blob)) // もしコンパイル済みのバイナリなら
		{
			// そのまま VS を作成
			LOG_TRACE(U"CShader_D3D11::createVS(): `{}` is a precompiled shader file"_fmt(path));
			return createVS(std::move(blob), bindings);
		}
		
		Blob binary = compileHLSLFromFile(path, ShaderStage::Vertex, entryPoint);

		return createVS(std::move(binary), bindings);
	}

	VertexShader::IDType CShader_D3D11::createVSFromSource(const StringView source, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		Blob binary = compileHLSLFromSource(source, ShaderStage::Vertex, entryPoint);

		return createVS(std::move(binary), bindings);
	}

	VertexShader::IDType CShader_D3D11::createVS(Blob&& binary, const Array<ConstantBufferBinding>&)
	{
		// VS を作成
		auto vertexShader = std::make_unique<D3D11VertexShader>(std::move(binary), m_device);

		if (!vertexShader->isInitialized()) // もし作成に失敗していたら
		{
			return VertexShader::IDType::NullAsset();
		}

		// VS を管理に登録
		return m_vertexShaders.add(std::move(vertexShader));
	}

	PixelShader::IDType CShader_D3D11::createPSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		Blob blob{ path };

		if (not blob)
		{
			LOG_FAIL(U"CShader_D3D11::createPS(): failed to load data from `{}`"_fmt(path));
			return PixelShader::IDType::NullAsset();
		}

		if (detail::IsDXBC(blob)) // もしコンパイル済みのバイナリなら
		{
			// そのまま VS を作成
			LOG_TRACE(U"CShader_D3D11::createVS(): `{}` is a precompiled shader file"_fmt(path));
			return createPS(std::move(blob), bindings);
		}

		Blob binary = compileHLSLFromFile(path, ShaderStage::Pixel, entryPoint);

		return createPS(std::move(binary), bindings);
	}

	PixelShader::IDType CShader_D3D11::createPSFromSource(const StringView source, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		Blob binary = compileHLSLFromSource(source, ShaderStage::Pixel, entryPoint);

		return createPS(std::move(binary), bindings);
	}

	PixelShader::IDType CShader_D3D11::createPS(Blob&& binary, const Array<ConstantBufferBinding>&)
	{
		// PS を作成
		auto pixelShader = std::make_unique<D3D11PixelShader>(std::move(binary), m_device);

		if (!pixelShader->isInitialized()) // もし作成に失敗していたら
		{
			return PixelShader::IDType::NullAsset();
		}

		// PS を管理に登録
		return m_pixelShaders.add(std::move(pixelShader));
	}

	void CShader_D3D11::releaseVS(const VertexShader::IDType handleID)
	{
		// 指定した VS を管理から除外
		m_vertexShaders.erase(handleID);
	}

	void CShader_D3D11::releasePS(const PixelShader::IDType handleID)
	{
		// 指定した PS を管理から除外
		m_pixelShaders.erase(handleID);
	}

	void CShader_D3D11::setVS(const VertexShader::IDType handleID)
	{
		// 指定した VS を context にセット
		m_context->VSSetShader(m_vertexShaders[handleID]->getShader(), nullptr, 0);
	}

	void CShader_D3D11::setPS(const PixelShader::IDType handleID)
	{
		// 指定した PS を context にセット
		m_context->PSSetShader(m_pixelShaders[handleID]->getShader(), nullptr, 0);
	}

	const Blob& CShader_D3D11::getBinaryVS(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getBinary();
	}

	const Blob& CShader_D3D11::getBinaryPS(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getBinary();
	}

	bool CShader_D3D11::hasHLSLCompiler() const noexcept
	{
		// D3DCompile2 関数が利用できるなら true
		return (p_D3DCompile2 != nullptr);
	}

	void CShader_D3D11::setConstantBufferVS(const uint32 slot, const ConstantBufferBase& cb)
	{
		assert(slot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);

		const auto pCB = dynamic_cast<const ConstantBufferDetail_D3D11*>(cb._detail());

		m_context->VSSetConstantBuffers(slot, 1, pCB->getBufferPtr());
	}

	void CShader_D3D11::setConstantBufferPS(const uint32 slot, const ConstantBufferBase& cb)
	{
		assert(slot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
		
		const auto pCB = dynamic_cast<const ConstantBufferDetail_D3D11*>(cb._detail());

		m_context->PSSetConstantBuffers(slot, 1, pCB->getBufferPtr());
	}


	Blob CShader_D3D11::compileHLSLFromFile(const FilePathView path, const ShaderStage stage, const StringView entryPoint, const Platform::Windows::HLSLCompileOption flags) const
	{
		LOG_TRACE(U"CShader_D3D11::compileHLSLFromFile(path = {}, stage = {}, entryPoint = {}, flags = {:#X})"_fmt(
			path, Unicode::Widen(detail::StageToTarget(stage)), entryPoint, flags));

		TextReader reader{ path };

		if (!reader)
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSLFromFile(): failed to load source from `{}`"_fmt(path));
			return{};
		}

		const std::string sourceUTF8 = reader.readAll().toUTF8();
		return compileHLSL(sourceUTF8, path, stage, entryPoint, flags);
	}

	Blob CShader_D3D11::compileHLSLFromSource(const StringView source, const ShaderStage stage, const StringView entryPoint, const Platform::Windows::HLSLCompileOption flags) const
	{
		LOG_TRACE(U"CShader_D3D11::compileHLSLFromSource(stage = {}, entryPoint = {}, flags = {:#X})"_fmt(
			Unicode::Widen(detail::StageToTarget(stage)), entryPoint, flags));

		if (!source)
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSLFromSource(): source is empty");
			return{};
		}

		return compileHLSL(source.toUTF8(), U"", stage, entryPoint, flags);
	}

	Blob CShader_D3D11::compileHLSL(const std::string_view sourceUTF8, const FilePathView pathHint, const ShaderStage stage, const StringView entryPoint, const Platform::Windows::HLSLCompileOption flags) const
	{
		if (!hasHLSLCompiler()) // もし HLSL コンパイラが利用不可なら
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSL() failed: !hasShaderCompiler()");
			return{};
		}

		// HLSL ソースコードのコンパイル
		ComPtr<ID3DBlob> binary, error;
		const HRESULT hr = p_D3DCompile2(sourceUTF8.data(), sourceUTF8.size(),
			pathHint.narrow().c_str(), nullptr, nullptr,
			entryPoint.narrow().c_str(),
			detail::StageToTarget(stage),
			FromEnum(flags),
			0, 0, nullptr, 0, &binary, &error);

		if (error) // もしエラーメッセージがあれば
		{
			const std::string errorMessgae = static_cast<const char*>(error->GetBufferPointer());
			LOG_FAIL(U"CShader_D3D11::compileHLSL(): D3DCompile2(): {}"_fmt(Unicode::Widen(errorMessgae)));
		}

		if (FAILED(hr)) // 失敗したら
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSL(): D3DCompile2() failed");
			return{};
		}

		// コンパイルしたバイナリデータを返す
		return Blob{ binary->GetBufferPointer(), binary->GetBufferSize() };
	}
}
