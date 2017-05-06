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

		virtual void setScissorRect(const Rect& rect) = 0;

		virtual Rect getScissorRect() const = 0;

		virtual void setViewport(const Optional<Rect>& viewport) = 0;

		virtual Optional<Rect> getViewport() const = 0;

		virtual void addTriangle(const Float2(&pts)[3], const Float4& color) = 0;

		virtual void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) = 0;

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;

		virtual void addRect(const FloatRect& rect, const Float4(&colors)[4]) = 0;

		virtual void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) = 0;

		virtual void addCircle(const Float2& center, float r, const Float4& color) = 0;

		virtual void addCircleFrame(const Float2& center, float r, float thickness, const Float4& color) = 0;

		virtual void addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addEllipse(const Float2& center, float a, float b, const Float4& color) = 0;

		virtual void addEllipseFrame(const Float2& center, float a, float b, float thickness, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) = 0;
	};
}
