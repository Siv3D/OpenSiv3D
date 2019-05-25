//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Renderer2D/IRenderer2D.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ConstantBuffer.hpp>
//# include "D3D11SpriteBatch.hpp"
//# include "D3D11Renderer2DCommand.hpp"
# include <Renderer2D/Vertex2DBuilder.hpp>

namespace s3d
{
	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:
		
		std::unique_ptr<Texture> m_boxShadowTexture;

	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		void init();

		void flush() override;

		std::pair<float, FloatRect> getLetterboxingTransform() const override;

		void drawResolved() override;

		void setColorMul(const Float4& color) override;

		ColorF getColorMul() const override;

		void setColorAdd(const Float4& color) override;

		ColorF getColorAdd() const override;

		void setBlendState(const BlendState& state) override;

		BlendState getBlendState() const override;

		void setRasterizerState(const RasterizerState& state) override;

		RasterizerState getRasterizerState() const override;

		void setPSSamplerState(uint32 slot, const SamplerState& state) override;

		SamplerState getPSSamplerState(uint32 slot) const override;

		void setLocalTransform(const Mat3x2& matrix) override;

		const Mat3x2& getLocalTransform() const override;

		void setCameraTransform(const Mat3x2& matrix) override;

		const Mat3x2& getCameraTransform() const override;

		void setScissorRect(const Rect& rect) override;

		float getMaxScaling() const override;

		Rect getScissorRect() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;

		void setSDFParameters(const Float4& parameters) override;

		Float4 getSDFParameters() const override;

		void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;

		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;

		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;

		void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) override;

		void addCircleArc(const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& color) override;

		void addEllipse(const Float2& center, float a, float b, const Float4& color) override;

		void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;

		void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) override;

		void addLineString(const LineStyle& style, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) override;

		void addShape2D(const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color) override;

		void addShape2DTransformed(const Array<Float2>& vertices, const Array<uint16>& indices, float s, float c, const Float2& offset, const Float4& color) override;

		void addShape2DFrame(const Float2* pts, uint16 size, float thickness, const Float4& color) override;

		void addSprite(const Sprite& sprite, uint16 startIndex, uint16 indexCount) override;

		void addSprite(const Texture& texture, const Sprite& sprite, uint16 startIndex, uint16 indexCount);

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) override;

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]) override;

		void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) override;

		void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) override;
	
		void addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
			ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
			ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc) override;

		const Texture& getBoxShadowTexture() const override;
	};
}
