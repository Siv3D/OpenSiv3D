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
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/TextureFilter.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer2D/Vertex2DBuilder.hpp>
# include <Siv3D/Renderer2D/Renderer2DCommon.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "GL4Renderer2DCommand.hpp"
# include "GL4Vertex2DBatch.hpp"

namespace s3d
{
	class CRenderer_GL4;
	class CShader_GL4;
	class CTexture_GL4;

	struct GL4StandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		VertexShader::IDType spriteID;

		bool setup()
		{
			const bool result = sprite
				&& fullscreen_triangle;

			spriteID = sprite.id();

			return result;
		}
	};

	struct GL4StandardPS2D
	{
		PixelShader shape;
		PixelShader square_dot;
		PixelShader round_dot;
		PixelShader texture;
		PixelShader fullscreen_triangle;

		PixelShader::IDType shapeID;
		PixelShader::IDType square_dotID;
		PixelShader::IDType round_dotID;
		PixelShader::IDType textureID;

		bool setup()
		{
			const bool result = shape
				&& square_dot
				&& round_dot
				&& texture
				&& fullscreen_triangle;

			shapeID		= shape.id();
			square_dotID = square_dot.id();
			round_dotID = round_dot.id();
			textureID	= texture.id();

			return result;
		}
	};

	class CRenderer2D_GL4 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_GL4* pRenderer = nullptr;
		CShader_GL4* pShader = nullptr;
		CTexture_GL4* pTexture = nullptr;

		std::unique_ptr<GL4StandardVS2D> m_standardVS;
		std::unique_ptr<GL4StandardPS2D> m_standardPS;

		ConstantBuffer<VSConstants2D> m_vsConstants2D;
		ConstantBuffer<PSConstants2D> m_psConstants2D;

		GL4Vertex2DBatch m_batches;
		GL4Renderer2DCommandManager m_commandManager;
		BufferCreatorFunc m_bufferCreator;

		Optional<VertexShader> m_currentCustomVS;
		Optional<PixelShader> m_currentCustomPS;

		std::unique_ptr<Texture> m_boxShadowTexture;

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////
		GLuint m_vertexArray		= 0;

		// VertexBuilder でのメモリアロケーションを避けるためのバッファ
		Array<Float2> m_buffer;


		Renderer2DStat m_stat;

	public:

		CRenderer2D_GL4();

		~CRenderer2D_GL4() override;

		void init() override;

		void update() override;

		const Renderer2DStat& getStat() const override;

		void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;

		void addTriangle(const Float2(&points)[3], const Float4& color) override;

		void addTriangle(const Float2(&points)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;

		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addRectFrameTB(const FloatRect& rect, float thickness, const Float4& topColor, const Float4& bottomColor) override;

		void addCircle(const Float2& center, float r, const Float4& innerColor, const Float4& outerColor) override;

		void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& innerColor, const Float4& outerColor) override;

		void addCircleArc(const LineStyle& style, const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCircleSegment(const Float2& center, float r, float startAngle, float angle, const Float4& color) override;

		void addEllipse(const Float2& center, float a, float b, const Float4& innerColor, const Float4& outerColor) override;

		void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;

		void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) override;

		void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& topColor, const Float4& bottomColor) override;

		void addRoundRectFrame(const RoundRect& outer, const RoundRect& inner, const Float4& color) override;

		void addRoundRectFrame(const RoundRect& outer, const RoundRect& inner, const Float4& topColor, const Float4& bottomColor) override;

		void addLineString(const LineStyle& style, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, CloseRing closeRing) override;

		void addLineString(const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, float thickness, bool inner, CloseRing closeRing) override;

		void addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color) override;

		void addPolygon(const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) override;
	
		void addPolygonTransformed(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, float s, float c, const Float2& offset, const Float4& color) override;

		void addPolygonFrame(const Float2* points, size_t size, float thickness, const Float4& color) override;

		void addNullVertices(uint32 count) override;

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) override;

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]) override;

		void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) override;

		void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) override;

		void addTexturedRoundRect(const Texture& texture, const FloatRect& rect, float w, float h, float r, const FloatRect& uvRect, const Float4& color) override;

		void addTexturedVertices(const Texture& texture, const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) override;

		void addRectShadow(const FloatRect& rect, float blur, const Float4& color, bool fill) override;

		void addCircleShadow(const Circle& circle, float blur, const Float4& color) override;

		void addRoundRectShadow(const RoundRect& roundRect, float blur, const Float4& color, bool fill) override;
		
		void addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
			ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
			ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc) override;


		Float4 getColorMul() const override;

		Float4 getColorAdd() const override;

		void setColorMul(const Float4& color) override;

		void setColorAdd(const Float4& color) override;


		BlendState getBlendState() const override;

		RasterizerState getRasterizerState() const override;

		SamplerState getSamplerState(ShaderStage shaderStage, uint32 slot) const override;

		void setBlendState(const BlendState& state) override;

		void setRasterizerState(const RasterizerState& state) override;

		void setSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& state) override;


		void setScissorRect(const Rect& rect) override;

		Rect getScissorRect() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;

		void setSDFParameters(const std::array<Float4, 3>& params) override;

		void setInternalPSConstants(const Float4& value) override;


		Optional<VertexShader> getCustomVS() const override;

		Optional<PixelShader> getCustomPS() const override;

		void setCustomVS(const Optional<VertexShader>& vs) override;

		void setCustomPS(const Optional<PixelShader>& ps) override;


		const Mat3x2& getLocalTransform() const override;

		const Mat3x2& getCameraTransform() const override;

		void setLocalTransform(const Mat3x2& matrix) override;

		void setCameraTransform(const Mat3x2& matrix) override;

		float getMaxScaling() const noexcept override;


		void setVSTexture(uint32 slot, const Optional<Texture>& texture) override;

		void setPSTexture(uint32 slot, const Optional<Texture>& texture) override;


		void setRenderTarget(const Optional<RenderTexture>& rt) override;

		Optional<RenderTexture> getRenderTarget() const override;


		void setConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors) override;

		const Texture& getBoxShadowTexture() const noexcept override;

		void flush() override;

		//
		// OpenGL
		//

		void drawFullScreenTriangle(TextureFilter textureFilter);
	};
}
