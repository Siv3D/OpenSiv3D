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
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/TriangleIndex.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/YesNo.hpp>
# include <Siv3D/PredefinedYesNo.hpp>
# include "Vertex2DBufferPointer.hpp"

namespace s3d
{
	using BufferCreatorFunc = std::function<Vertex2DBufferPointer(Vertex2D::IndexType, Vertex2D::IndexType)>;

	namespace Vertex2DBuilder
	{
		[[nodiscard]]
		Vertex2D::IndexType BuildDefaultLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]);

		[[nodiscard]]
		Vertex2D::IndexType BuildTriangle(const BufferCreatorFunc& bufferCreator, const Float2(&points)[3], const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildTriangle(const BufferCreatorFunc& bufferCreator, const Float2(&points)[3], const Float4(&colors)[3]);

		[[nodiscard]]
		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4(&colors)[4]);

		[[nodiscard]]
		Vertex2D::IndexType BuildRectFrame(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor);

		[[nodiscard]]
		Vertex2D::IndexType BuildCircle(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildCircleFrame(const BufferCreatorFunc& bufferCreator, const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const Float4 color);

		[[nodiscard]]
		Vertex2D::IndexType BuildQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const Float4(&colors)[4]);

		[[nodiscard]]
		Vertex2D::IndexType BuildDefaultLineString(const BufferCreatorFunc& bufferCreator, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, IsClosed isClosed, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Array<Float2>& vertices, const Array<TriangleIndex>& tirnagleIndices, const Optional<Float2>& offset, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles);
	
		[[nodiscard]]
		Vertex2D::IndexType BuildPolygonFrame(const BufferCreatorFunc& bufferCreator, const Float2* points, size_t size, float thickness, const Float4& color, float scale);
	}
}
