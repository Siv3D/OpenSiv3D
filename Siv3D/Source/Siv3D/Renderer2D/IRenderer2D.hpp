﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/SamplerState.hpp>

namespace s3d
{
	class ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void flush(bool clearGraphics) = 0;

		virtual void setBlendState(const BlendState& state) = 0;

		virtual BlendState getBlendState() const = 0;

		virtual void setRasterizerState(const RasterizerState& state) = 0;

		virtual RasterizerState getRasterizerState() const = 0;

		virtual void setSamplerState(ShaderStage stage, uint32 slot, const SamplerState& state) = 0;

		virtual const std::array<SamplerState, SamplerState::MaxSamplerCount>& getSamplerStates(ShaderStage stage) const = 0;

		virtual void setScissorRect(const Rect& rect) = 0;

		virtual Rect getScissorRect() const = 0;

		virtual void setViewport(const Optional<Rect>& viewport) = 0;

		virtual Optional<Rect> getViewport() const = 0;

		virtual void setTransformLocal(const Mat3x2& matrix) = 0;

		virtual void setTransformCamera(const Mat3x2& matrix) = 0;

		virtual void setTransformScreen(const Mat3x2& matrix) = 0;

		virtual const Mat3x2& getTransformLocal() const = 0;

		virtual const Mat3x2& getTransformCamera() const = 0;

		virtual const Mat3x2& getTransformScreen() const = 0;

		virtual float getMaxScaling() const = 0;

		virtual void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) = 0;

		virtual void addTriangle(const Float2(&pts)[3], const Float4& color) = 0;

		virtual void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) = 0;

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;

		virtual void addRect(const FloatRect& rect, const Float4(&colors)[4]) = 0;

		virtual void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) = 0;

		virtual void addCircle(const Float2& center, float r, const Float4& color) = 0;

		virtual void addCircleFrame(const Float2& center, float r, float thickness, const Float4& color) = 0;

		virtual void addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) = 0;

		virtual void addCircleArc(const Float2& center, float r, float startAngle, float angle, float thickness, const Float4& color) = 0;

		virtual void addEllipse(const Float2& center, float a, float b, const Float4& color) = 0;

		virtual void addEllipseFrame(const Float2& center, float a, float b, float thickness, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) = 0;

		virtual void addLineString(LineStyle style, const Vec2* pts, uint32 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) = 0;

		virtual void addShape2D(const Array<Float2>& vertices, const Array<uint32>& indices, const Float4& color) = 0;

		virtual void addShape2DFrame(const Float2* pts, uint32 size, float thickness, const Float4& color) = 0;


		virtual void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) = 0;

		virtual void addSprite(const Optional<Texture>& texture, const Sprite& sprite, uint32 startIndex, uint32 indexCount) = 0;


		virtual const Texture& getBoxShadowTexture() const = 0;
	};
}
