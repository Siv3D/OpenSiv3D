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
# include <Siv3D/FastMath.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

		static constexpr Vertex2D::IndexType MaxSinCosTableQuality = 40;

		static constexpr Vertex2D::IndexType SinCosTableSize = ((MaxSinCosTableQuality - 5) * (6 + (MaxSinCosTableQuality))) / 2;

		static const std::array<Float2, SinCosTableSize> CircleSinCosTable = []()
		{
			std::array<Float2, SinCosTableSize> results;
			Float2* pDst = results.data();

			for (int32 quality = 6; quality <= MaxSinCosTableQuality; ++quality)
			{
				const float radDelta = Math::Constants::TwoPiF / quality;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = radDelta * i;
					(pDst++)->set(std::cos(rad), -std::sin(rad));
				}
			}

			return results;
		}();

		[[nodiscard]]
		inline const Float2* GetSinCosTableStartPtr(const uint16 quality) noexcept
		{
			return &CircleSinCosTable[((quality - 6) * (6 + (quality - 1))) / 2];
		}

		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CalculateCircleQuality(const float size) noexcept
		{
			if (size <= 5.0f)
			{
				return static_cast<Vertex2D::IndexType>(size + 3) * 2;
			}
			else
			{
				return static_cast<Vertex2D::IndexType>(Min(18 + (size - 5.0f) / 2.2f, 255.0f));
			}
		}
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

		Vertex2D::IndexType BuildCircle(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, const Float4& innerColor, const Float4& outerColor, const float scale)
		{
			const float absR = Abs(r);
			const Vertex2D::IndexType quality = detail::CalculateCircleQuality(absR * scale);
			const Vertex2D::IndexType vertexSize = (quality + 1), indexSize = (quality * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			// 中心
			const float centerX = center.x;
			const float centerY = center.y;
			pVertex[0].pos.set(centerX, centerY);

			// 周
			if (quality <= detail::MaxSinCosTableQuality)
			{
				const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
				Vertex2D* pDst = &pVertex[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					(pDst++)->pos.set(r * pCS->x + centerX, r * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = Math::TwoPiF / quality;
				Vertex2D* pDst = &pVertex[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + r * c, centerY - r * s);
				}
			}

			{
				(pVertex++)->color = innerColor;

				for (size_t i = 1; i < vertexSize; ++i)
				{
					(pVertex++)->color = outerColor;
				}
			}

			{
				for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
				{
					*pIndex++ = indexOffset + (i + 1);
					*pIndex++ = indexOffset;
					*pIndex++ = indexOffset + (i + 2);
				}

				*pIndex++ = (indexOffset + quality);
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + 1);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Array<Float2>& vertices, const Array<TriangleIndex>& tirnagleIndices, const Optional<Float2>& offset, const Float4& color)
		{
			if (vertices.isEmpty()
				|| tirnagleIndices.isEmpty())
			{
				return 0;
			}

			const Vertex2D::IndexType vertexSize = static_cast<Vertex2D::IndexType>(vertices.size());
			const Vertex2D::IndexType indexSize = static_cast<Vertex2D::IndexType>(tirnagleIndices.size() * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			{
				const Float2* pSrc = vertices.data();
				const Float2* pSrcEnd = (pSrc + vertices.size());

				if (offset)
				{
					const Float2 _offset = offset.value();

					while (pSrc != pSrcEnd)
					{
						pVertex->pos = (_offset + *pSrc++);
						pVertex->color = color;
						++pVertex;
					}
				}
				else
				{
					while (pSrc != pSrcEnd)
					{
						pVertex->pos = *pSrc++;
						pVertex->color = color;
						++pVertex;
					}
				}
			}

			{
				std::memcpy(pIndex, tirnagleIndices.data(), tirnagleIndices.size_bytes());

				for (size_t i = 0; i < indexSize; ++i)
				{
					*(pIndex++) += indexOffset;
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
		{
			if ((not vertices)
				|| (vertexCount == 0)
				|| (not indices)
				|| (num_triangles == 0))
			{
				return 0;
			}

			const Vertex2D::IndexType vertexSize = static_cast<Vertex2D::IndexType>(vertexCount);
			const Vertex2D::IndexType indexSize = static_cast<Vertex2D::IndexType>(num_triangles * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			std::memcpy(pVertex, vertices, vertexSize * sizeof(Vertex2D));

			const TriangleIndex* pSrc = indices;
			const TriangleIndex* const pSrcEnd = (indices + num_triangles);

			while (pSrc != pSrcEnd)
			{
				*pIndex++ = (indexOffset + pSrc->i0);
				*pIndex++ = (indexOffset + pSrc->i1);
				*pIndex++ = (indexOffset + pSrc->i2);
				++pSrc;
			}

			return indexSize;
		}
	}
}
