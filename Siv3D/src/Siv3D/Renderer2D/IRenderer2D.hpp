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
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/TriangleIndex.hpp>

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

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;

		virtual void addCircle(const Float2& center, float r, const Float4& innerColor, const Float4& outerColor) = 0;

		virtual void addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color) = 0;

		virtual void addPolygon(const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) = 0;
	
		virtual float getMaxScaling() const noexcept = 0;
	};
}
