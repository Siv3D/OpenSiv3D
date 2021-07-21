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
# include <Siv3D/Renderer3D/IRenderer3D.hpp>

namespace s3d
{
	class CRenderer3D_Null final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_Null();

		~CRenderer3D_Null() override;

		void init() override;

		const Renderer3DStat& getStat() const override;

		void addMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const Mat4x4& mat, const PhongMaterial& material) override;

		void addTexturedMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const Texture& texture, const Mat4x4& mat, const PhongMaterial& material) override;

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


		Optional<VertexShader> getCustomVS() const override;

		Optional<PixelShader> getCustomPS() const override;

		void setCustomVS(const Optional<VertexShader>& vs) override;

		void setCustomPS(const Optional<PixelShader>& ps) override;


		const Mat4x4& getCameraTransform() const override;

		void setCameraTransform(const Mat4x4& matrix, const Float3& eyePosition) override;


		void setVSTexture(uint32 slot, const Optional<Texture>& texture) override;

		void setPSTexture(uint32 slot, const Optional<Texture>& texture) override;


		void setRenderTarget(const Optional<RenderTexture>& rt) override;

		Optional<RenderTexture> getRenderTarget() const override;


		void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) override;


		void flush() override;

	private:

		Renderer3DStat m_stat;
	};
}
