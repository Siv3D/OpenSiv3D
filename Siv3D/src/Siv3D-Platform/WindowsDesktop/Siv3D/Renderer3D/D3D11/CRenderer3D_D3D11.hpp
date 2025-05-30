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
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Renderer3D/Renderer3DCommon.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "D3D11Renderer3DCommand.hpp"
# include "D3D11Line3DBatch.hpp"

namespace s3d
{
	class CRenderer_D3D11;
	class CShader_D3D11;
	class CTexture_D3D11;
	class CMesh_D3D11;

	struct D3D11StandardVS3D
	{
		VertexShader forward;
		VertexShader line3D;

		VertexShader::IDType forwardID;
		VertexShader::IDType line3DID;

		bool setup()
		{
			const bool result = forward && line3D;

			forwardID	= forward.id();
			line3DID	= line3D.id();

			return result;
		}
	};

	struct D3D11StandardPS3D
	{
		PixelShader forward;
		PixelShader line3D;

		PixelShader::IDType forwardID;
		PixelShader::IDType line3DID;

		bool setup()
		{
			const bool result = forward && line3D;

			forwardID = forward.id();
			line3DID = line3D.id();

			return result;
		}
	};

	class CRenderer3D_D3D11 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_D3D11();

		~CRenderer3D_D3D11() override;

		void init() override;

		const Renderer3DStat& getStat() const override;

		void addMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const PhongMaterial& material) override;

		void addTexturedMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const Texture& texture, const PhongMaterial& material) override;

		void addTexturedMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const TextureRegion& textureRegion, const PhongMaterial& material) override;

		void addLine3D(const Float3& begin, const Float3& end, const Float4(&colors)[2]) override;


		BlendState getBlendState() const override;

		RasterizerState getRasterizerState() const override;

		DepthStencilState getDepthStencilState() const override;

		SamplerState getSamplerState(ShaderStage shaderStage, uint32 slot) const override;

		void setBlendState(const BlendState& state) override;

		void setRasterizerState(const RasterizerState& state) override;

		void setDepthStencilState(const DepthStencilState& state) override;

		void setSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& state) override;


		void setScissorRect(const Rect& rect) override;

		Rect getScissorRect() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;


		void setGlobalAmbientColor(const Float3& color) override;

		Float3 getGlobalAmbientColor() const override;

		void setSunDirection(const Float3& direction) override;

		Float3 getSunDirection() const override;

		void setSunColor(const Float3& color) override;

		Float3 getSunColor() const override;


		Optional<VertexShader> getCustomVS() const override;

		Optional<PixelShader> getCustomPS() const override;

		void setCustomVS(const Optional<VertexShader>& vs) override;

		void setCustomPS(const Optional<PixelShader>& ps) override;


		const Mat4x4& getCameraTransform() const override;

		Float3 getEyePosition() const override;

		void setCameraTransform(const Mat4x4& matrix, const Float3& eyePosition) override;


		const Mat4x4& getLocalTransform() const override;

		void setLocalTransform(const Mat4x4& matrix) override;


		void setVSTexture(uint32 slot, const Optional<Texture>& texture) override;

		void setPSTexture(uint32 slot, const Optional<Texture>& texture) override;


		void setRenderTarget(const Optional<RenderTexture>& rt) override;

		Optional<RenderTexture> getRenderTarget() const override;


		void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) override;


		void flush() override;

	private:

		CRenderer_D3D11* pRenderer = nullptr;
		CShader_D3D11* pShader = nullptr;
		CTexture_D3D11* pTexture = nullptr;
		CMesh_D3D11* pMesh = nullptr;
		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

		std::unique_ptr<D3D11StandardVS3D> m_standardVS;
		std::unique_ptr<D3D11StandardPS3D> m_standardPS;

		ConstantBuffer<VSPerViewConstants3D> m_vsPerViewConstants;
		ConstantBuffer<VSPerObjectConstants3D> m_vsPerObjectConstants;
		ConstantBuffer<VSPerMaterialConstants3D> m_vsPerMaterialConstants;
		ConstantBuffer<PSPerFrameConstants3D> m_psPerFrameConstants;
		ConstantBuffer<PSPerViewConstants3D> m_psPerViewConstants;
		ConstantBuffer<PSPerMaterialConstants3D> m_psPerMaterialConstants;

		ComPtr<ID3D11InputLayout> m_inputLayoutDefault;
		ComPtr<ID3D11InputLayout> m_inputLayoutLine3D;

		D3D11Renderer3DCommandManager m_commandManager;

		D3D11Line3DBatch m_line3DBatch;

		Optional<VertexShader> m_currentCustomVS;
		Optional<PixelShader> m_currentCustomPS;

		Renderer3DStat m_stat;
	};
}
