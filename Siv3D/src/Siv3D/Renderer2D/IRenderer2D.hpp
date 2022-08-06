//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/TriangleIndex.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/YesNo.hpp>
# include <Siv3D/PredefinedYesNo.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Particle2D.hpp>
# include <Siv3D/ParticleSystem2DParameters.hpp>

namespace s3d
{
	struct FloatRect;
	struct ColorF;

	struct Renderer2DStat
	{
		uint32 drawCalls = 0;
		uint32 triangleCount = 0;
	};

	class SIV3D_NOVTABLE ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual const Renderer2DStat& getStat() const = 0;

		virtual void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) = 0;

		virtual void addTriangle(const Float2(&points)[3], const Float4& color) = 0;

		virtual void addTriangle(const Float2(&points)[3], const Float4(&colors)[3]) = 0;

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;

		virtual void addRect(const FloatRect& rect, const Float4(&colors)[4]) = 0;

		virtual void addRectFrame(const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCircle(const Float2& center, float r, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCircleArc(const LineStyle& style, const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addEllipse(const Float2& center, float a, float b, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) = 0;

		virtual void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) = 0;

		virtual void addRoundRectFrame(const RoundRect& outer, const RoundRect& inner, const Float4& color) = 0;

		virtual void addLineString(const LineStyle& style, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, CloseRing closeRing) = 0;

		virtual void addLineString(const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, float thickness, bool inner, CloseRing closeRing) = 0;

		virtual void addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color) = 0;

		virtual void addPolygon(const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) = 0;

		virtual void addPolygonTransformed(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, float s, float c, const Float2& offset, const Float4& color) = 0;

		virtual void addPolygonFrame(const Float2* points, size_t size, float thickness, const Float4& color) = 0;

		virtual void addNullVertices(uint32 count) = 0;

		virtual void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]) = 0;

		virtual void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedRoundRect(const Texture& texture, const FloatRect& rect, float w, float h, float r, const FloatRect& uvRect, const Float4& color) = 0;

		virtual void addTexturedVertices(const Texture& texture, const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) = 0;

		virtual void addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
			ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
			ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc) = 0;


		virtual Float4 getColorMul() const = 0;

		virtual Float4 getColorAdd() const = 0;

		virtual void setColorMul(const Float4& color) = 0;

		virtual void setColorAdd(const Float4& color) = 0;


		virtual BlendState getBlendState() const = 0;

		virtual RasterizerState getRasterizerState() const = 0;

		virtual SamplerState getSamplerState(ShaderStage shaderStage, uint32 slot) const = 0;

		virtual void setBlendState(const BlendState& state) = 0;

		virtual void setRasterizerState(const RasterizerState& state) = 0;

		virtual void setSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& state) = 0;


		virtual void setScissorRect(const Rect& rect) = 0;

		virtual Rect getScissorRect() const = 0;

		virtual void setViewport(const Optional<Rect>& viewport) = 0;

		virtual Optional<Rect> getViewport() const = 0;

		virtual void setSDFParameters(const std::array<Float4, 3>& params) = 0;

		virtual void setInternalPSConstants(const Float4& value) = 0;


		virtual Optional<VertexShader> getCustomVS() const = 0;

		virtual Optional<PixelShader> getCustomPS() const = 0;

		virtual void setCustomVS(const Optional<VertexShader>& vs) = 0;

		virtual void setCustomPS(const Optional<PixelShader>& ps) = 0;


		virtual const Mat3x2& getLocalTransform() const = 0;

		virtual const Mat3x2& getCameraTransform() const = 0;

		virtual void setLocalTransform(const Mat3x2& matrix) = 0;

		virtual void setCameraTransform(const Mat3x2& matrix) = 0;

		virtual float getMaxScaling() const noexcept = 0;


		virtual void setVSTexture(uint32 slot, const Optional<Texture>& texture) = 0;

		virtual void setPSTexture(uint32 slot, const Optional<Texture>& texture) = 0;


		virtual void setRenderTarget(const Optional<RenderTexture>& rt) = 0;

		virtual Optional<RenderTexture> getRenderTarget() const = 0;


		virtual void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) = 0;


		virtual const Texture& getBoxShadowTexture() const noexcept = 0;


		virtual void flush() = 0;
	};
}
