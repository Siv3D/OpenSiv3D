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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/ParticleSystem2D.hpp>
# include <Siv3D/ConstantBuffer.hpp>

namespace s3d
{
	class ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void flush() = 0;

		virtual std::pair<float, FloatRect> getLetterboxingTransform() const = 0;

		virtual void drawFullscreen(bool multisample) = 0;

		virtual void setColorMul(const Float4& color) = 0;

		virtual ColorF getColorMul() const = 0;

		virtual void setColorAdd(const Float4& color) = 0;

		virtual ColorF getColorAdd() const = 0;

		virtual void setBlendState(const BlendState& state) = 0;

		virtual BlendState getBlendState() const = 0;

		virtual void setRasterizerState(const RasterizerState& state) = 0;

		virtual RasterizerState getRasterizerState() const = 0;

		virtual void setPSSamplerState(uint32 slot, const SamplerState& state) = 0;

		virtual SamplerState getPSSamplerState(uint32 slot) const = 0;

		virtual void setLocalTransform(const Mat3x2& matrix) = 0;

		virtual const Mat3x2& getLocalTransform() const = 0;

		virtual void setCameraTransform(const Mat3x2& matrix) = 0;

		virtual const Mat3x2& getCameraTransform() const = 0;

		virtual float getMaxScaling() const = 0;

		virtual void setScissorRect(const Rect& rect) = 0;

		virtual Rect getScissorRect() const = 0;

		virtual void setViewport(const Optional<Rect>& viewport) = 0;

		virtual Optional<Rect> getViewport() const = 0;

		virtual void setSDFParameters(const Float4& parameters) = 0;

		virtual Float4 getSDFParameters() const = 0;

		virtual void setPSTexture(uint32 slot, const Optional<Texture>& texture) = 0;

		virtual void setCustomPS(const Optional<PixelShader>& ps) = 0;

		virtual Optional<PixelShader> getCustomPS() const = 0;

		virtual void setConstant(ShaderStage stage, uint32 slot, const s3d::detail::ConstantBufferBase& buffer, const float* data, uint32 num_vectors) = 0;

		virtual void setInternalConstantBufferValue(ShaderStage stage, const Float4& value) = 0;

		virtual void setRT(const Optional<RenderTexture>& rt) = 0;

		virtual Optional<RenderTexture> getRT() const = 0;

		virtual void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) = 0;

		virtual void addTriangle(const Float2(&pts)[3], const Float4& color) = 0;

		virtual void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) = 0;

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;

		virtual void addRect(const FloatRect& rect, const Float4(&colors)[4]) = 0;

		virtual void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) = 0;

		virtual void addCircle(const Float2& center, float r, const Float4& color) = 0;

		virtual void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) = 0;

		virtual void addCircleArc(const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& color) = 0;

		virtual void addEllipse(const Float2& center, float a, float b, const Float4& color) = 0;

		virtual void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) = 0;

		virtual void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) = 0;

		virtual void addLineString(const LineStyle& style, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) = 0;

		virtual void addShape2D(const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color) = 0;

		virtual void addShape2DTransformed(const Array<Float2>& vertices, const Array<uint16>& indices, float s, float c, const Float2& offset, const Float4& color) = 0;

		virtual void addShape2DFrame(const Float2* pts, uint16 size, float thickness, const Float4& color) = 0;

		virtual void addSprite(const Sprite& sprite, uint16 startIndex, uint16 indexCount) = 0;

		virtual void addSprite(const Texture& texture, const Sprite& sprite, uint16 startIndex, uint16 indexCount) = 0;

		virtual void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]) = 0;

		virtual void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
			ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
			ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc) = 0;

		virtual const Texture& getBoxShadowTexture() const = 0;
	};
}
