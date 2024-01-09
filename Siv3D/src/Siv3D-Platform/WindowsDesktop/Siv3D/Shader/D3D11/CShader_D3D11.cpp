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

# include "CShader_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Resource.hpp>
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

		// エンジン PS を破棄
		m_enginePSs.clear();

		// エンジン VS を破棄
		m_engineVSs.clear();

		// PS の管理を破棄
		m_pixelShaders.destroy();

		// VS の管理を破棄
		m_vertexShaders.destroy();
	}

	void CShader_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CShader_D3D11::init()");

		pRenderer	= static_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer));
		m_device	= pRenderer->getDevice();
		m_context	= pRenderer->getContext();

	# if 0

		// エンジン用 HLSL シェーダをコンパイル
		{
			//compileHLSLFromFile(U"engine/shader/d3d11/fullscreen_triangle.hlsl", ShaderStage::Vertex, U"VS")
			//	.save(U"engine/shader/d3d11/fullscreen_triangle.vs");

			//compileHLSLFromFile(U"engine/shader/d3d11/fullscreen_triangle.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/fullscreen_triangle.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Vertex, U"VS")
			//	.save(U"engine/shader/d3d11/sprite.vs");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_Shape")
			//	.save(U"engine/shader/d3d11/shape.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_SquareDot")
			//	.save(U"engine/shader/d3d11/square_dot.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_RoundDot")
			//	.save(U"engine/shader/d3d11/round_dot.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_Texture")
			//	.save(U"engine/shader/d3d11/texture.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_BitmapFont")
			//	.save(U"engine/shader/d3d11/bitmapfont.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_SDFFont")
			//	.save(U"engine/shader/d3d11/sdffont.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_SDFFont_Outline")
			//	.save(U"engine/shader/d3d11/sdffont_outline.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_SDFFont_Shadow")
			//	.save(U"engine/shader/d3d11/sdffont_shadow.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_SDFFont_OutlineShadow")
			//	.save(U"engine/shader/d3d11/sdffont_outlineshadow.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_MSDFFont")
			//	.save(U"engine/shader/d3d11/msdffont.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_MSDFFont_Outline")
			//	.save(U"engine/shader/d3d11/msdffont_outline.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_MSDFFont_Shadow")
			//	.save(U"engine/shader/d3d11/msdffont_shadow.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_MSDFFont_OutlineShadow")
			//	.save(U"engine/shader/d3d11/msdffont_outlineshadow.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sprite.hlsl", ShaderStage::Pixel, U"PS_MSDFPrint")
			//	.save(U"engine/shader/d3d11/msdfprint.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/forward3d.hlsl", ShaderStage::Vertex, U"VS")
			//	.save(U"engine/shader/d3d11/forward3d.vs");

			//compileHLSLFromFile(U"engine/shader/d3d11/forward3d.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/forward3d.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/line3d.hlsl", ShaderStage::Vertex, U"VS")
			//	.save(U"engine/shader/d3d11/line3d.vs");

			//compileHLSLFromFile(U"engine/shader/d3d11/line3d.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/line3d.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/copy.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/copy.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/gaussian_blur.hlsl", ShaderStage::Pixel, U"Blur5_PS")
			//	.save(U"engine/shader/d3d11/gaussian_blur_5.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/gaussian_blur.hlsl", ShaderStage::Pixel, U"Blur9_PS")
			//	.save(U"engine/shader/d3d11/gaussian_blur_9.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/gaussian_blur.hlsl", ShaderStage::Pixel, U"Blur13_PS")
			//	.save(U"engine/shader/d3d11/gaussian_blur_13.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/apply_srgb_curve.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/apply_srgb_curve.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/quad_warp.hlsl", ShaderStage::Vertex, U"VS")
			//	.save(U"engine/shader/d3d11/quad_warp.vs");

			//compileHLSLFromFile(U"engine/shader/d3d11/quad_warp.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/quad_warp.ps");

			//compileHLSLFromFile(U"engine/shader/d3d11/sky.hlsl", ShaderStage::Pixel, U"PS")
			//	.save(U"engine/shader/d3d11/sky.ps");

			throw EngineError{ U"Engine shaders have compiled. Please rebuild the project." };
		}

	# endif

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<D3D11VertexShader>(D3D11VertexShader::Null{});

			if (not nullVertexShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null VertexShader initialization failed" };
			}

			// 管理に登録
			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}

		// null PS を管理に登録
		{
			// null PS を作成
			auto nullPixelShader = std::make_unique<D3D11PixelShader>(D3D11PixelShader::Null{});

			if (not nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null PixelShader initialization failed" };
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}

		// エンジン VS をロード
		{
			m_engineVSs << HLSL{ Resource(U"engine/shader/d3d11/quad_warp.vs") };

			if (not m_engineVSs.all([](const auto& vs) { return !!vs; })) // もしロードに失敗したシェーダがあれば
			{
				throw EngineError{ U"CShader_D3D11::m_engineVSs initialization failed" };
			}
		}

		// エンジン PS をロード
		{
			m_enginePSs << HLSL{ Resource(U"engine/shader/d3d11/copy.ps") };
			m_enginePSs << HLSL{ Resource(U"engine/shader/d3d11/gaussian_blur_5.ps") };
			m_enginePSs << HLSL{ Resource(U"engine/shader/d3d11/gaussian_blur_9.ps") };
			m_enginePSs << HLSL{ Resource(U"engine/shader/d3d11/gaussian_blur_13.ps") };
			m_enginePSs << HLSL{ Resource(U"engine/shader/d3d11/apply_srgb_curve.ps") };
			m_enginePSs << HLSL{ Resource(U"engine/shader/d3d11/quad_warp.ps") };

			if (not m_enginePSs.all([](const auto& ps) { return !!ps; })) // もしロードに失敗したシェーダがあれば
			{
				throw EngineError{ U"CShader_D3D11::m_enginePSs initialization failed" };
			}
		}
	}

	VertexShader::IDType CShader_D3D11::createVSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		Blob blob{ path };

		if (not blob)
		{
			LOG_FAIL(U"CShader_D3D11::createVSFromFile(): failed to load data from `{}`"_fmt(path));
			return VertexShader::IDType::NullAsset();
		}

		if (detail::IsDXBC(blob)) // もしコンパイル済みのバイナリなら
		{
			// そのまま VS を作成
			LOG_TRACE(U"CShader_D3D11::createVSFromFile(): `{}` is a precompiled shader file"_fmt(path));
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

		if (not vertexShader->isInitialized()) // もし作成に失敗していたら
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
			LOG_FAIL(U"CShader_D3D11::createPSFromFile(): failed to load data from `{}`"_fmt(path));
			return PixelShader::IDType::NullAsset();
		}

		if (detail::IsDXBC(blob)) // もしコンパイル済みのバイナリなら
		{
			// そのまま VS を作成
			LOG_TRACE(U"CShader_D3D11::createPSFromFile(): `{}` is a precompiled shader file"_fmt(path));
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

		if (not pixelShader->isInitialized()) // もし作成に失敗していたら
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
		if (not m_D3DCompile2Available.has_value())
		{
			loadD3DCompile2();
		}

		assert(m_D3DCompile2Available.has_value());

		// D3DCompile2 関数が利用できるなら true
		return *m_D3DCompile2Available;
	}

	bool CShader_D3D11::compileHLSLToFile(const FilePathView hlslFilePath, const FilePathView toFilePath, const ShaderStage stage, const StringView entryPoint, const Platform::Windows::HLSLCompileOption flags) const
	{
		const Blob blob = compileHLSLFromFile(hlslFilePath, stage, entryPoint, flags);

		if (not blob)
		{
			return false;
		}

		return blob.save(toFilePath);
	}

	void CShader_D3D11::setConstantBufferVS(const uint32 slot, const ConstantBufferBase& cb)
	{
		assert(slot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);

		const auto pCB = static_cast<const ConstantBufferDetail_D3D11*>(cb._detail());

		m_context->VSSetConstantBuffers(slot, 1, pCB->getBufferPtr());
	}

	void CShader_D3D11::setConstantBufferPS(const uint32 slot, const ConstantBufferBase& cb)
	{
		assert(slot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
		
		const auto pCB = static_cast<const ConstantBufferDetail_D3D11*>(cb._detail());

		m_context->PSSetConstantBuffers(slot, 1, pCB->getBufferPtr());
	}

	const VertexShader& CShader_D3D11::getEngineVS(const EngineVS vs) const
	{
		return m_engineVSs[FromEnum(vs)];
	}

	const PixelShader& CShader_D3D11::getEnginePS(const EnginePS ps) const
	{
		return m_enginePSs[FromEnum(ps)];
	}

	void CShader_D3D11::setQuadWarpCB(const VS2DQuadWarp& vsCB, const PS2DQuadWarp& psCB)
	{
		m_engineShaderCBs.vs2DQuadWarp = vsCB;
		m_engineShaderCBs.ps2DQuadWarp = psCB;

		Graphics2D::SetVSConstantBuffer(1, m_engineShaderCBs.vs2DQuadWarp);
		Graphics2D::SetPSConstantBuffer(1, m_engineShaderCBs.ps2DQuadWarp);
	}


	void CShader_D3D11::loadD3DCompile2() const
	{
		LOG_SCOPED_TRACE(U"CShader_D3D11::loadD3DCompile2()");

		// HLSL コンパイラをロード
		{
			// HLSL コンパイラ用の DLL をロード
			m_d3dcompiler = DLL::LoadSystemLibraryNoThrow(L"d3dcompiler_47.dll");

			if (m_d3dcompiler) // ロードに成功 (Windows 8.1 以降か、最新の D3D ランタイムをインストールした Windows 7 ならここ）
			{
				LOG_INFO(U"`d3dcompiler_47.dll` found");

				// D3DCompile2() 関数を見つける
				p_D3DCompile2 = DLL::GetFunctionNoThrow(m_d3dcompiler, "D3DCompile2");

				if (p_D3DCompile2) // もし D3DCompile2() 関数が見つかったら
				{
					LOG_INFO(U"HLSL compiler is available");

					m_D3DCompile2Available = true;
				}
				else // もし見つからなかったら
				{
					LOG_WARNING(U"HLSL compiler is not available");

					m_D3DCompile2Available = false;
				}
			}
			else // ロードに失敗
			{
				LOG_INFO(U"`d3dcompiler_47.dll` not found. HLSL compiler is not available");

				m_D3DCompile2Available = false;
			}
		}
	}

	Blob CShader_D3D11::compileHLSLFromFile(const FilePathView path, const ShaderStage stage, const StringView entryPoint, const Platform::Windows::HLSLCompileOption flags) const
	{
		LOG_TRACE(U"CShader_D3D11::compileHLSLFromFile(path = {}, stage = {}, entryPoint = {}, flags = {:#X})"_fmt(
			path, Unicode::Widen(detail::StageToTarget(stage)), entryPoint, FromEnum(flags)));

		TextReader reader{ path };

		if (not reader)
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
			Unicode::Widen(detail::StageToTarget(stage)), entryPoint, FromEnum(flags)));

		if (not source)
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSLFromSource(): source is empty");
			return{};
		}

		return compileHLSL(source.toUTF8(), U"", stage, entryPoint, flags);
	}

	Blob CShader_D3D11::compileHLSL(const std::string_view sourceUTF8, const FilePathView pathHint, const ShaderStage stage, const StringView entryPoint, const Platform::Windows::HLSLCompileOption flags) const
	{
		if (not hasHLSLCompiler()) // もし HLSL コンパイラが利用不可なら
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
			LOG_FAIL(U"CShader_D3D11::compileHLSL(): D3DCompile2(): " + Unicode::Widen(errorMessgae));
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
