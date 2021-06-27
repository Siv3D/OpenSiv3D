//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
# include "GL4Renderer3DCommand.hpp"

namespace s3d
{
	class CRenderer_GL4;
	class CShader_GL4;
	class CTexture_GL4;
	class CMesh_GL4;

	struct GL4StandardVS3D
	{
		VertexShader forward;

		VertexShader::IDType forwardID;

		bool setup()
		{
			const bool result = !!forward;

			forwardID = forward.id();

			return result;
		}
	};

	struct GL4StandardPS3D
	{
		PixelShader forwardShape;
		PixelShader forwardTexture;

		PixelShader::IDType forwardShapeID;
		PixelShader::IDType forwardTextureID;

		bool setup()
		{
			const bool result = forwardShape && forwardTexture;

			forwardShapeID = forwardShape.id();
			forwardTextureID = forwardTexture.id();

			return result;
		}
	};

	class CRenderer3D_GL4 final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_GL4();

		~CRenderer3D_GL4() override;

		void init() override;

		const Renderer3DStat& getStat() const override;

		void addMesh(const Mesh& mesh, const Mat4x4& mat, const Float4& color) override;

		void addTexturedMesh(const Mesh& mesh, const Texture& texture, const Mat4x4& mat, const Float4& color) override;


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


		Optional<VertexShader> getCustomVS() const override;

		Optional<PixelShader> getCustomPS() const override;

		void setCustomVS(const Optional<VertexShader>& vs) override;

		void setCustomPS(const Optional<PixelShader>& ps) override;


		const Mat4x4& getCameraTransform() const override;

		void setCameraTransform(const Mat4x4& matrix) override;


		void setVSTexture(uint32 slot, const Optional<Texture>& texture) override;

		void setPSTexture(uint32 slot, const Optional<Texture>& texture) override;


		void setRenderTarget(const Optional<RenderTexture>& rt) override;

		Optional<RenderTexture> getRenderTarget() const override;


		void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) override;


		void flush() override;

	private:

		CRenderer_GL4* pRenderer = nullptr;
		CShader_GL4* pShader = nullptr;
		CTexture_GL4* pTexture = nullptr;
		CMesh_GL4* pMesh = nullptr;

		std::unique_ptr<GL4StandardVS3D> m_standardVS;
		std::unique_ptr<GL4StandardPS3D> m_standardPS;

		ConstantBuffer<VSConstants3D> m_vsConstants3D;
		ConstantBuffer<PSConstants3D> m_psConstants3D;

		GL4Renderer3DCommandManager m_commandManager;

		Optional<VertexShader> m_currentCustomVS;
		Optional<PixelShader> m_currentCustomPS;

		Renderer3DStat m_stat;
	};
}
