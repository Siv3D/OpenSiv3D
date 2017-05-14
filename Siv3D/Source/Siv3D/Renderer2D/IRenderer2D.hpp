//-----------------------------------------------
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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/SamplerState.hpp>

namespace s3d
{
	class ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void flush() = 0;

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

		virtual void addLine(LineStyle style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) = 0;

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

		virtual void addLineString(const Vec2* pts, uint32 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) = 0;

		virtual void addShape2D(const Array<Float2>& vertices, const Array<uint32>& indices, const Float4& color) = 0;

		virtual void addShape2DFrame(const Float2* pts, uint32 size, float thickness, const Float4& color) = 0;


		virtual void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) = 0;

		virtual void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) = 0;
	};
}
