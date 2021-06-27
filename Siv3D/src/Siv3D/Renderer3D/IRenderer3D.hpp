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
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/DepthStencilState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Mat4x4.hpp>

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

		virtual const Renderer3DStat& getStat() const { static Renderer3DStat s; return s; }

		virtual void addMesh(const Mesh& mesh, const Mat4x4& mat, const Float4& color) {}

		virtual void addTexturedMesh(const Mesh& mesh, const Texture& texture, const Mat4x4& mat, const Float4& color) {}


		virtual BlendState getBlendState() const { return BlendState::Default; }

		virtual RasterizerState getRasterizerState() const { return RasterizerState::Default3D; }

		virtual DepthStencilState getDepthStencilState() const { return DepthStencilState::Default3D; }

		virtual SamplerState getSamplerState(ShaderStage shaderStage, uint32 slot) const { return SamplerState::Default3D; }

		virtual void setBlendState(const BlendState& state) {}

		virtual void setRasterizerState(const RasterizerState& state) {}

		virtual void setDepthStencilState(const DepthStencilState& state) {}

		virtual void setSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& state) {}


		virtual void setScissorRect(const Rect& rect) {}

		virtual Rect getScissorRect() const { return Rect{ 0 }; }

		virtual void setViewport(const Optional<Rect>& viewport) {}

		virtual Optional<Rect> getViewport() const { return none; }


		virtual Optional<VertexShader> getCustomVS() const { return none; }

		virtual Optional<PixelShader> getCustomPS() const { return none; }

		virtual void setCustomVS(const Optional<VertexShader>& vs) {}

		virtual void setCustomPS(const Optional<PixelShader>& ps) {}


		virtual const Mat4x4& getCameraTransform() const { static Mat4x4 m = Mat4x4::Identity(); return m; }

		virtual void setCameraTransform(const Mat4x4& matrix) {}


		virtual void setVSTexture(uint32 slot, const Optional<Texture>& texture) {}

		virtual void setPSTexture(uint32 slot, const Optional<Texture>& texture) {}


		virtual void setRenderTarget(const Optional<RenderTexture>& rt) {}

		virtual Optional<RenderTexture> getRenderTarget() const { return none; }


		virtual void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) {}


		virtual void flush() {}
	};
}
