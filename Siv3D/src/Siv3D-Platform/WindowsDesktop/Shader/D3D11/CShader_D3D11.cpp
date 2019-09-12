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
		// IReader から 4 バイト読み込む
		static bool LookaheadFourCC(const IReader& reader, std::array<uint8, 4>& fourcc)
		{
			if (!reader.isOpened() || reader.size() == 0 || !reader.supportsLookahead())
			{
				return false;
			}

			return reader.lookahead(fourcc);
		}

		// 4 バイトの FourCC が、コンパイル済みシェーダ "DXBC" かを調べる
		constexpr bool IsDXBC_FourCC(const std::array<uint8, 4>& fourCC) noexcept
		{
			return fourCC[0] == 'D'
				&& fourCC[1] == 'X'
				&& fourCC[2] == 'B'
				&& fourCC[3] == 'C';
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
		LOG_TRACE(U"CShader_D3D11::~CShader_D3D11()");

		// PS の管理を破棄
		m_pixelShaders.destroy();

		// VS の管理を破棄
		m_vertexShaders.destroy();
	}

	void CShader_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		LOG_TRACE(U"CShader_D3D11::init()");

		// device と context をコピー
		{
			m_device = device;
			m_context = context;
		}

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
			compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/sprite.vs", ShaderStage::Vertex, U"VS");
			compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/shape.ps", ShaderStage::Pixel, U"PS_Shape");
			compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/texture.ps", ShaderStage::Pixel, U"PS_Texture");
			compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/square_dot.ps", ShaderStage::Pixel, U"PS_SquareDot");
			compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/round_dot.ps", ShaderStage::Pixel, U"PS_RoundDot");
			compileHLSLToFile(U"engine/shader/sprite.hlsl", U"engine/shader/sdf.ps", ShaderStage::Pixel, U"PS_SDF");
			compileHLSLToFile(U"engine/shader/fullscreen_triangle.hlsl", U"engine/shader/fullscreen_triangle_resolve.vs", ShaderStage::Vertex, U"VS_Resolve");
			compileHLSLToFile(U"engine/shader/fullscreen_triangle.hlsl", U"engine/shader/fullscreen_triangle_draw.vs", ShaderStage::Vertex, U"VS_Draw");
			compileHLSLToFile(U"engine/shader/fullscreen_triangle_resolve.hlsl", U"engine/shader/fullscreen_triangle_resolve.ps", ShaderStage::Pixel, U"PS");
			compileHLSLToFile(U"engine/shader/fullscreen_triangle_draw.hlsl", U"engine/shader/fullscreen_triangle_draw.ps", ShaderStage::Pixel, U"PS");

			compileHLSLToFile(U"engine/shader/copy.hlsl", U"engine/shader/copy.ps", ShaderStage::Pixel, U"PS");
			compileHLSLToFile(U"engine/shader/gaussian_blur_9.hlsl", U"engine/shader/copy.ps", ShaderStage::Pixel, U"PS");
		}

	# endif

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<VertexShader_D3D11>(VertexShader_D3D11::Null{});

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
			auto nullPixelShader = std::make_unique<PixelShader_D3D11>(PixelShader_D3D11::Null{});

			if (!nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null PixelShader initialization failed");
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}

		//m_enginePSs << PixelShader();

		LOG_INFO(U"ℹ️ CShader_D3D11 initialized");
	}

	VertexShaderID CShader_D3D11::createVS(ByteArray&& binary, const Array<ConstantBufferBinding>&)
	{
		// VS を作成
		auto vertexShader = std::make_unique<VertexShader_D3D11>(std::move(binary), m_device);

		if (!vertexShader->isInitialized()) // もし作成に失敗していたら
		{
			return VertexShaderID::NullAsset();
		}

		// VS を管理に登録
		return m_vertexShaders.add(std::move(vertexShader));
	}

	VertexShaderID CShader_D3D11::createVSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings)
	{
		// HLSL ソースコード
		ByteArray hlslSourceCode;
		{
			// シェーダファイルをオープン
			BinaryReader reader(path);

			if (!reader) // もしオープンに失敗したら
			{
				LOG_FAIL(U"CShader_D3D11::createVSFromFile(): failed to open `{}`"_fmt(path));
				return VertexShaderID::NullAsset();
			}

			// FourCC
			std::array<uint8, 4> fourCC;

			// FourCC を読み込み
			if (!detail::LookaheadFourCC(reader, fourCC))
			{
				LOG_FAIL(U"CShader_D3D11::createVSFromFile(): LookaheadFourCC() failed");
				return VertexShaderID::NullAsset();
			}

			if (detail::IsDXBC_FourCC(fourCC)) // もしコンパイル済みのバイナリなら
			{
				// そのまま VS を作成
				LOG_DEBUG(U"CShader_D3D11::createVSFromFile(): `{}` is a precompiled shader file"_fmt(path));
				return createVS(reader.readAll(), bindings);
			}

			// HLSL ソースコード
			hlslSourceCode = reader.readAll();
		}

		// コンパイル結果の格納先
		ByteArray compiledBinary;

		// HLSL のコンパイル
		if (!compileHLSL(hlslSourceCode.data(), hlslSourceCode.size(), compiledBinary, path, ShaderStage::Vertex, U"VS"))
		{
			LOG_FAIL(U"CShader_D3D11::createVSFromFile(): compileHLSL() failed");
			return VertexShaderID::NullAsset();
		}

		// VS を作成
		return createVS(std::move(compiledBinary), bindings);
	}

	PixelShaderID CShader_D3D11::createPS(ByteArray&& binary, const Array<ConstantBufferBinding>&)
	{
		// PS を作成
		auto pixelShader = std::make_unique<PixelShader_D3D11>(std::move(binary), m_device);

		if (!pixelShader->isInitialized()) // もし作成に失敗していたら
		{
			return PixelShaderID::NullAsset();
		}

		// PS を管理に登録
		return m_pixelShaders.add(std::move(pixelShader));
	}

	PixelShaderID CShader_D3D11::createPSFromFile(const FilePath& path, const Array<ConstantBufferBinding>& bindings)
	{
		// HLSL ソースコード
		ByteArray hlslSourceCode;
		{
			// シェーダファイルをオープン
			BinaryReader reader(path);

			if (!reader) // もしオープンに失敗したら
			{
				LOG_FAIL(U"CShader_D3D11::createPSFromFile(): failed to open `{}`"_fmt(path));
				return PixelShaderID::NullAsset();
			}

			// FourCC
			std::array<uint8, 4> fourCC;

			// FourCC を読み込み
			if (!detail::LookaheadFourCC(reader, fourCC))
			{
				LOG_FAIL(U"CShader_D3D11::createPSFromFile(): LookaheadFourCC() failed");
				return PixelShaderID::NullAsset();
			}

			if (detail::IsDXBC_FourCC(fourCC)) // もしコンパイル済みのバイナリなら
			{
				// そのまま PS を作成
				LOG_DEBUG(U"CShader_D3D11::createVSFromFile(): `{}` is a precompiled shader file"_fmt(path));
				return createPS(reader.readAll(), bindings);
			}

			// HLSL ソースコード
			hlslSourceCode = reader.readAll();
		}

		// コンパイル結果の格納先
		ByteArray compiledBinary;

		// HLSL のコンパイル
		if (!compileHLSL(hlslSourceCode.data(), hlslSourceCode.size(), compiledBinary, path, ShaderStage::Pixel, U"PS"))
		{
			LOG_FAIL(U"CShader_D3D11::createVSFromFile(): compileHLSL() failed");
			return PixelShaderID::NullAsset();
		}

		// PS を作成
		return createPS(std::move(compiledBinary), bindings);
	}

	//PixelShaderID CShader_D3D11::createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints)
	//{

	//}

	void CShader_D3D11::release(const VertexShaderID handleID)
	{
		// 指定した VS を管理から除外
		m_vertexShaders.erase(handleID);
	}

	void CShader_D3D11::release(const PixelShaderID handleID)
	{
		// 指定した PS を管理から除外
		m_pixelShaders.erase(handleID);
	}

	ByteArrayView CShader_D3D11::getBinaryView(const VertexShaderID handleID)
	{
		// 指定した VS のバイナリを取得
		return m_vertexShaders[handleID]->getView();
	}

	ByteArrayView CShader_D3D11::getBinaryView(const PixelShaderID handleID)
	{
		// 指定した PS のバイナリを取得
		return m_pixelShaders[handleID]->getView();
	}

	void CShader_D3D11::setVS(const VertexShaderID handleID)
	{
		// 指定した VS を context にセット
		m_context->VSSetShader(m_vertexShaders[handleID]->getShader(), nullptr, 0);
	}

	void CShader_D3D11::setPS(const PixelShaderID handleID)
	{
		// 指定した PS を context にセット
		m_context->PSSetShader(m_pixelShaders[handleID]->getShader(), nullptr, 0);
	}

	bool CShader_D3D11::hasHLSLCompiler() const noexcept
	{
		// D3DCompile2 関数が利用できるなら true
		return (p_D3DCompile2 != nullptr);
	}

	bool CShader_D3D11::compileHLSLToFile(const FilePath& hlslFilePath, const FilePath& toFilePath, const ShaderStage stage, const String& entryPoint, uint32 flags) const
	{
		LOG_TRACE(U"CShader_D3D11::compileHLSLToFile(hlslFilePath = {}, stage = {}, entryPoint = {}, flags = {:#X})"_fmt(
			hlslFilePath, Unicode::Widen(detail::StageToTarget(stage)), entryPoint, flags));

		// HLSL ソースコード
		ByteArray hlslSourceCode;
		{
			// HLSL ファイルをオープン
			BinaryReader reader(hlslFilePath);

			if (!reader) // もしオープンに失敗したら
			{
				LOG_FAIL(U"CShader_D3D11::compileHLSLToFile(): failed to open `{}`"_fmt(hlslFilePath));
				return false;
			}

			// HLSL ソースコードを読み込み
			hlslSourceCode = reader.readAll();
		}

		// コンパイル結果の格納先
		ByteArray compiledBinary;

		// HLSL のコンパイル
		if (!compileHLSL(hlslSourceCode.data(), hlslSourceCode.size(), compiledBinary, hlslFilePath, stage, entryPoint, flags))
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSLToFile(): compileHLSL() failed");
			return false;
		}

		// コンパイル結果をファイルに保存
		if (!compiledBinary.save(toFilePath))
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSLToFile(): compiledBinary.save({}) failed"_fmt(toFilePath));
			return false;
		}

		return true;
	}

	bool CShader_D3D11::compileHLSL(const void* hlslSourceCode, const size_t hlslSourceCodeSize, ByteArray& to, const FilePath& path_hint, ShaderStage stage, const String& entryPoint, uint32 flags) const
	{
		if (!hasHLSLCompiler()) // もし HLSL コンパイラが利用不可なら
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSL() failed: !hasShaderCompiler()");
			return false;
		}

		// HLSL ソースコードのコンパイル
		ComPtr<ID3DBlob> blob, error;
		const HRESULT hr = p_D3DCompile2(hlslSourceCode, hlslSourceCodeSize,
			path_hint.narrow().c_str(), nullptr, nullptr,
			entryPoint.narrow().c_str(),
			detail::StageToTarget(stage),
			flags,
			0, 0, nullptr, 0, &blob, &error);

		if (error) // もしエラーメッセージがあれば
		{
			const std::string errorMessgae = static_cast<const char*>(error->GetBufferPointer());
			LOG_FAIL(U"CShader_D3D11::compileHLSL(): D3DCompile2(): {}"_fmt(Unicode::Widen(errorMessgae)));
		}

		if (FAILED(hr)) // 失敗したら
		{
			LOG_FAIL(U"CShader_D3D11::compileHLSL(): D3DCompile2() failed");
			return false;
		}

		// コンパイルしたバイナリデータを返す
		return to.create(blob->GetBufferPointer(), blob->GetBufferSize());
	}
}
