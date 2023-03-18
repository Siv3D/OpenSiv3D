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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include <Siv3D/Texture/WebGPU/WebGPURenderTargetState.hpp>
# include "VertexShader/WebGPUVertexShader.hpp"
# include "PixelShader/WebGPUPixelShader.hpp"
# include "ShaderPipeline/WebGPUShaderPipeline.hpp"
# include "UniformState/WebGPUUniformState.hpp"

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class CShader_WebGPU final : public ISiv3DShader
	{
	public:

		CShader_WebGPU();

		~CShader_WebGPU() override;

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

		void resetConstantBufferVS();

		void resetConstantBufferPS();

		const PixelShader& getEnginePS(EnginePS ps) const override;

		wgpu::RenderPipeline usePipeline(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState, const WebGPUVertexAttribute& attribute);

		wgpu::RenderPipeline usePipelineWithStandard2DVertexLayout(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState);
		
		wgpu::RenderPipeline usePipelineWithStandard3DVertexLayout(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState);

		wgpu::RenderPipeline usePipelineWithStandard3DLineVertexLayout(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState);

		void setUniform(const Array<wgpu::BindGroupEntry>& uniforms);

		wgpu::ShaderModule getShaderModuleVS(VertexShader::IDType handleID);

		wgpu::ShaderModule getShaderModulePS(PixelShader::IDType handleID);

		wgpu::BindGroupLayout getBindingGroupVS(VertexShader::IDType handleID);

		wgpu::BindGroupLayout getBindingGroupPS(PixelShader::IDType handleID);

	private:

		// VS の管理
		AssetHandleManager<VertexShader::IDType, WebGPUVertexShader> m_vertexShaders{ U"VertexShader" };

		// PS の管理
		AssetHandleManager<PixelShader::IDType, WebGPUPixelShader> m_pixelShaders{ U"PixelShader" };

		// Shader:: 用の内部シェーダ
		Array<PixelShader> m_enginePSs;

		VertexShader::IDType m_currentVS;
		
		PixelShader::IDType m_currentPS;

		wgpu::RenderPipeline m_currentPipeline;

		Array<wgpu::BindGroupEntry> m_currentVSConstants;

		Array<wgpu::BindGroupEntry> m_currentPSConstants;

		Array<wgpu::BindGroupEntry> m_currentUniforms;

		// シェーダプログラム (VS と PS のペア) の管理
		WebGPUShaderPipeline m_pipeline;

		WebGPUUniformState m_bindGroups;

		wgpu::Device* m_device;
	};
}
