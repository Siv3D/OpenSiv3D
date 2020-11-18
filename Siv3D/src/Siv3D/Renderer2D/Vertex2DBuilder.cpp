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

# include "Vertex2DBuilder.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };
	}

	namespace Vertex2DBuilder
	{
		Vertex2D::IndexType BuildDefaultLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float halfThickness = (thickness * 0.5f);
			const Float2 line = (end - begin).normalized();
			const Float2 vNormal{ (-line.y * halfThickness), (line.x * halfThickness) };
			const Float2 lineHalf{ line * halfThickness };

			const Float2 begin2 = (begin - lineHalf);
			const Float2 end2 = (end + lineHalf);

			pVertex[0].set(begin2 + vNormal , colors[0]);
			pVertex[1].set(begin2 - vNormal, colors[0]);
			pVertex[2].set(end2 + vNormal, colors[1]);
			pVertex[3].set(end2 - vNormal, colors[1]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4& color)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, color);
			pVertex[1].set(rect.right, rect.top, color);
			pVertex[2].set(rect.left, rect.bottom, color);
			pVertex[3].set(rect.right, rect.bottom, color);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}
	}
}
