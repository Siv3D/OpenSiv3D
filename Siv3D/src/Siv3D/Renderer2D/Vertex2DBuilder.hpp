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
# include <Siv3D/TriangleIndex.hpp>
# include <Siv3D/Optional.hpp>
# include "Vertex2DBufferPointer.hpp"

namespace s3d
{
	using BufferCreatorFunc = std::function<Vertex2DBufferPointer(Vertex2D::IndexType, Vertex2D::IndexType)>;

	namespace Vertex2DBuilder
	{
		[[nodiscard]]
		Vertex2D::IndexType BuildDefaultLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]);

		[[nodiscard]]
		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4& color);
	
		[[nodiscard]]
		Vertex2D::IndexType BuildCircle(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Array<Float2>& vertices, const Array<TriangleIndex>& tirnagleIndices, const Optional<Float2>& offset, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles);
	}
}
