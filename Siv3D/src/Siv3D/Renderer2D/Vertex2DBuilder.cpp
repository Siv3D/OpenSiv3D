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

# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Sprite.hpp>
# include <Siv3D/Math.hpp>
# include "Vertex2DBuilder.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

		static constexpr IndexType RectFrameIndexTable[24] = { 0, 1, 2, 3, 2, 1, 0, 4, 1, 5, 1, 4, 5, 4, 7, 6, 7, 4, 3, 7, 2, 6, 2, 7 };

		static constexpr IndexType MaxSinCosTableQuality = 40;

		static constexpr IndexType SinCosTableSize = ((MaxSinCosTableQuality - 5) * (6 + (MaxSinCosTableQuality))) / 2;

		static const std::array<Float2, SinCosTableSize> CircleSinCosTable = []()
		{
			std::array<Float2, SinCosTableSize> results;
			Float2* pDst = results.data();

			for (int32 quality = 6; quality <= MaxSinCosTableQuality; ++quality)
			{
				const float radDelta = Math::TwoPiF / quality;

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = radDelta * i;
					(pDst++)->set(std::cos(rad), -std::sin(rad));
				}
			}

			return results;
		}();

		inline const Float2* GetSinCosTableStartPtr(const uint16 quality) noexcept
		{
			return &CircleSinCosTable[((quality - 6) * (6 + (quality - 1))) / 2];
		}

		inline constexpr IndexType CalculateCircleQuality(const float size) noexcept
		{
			if (size <= 5.0f)
			{
				return static_cast<IndexType>(size + 3) * 2;
			}
			else
			{
				return static_cast<IndexType>(std::min(18 + (size - 5.0f) / 2.2f, 255.0f));
			}
		}

		inline constexpr IndexType CalculateCircleFrameQuality(const float size) noexcept
		{
			if (size <= 1.0f)
			{
				return 6;
			}
			else if (size <= 8.0f)
			{
				return std::max(static_cast<IndexType>(2.0 * size), IndexType(8));
			}
			else
			{
				return static_cast<IndexType>(std::min(16 + (size - 8.0f) / 2.2f, 255.0f));
			}
		}

		inline IndexType CalculateCirclePieQuality(const float size, const float angle)
		{
			const float rate = std::min(Math::Abs(angle) / (Math::TwoPiF) * 2.0f, 1.0f);

			IndexType quality;

			if (size <= 1.0f)
			{
				quality = 4;
			}
			else if (size <= 6.0f)
			{
				quality = 7;
			}
			else if (size <= 8.0f)
			{
				quality = 11;
			}
			else
			{
				quality = static_cast<IndexType>(std::min(size * 0.225f + 18.0f, 255.0f));
			}

			return static_cast<IndexType>(std::max(quality * rate, 3.0f));
		}

		inline IndexType CaluculateFanQuality(const float r) noexcept
		{
			return r <= 1.0f ? 3
				: r <= 6.0f ? 5
				: r <= 12.0f ? 8
				: static_cast<uint16>(std::min(64.0f, r * 0.2f + 6));
		}
	}

	namespace Vertex2DBuilder
	{
		uint16 BuildSquareCappedLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2])
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;
			const Float2 line = (end - begin).normalize();
			const Float2 vNormal(-line.y * thicknessHalf, line.x * thicknessHalf);
			const Float2 lineHalf(line * thicknessHalf);

			pVertex[0].set(begin + vNormal - lineHalf, colors[0]);
			pVertex[1].set(begin - vNormal - lineHalf, colors[0]);
			pVertex[2].set(end + vNormal + lineHalf, colors[1]);
			pVertex[3].set(end - vNormal + lineHalf, colors[1]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildRoundCappedLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float& startAngle)
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;
			const Float2 line = (end - begin).normalize();
			const Float2 vNormal(-line.y * thicknessHalf, line.x * thicknessHalf);
			pVertex[0].set(begin + vNormal, colors[0]);
			pVertex[1].set(begin - vNormal, colors[0]);
			pVertex[2].set(end + vNormal, colors[1]);
			pVertex[3].set(end - vNormal, colors[1]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			startAngle = std::atan2(vNormal.x, -vNormal.y);

			return indexSize;
		}

		uint16 BuildUncappedLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2])
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;
			const Float2 line = (end - begin).normalize();
			const Float2 vNormal(-line.y * thicknessHalf, line.x * thicknessHalf);
			pVertex[0].set(begin + vNormal, colors[0]);
			pVertex[1].set(begin - vNormal, colors[0]);
			pVertex[2].set(end + vNormal, colors[1]);
			pVertex[3].set(end - vNormal, colors[1]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildSquareDotLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], const float dotOffset, const float scale)
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;
			const Float2 v = (end - begin);
			const float lineLength = v.length();
			const Float2 line = v / lineLength;
			const Float2 vNormal(-line.y * thicknessHalf, line.x * thicknessHalf);
			const Float2 lineHalf(line * thicknessHalf);
			const float lineLengthN = lineLength / thickness;
			const float uOffset = static_cast<float>((1.0f - Math::Fraction(dotOffset / 3.0f / thickness)) * 3.0f);
			const float vInfo = std::min(1.0f / (thickness * scale), 1.0f);

			pVertex[0].set(begin + vNormal - lineHalf, uOffset, vInfo, colors[0]);
			pVertex[1].set(begin - vNormal - lineHalf, uOffset, vInfo, colors[0]);
			pVertex[2].set(end + vNormal + lineHalf, uOffset + lineLengthN, vInfo, colors[1]);
			pVertex[3].set(end - vNormal + lineHalf, uOffset + lineLengthN, vInfo, colors[1]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildRoundDotLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], const float dotOffset, const bool hasAlignedDot)
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;
			const Float2 v = (end - begin);
			const float lineLength = v.length();
			const Float2 line = v / lineLength;
			const Float2 vNormal(-line.y * thicknessHalf, line.x * thicknessHalf);
			const Float2 lineHalf(line * thicknessHalf);
			float lineLengthN = lineLength / thickness;
			float uOffset = static_cast<float>((1.0f - Math::Fraction(dotOffset / 2.0 / thickness)) * 2.0f);

			if (hasAlignedDot)
			{
				const float m = std::fmod(lineLengthN - 1.0f, 2.0f);
				lineLengthN += 2.0f - m;
				uOffset = 0.5f;
			}

			pVertex[0].set(begin + vNormal - lineHalf, uOffset, 1.0f, colors[0]);
			pVertex[1].set(begin - vNormal - lineHalf, uOffset, -1.0f, colors[0]);
			pVertex[2].set(end + vNormal + lineHalf, uOffset + lineLengthN, 1.0f, colors[1]);
			pVertex[3].set(end - vNormal + lineHalf, uOffset + lineLengthN, -1.0f, colors[1]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildTriangle(BufferCreatorFunc bufferCreator, const Float2(&pts)[3], const Float4& color)
		{
			constexpr IndexType vertexSize = 3, indexSize = 3;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(pts[0], color);
			pVertex[1].set(pts[1], color);
			pVertex[2].set(pts[2], color);

			pIndex[0] = indexOffset;
			pIndex[1] = indexOffset + 1;
			pIndex[2] = indexOffset + 2;

			return indexSize;
		}

		uint16 BuildTriangle(BufferCreatorFunc bufferCreator, const Float2(&pts)[3], const Float4(&colors)[3])
		{
			constexpr IndexType vertexSize = 3, indexSize = 3;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(pts[0], colors[0]);
			pVertex[1].set(pts[1], colors[1]);
			pVertex[2].set(pts[2], colors[2]);

			pIndex[0] = indexOffset;
			pIndex[1] = indexOffset + 1;
			pIndex[2] = indexOffset + 2;

			return indexSize;
		}

		uint16 BuildRect(BufferCreatorFunc bufferCreator, const FloatRect& rect, const Float4& color)
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, color);
			pVertex[1].set(rect.right, rect.top, color);
			pVertex[2].set(rect.left, rect.bottom, color);
			pVertex[3].set(rect.right, rect.bottom, color);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		uint16 BuildRect(BufferCreatorFunc bufferCreator, const FloatRect& rect, const Float4(&colors)[4])
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, colors[0]);
			pVertex[1].set(rect.right, rect.top, colors[1]);
			pVertex[2].set(rect.left, rect.bottom, colors[3]);
			pVertex[3].set(rect.right, rect.bottom, colors[2]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		uint16 BuildRectFrame(BufferCreatorFunc bufferCreator, const FloatRect& rect, float thickness, const Float4& color)
		{
			constexpr IndexType vertexSize = 8, indexSize = 24;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].pos.set(rect.left - thickness, rect.top - thickness);
			pVertex[1].pos.set(rect.left, rect.top);
			pVertex[2].pos.set(rect.left - thickness, rect.bottom + thickness);
			pVertex[3].pos.set(rect.left, rect.bottom);
			pVertex[4].pos.set(rect.right + thickness, rect.top - thickness);
			pVertex[5].pos.set(rect.right, rect.top);
			pVertex[6].pos.set(rect.right + thickness, rect.bottom + thickness);
			pVertex[7].pos.set(rect.right, rect.bottom);

			for (size_t i = 0; i < 8; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectFrameIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildCircle(BufferCreatorFunc bufferCreator, const Float2& center, float r, const Float4& color, const float scale)
		{
			const float absR = Math::Abs(r);
			const IndexType quality = detail::CalculateCircleQuality(absR * scale);
			const IndexType vertexSize = quality + 1, indexSize = quality * 3;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
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

				for (IndexType i = 0; i < quality; ++i)
				{
					(pDst++)->pos.set(r * pCS->x + centerX, r * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = Math::TwoPiF / quality;
				Vertex2D* pDst = &pVertex[1];

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = radDelta * i;
					(pDst++)->pos.set(centerX + r * std::cos(rad), centerY - r * std::sin(rad));
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			{
				for (IndexType i = 0; i < quality - 1; ++i)
				{
					*pIndex++ = indexOffset + (i + 1);
					*pIndex++ = indexOffset;
					*pIndex++ = indexOffset + (i + 2);
				}

				*pIndex++ = indexOffset + quality;
				*pIndex++ = indexOffset;
				*pIndex++ = indexOffset + 1;
			}

			return indexSize;
		}

		uint16 BuildCircleFrame(BufferCreatorFunc bufferCreator, const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor, const float scale)
		{
			const float rOuter = rInner + thickness;
			const IndexType quality = detail::CalculateCircleFrameQuality(rOuter * scale);
			const IndexType vertexSize = quality * 2, indexSize = quality * 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			if (quality <= detail::MaxSinCosTableQuality)
			{
				const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < quality; ++i)
				{
					(pDst++)->pos.set(rOuter * pCS->x + centerX, rOuter * pCS->y + centerY);
					(pDst++)->pos.set(rInner * pCS->x + centerX, rInner * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = Math::TwoPiF / quality;
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = radDelta * i;
					const float c = std::cos(rad);
					const float s = std::sin(rad);
					(pDst++)->pos.set(centerX + rOuter * c, centerY - rOuter * s);
					(pDst++)->pos.set(centerX + rInner * c, centerY - rInner * s);
				}
			}

			for (IndexType i = 0; i < quality; ++i)
			{
				(pVertex++)->color = outerColor;
				(pVertex++)->color = innerColor;
			}

			for (IndexType i = 0; i < quality; ++i)
			{
				for (IndexType k = 0; k < 6; ++k)
				{
					*pIndex++ = indexOffset + (i * 2 + detail::RectIndexTable[k]) % (quality * 2);
				}
			}

			return indexSize;
		}

		uint16 BuildCirclePie(BufferCreatorFunc bufferCreator, const Float2& center, const float r, const float startAngle, const float _angle, const Float4& color, const float scale)
		{
			if (_angle == 0.0f)
			{
				return 0;
			}

			const float angle = Clamp(_angle, -Math::TwoPiF, Math::TwoPiF);
			const IndexType quality = detail::CalculateCirclePieQuality(r * scale, angle);
			const IndexType vertexSize = quality + 1, indexSize = (quality - 1) * 3;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			// 中心
			pVertex[0].pos.set(centerX, centerY);

			// 周
			{
				const float radDelta = Math::TwoPiF / (quality - 1);
				const float start = -(startAngle + angle) + Math::HalfPiF;
				const float angleScale = angle / Math::TwoPiF;
				Vertex2D* pDst = &pVertex[1];

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = start + (radDelta * i) * angleScale;
					(pDst++)->pos.set(centerX + r * std::cos(rad), centerY - r * std::sin(rad));
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType i = 0; i < quality - 1; ++i)
			{
				*pIndex++ = indexOffset + i + 1;
				*pIndex++ = indexOffset;
				*pIndex++ = indexOffset + i + 2;
			}

			return indexSize;
		}

		uint16 BuildCircleArc(BufferCreatorFunc bufferCreator, const Float2& center, const float rInner, const float startAngle, const float _angle, const float thickness, const Float4& color, const float scale)
		{
			if (_angle == 0.0f)
			{
				return 0;
			}

			const float angle = Clamp(_angle, -Math::TwoPiF, Math::TwoPiF);
			const float rOuter = rInner + thickness;
			const IndexType quality = detail::CalculateCirclePieQuality(rOuter * scale, angle);
			const IndexType vertexSize = quality * 2, indexSize = (quality - 1) * 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			{
				const float centerX = center.x;
				const float centerY = center.y;
				const float radDelta = Math::TwoPiF / (quality - 1);
				const float start = -(startAngle + angle) + Math::HalfPiF;
				const float angleScale = angle / Math::TwoPiF;
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = start + (radDelta * i) * angleScale;
					const float c = std::cos(rad);
					const float s = std::sin(rad);
					(pDst++)->pos.set(centerX + rOuter * c, centerY - rOuter * s);
					(pDst++)->pos.set(centerX + rInner * c, centerY - rInner * s);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType i = 0; i < quality - 1; ++i)
			{
				for (IndexType k = 0; k < 6; ++k)
				{
					*pIndex++ = indexOffset + (i * 2 + detail::RectIndexTable[k]);
				}
			}

			return indexSize;
		}

		uint16 BuildEllipse(BufferCreatorFunc bufferCreator, const Float2& center, const float a, const float b, const Float4& color, const float scale)
		{
			const float majorAxis = std::max(Math::Abs(a), Math::Abs(b));
			const IndexType quality = static_cast<IndexType>(std::clamp(majorAxis * scale * 0.225f + 18.0f, 6.0f, 255.0f));
			const IndexType vertexSize = quality + 1, indexSize = quality * 3;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
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

				for (IndexType i = 0; i < quality; ++i)
				{
					(pDst++)->pos.set(a * pCS->x + centerX, b * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = Math::TwoPiF / quality;
				Vertex2D* pDst = &pVertex[1];

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = radDelta * i;
					(pDst++)->pos.set(centerX + a * std::cos(rad), centerY - b * std::sin(rad));
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			{
				for (IndexType i = 0; i < quality - 1; ++i)
				{
					*pIndex++ = indexOffset + (i + 1);
					*pIndex++ = indexOffset;
					*pIndex++ = indexOffset + (i + 2);
				}

				*pIndex++ = indexOffset + quality;
				*pIndex++ = indexOffset;
				*pIndex++ = indexOffset + 1;
			}

			return indexSize;
		}

		uint16 BuildEllipseFrame(BufferCreatorFunc bufferCreator, const Float2& center, const float aInner, const float bInner, const float thickness, const Float4& innerColor, const Float4& outerColor, const float scale)
		{
			const float aOuter = aInner + thickness;
			const float bOuter = bInner + thickness;
			const float majorT = std::max(Math::Abs(aOuter), Math::Abs(bOuter));
			const IndexType quality = detail::CalculateCircleFrameQuality(majorT * scale);
			const IndexType vertexSize = quality * 2, indexSize = quality * 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			if (quality <= detail::MaxSinCosTableQuality)
			{
				const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < quality; ++i)
				{
					(pDst++)->pos.set(aOuter * pCS->x + centerX, bOuter * pCS->y + centerY);
					(pDst++)->pos.set(aInner * pCS->x + centerX, bInner * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = Math::TwoPiF / quality;
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < quality; ++i)
				{
					const float rad = radDelta * i;
					const float c = std::cos(rad);
					const float s = std::sin(rad);
					(pDst++)->pos.set(centerX + aOuter * c, centerY - bOuter * s);
					(pDst++)->pos.set(centerX + aInner * c, centerY - bInner * s);
				}
			}

			for (IndexType i = 0; i < quality; ++i)
			{
				(pVertex++)->color = outerColor;
				(pVertex++)->color = innerColor;
			}

			for (IndexType i = 0; i < quality; ++i)
			{
				for (IndexType k = 0; k < 6; ++k)
				{
					*pIndex++ = indexOffset + (i * 2 + detail::RectIndexTable[k]) % (quality * 2);
				}
			}

			return indexSize;
		}

		uint16 BuildQuad(BufferCreatorFunc bufferCreator, const FloatQuad& quad, const Float4 color)
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(quad.p[0], color);
			pVertex[1].set(quad.p[1], color);
			pVertex[2].set(quad.p[3], color);
			pVertex[3].set(quad.p[2], color);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildQuad(BufferCreatorFunc bufferCreator, const FloatQuad& quad, const Float4(&colors)[4])
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(quad.p[0], colors[0]);
			pVertex[1].set(quad.p[1], colors[1]);
			pVertex[2].set(quad.p[3], colors[3]);
			pVertex[3].set(quad.p[2], colors[2]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		uint16 BuildRoundRect(BufferCreatorFunc bufferCreator, const FloatRect& rect, const float w, const float h, const float r, const Float4& color, float scale)
		{
			const float rr = std::min({ w * 0.5f, h * 0.5f, std::max(0.0f, r) });
			const IndexType quality = detail::CaluculateFanQuality(rr * scale);
			
			Array<Float2> fanPositions(quality);
			{
				const float radDelta = Math::HalfPiF / (quality - 1);

				for (int32 i = 0; i < quality; ++i)
				{
					const float angle = radDelta * i;
					fanPositions[i].set(std::sin(angle) * rr, -std::cos(angle) * rr);
				}
			}

			const bool uniteV = (h * 0.5f == rr);
			const bool uniteH = (w * 0.5f == rr);
			const std::array<Float2, 4> centers =
			{ {
				{ rect.right - rr, rect.top + rr },
				{ rect.right - rr, rect.bottom - rr },
				{ rect.left + rr, rect.bottom - rr },
				{ rect.left + rr, rect.top + rr },
			} };

			const IndexType vertexSize = (quality - uniteV + quality - uniteH) * 2;
			const IndexType indexSize = (vertexSize - 2) * 3;

			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			{
				Vertex2D* pDst = pVertex;

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[0] + fanPositions[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[1] + Float2(fanPositions[quality - i - 1].x, -fanPositions[quality - i - 1].y);
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[2] + Float2(-fanPositions[i].x, -fanPositions[i].y);
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[3] + Float2(-fanPositions[quality - i - 1].x, fanPositions[quality - i - 1].y);
					++pDst;
				}

				for (size_t i = 0; i < vertexSize; ++i)
				{
					(pVertex++)->color = color;
				}
			}

			for (uint16 i = 0; i < (vertexSize - 2); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = indexOffset + i + 1;
				*pIndex++ = indexOffset + ((i + 2 < vertexSize) ? (i + 2) : 0);
			}

			return indexSize;
		}

		uint16 BuildShape2D(BufferCreatorFunc bufferCreator, const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color)
		{
			if (vertices.isEmpty() || indices.isEmpty())
			{
				return 0;
			}

			const IndexType vertexSize = static_cast<IndexType>(vertices.size());
			const IndexType indexSize = static_cast<IndexType>(indices.size());
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			{
				const Float2* pSrc = vertices.data();
				const Float2* pSrcEnd = pSrc + vertices.size();

				if (offset)
				{
					const Float2 _offset = offset.value();

					while (pSrc != pSrcEnd)
					{
						pVertex->pos = _offset + *pSrc++;
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
				std::memcpy(pIndex, indices.data(), indices.size_bytes());

				for (size_t i = 0; i < indexSize; ++i)
				{
					*(pIndex++) += indexOffset;
				}
			}

			return indexSize;
		}

		uint16 BuildShape2DTransformed(BufferCreatorFunc bufferCreator, const Array<Float2>& vertices, const Array<uint16>& indices, const float s, const float c, const Float2& offset, const Float4& color)
		{
			if (vertices.isEmpty() || indices.isEmpty())
			{
				return 0;
			}

			const IndexType vertexSize = static_cast<IndexType>(vertices.size());
			const IndexType indexSize = static_cast<IndexType>(indices.size());
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			{
				const Float2* pSrc = vertices.data();
				const Float2* pSrcEnd = pSrc + vertices.size();

				while (pSrc != pSrcEnd)
				{
					const Float2 v = *pSrc++;
					const float x = v.x * c - v.y * s + offset.x;
					const float y = v.x * s + v.y * c + offset.y;
					pVertex->pos.set(x, y);
					pVertex->color = color;
					++pVertex;
				}
			}

			{
				std::memcpy(pIndex, indices.data(), indices.size_bytes());

				for (size_t i = 0; i < indexSize; ++i)
				{
					*(pIndex++) += indexOffset;
				}
			}

			return indexSize;
		}

		uint16 BuildShape2DFrame(BufferCreatorFunc bufferCreator, const Float2* pts, uint16 size, const float thickness, const Float4& color, const float scale)
		{
			if (size < 2 || !pts)
			{
				return 0;
			}

			const float th2 = 0.01f / scale;

			Array<Float2> buf;
			{
				buf.push_back(pts[0]);

				for (uint16 i = 1; i < size - 1; ++i)
				{
					const Float2 back = pts[i - 1];
					const Float2 current = pts[i];

					if (back.distanceFromSq(current) < th2)
					{
						continue;
					}

					buf.push_back(current);
				}

				const Float2 back = pts[size - 2];
				const Float2 current = pts[size - 1];

				if (back.distanceFromSq(current) >= th2)
				{
					buf.push_back(current);
				}

				if (buf.size() >= 2 && buf.back().distanceFromSq(buf.front()) <= th2)
				{
					buf.pop_back();
				}

				if (buf.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2;

			buf2.push_back(buf.front());

			for (size_t i = 1; i < buf.size(); ++i)
			{
				const Float2 back = buf[i - 1];
				const Float2 current = buf[i];
				const Float2 next = buf[(i + 1) % buf.size()];

				const Float2 v1 = (back - current).normalized();
				const Float2 v2 = (next - current).normalized();

				buf2.push_back(current);

				if (v1.dot(v2) > threshold)
				{
					const Float2 line = current - back;
					const Float2 normal = Float2{ -line.y, line.x }.normalized();
					const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
					const Float2 line2 = next - current;

					if (tangent.dot(line2) >= (-tangent).dot(line2))
					{
						buf2.push_back(current + tangent.normalized()*th2);
					}
					else if (tangent.dot(line2) <= (-tangent).dot(line2))
					{
						buf2.push_back(current + (-tangent).normalized()*th2);
					}
					else
					{
						buf2.push_back(current + normal * 0.001f);
					}
				}
			}

			{
				const Float2 back = buf[buf.size() - 1];
				const Float2 current = buf[0];
				const Float2 next = buf[1];

				const Float2 v1 = (back - current).normalized();
				const Float2 v2 = (next - current).normalized();

				if (v1.dot(v2) > threshold)
				{
					const Float2 line = current - back;
					const Float2 normal = Float2{ -line.y, line.x }.normalized();
					const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
					const Float2 line2 = next - current;

					if (tangent.dot(line2) >= (-tangent).dot(line2))
					{
						buf2.push_back(current - tangent.normalized() * th2);
					}
					else if (tangent.dot(line2) <= (-tangent).dot(line2))
					{
						buf2.push_back(current - (-tangent).normalized() * th2);
					}
					else
					{
						buf2.push_back(current - normal * 0.001f);
					}
				}
			}

			size = static_cast<IndexType>(buf2.size());
			const IndexType vertexSize = size * 2, indexSize = 6 * (size - 1) + 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;

			{
				const Float2 p0 = buf2[buf2.size() - 1];
				const Float2 p1 = buf2[0];
				const Float2 p2 = buf2[1];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[0].pos.set(result0);
				pVertex[1].pos.set(result1);
			}

			for (uint16 i = 0; i < size - 2; ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			{
				const Float2 p0 = buf2[size - 2];
				const Float2 p1 = buf2[size - 1];
				const Float2 p2 = buf2[0];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[size * 2 - 2].pos.set(result0);
				pVertex[size * 2 - 1].pos.set(result1);
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType k = 0; k < size; ++k)
			{
				for (IndexType i = 0; i < 6; ++i)
				{
					*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
				}
			}

			return indexSize;
		}

		uint16 BuildSprite(BufferCreatorFunc bufferCreator, const Sprite& sprite, const IndexType startIndex, IndexType indexCount)
		{
			if (sprite.vertices.isEmpty() || sprite.indices.isEmpty() || sprite.indices.size() <= startIndex)
			{
				return 0;
			}

			if (sprite.indices.size() < (startIndex + indexCount))
			{
				indexCount = static_cast<IndexType>(sprite.indices.size() - startIndex);
			}

			if (indexCount % 3 != 0)
			{
				indexCount -= (indexCount % 3);
			}

			if (indexCount == 0)
			{
				return 0;
			}

			const IndexType vertexSize = static_cast<IndexType>(sprite.vertices.size());
			const IndexType indexSize = static_cast<IndexType>(indexCount);
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			std::memcpy(pVertex, sprite.vertices.data(), vertexSize * sizeof(Vertex2D));

			const IndexType* const pDstEnd = pIndex + indexSize;
			const IndexType* pSrc = &sprite.indices[startIndex];

			while (pIndex != pDstEnd)
			{
				*pIndex++ = indexOffset + (*pSrc++);
			}

			return indexSize;
		}

		uint16 BuildSquareCappedLineString(BufferCreatorFunc bufferCreator, const Vec2* pts, uint16 size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const bool isClosed, const float scale)
		{
			if (thickness <= 0.0f || !pts || size < 2)
			{
				return 0;
			}

			const bool hasCap = !isClosed;
			Float2 vNormalBegin(0, 0), vNormalEnd(0, 0);

			const float th2 = 0.01f / scale;

			Array<Float2> buf;
			{
				buf.push_back(pts[0]);

				for (uint16 i = 1; i < size - 1; ++i)
				{
					const Float2 back = pts[i - 1];
					const Float2 current = pts[i];

					if (back.distanceFromSq(current) < th2)
					{
						continue;
					}

					buf.push_back(current);
				}

				const Float2 back = pts[size - 2];
				const Float2 current = pts[size - 1];

				if (back.distanceFromSq(current) >= th2)
				{
					buf.push_back(current);
				}

				if (isClosed && buf.size() >= 2 && buf.back().distanceFromSq(buf.front()) <= th2)
				{
					buf.pop_back();
				}

				if (buf.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2;

			buf2.push_back(buf.front());

			for (size_t i = 1; i < buf.size() - 1 + isClosed; ++i)
			{
				const Float2 back = buf[i - 1];
				const Float2 current = buf[i];
				const Float2 next = buf[(i + 1) % buf.size()];

				const Float2 v1 = (back - current).normalized();
				const Float2 v2 = (next - current).normalized();

				buf2.push_back(current);

				if (!inner && v1.dot(v2) > threshold)
				{
					const Float2 line = current - back;
					const Float2 normal = Float2{ -line.y, line.x }.normalized();
					const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
					const Float2 line2 = next - current;

					if (tangent.dot(line2) >= (-tangent).dot(line2))
					{
						buf2.push_back(current + tangent.normalized()*th2);
					}
					else if (tangent.dot(line2) <= (-tangent).dot(line2))
					{
						buf2.push_back(current + (-tangent).normalized()*th2);
					}
					else
					{
						buf2.push_back(current + normal * 0.001f);
					}
				}
			}

			if (isClosed)
			{
				const Float2 back = buf[buf.size() - 1];
				const Float2 current = buf[0];
				const Float2 next = buf[1];

				const Float2 v1 = (back - current).normalized();
				const Float2 v2 = (next - current).normalized();

				if (!inner && v1.dot(v2) > threshold)
				{
					const Float2 line = current - back;
					const Float2 normal = Float2{ -line.y, line.x }.normalized();
					const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
					const Float2 line2 = next - current;

					if (tangent.dot(line2) >= (-tangent).dot(line2))
					{
						buf2.push_back(current - tangent.normalized() * th2);
					}
					else if (tangent.dot(line2) <= (-tangent).dot(line2))
					{
						buf2.push_back(current - (-tangent).normalized() * th2);
					}
					else
					{
						buf2.push_back(current - normal * 0.001f);
					}
				}
			}
			else
			{
				buf2.push_back(buf.back());
			}

			size = static_cast<IndexType>(buf2.size());
			const IndexType vertexSize = size * 2, indexSize = 6 * (size - 1) + (isClosed * 6);
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;

			if (isClosed)
			{
				const Float2 p0 = buf2.back();
				const Float2 p1 = buf2[0];
				const Float2 p2 = buf2[1];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[0].pos.set(result0);
				pVertex[1].pos.set(result1);
			}
			else
			{
				const Float2 p0 = buf2[0];
				const Float2 p1 = buf2[1];
				const Float2 line = (p1 - p0).normalize();
				vNormalBegin = Float2(-line.y * thicknessHalf, line.x * thicknessHalf);
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[0].pos.set(p0 + vNormalBegin - lineHalf * hasCap);
				pVertex[1].pos.set(p0 - vNormalBegin - lineHalf * hasCap);
			}

			for (uint16 i = 0; i < size - 2; ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			if (isClosed)
			{
				const Float2 p0 = buf2[size - 2];
				const Float2 p1 = buf2[size - 1];
				const Float2 p2 = buf2[0];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[size * 2 - 2].pos.set(result0);
				pVertex[size * 2 - 1].pos.set(result1);
			}
			else
			{
				const Float2 p0 = buf2[size - 2];
				const Float2 p1 = buf2[size - 1];
				const Float2 line = (p1 - p0).normalize();
				vNormalEnd = Float2(-line.y * thicknessHalf, line.x * thicknessHalf);
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[size * 2 - 2].pos.set(p1 + vNormalEnd + lineHalf * hasCap);
				pVertex[size * 2 - 1].pos.set(p1 - vNormalEnd + lineHalf * hasCap);
			}

			if (offset)
			{
				const Float2 v = offset.value();
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < vertexSize; ++i)
				{
					(pDst++)->pos.moveBy(v);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType k = 0; k < size - 1 + isClosed; ++k)
			{
				for (IndexType i = 0; i < 6; ++i)
				{
					*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
				}
			}

			return indexSize;
		}

		uint16 BuildRoundCappedLineString(BufferCreatorFunc bufferCreator, const Vec2* pts, uint16 size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const float scale, float& startAngle, float& endAngle)
		{
			if (thickness <= 0.0f || !pts || size < 2)
			{
				return 0;
			}

			const bool hasCap = false;
			Float2 vNormalBegin(0, 0), vNormalEnd(0, 0);

			const float th2 = 0.01f / scale;

			Array<Float2> buf;
			{
				buf.push_back(pts[0]);

				for (uint16 i = 1; i < size - 1; ++i)
				{
					const Float2 back = pts[i - 1];
					const Float2 current = pts[i];

					if (back.distanceFromSq(current) < th2)
					{
						continue;
					}

					buf.push_back(current);
				}

				const Float2 back = pts[size - 2];
				const Float2 current = pts[size - 1];

				if (back.distanceFromSq(current) >= th2)
				{
					buf.push_back(current);
				}

				if (buf.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2;

			buf2.push_back(buf.front());

			for (size_t i = 1; i < buf.size() - 1; ++i)
			{
				const Float2 back = buf[i - 1];
				const Float2 current = buf[i];
				const Float2 next = buf[(i + 1) % buf.size()];

				const Float2 v1 = (back - current).normalized();
				const Float2 v2 = (next - current).normalized();

				buf2.push_back(current);

				if (!inner && v1.dot(v2) > threshold)
				{
					const Float2 line = current - back;
					const Float2 normal = Float2{ -line.y, line.x }.normalized();
					const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
					const Float2 line2 = next - current;

					if (tangent.dot(line2) >= (-tangent).dot(line2))
					{
						buf2.push_back(current + tangent.normalized()*th2);
					}
					else if (tangent.dot(line2) <= (-tangent).dot(line2))
					{
						buf2.push_back(current + (-tangent).normalized()*th2);
					}
					else
					{
						buf2.push_back(current + normal * 0.001f);
					}
				}
			}

			buf2.push_back(buf.back());

			size = static_cast<IndexType>(buf2.size());
			const IndexType vertexSize = size * 2, indexSize = 6 * (size - 1);
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;

			{
				const Float2 p0 = buf2[0];
				const Float2 p1 = buf2[1];
				const Float2 line = (p1 - p0).normalize();
				vNormalBegin = Float2(-line.y * thicknessHalf, line.x * thicknessHalf);
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[0].pos.set(p0 + vNormalBegin - lineHalf * hasCap);
				pVertex[1].pos.set(p0 - vNormalBegin - lineHalf * hasCap);
			}

			for (uint16 i = 0; i < size - 2; ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 tangent = ((p2 - p1).normalized() + (p1 - p0).normalized()).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			{
				const Float2 p0 = buf2[size - 2];
				const Float2 p1 = buf2[size - 1];
				const Float2 line = (p1 - p0).normalize();
				vNormalEnd = Float2(-line.y * thicknessHalf, line.x * thicknessHalf);
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[size * 2 - 2].pos.set(p1 + vNormalEnd + lineHalf * hasCap);
				pVertex[size * 2 - 1].pos.set(p1 - vNormalEnd + lineHalf * hasCap);
			}

			if (offset)
			{
				const Float2 v = offset.value();
				Vertex2D* pDst = pVertex;

				for (IndexType i = 0; i < vertexSize; ++i)
				{
					(pDst++)->pos.moveBy(v);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType k = 0; k < size - 1; ++k)
			{
				for (IndexType i = 0; i < 6; ++i)
				{
					*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
				}
			}

			startAngle = std::atan2(vNormalBegin.x, -vNormalBegin.y);
			endAngle = std::atan2(-vNormalEnd.x, vNormalEnd.y);

			return indexSize;
		}

		uint16 BuildDotLineString(BufferCreatorFunc bufferCreator, const Vec2* pts, uint16 size, const Optional<Float2>& offset, const float thickness, const Float4& color, const bool isClosed, const bool squareDot, const float dotOffset, const bool hasAlignedDot, const float scale)
		{
			if (thickness <= 0.0f || !pts || size < 2)
			{
				return 0;
			}

			Float2 vNormalBegin(0, 0);

			const float th2 = 0.01f / scale;

			Array<Float2> buf;
			{
				buf.push_back(pts[0]);

				for (uint16 i = 1; i < size - 1; ++i)
				{
					const Float2 back = pts[i - 1];
					const Float2 current = pts[i];

					if (back.distanceFromSq(current) < th2)
					{
						continue;
					}

					buf.push_back(current);
				}

				const Float2 back = pts[size - 2];
				const Float2 current = pts[size - 1];

				if (back.distanceFromSq(current) >= th2)
				{
					buf.push_back(current);
				}

				if (isClosed && buf.size() >= 2 && buf.back().distanceFromSq(buf.front()) <= th2)
				{
					buf.pop_back();
				}

				if (buf.size() < 2)
				{
					return 0;
				}
			}

			Array<Float2> buf2;

			buf2.push_back(buf.front());

			for (size_t i = 1; i < buf.size() - 1 + isClosed; ++i)
			{
				const Float2 current = buf[i];

				buf2.push_back(current);
			}

			if (!isClosed)
			{
				buf2.push_back(buf.back());
			}

			if (isClosed)
			{
				buf2.push_back(buf.front());
			}

			size = static_cast<IndexType>(buf2.size());
			const IndexType vertexSize = (size - 1) * 4, indexSize = 6 * (size - 1);
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			const float thicknessHalf = thickness * 0.5f;

			for (uint16 i = 0; i < size - 1; ++i)
			{
				const Float2 p0 = buf2[i + 0];
				const Float2 p1 = buf2[i + 1];
				const Float2 line = (p1 - p0).normalize();
				vNormalBegin = Float2(-line.y * thicknessHalf, line.x * thicknessHalf);
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[i * 4 + 0].pos.set(p0 + vNormalBegin - lineHalf);
				pVertex[i * 4 + 1].pos.set(p0 - vNormalBegin - lineHalf);
				pVertex[i * 4 + 2].pos.set(p1 + vNormalBegin + lineHalf);
				pVertex[i * 4 + 3].pos.set(p1 - vNormalBegin + lineHalf);
			}

			if (offset)
			{
				const Float2 v = offset.value();

				for (IndexType i = 0; i < vertexSize; ++i)
				{
					pVertex[i].pos.moveBy(v);
				}
			}

			if (squareDot)
			{
				const float uOffset = static_cast<float>((1.0f - Math::Fraction(dotOffset / 3.0f / thickness)) * 3.0f);
				const float vInfo = std::min(1.0f / (thickness * scale), 1.0f);
				const float invThickness = 1.0f / thickness;
				float distance = 0.0f;

				pVertex[0].tex.set(uOffset, vInfo);
				pVertex[1].tex.set(uOffset, vInfo);

				for (IndexType i = 1; i < vertexSize / 2; ++i)
				{
					distance += pVertex[(i - 1) * 2].pos.distanceFrom(pVertex[i * 2].pos);

					pVertex[i * 2 + 0].tex.set(distance * invThickness + uOffset, vInfo);
					pVertex[i * 2 + 1].tex.set(distance * invThickness + uOffset, vInfo);
				}
			}
			else
			{
				float uOffset = static_cast<float>((1.0f - Math::Fraction(dotOffset / 2.0 / thickness)) * 2.0f);
				const float invThickness = 1.0f / thickness;
				float distance = 0.0f;

				if (hasAlignedDot)
				{
					const float m = std::fmod(distance - 1.0f, 2.0f);
					distance += 2.0f - m;
					uOffset = 0.0f;
				}

				pVertex[0].tex.set(0.5f + uOffset, 1.0f);
				pVertex[1].tex.set(0.5f + uOffset, -1.0f);

				for (IndexType i = 1; i < vertexSize / 2; ++i)
				{
					distance += pVertex[(i - 1) * 2].pos.distanceFrom(pVertex[i * 2].pos) * invThickness;

					if (hasAlignedDot)
					{
						const float m = std::fmod(distance - 1.0f, 2.0f);
						distance += 2.0f - m;
						uOffset = 0.0f;
					}

					pVertex[i * 2 + 0].tex.set(0.5f + distance + uOffset, 1.0f);
					pVertex[i * 2 + 1].tex.set(0.5f + distance + uOffset, -1.0f);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType k = 0; k < size - 1; ++k)
			{
				for (IndexType i = 0; i < 6; ++i)
				{
					*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 4));
				}
			}

			return indexSize;
		}

		uint16 BuildTextureRegion(BufferCreatorFunc bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4& color)
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, uv.left, uv.top, color);
			pVertex[1].set(rect.right, rect.top, uv.right, uv.top, color);
			pVertex[2].set(rect.left, rect.bottom, uv.left, uv.bottom, color);
			pVertex[3].set(rect.right, rect.bottom, uv.right, uv.bottom, color);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		uint16 BuildTextureRegion(BufferCreatorFunc bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, uv.left, uv.top, colors[0]);
			pVertex[1].set(rect.right, rect.top, uv.right, uv.top, colors[1]);
			pVertex[2].set(rect.left, rect.bottom, uv.left, uv.bottom, colors[3]);
			pVertex[3].set(rect.right, rect.bottom, uv.right, uv.bottom, colors[2]);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		uint16 BuildTexturedCircle(BufferCreatorFunc bufferCreator, const Circle& circle, const FloatRect& uv, const Float4& color, const float scale)
		{
			const float rf = static_cast<float>(circle.r);
			const float absR = Math::Abs(rf);
			const float centerX = static_cast<float>(circle.x);
			const float centerY = static_cast<float>(circle.y);
			const float centerU = (uv.left + uv.right) * 0.5f;
			const float centerV = (uv.top + uv.bottom) * 0.5f;
			const float rU = (uv.right - uv.left) * 0.5f;
			const float rV = (uv.bottom - uv.top) * 0.5f;

			const IndexType quality = static_cast<IndexType>(std::min((absR * scale) * 0.225f + 18.0f, 255.0f));
			const IndexType vertexSize = quality + 1, indexSize = quality * 3;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			// 中心
			pVertex[0].set(centerX, centerY, centerU, centerV);

			// 周
			const float radDelta = Math::TwoPiF / quality;

			for (IndexType i = 1; i <= quality; ++i)
			{
				const float rad = radDelta * (i - 1.0f);
				const float c = std::cos(rad);
				const float s = std::sin(rad);
				pVertex[i].set(centerX + rf * c, centerY - rf * s, centerU + rU * c, centerV - rV * s);
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (IndexType i = 0; i < quality; ++i)
			{
				*pIndex++ = indexOffset + (i + 0) + 1;
				*pIndex++ = indexOffset;
				*pIndex++ = indexOffset + (i + 1) % quality + 1;
			}

			return indexSize;
		}

		uint16 BuildTexturedQuad(BufferCreatorFunc bufferCreator, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
		{
			constexpr IndexType vertexSize = 4, indexSize = 6;
			auto[pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			pVertex[0].set(quad.p[0], uv.left, uv.top, color);
			pVertex[1].set(quad.p[1], uv.right, uv.top, color);
			pVertex[2].set(quad.p[3], uv.left, uv.bottom, color);
			pVertex[3].set(quad.p[2], uv.right, uv.bottom, color);

			for (IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		uint16 BuildTexturedParticles(BufferCreatorFunc bufferCreator, const Array<Particle2D>& particles,
			const ParticleSystem2DParameters::SizeOverLifeTimeFunc& sizeOverLifeTimeFunc, const ParticleSystem2DParameters::ColorOverLifeTimeFunc& colorOverLifeTimeFunc)
		{
			const IndexType vertexSize = static_cast<IndexType>(particles.size() * 4), indexSize = static_cast<IndexType>(particles.size() * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (!pVertex)
			{
				return 0;
			}

			for (const auto& particle : particles)
			{
				const float size = sizeOverLifeTimeFunc(particle.startSize, particle.startLifeTime, particle.remainingLifeTime);
				const Float4 color = colorOverLifeTimeFunc(particle.startColor, particle.startLifeTime, particle.remainingLifeTime);

				const float size_half = (size * 0.5f);
				const float cx = particle.position.x;
				const float cy = particle.position.y;

				const float x = size_half;
				const float s = std::sin(particle.rotation);
				const float c = std::cos(particle.rotation);
				const float xc = x * c;
				const float xs = x * s;

				pVertex[0].set({ -xc + xs + cx, -xs - xc + cy }, 0.0f, 0.0f, color);
				pVertex[1].set({ xc + xs + cx, xs - xc + cy }, 1.0f, 0.0f, color);
				pVertex[2].set({ -xc - xs + cx, -xs + xc + cy }, 0.0f, 1.0f, color);
				pVertex[3].set({ xc - xs + cx, xs + xc + cy }, 1.0f, 1.0f, color);
				pVertex += 4;
			}

			{
				IndexType indexBase = indexOffset;

				for (IndexType n = 0; n < particles.size(); ++n)
				{
					for (IndexType i = 0; i < 6; ++i)
					{
						*pIndex++ = (indexBase + detail::RectIndexTable[i]);
					}

					indexBase += 4;
				}
			}

			return indexSize;
		}
	}
}
