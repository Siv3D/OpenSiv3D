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
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/DepthStencilState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/PhongMaterial.hpp>

namespace s3d
{
	struct Renderer3DStat
	{
		uint32 drawCalls = 0;
		uint32 triangleCount = 0;
	};

	class SIV3D_NOVTABLE ISiv3DRenderer3D
	{
	public:

		static ISiv3DRenderer3D* Create();

		virtual ~ISiv3DRenderer3D() = default;

		virtual void init() = 0;

		virtual const Renderer3DStat& getStat() const = 0;

		virtual void addMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const PhongMaterial& material) = 0;

		virtual void addTexturedMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const Texture& texture, const PhongMaterial& material) = 0;

		virtual void addTexturedMesh(uint32 startIndex, uint32 indexCount, const Mesh& mesh, const TextureRegion& textureRegion, const PhongMaterial& material) = 0;

		virtual void addLine3D(const Float3& begin, const Float3& end, const Float4(&colors)[2]) = 0;


		virtual BlendState getBlendState() const = 0;

		virtual RasterizerState getRasterizerState() const = 0;

		virtual DepthStencilState getDepthStencilState() const = 0;

		virtual SamplerState getSamplerState(ShaderStage shaderStage, uint32 slot) const = 0;

		virtual void setBlendState(const BlendState& state) = 0;

		virtual void setRasterizerState(const RasterizerState& state) = 0;

		virtual void setDepthStencilState(const DepthStencilState& state) = 0;

		virtual void setSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& state) = 0;


		virtual void setScissorRect(const Rect& rect) = 0;

		virtual Rect getScissorRect() const = 0;

		virtual void setViewport(const Optional<Rect>& viewport) = 0;

		virtual Optional<Rect> getViewport() const = 0;


		virtual void setGlobalAmbientColor(const Float3& color) = 0;

		virtual Float3 getGlobalAmbientColor() const = 0;

		virtual void setSunDirection(const Float3& direction) = 0;

		virtual Float3 getSunDirection() const = 0;

		virtual void setSunColor(const Float3& color) = 0;

		virtual Float3 getSunColor() const = 0;




		virtual Optional<VertexShader> getCustomVS() const = 0;

		virtual Optional<PixelShader> getCustomPS() const = 0;

		virtual void setCustomVS(const Optional<VertexShader>& vs) = 0;

		virtual void setCustomPS(const Optional<PixelShader>& ps) = 0;


		virtual const Mat4x4& getCameraTransform() const = 0;

		virtual Float3 getEyePosition() const = 0;

		virtual void setCameraTransform(const Mat4x4& matrix, const Float3& eyePosition) = 0;


		virtual const Mat4x4& getLocalTransform() const = 0;

		virtual void setLocalTransform(const Mat4x4& matrix) = 0;


		virtual void setVSTexture(uint32 slot, const Optional<Texture>& texture) = 0;

		virtual void setPSTexture(uint32 slot, const Optional<Texture>& texture) = 0;


		virtual void setRenderTarget(const Optional<RenderTexture>& rt) = 0;

		virtual Optional<RenderTexture> getRenderTarget() const = 0;


		virtual void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) = 0;


		virtual void flush() = 0;
	};
}
