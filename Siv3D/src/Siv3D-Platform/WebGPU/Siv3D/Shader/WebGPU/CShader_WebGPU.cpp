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

# include "CShader_WebGPU.hpp"
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>
# include <Siv3D/ConstantBuffer/WebGPU/ConstantBufferDetail_WebGPU.hpp>

namespace s3d
{
	CShader_WebGPU::CShader_WebGPU()
	{
		// do nothing
	}

	CShader_WebGPU::~CShader_WebGPU()
	{
		LOG_SCOPED_TRACE(U"CShader_WebGPU::~CShader_WebGPU()");

		// エンジン PS を破棄
		m_enginePSs.clear();

		// PS の管理を破棄
		m_pixelShaders.destroy();

		// VS の管理を破棄
		m_vertexShaders.destroy();
	}

	void CShader_WebGPU::init()
	{
		LOG_SCOPED_TRACE(U"CShader_WebGPU::init()");

		auto pRenderer	= static_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer));
		m_device = pRenderer->getDevice();

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<WebGPUVertexShader>(WebGPUVertexShader::Null{});

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
			auto nullPixelShader = std::make_unique<WebGPUPixelShader>(WebGPUPixelShader::Null{});

			if (not nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null PixelShader initialization failed" };
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}

		// エンジン PS をロード
		{
			m_enginePSs << WGSL{ Resource(U"engine/shader/wgsl/copy.frag.wgsl"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << WGSL{ Resource(U"engine/shader/wgsl/gaussian_blur_5.frag.wgsl"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << WGSL{ Resource(U"engine/shader/wgsl/gaussian_blur_9.frag.wgsl"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << WGSL{ Resource(U"engine/shader/wgsl/gaussian_blur_13.frag.wgsl"), {{ U"PSConstants2D", 0 }} };
			m_enginePSs << WGSL{ Resource(U"engine/shader/wgsl/apply_srgb_curve.frag.wgsl"), {{ U"PSConstants2D", 0 }} };

			if (not m_enginePSs.all([](const auto& ps) { return !!ps; })) // もしロードに失敗したシェーダがあれば
			{
				throw EngineError{ U"CShader_WebGPU::m_enginePSs initialization failed" };
			}
		}

		m_pipeline.init(*m_device);
		m_bindGroups.init(*m_device);
	}

	VertexShader::IDType CShader_WebGPU::createVSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader{ path };

		if (not reader)
		{
			return VertexShader::IDType::NullAsset();
		}

		return createVSFromSource(reader.readAll(), entryPoint, bindings);
	}

	VertexShader::IDType CShader_WebGPU::createVSFromSource(const StringView source, const StringView, const Array<ConstantBufferBinding>& bindings)
	{
		// VS を作成
		auto vertexShader = std::make_unique<WebGPUVertexShader>(*m_device, source, bindings);

		if (not vertexShader->isInitialized()) // もし作成に失敗していたら
		{
			return VertexShader::IDType::NullAsset();
		}

		// VS を管理に登録
		return m_vertexShaders.add(std::move(vertexShader));
	}

	PixelShader::IDType CShader_WebGPU::createPSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader{ path };

		if (not reader)
		{
			return PixelShader::IDType::NullAsset();
		}

		return createPSFromSource(reader.readAll(), entryPoint, bindings);
	}

	PixelShader::IDType CShader_WebGPU::createPSFromSource(const StringView source, const StringView, const Array<ConstantBufferBinding>& bindings)
	{
		// PS を作成
		auto pixelShader = std::make_unique<WebGPUPixelShader>(*m_device, source, bindings);

		if (not pixelShader->isInitialized()) // もし作成に失敗していたら
		{
			return PixelShader::IDType::NullAsset();
		}

		// PS を管理に登録
		return m_pixelShaders.add(std::move(pixelShader));
	}

	void CShader_WebGPU::releaseVS(const VertexShader::IDType handleID)
	{
		// 指定した VS を管理から除外
		m_vertexShaders.erase(handleID);
	}

	void CShader_WebGPU::releasePS(const PixelShader::IDType handleID)
	{
		// 指定した PS を管理から除外
		m_pixelShaders.erase(handleID);
	}

	void CShader_WebGPU::setVS(const VertexShader::IDType handleID)
	{
		m_currentVS = handleID;
	}

	void CShader_WebGPU::setPS(const PixelShader::IDType handleID)
	{
		m_currentPS = handleID;
	}

	const Blob& CShader_WebGPU::getBinaryVS(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getBinary();
	}

	const Blob& CShader_WebGPU::getBinaryPS(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getBinary();
	}

	void CShader_WebGPU::setConstantBufferVS(const uint32 slot, const ConstantBufferBase& cb)
	{
		auto entry = static_cast<const ConstantBufferDetail_WebGPU*>(cb._detail())->getBindGroupEntry();
		entry.binding = slot;

		auto iter = std::find_if(
			m_currentVSConstants.begin(), m_currentVSConstants.end(),
			[=](const wgpu::BindGroupEntry& v) -> bool
			{ 
				return v.binding == slot;
			}
		);

		if (iter != m_currentVSConstants.end())
		{
			*iter = entry;
		}
		else
		{
			m_currentVSConstants << entry;
		}
	}

	void CShader_WebGPU::setConstantBufferPS(const uint32 slot, const ConstantBufferBase& cb)
	{
		auto entry = static_cast<const ConstantBufferDetail_WebGPU*>(cb._detail())->getBindGroupEntry();
		entry.binding = slot;

		auto iter = std::find_if(
			m_currentPSConstants.begin(), m_currentPSConstants.end(),
			[=](const wgpu::BindGroupEntry& v) -> bool
			{ 
				return v.binding == slot;
			}
		);

		if (iter != m_currentPSConstants.end())
		{
			*iter = entry;
		}
		else
		{
			m_currentPSConstants << entry;
		}
	}

	void CShader_WebGPU::resetConstantBufferVS()
	{
		m_currentVSConstants.clear();
	}

	void CShader_WebGPU::resetConstantBufferPS()
	{
		m_currentPSConstants.clear();
	}

	const PixelShader& CShader_WebGPU::getEnginePS(const EnginePS ps) const
	{
		return m_enginePSs[FromEnum(ps)];
	}

	wgpu::ShaderModule CShader_WebGPU::getShaderModuleVS(VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getShaderModule();
	}

	wgpu::ShaderModule CShader_WebGPU::getShaderModulePS(PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getShaderModule();
	}

	wgpu::BindGroupLayout CShader_WebGPU::getBindingGroupVS(VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getBindingGroup();
	}

	wgpu::BindGroupLayout CShader_WebGPU::getBindingGroupPS(PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getBindingGroup();
	}

	wgpu::RenderPipeline CShader_WebGPU::usePipeline(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState, const WebGPUVertexAttribute& attribute)
	{
		auto pipeline = m_pipeline.getPipeline(m_currentVS, m_currentPS, rasterizerState, blendState, renderTargetState, depthStencilState, attribute);
		pass.SetPipeline(pipeline);

		m_bindGroups.bindUniformBindGroup(pass, 0, pipeline, m_currentUniforms);

		return pipeline;
	}

	wgpu::RenderPipeline CShader_WebGPU::usePipelineWithStandard2DVertexLayout(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState)
	{
		auto pipeline = m_pipeline.getPipelineWithStandard2DVertexLayout(m_currentVS, m_currentPS, rasterizerState, blendState, renderTargetState);
		pass.SetPipeline(pipeline);
		
		m_bindGroups.bindUniformBindGroup(pass, 0, pipeline, m_currentVSConstants);
		m_bindGroups.bindUniformBindGroup(pass, 1, pipeline, m_currentPSConstants);

		return pipeline;
	}

	wgpu::RenderPipeline CShader_WebGPU::usePipelineWithStandard3DVertexLayout(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState)
	{
		auto pipeline = m_pipeline.getPipelineWithStandard3DVertexLayout(m_currentVS, m_currentPS, rasterizerState, blendState, renderTargetState, depthStencilState);
		pass.SetPipeline(pipeline);

		m_bindGroups.bindUniformBindGroup(pass, 0, pipeline, m_currentVSConstants);
		m_bindGroups.bindUniformBindGroup(pass, 1, pipeline, m_currentPSConstants);

		return pipeline;
	}

	wgpu::RenderPipeline CShader_WebGPU::usePipelineWithStandard3DLineVertexLayout(const wgpu::RenderPassEncoder& pass, RasterizerState rasterizerState, BlendState blendState, WebGPURenderTargetState renderTargetState, DepthStencilState depthStencilState)
	{
		auto pipeline = m_pipeline.getPipelineWithStandard3DLineVertexLayout(m_currentVS, m_currentPS, rasterizerState, blendState, renderTargetState, depthStencilState);
		pass.SetPipeline(pipeline);

		m_bindGroups.bindUniformBindGroup(pass, 0, pipeline, m_currentVSConstants);
		m_bindGroups.bindUniformBindGroup(pass, 1, pipeline, {});

		return pipeline;
	}

	void CShader_WebGPU::setUniform(const Array<wgpu::BindGroupEntry>& uniforms)
	{
		m_currentUniforms = uniforms;
	}
}
