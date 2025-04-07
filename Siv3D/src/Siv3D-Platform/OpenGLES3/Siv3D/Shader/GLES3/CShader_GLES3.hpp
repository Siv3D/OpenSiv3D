﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include <Siv3D/Shader/EngineShader.hpp>
# include "VertexShader/GLES3VertexShader.hpp"
# include "PixelShader/GLES3PixelShader.hpp"
# include "ShaderPipeline/GLES3ShaderPipeline.hpp"

namespace s3d
{
	class CShader_GLES3 final : public ISiv3DShader
	{
	public:

		CShader_GLES3();

		~CShader_GLES3() override;

		void init() override;

		VertexShader::IDType createVSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;
		
		VertexShader::IDType createVSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;


		PixelShader::IDType createPSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;
	
		PixelShader::IDType createPSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) override;


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

		const VertexShader& getEngineVS(EngineVS vs) const override;

		const PixelShader& getEnginePS(EnginePS ps) const override;

		void setQuadWarpCB(const VS2DQuadWarp& vsCB, const PS2DQuadWarp& psCB) override;

		void usePipeline();

	private:

		// VS の管理
		AssetHandleManager<VertexShader::IDType, GLES3VertexShader> m_vertexShaders{ U"VertexShader" };

		// PS の管理
		AssetHandleManager<PixelShader::IDType, GLES3PixelShader> m_pixelShaders{ U"PixelShader" };

		// Shader:: 用の内部シェーダ
		Array<PixelShader> m_enginePSs;

		// Shader:: 用の内部シェーダ
		Array<VertexShader> m_engineVSs;

		EngineShaderConstantBuffer m_engineShaderCBs;

		VertexShader::IDType m_currentVS;
		
		PixelShader::IDType m_currentPS;

		// シェーダプログラム (VS と PS のペア) の管理
		ShaderPipeline m_pipeline;
	};
}
