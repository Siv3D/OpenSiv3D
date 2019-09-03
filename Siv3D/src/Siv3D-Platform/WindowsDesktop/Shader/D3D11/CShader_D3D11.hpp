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

# pragma once
# include <Siv3D/Windows.hpp>
# include <Siv3D/Shader.hpp>
# include <Shader/IShader.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include <d3dcompiler.h>
# include "VertexShader_D3D11.hpp"
# include "PixelShader_D3D11.hpp"

namespace s3d
{
	class CShader_D3D11 : public ISiv3DShader
	{
	private:

		// device のコピー
		ID3D11Device* m_device = nullptr;

		// context のコピー
		ID3D11DeviceContext* m_context = nullptr;

		// HLSL コンパイラ用の DLL (d3dcompiler_47.dll)
		HMODULE m_d3dcompiler = nullptr;

		// D3DCompile2() 関数
		decltype(D3DCompile2)* p_D3DCompile2 = nullptr;

		// VS の管理
		AssetHandleManager<VertexShaderID, VertexShader_D3D11> m_vertexShaders{ U"VertexShader" };
		
		// PS の管理
		AssetHandleManager<PixelShaderID, PixelShader_D3D11> m_pixelShaders{ U"PixelShader" };

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		// 初期化
		void init(ID3D11Device* device, ID3D11DeviceContext* context);

		// コンパイル済みシェーダから VS を作成
		VertexShaderID createVS(ByteArray&& binary, const Array<BindingPoint>& bindingPoints) override;
		
		// シェーダファイル（ソースコードまたはコンパイル済みバイナリ）から VS を作成
		VertexShaderID createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;	
		//VertexShaderID createVSFromSource(const String&, const Array<BindingPoint>&) override

		// コンパイル済みシェーダから PS を作成
		PixelShaderID createPS(ByteArray&& binary, const Array<BindingPoint>& bindingPoints) override;
		
		// シェーダファイル（ソースコードまたはコンパイル済みバイナリ）から PS を作成
		PixelShaderID createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) override;
		//PixelShaderID createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) override;

		// 指定した VS を管理から除外
		void release(VertexShaderID handleID) override;
		
		// 指定した PS を管理から除外
		void release(PixelShaderID handleID) override;

		// 指定した VS のバイナリを取得
		ByteArrayView getBinaryView(VertexShaderID handleID) override;

		// 指定した PS のバイナリを取得
		ByteArrayView getBinaryView(PixelShaderID handleID) override;

		// 指定した VS を context にセット
		void setVS(VertexShaderID handleID) override;
		
		// 指定した PS を context にセット
		void setPS(PixelShaderID handleID) override;

		// HLSL シェーダコンパイラが利用可能かを返す
		bool hasHLSLCompiler() const noexcept;

		// HLSL ファイルをコンパイルしてコンパイル結果をファイルに保存
		bool compileHLSLToFile(const FilePath& hlslFilePath, const FilePath& toFilePath, ShaderStage stage, const String& entryPoint, uint32 flags = Platform::Windows::Shader::HLSLCompileOption::Default) const;

		// HLSL ソースコードをコンパイルして結果を ByteArray に格納
		bool compileHLSL(const void* hlslSourceCode, size_t hlslSourceCodeSize, ByteArray& to, const FilePath& path_hint, ShaderStage stage, const String& entryPoint, uint32 flags = Platform::Windows::Shader::HLSLCompileOption::Default) const;
	};
}
