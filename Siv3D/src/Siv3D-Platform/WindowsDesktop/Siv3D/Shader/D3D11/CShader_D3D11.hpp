﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/ShaderStatge.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "VertexShader/D3D11VertexShader.hpp"
# include "PixelShader/D3D11PixelShader.hpp"

namespace s3d
{
	class CShader_D3D11 final : public ISiv3DShader
	{
	private:

		CRenderer_D3D11* pRenderer		= nullptr;

		// device のコピー
		ID3D11Device* m_device			= nullptr;

		// context のコピー
		ID3D11DeviceContext* m_context	= nullptr;

		// HLSL コンパイラ用の DLL (d3dcompiler_47.dll)
		HMODULE m_d3dcompiler			= nullptr;

		// D3DCompile2() 関数
		decltype(D3DCompile2)* p_D3DCompile2 = nullptr;

		// VS の管理
		AssetHandleManager<VertexShader::IDType, D3D11VertexShader> m_vertexShaders{ U"VertexShader" };

		// PS の管理
		AssetHandleManager<PixelShader::IDType, D3D11PixelShader> m_pixelShaders{ U"PixelShader" };

		[[nodiscard]]
		Blob compileHLSLFromFile(FilePathView path, ShaderStage stage, StringView entryPoint, Platform::Windows::HLSLCompileOption flags = Platform::Windows::HLSLCompileOption::Default) const;

		[[nodiscard]]
		Blob compileHLSLFromSource(StringView source, ShaderStage stage, StringView entryPoint, Platform::Windows::HLSLCompileOption flags = Platform::Windows::HLSLCompileOption::Default) const;

		[[nodiscard]]
		Blob compileHLSL(std::string_view sourceUTF8, FilePathView pathHint, ShaderStage stage, StringView entryPoint, Platform::Windows::HLSLCompileOption flags = Platform::Windows::HLSLCompileOption::Default) const;

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		void init() override;


		VertexShader::IDType createVSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		VertexShader::IDType createVSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		VertexShader::IDType createVS(Blob&& binary, const Array<ConstantBufferBinding>& bindings);
		
		PixelShader::IDType createPSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPS(Blob&& binary, const Array<ConstantBufferBinding>& bindings);

		// 指定した VS を管理から除外
		void releaseVS(VertexShader::IDType handleID) override;

		// 指定した PS を管理から除外
		void releasePS(PixelShader::IDType handleID) override;
	
		// 指定した VS を context にセット
		void setVS(VertexShader::IDType handleID) override;

		// 指定した PS を context にセット
		void setPS(PixelShader::IDType handleID) override;
	
		const Blob& getBinaryVS(VertexShader::IDType handleID) override;

		const Blob& getBinaryPS(PixelShader::IDType handleID) override;

		void setConstantBufferVS(uint32 slot, const ConstantBufferBase& cb) override;

		void setConstantBufferPS(uint32 slot, const ConstantBufferBase& cb) override;


		// HLSL シェーダコンパイラが利用可能かを返す
		bool hasHLSLCompiler() const noexcept;
	};
}
