//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>

namespace s3d
{
	struct FloatRect;
	struct ColorF;

	class SIV3D_NOVTABLE ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void init() = 0;

		virtual void addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) = 0;

		virtual void addTriangle(const Float2(&points)[3], const Float4& color) = 0;

		virtual void addTriangle(const Float2(&points)[3], const Float4(&colors)[3]) = 0;

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;

		virtual void addRect(const FloatRect& rect, const Float4(&colors)[4]) = 0;

		virtual void addRectFrame(const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCircle(const Float2& center, float r, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		//virtual void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) = 0;

		//virtual void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& innerColor, const Float4& outerColor) = 0;

		//virtual void addCircleArc(const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& color) = 0;

		//virtual void addCircleArc(const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		//virtual void addEllipse(const Float2& center, float a, float b, const Float4& innerColor, const Float4& outerColor) = 0;

		//virtual void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4& color) = 0;

		virtual void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) = 0;

		//virtual void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) = 0;

		virtual void addLineString(const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, IsClosed isClosed) = 0;

		virtual void addLineString(const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, float thickness, bool inner, IsClosed isClosed) = 0;

		virtual void addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color) = 0;

		virtual void addPolygon(const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) = 0;
	
		virtual void addPolygonFrame(const Float2* points, size_t size, float thickness, const Float4& color) = 0;

		virtual void addNullVertices(uint32 count) {}

		virtual Optional<VertexShader> getCustomVS() const { return none; }

		virtual Optional<PixelShader> getCustomPS() const { return none; }

		virtual void setCustomVS(const Optional<VertexShader>& vs) {}

		virtual void setCustomPS(const Optional<PixelShader>& ps) {}

		virtual float getMaxScaling() const noexcept = 0;
	};
}
