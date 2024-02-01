//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Vertex2DBuilder.hpp"
# include <Siv3D/FastMath.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/OffsetCircular.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

		static constexpr Vertex2D::IndexType RectFrameIndexTable[24] = { 0, 1, 2, 3, 2, 1, 0, 4, 1, 5, 1, 4, 5, 4, 7, 6, 7, 4, 3, 7, 2, 6, 2, 7 };

		static constexpr Vertex2D::IndexType MaxSinCosTableQuality = 40;

		static constexpr Vertex2D::IndexType SinCosTableSize = ((MaxSinCosTableQuality - 5) * (6 + (MaxSinCosTableQuality))) / 2;

		static const std::array<Float2, SinCosTableSize> CircleSinCosTable = []()
		{
			std::array<Float2, SinCosTableSize> results;
			Float2* pDst = results.data();

			for (int32 quality = 6; quality <= MaxSinCosTableQuality; ++quality)
			{
				const float radDelta = Math::TwoPiF / quality;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
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

		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CalculateCircleFrameQuality(const float size) noexcept
		{
			if (size <= 1.0f)
			{
				return 6;
			}
			else if (size <= 8.0f)
			{
				return Max(static_cast<Vertex2D::IndexType>(2.0 * size), Vertex2D::IndexType(8));
			}
			else
			{
				return static_cast<Vertex2D::IndexType>(Min(16 + (size - 8.0f) / 2.2f, 255.0f));
			}
		}

		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CalculateCirclePieQuality(const float size, const float angle)
		{
			const float rate = Min(Abs(angle) / (Math::TwoPiF) * 2.0f, 1.0f);

			Vertex2D::IndexType quality = 0;

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
				quality = static_cast<Vertex2D::IndexType>(Min(size * 0.225f + 18.0f, 255.0f));
			}

			return static_cast<Vertex2D::IndexType>(Max(quality * rate, 3.0f));
		}

		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CaluculateFanQuality(const float r) noexcept
		{
			return r <= 1.0f ? 3
				: r <= 6.0f ? 5
				: r <= 12.0f ? 8
				: static_cast<Vertex2D::IndexType>(Min(64.0f, r * 0.2f + 6));
		}
	}

	namespace Vertex2DBuilder
	{
		Vertex2D::IndexType BuildLine(const LineStyle& style, const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2], const float scale)
		{
			if (thickness <= 0.0f)
			{
				return 0;
			}

			if (style.hasSquareCap())
			{
				return BuildCappedLine(bufferCreator, begin, end, thickness, colors);
			}
			else if (style.hasNoCap())
			{
				return BuildUncappedLine(bufferCreator, begin, end, thickness, colors);
			}
			else if (style.hasRoundCap())
			{
				float startAngle = 0.0f;
				Vertex2D::IndexType indexCount = BuildUncappedLine(bufferCreator, begin, end, thickness, colors, startAngle);

				const float thicknessHalf = (thickness * 0.5f);
				indexCount += BuildCirclePie(bufferCreator, begin, thicknessHalf, startAngle, Math::PiF, colors[0], colors[0], scale);
				indexCount += BuildCirclePie(bufferCreator, end, thicknessHalf, startAngle + Math::PiF, Math::PiF, colors[1], colors[1], scale);

				return indexCount;
			}
			else if (style.hasSquareDot())
			{
				return BuildSquareDotLine(bufferCreator, begin, end, thickness, colors, static_cast<float>(style.dotOffset), scale);
			}
			else if (style.hasRoundDot())
			{
				return BuildRoundDotLine(bufferCreator, begin, end, thickness, colors, static_cast<float>(style.dotOffset), style.hasAlignedDot);
			}
			else
			{
				return 0;
			}
		}

		Vertex2D::IndexType BuildCappedLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2])
		{
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

			pVertex[0].set(begin2 + vNormal, colors[0]);
			pVertex[1].set(begin2 - vNormal, colors[0]);
			pVertex[2].set(end2 + vNormal, colors[1]);
			pVertex[3].set(end2 - vNormal, colors[1]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildUncappedLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2])
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float halfThickness = (thickness * 0.5f);
			const Float2 line = (end - begin).normalized();
			const Float2 vNormal{ (-line.y * halfThickness), (line.x * halfThickness) };

			pVertex[0].set(begin + vNormal, colors[0]);
			pVertex[1].set(begin - vNormal, colors[0]);
			pVertex[2].set(end + vNormal, colors[1]);
			pVertex[3].set(end - vNormal, colors[1]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildUncappedLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float& startAngle)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float halfThickness = (thickness * 0.5f);
			const Float2 line = (end - begin).normalized();
			const Float2 vNormal{ (-line.y * halfThickness), (line.x * halfThickness) };

			pVertex[0].set(begin + vNormal, colors[0]);
			pVertex[1].set(begin - vNormal, colors[0]);
			pVertex[2].set(end + vNormal, colors[1]);
			pVertex[3].set(end - vNormal, colors[1]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			startAngle = std::atan2(vNormal.x, -vNormal.y);

			return indexSize;
		}

		Vertex2D::IndexType BuildSquareDotLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], const float dotOffset, const float scale)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float halfThickness = (thickness * 0.5f);
			const Float2 v = (end - begin);
			const float lineLength = v.length();
			const Float2 line = (v / lineLength);
			const Float2 vNormal{ (-line.y * halfThickness), (line.x * halfThickness) };
			const Float2 lineHalf{ line * halfThickness };

			const Float2 begin2 = (begin - lineHalf);
			const Float2 end2 = (end + lineHalf);

			// UV
			const float lineLengthN = lineLength / thickness;
			const float uOffset = static_cast<float>((1.0f - Math::Fraction(dotOffset / 3.0f / thickness)) * 3.0f);
			const float vInfo = Min(1.0f / (thickness * scale), 1.0f);

			pVertex[0].set(begin2 + vNormal, uOffset, vInfo, colors[0]);
			pVertex[1].set(begin2 - vNormal, uOffset, vInfo, colors[0]);
			pVertex[2].set(end2 + vNormal, uOffset + lineLengthN, vInfo, colors[1]);
			pVertex[3].set(end2 - vNormal, uOffset + lineLengthN, vInfo, colors[1]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRoundDotLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], const float dotOffset, const bool hasAlignedDot)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float halfThickness = (thickness * 0.5f);
			const Float2 v = (end - begin);
			const float lineLength = v.length();
			const Float2 line = (v / lineLength);
			const Float2 vNormal{ (-line.y * halfThickness), (line.x * halfThickness) };
			const Float2 lineHalf{ line * halfThickness };

			const Float2 begin2 = (begin - lineHalf);
			const Float2 end2 = (end + lineHalf);

			// UV
			float lineLengthN = (lineLength / thickness);
			float uOffset = static_cast<float>((1.0f - Math::Fraction(dotOffset / 2.0f / thickness)) * 2.0f);
			if (hasAlignedDot)
			{
				const float m = Math::Fmod(lineLengthN - 1.0f, 2.0f);
				lineLengthN += (2.0f - m);
				uOffset = 0.5f;
			}

			pVertex[0].set(begin2 + vNormal, uOffset, 1.0f, colors[0]);
			pVertex[1].set(begin2 - vNormal, uOffset, -1.0f, colors[0]);
			pVertex[2].set(end2 + vNormal, uOffset + lineLengthN, 1.0f, colors[1]);
			pVertex[3].set(end2 - vNormal, uOffset + lineLengthN, -1.0f, colors[1]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = indexOffset + detail::RectIndexTable[i];
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildTriangle(const BufferCreatorFunc& bufferCreator, const Float2(&points)[3], const Float4& color)
		{
			constexpr Vertex2D::IndexType vertexSize = 3, indexSize = 3;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(points[0], color);
			pVertex[1].set(points[1], color);
			pVertex[2].set(points[2], color);

			pIndex[0] = indexOffset;
			pIndex[1] = (indexOffset + 1);
			pIndex[2] = (indexOffset + 2);

			return indexSize;
		}

		Vertex2D::IndexType BuildTriangle(const BufferCreatorFunc& bufferCreator, const Float2(&points)[3], const Float4(&colors)[3])
		{
			constexpr Vertex2D::IndexType vertexSize = 3, indexSize = 3;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(points[0], colors[0]);
			pVertex[1].set(points[1], colors[1]);
			pVertex[2].set(points[2], colors[2]);

			pIndex[0] = indexOffset;
			pIndex[1] = (indexOffset + 1);
			pIndex[2] = (indexOffset + 2);

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

		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4(&colors)[4])
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, colors[0]);
			pVertex[1].set(rect.right, rect.top, colors[1]);
			pVertex[2].set(rect.left, rect.bottom, colors[3]);
			pVertex[3].set(rect.right, rect.bottom, colors[2]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRectFrame(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor)
		{
			constexpr Vertex2D::IndexType vertexSize = 8, indexSize = 24;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].pos.set((rect.left - thickness), (rect.top - thickness));
			pVertex[1].pos.set(rect.left, rect.top);
			pVertex[2].pos.set((rect.left - thickness), (rect.bottom + thickness));
			pVertex[3].pos.set(rect.left, rect.bottom);
			pVertex[4].pos.set((rect.right + thickness), (rect.top - thickness));
			pVertex[5].pos.set(rect.right, rect.top);
			pVertex[6].pos.set((rect.right + thickness), (rect.bottom + thickness));
			pVertex[7].pos.set(rect.right, rect.bottom);

			for (size_t i = 0; i < 4; ++i)
			{
				(pVertex++)->color = outerColor;
				(pVertex++)->color = innerColor;
			}

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectFrameIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRectFrameTB(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, float thickness, const Float4& topColor, const Float4& bottomColor)
		{
			constexpr Vertex2D::IndexType vertexSize = 8, indexSize = 24;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].pos.set((rect.left - thickness), (rect.top - thickness));
			pVertex[1].pos.set(rect.left, rect.top);
			pVertex[2].pos.set((rect.left - thickness), (rect.bottom + thickness));
			pVertex[3].pos.set(rect.left, rect.bottom);
			pVertex[4].pos.set((rect.right + thickness), (rect.top - thickness));
			pVertex[5].pos.set(rect.right, rect.top);
			pVertex[6].pos.set((rect.right + thickness), (rect.bottom + thickness));
			pVertex[7].pos.set(rect.right, rect.bottom);

			{
				const Float4 tc = topColor;
				const Float4 bc = bottomColor;
				const float y = rect.top;
				const float invH = (1.0f / (rect.bottom - rect.top));

				for (size_t i = 0; i < vertexSize; ++i)
				{
					const float t = ((pVertex->pos.y - y) * invH);
					(pVertex++)->color = tc.lerp(bc, t);
				}
			}

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectFrameIndexTable[i]);
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

		Vertex2D::IndexType BuildCircleFrame(const BufferCreatorFunc& bufferCreator, const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor, const float scale)
		{
			const float rOuter = (rInner + thickness);
			const Vertex2D::IndexType quality = detail::CalculateCircleFrameQuality(rOuter * scale);
			const Vertex2D::IndexType vertexSize = (quality * 2), indexSize = (quality * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			if (quality <= detail::MaxSinCosTableQuality)
			{
				const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
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

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + rOuter * c, centerY - rOuter * s);
					(pDst++)->pos.set(centerX + rInner * c, centerY - rInner * s);
				}
			}

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				(pVertex++)->color = outerColor;
				(pVertex++)->color = innerColor;
			}

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				for (Vertex2D::IndexType k = 0; k < 6; ++k)
				{
					*pIndex++ = (indexOffset + (i * 2 + detail::RectIndexTable[k]) % (quality * 2));
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildCirclePie(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, float startAngle, float _angle, const Float4& innerColor, const Float4& outerColor, float scale)
		{
			if (_angle == 0.0f)
			{
				return 0;
			}

			const float angle = Clamp(_angle, -Math::TwoPiF, Math::TwoPiF);
			const Vertex2D::IndexType quality = detail::CalculateCirclePieQuality(r * scale, angle);
			const Vertex2D::IndexType vertexSize = (quality + 1), indexSize = ((quality - 1) * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			// 中心
			pVertex[0].pos.set(centerX, centerY);

			// 周
			{
				const float start = (startAngle + ((angle < 0.0f) ? angle : 0.0f));
				const float radDelta = (Abs(angle) / (quality - 1));
				Vertex2D* pDst = &pVertex[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (start + (radDelta * i));
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + r * s, centerY - r * c);
				}
			}

			{
				(pVertex++)->color = innerColor;

				for (size_t i = 1; i < vertexSize; ++i)
				{
					(pVertex++)->color = outerColor;
				}
			}

			for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + i + 1);
				*pIndex++ = (indexOffset + i + 2);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildCircleArcRoundCap(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, float startAngle, const Float4& startColor, const Float4& endColor, float scale)
		{
			const Vertex2D::IndexType quality = detail::CalculateCirclePieQuality(r * scale, Math::PiF);
			const Vertex2D::IndexType vertexSize = quality, indexSize = ((quality - 2) * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;
			const float radDelta = (Math::PiF / (quality - 1));

			// 周
			{
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (startAngle + (radDelta * i));
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + r * s, centerY - r * c);
				}
			}

			{
				const size_t midIndex = (vertexSize >> 1);

				pVertex[0].color = startColor;
				pVertex[vertexSize - 1].color = endColor;

				for (size_t i = 1; i < midIndex; ++i)
				{
					const float rad = (radDelta * i);
					const auto f = (std::cos(rad) * 0.5f + 0.5f);
					pVertex[i].color = endColor.lerp(startColor, f);
					pVertex[vertexSize - i - 1].color = startColor.lerp(endColor, f);
				}

				if (vertexSize & 1)
				{
					pVertex[midIndex].color = endColor.lerp(startColor, 0.5f);
				}
			}

			for (Vertex2D::IndexType i = 0; i < (quality - 2); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + i + 1);
				*pIndex++ = (indexOffset + i + 2);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildCircleArc(const BufferCreatorFunc& bufferCreator, const LineStyle& style, const Float2& center, const float rInner, const float startAngle, const float _angle, const float thickness, const Float4& innerColor, const Float4& outerColor, const float scale)
		{
			if (style.hasRoundCap())
			{
				Vertex2D::IndexType indexCount = BuildUncappedCircleArc(bufferCreator, center, rInner, startAngle, _angle, thickness, innerColor, outerColor, scale);

				const float halfThickness = (thickness * 0.5f);
				const Float2 startPos	= OffsetCircularF(center, (rInner + halfThickness), startAngle).fastToFloat2();
				const Float2 endPos		= OffsetCircularF(center, (rInner + halfThickness), startAngle + _angle).fastToFloat2();

				indexCount += BuildCircleArcRoundCap(bufferCreator, startPos, halfThickness, (startAngle + Math::PiF), innerColor, outerColor, scale);
				indexCount += BuildCircleArcRoundCap(bufferCreator, endPos, halfThickness, (startAngle + _angle), outerColor, innerColor, scale);

				return indexCount;
			}
			else
			{
				return BuildUncappedCircleArc(bufferCreator, center, rInner, startAngle, _angle, thickness, innerColor, outerColor, scale);
			}
		}

		Vertex2D::IndexType BuildUncappedCircleArc(const BufferCreatorFunc& bufferCreator, const Float2& center, const float rInner, const float startAngle, const float _angle, const float thickness, const Float4& innerColor, const Float4& outerColor, const float scale)
		{
			if (_angle == 0.0f)
			{
				return 0;
			}

			const float angle = Clamp(_angle, -Math::TwoPiF, Math::TwoPiF);
			const float rOuter = rInner + thickness;
			const Vertex2D::IndexType quality = detail::CalculateCirclePieQuality(rOuter * scale, angle);
			const Vertex2D::IndexType vertexSize = (quality * 2), indexSize = ((quality - 1) * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			{
				const float centerX = center.x;
				const float centerY = center.y;
				const float start = (startAngle + ((angle < 0.0f) ? angle : 0.0f));
				const float radDelta = (Abs(angle) / (quality - 1));
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (start + (radDelta * i));
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + rInner * s, centerY - rInner * c);
					(pDst++)->pos.set(centerX + rOuter * s, centerY - rOuter * c);
				}
			}

			for (size_t i = 0; i < vertexSize / 2; ++i)
			{
				(pVertex++)->color = innerColor;
				(pVertex++)->color = outerColor;
			}

			for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
			{
				for (Vertex2D::IndexType k = 0; k < 6; ++k)
				{
					*pIndex++ = indexOffset + (i * 2 + detail::RectIndexTable[k]);
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildCircleSegment(const BufferCreatorFunc& bufferCreator, const Float2& center, const float r, const float startAngle, const float _angle, const Float4& color, const float scale)
		{
			if (_angle == 0.0f)
			{
				return 0;
			}

			const float angle = Clamp(_angle, -Math::TwoPiF, Math::TwoPiF);
			const Vertex2D::IndexType quality = detail::CalculateCirclePieQuality(r * scale, angle);
			const Vertex2D::IndexType vertexSize = (quality + 1), indexSize = ((quality - 1) * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			{
				const auto [s1, c1] = FastMath::SinCos(startAngle);
				const Float2 p1{ s1, -c1 };

				const auto [s2, c2] = FastMath::SinCos(startAngle + angle);
				const Float2 p2{ s2, -c2 };

				const Float2 mid = ((p1 + p2) * 0.5f * r);

				// 中心
				pVertex[0].pos = (mid + Float2{ centerX, centerY });
			}

			// 周
			{
				const float start = (startAngle + ((angle < 0.0f) ? angle : 0.0f));
				const float radDelta = (Abs(angle) / (quality - 1));
				Vertex2D* pDst = &pVertex[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (start + (radDelta * i));
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + r * s, centerY - r * c);
				}
			}

			{
				for (size_t i = 0; i < vertexSize; ++i)
				{
					(pVertex++)->color = color;
				}
			}

			for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + i + 1);
				*pIndex++ = (indexOffset + i + 2);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildEllipse(const BufferCreatorFunc& bufferCreator, const Float2& center, float a, float b, const Float4& innerColor, const Float4& outerColor, float scale)
		{
			const float majorAxis = Max(Abs(a), Abs(b));
			const Vertex2D::IndexType quality = static_cast<Vertex2D::IndexType>(Clamp(majorAxis * scale * 0.225f + 18.0f, 6.0f, 255.0f));
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
					(pDst++)->pos.set(a * pCS->x + centerX, b * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = (Math::TwoPiF / quality);
				Vertex2D* pDst = &pVertex[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + a * c, centerY - b * s);
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
				for (Vertex2D::IndexType i = 0; i < quality - 1; ++i)
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

		Vertex2D::IndexType BuildEllipseFrame(const BufferCreatorFunc& bufferCreator, const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor, float scale)
		{
			const float aOuter = (aInner + thickness);
			const float bOuter = (bInner + thickness);
			const float majorT = Max(Abs(aOuter), Abs(bOuter));
			const Vertex2D::IndexType quality = detail::CalculateCircleFrameQuality(majorT * scale);
			const Vertex2D::IndexType vertexSize = (quality * 2), indexSize = (quality * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float centerX = center.x;
			const float centerY = center.y;

			if (quality <= detail::MaxSinCosTableQuality)
			{
				const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					(pDst++)->pos.set(aOuter * pCS->x + centerX, bOuter * pCS->y + centerY);
					(pDst++)->pos.set(aInner * pCS->x + centerX, bInner * pCS->y + centerY);
					++pCS;
				}
			}
			else
			{
				const float radDelta = (Math::TwoPiF / quality);
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->pos.set(centerX + aOuter * c, centerY - bOuter * s);
					(pDst++)->pos.set(centerX + aInner * c, centerY - bInner * s);
				}
			}

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				(pVertex++)->color = outerColor;
				(pVertex++)->color = innerColor;
			}

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				for (Vertex2D::IndexType k = 0; k < 6; ++k)
				{
					*pIndex++ = (indexOffset + (i * 2 + detail::RectIndexTable[k]) % (quality * 2));
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const Float4 color)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(quad.p[0], color);
			pVertex[1].set(quad.p[1], color);
			pVertex[2].set(quad.p[3], color);
			pVertex[3].set(quad.p[2], color);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const Float4(&colors)[4])
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(quad.p[0], colors[0]);
			pVertex[1].set(quad.p[1], colors[1]);
			pVertex[2].set(quad.p[3], colors[3]);
			pVertex[3].set(quad.p[2], colors[2]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRoundRect(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const FloatRect& rect, float w, float h, float r, const Float4& color, float scale)
		{
			const float rr = Min({ w * 0.5f, h * 0.5f, Max(0.0f, r) });
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(rr * scale);

			buffer.resize(quality);
			{
				const float radDelta = (Math::HalfPiF / (quality - 1));

				for (int32 i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					buffer[i].set(s * rr, -c * rr);
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

			const Vertex2D::IndexType vertexSize = (quality - uniteV + quality - uniteH) * 2;
			const Vertex2D::IndexType indexSize = (vertexSize - 2) * 3;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			{
				Vertex2D* pDst = pVertex;

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[0] + buffer[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y };
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[2] - buffer[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y };
					++pDst;
				}

				for (size_t i = 0; i < vertexSize; ++i)
				{
					(pVertex++)->color = color;
				}
			}

			for (Vertex2D::IndexType i = 0; i < (vertexSize - 2); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + i + 1);
				*pIndex++ = (indexOffset + ((i + 2 < vertexSize) ? (i + 2) : 0));
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRoundRect(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const FloatRect& rect, float w, float h, float r, const Float4& topColor, const Float4& bottomColor, float scale)
		{
			const float rr = Min({ w * 0.5f, h * 0.5f, Max(0.0f, r) });
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(rr * scale);

			buffer.resize(quality);
			{
				const float radDelta = (Math::HalfPiF / (quality - 1));

				for (int32 i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					buffer[i].set(s * rr, -c * rr);
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

			const Vertex2D::IndexType vertexSize = (quality - uniteV + quality - uniteH) * 2;
			const Vertex2D::IndexType indexSize = (vertexSize - 2) * 3;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			{
				Vertex2D* pDst = pVertex;

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[0] + buffer[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y };
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[2] - buffer[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y };
					++pDst;
				}

				{
					const Float4 tc = topColor;
					const Float4 bc = bottomColor;
					const float y = rect.top;
					const float invH = (1.0f / h);

					for (size_t i = 0; i < vertexSize; ++i)
					{
						const float t = ((pVertex->pos.y - y) * invH);
						(pVertex++)->color = tc.lerp(bc, t);
					}
				}
			}

			for (Vertex2D::IndexType i = 0; i < (vertexSize - 2); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + i + 1);
				*pIndex++ = (indexOffset + ((i + 2 < vertexSize) ? (i + 2) : 0));
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRoundRectFrame(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const RoundRect& outer, const RoundRect& inner, const Float4& color, float scale)
		{
			const float orr = static_cast<float>(outer.r);
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(orr * scale);

			const Vertex2D::IndexType outerVertexSize = (quality * 4);
			const Vertex2D::IndexType vertexSize = (outerVertexSize * 2);
			const Vertex2D::IndexType indexSize = (outerVertexSize * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			// 外側の頂点
			{
				buffer.resize(quality);
				{
					const float radDelta = (Math::HalfPiF / (quality - 1));

					for (int32 i = 0; i < quality; ++i)
					{
						const float rad = (radDelta * i);
						const auto [s, c] = FastMath::SinCos(rad);
						buffer[i].set(s * orr, -c * orr);
					}
				}

				const FloatRect rect{ outer.rect.x, outer.rect.y, outer.rect.rightX(), outer.rect.bottomY() };
				const std::array<Float2, 4> centers =
				{ {
					{ rect.right - orr, rect.top + orr },
					{ rect.right - orr, rect.bottom - orr },
					{ rect.left + orr, rect.bottom - orr },
					{ rect.left + orr, rect.top + orr },
				} };

				Vertex2D* pDst = pVertex;

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[0] + buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y });
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[2] - buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y });
					++pDst;
				}
			}

			// 内側の頂点
			{
				const float irr = static_cast<float>(inner.r);
				{
					const float s = (irr / orr);

					for (int32 i = 0; i < quality; ++i)
					{
						buffer[i] *= s;
					}
				}

				const FloatRect rect{ inner.rect.x, inner.rect.y, inner.rect.rightX(), inner.rect.bottomY() };
				const std::array<Float2, 4> centers =
				{ {
					{ rect.right - irr, rect.top + irr },
					{ rect.right - irr, rect.bottom - irr },
					{ rect.left + irr, rect.bottom - irr },
					{ rect.left + irr, rect.top + irr },
				} };

				Vertex2D* pDst = (pVertex + outerVertexSize);

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[0] + buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y });
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[2] - buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y });
					++pDst;
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			for (Vertex2D::IndexType i = 0; i < outerVertexSize; ++i)
			{
				const Vertex2D::IndexType i0 = (indexOffset + i);
				const Vertex2D::IndexType i1 = (indexOffset + (((i + 1) < outerVertexSize) ? (i + 1) : 0));
				const Vertex2D::IndexType i2 = (indexOffset + outerVertexSize + i);
				const Vertex2D::IndexType i3 = (indexOffset + outerVertexSize + (((i + 1) < outerVertexSize) ? (i + 1) : 0));

				*pIndex++ = i0;
				*pIndex++ = i1;
				*pIndex++ = i2;

				*pIndex++ = i2;
				*pIndex++ = i1;
				*pIndex++ = i3;
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildRoundRectFrame(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const RoundRect& outer, const RoundRect& inner, const Float4& topColor, const Float4& bottomColor, float scale)
		{
			const float orr = static_cast<float>(outer.r);
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(orr * scale);

			const Vertex2D::IndexType outerVertexSize = (quality * 4);
			const Vertex2D::IndexType vertexSize = (outerVertexSize * 2);
			const Vertex2D::IndexType indexSize = (outerVertexSize * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			// 外側の頂点
			{
				buffer.resize(quality);
				{
					const float radDelta = (Math::HalfPiF / (quality - 1));

					for (int32 i = 0; i < quality; ++i)
					{
						const float rad = (radDelta * i);
						const auto [s, c] = FastMath::SinCos(rad);
						buffer[i].set(s * orr, -c * orr);
					}
				}

				const FloatRect rect{ outer.rect.x, outer.rect.y, outer.rect.rightX(), outer.rect.bottomY() };
				const std::array<Float2, 4> centers =
				{ {
					{ rect.right - orr, rect.top + orr },
					{ rect.right - orr, rect.bottom - orr },
					{ rect.left + orr, rect.bottom - orr },
					{ rect.left + orr, rect.top + orr },
				} };

				Vertex2D* pDst = pVertex;

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[0] + buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y });
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[2] - buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y });
					++pDst;
				}
			}

			// 内側の頂点
			{
				const float irr = static_cast<float>(inner.r);
				{
					const float s = (irr / orr);

					for (int32 i = 0; i < quality; ++i)
					{
						buffer[i] *= s;
					}
				}

				const FloatRect rect{ inner.rect.x, inner.rect.y, inner.rect.rightX(), inner.rect.bottomY() };
				const std::array<Float2, 4> centers =
				{ {
					{ rect.right - irr, rect.top + irr },
					{ rect.right - irr, rect.bottom - irr },
					{ rect.left + irr, rect.bottom - irr },
					{ rect.left + irr, rect.top + irr },
				} };

				Vertex2D* pDst = (pVertex + outerVertexSize);

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[0] + buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y });
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[2] - buffer[i]);
					++pDst;
				}

				for (int32 i = 0; i < quality; ++i)
				{
					pDst->pos = (centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y });
					++pDst;
				}
			}

			{
				const Float4 tc = topColor;
				const Float4 bc = bottomColor;
				const float y = static_cast<float>(outer.rect.y);
				const float invH = (1.0f / static_cast<float>(outer.rect.h));

				for (size_t i = 0; i < vertexSize; ++i)
				{
					const float t = ((pVertex->pos.y - y) * invH);
					(pVertex++)->color = tc.lerp(bc, t);
				}
			}

			for (Vertex2D::IndexType i = 0; i < outerVertexSize; ++i)
			{
				const Vertex2D::IndexType i0 = (indexOffset + i);
				const Vertex2D::IndexType i1 = (indexOffset + (((i + 1) < outerVertexSize) ? (i + 1) : 0));
				const Vertex2D::IndexType i2 = (indexOffset + outerVertexSize + i);
				const Vertex2D::IndexType i3 = (indexOffset + outerVertexSize + (((i + 1) < outerVertexSize) ? (i + 1) : 0));

				*pIndex++ = i0;
				*pIndex++ = i1;
				*pIndex++ = i2;

				*pIndex++ = i2;
				*pIndex++ = i1;
				*pIndex++ = i3;
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const LineStyle& style, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const CloseRing closeRing, const float scale)
		{
			if ((size < 2)
				|| (32760 <= size)
				|| (thickness <= 0.0f)
				|| (not points))
			{
				return 0;
			}

			if (closeRing)
			{
				return BuildClosedLineString(bufferCreator, buffer, points, size, offset, thickness, inner, color, scale);
			}

			if (style.hasSquareCap())
			{
				return BuildCappedLineString(bufferCreator, buffer, points, size, offset, thickness, inner, color, scale);
			}
			else if (style.hasNoCap())
			{
				return BuildUncappedLineString(bufferCreator, buffer, points, size, offset, thickness, inner, color, scale, nullptr, nullptr);
			}
			else if (style.hasRoundCap())
			{
				float startAngle0 = 0.0f, startAngle1 = 0.0f;
				Vertex2D::IndexType indexCount = BuildUncappedLineString(bufferCreator, buffer, points, size, offset, thickness, inner, color, scale, &startAngle0, &startAngle1);

				if (indexCount)
				{
					const float thicknessHalf = (thickness * 0.5f);
					indexCount += BuildCirclePie(bufferCreator, points[0], thicknessHalf, startAngle0, Math::PiF, color, color, scale);
					indexCount += BuildCirclePie(bufferCreator, points[size - 1], thicknessHalf, startAngle1 + Math::PiF, Math::PiF, color, color, scale);
				}

				return indexCount;
			}
			else
			{
				throw NotImplementedError{ U"LineString does not support dotted line style yet" };
			}
		}

		Vertex2D::IndexType BuildClosedLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const float scale)
		{
			const float th2 = (0.01f / scale);
			const double th2D = th2;

			buffer.clear();
			{
				buffer.push_back(points[0]);

				for (size_t i = 1; i < (size - 1); ++i)
				{
					const Vec2 back = points[i - 1];
					const Vec2 current = points[i];

					if (back.distanceFromSq(current) < th2D)
					{
						continue;
					}

					buffer.push_back(current);
				}

				const Vec2 back = points[size - 2];
				const Vec2 current = points[size - 1];

				if (back.distanceFromSq(current) >= th2D)
				{
					buffer.push_back(current);
				}

				if ((buffer.size() >= 2)
					&& buffer.back().distanceFromSq(buffer.front()) <= th2)
				{
					buffer.pop_back();
				}

				if (buffer.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2(Arg::reserve = buffer.size());
			{
				buf2.push_back(buffer.front());

				const size_t count = buffer.size();

				for (size_t i = 1; i < count; ++i)
				{
					const Float2 back = buffer[i - 1];
					const Float2 current = buffer[i];
					const Float2 next = buffer[(i + 1) % buffer.size()];

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					buf2.push_back(current);

					if ((not inner)
						&& (v1.dot(v2) > threshold))
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

						if (tangent.dot(line2) >= (-tangent).dot(line2))
						{
							buf2.push_back(current + tangent.normalized() * th2);
						}
						else if (tangent.dot(line2) <= (-tangent).dot(line2))
						{
							buf2.push_back(current + (-tangent).normalized() * th2);
						}
						else
						{
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.push_back(current + normal * 0.001f);
						}
					}
				}

				
				{
					const Float2 back = buffer[buffer.size() - 1];
					const Float2 current = buffer[0];
					const Float2 next = buffer[1];

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					if ((not inner)
						&& (v1.dot(v2) > threshold))
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

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
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.push_back(current - normal * 0.001f);
						}
					}
				}
			}

			const Vertex2D::IndexType newSize = static_cast<Vertex2D::IndexType>(buf2.size());
			const Vertex2D::IndexType vertexSize = (newSize * 2), indexSize = (6 * (newSize - 1) + 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float thicknessHalf = (thickness * 0.5f);

			{
				const Float2 p0 = buf2.back();
				const Float2 p1 = buf2[0];
				const Float2 p2 = buf2[1];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[0].pos.set(result0);
				pVertex[1].pos.set(result1);
			}

			for (Vertex2D::IndexType i = 0; i < (newSize - 2); ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			
			{
				const Float2 p0 = buf2[newSize - 2];
				const Float2 p1 = buf2[newSize - 1];
				const Float2 p2 = buf2[0];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[newSize * 2 - 2].pos.set(result0);
				pVertex[newSize * 2 - 1].pos.set(result1);
			}

			if (offset)
			{
				const Float2 v = *offset;
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < vertexSize; ++i)
				{
					(pDst++)->pos.moveBy(v);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			{
				const Vertex2D::IndexType count = static_cast<Vertex2D::IndexType>(newSize);

				for (Vertex2D::IndexType k = 0; k < count; ++k)
				{
					for (Vertex2D::IndexType i = 0; i < 6; ++i)
					{
						*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
					}
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildCappedLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const float scale)
		{
			const float th2 = (0.01f / scale);
			const double th2D = th2;

			buffer.clear();
			{
				buffer.push_back(points[0]);

				for (size_t i = 1; i < (size - 1); ++i)
				{
					const Vec2 back = points[i - 1];
					const Vec2 current = points[i];

					if (back.distanceFromSq(current) < th2D)
					{
						continue;
					}

					buffer.push_back(current);
				}

				const Vec2 back = points[size - 2];
				const Vec2 current = points[size - 1];

				if (back != current)
				{
					buffer.push_back(current);
				}

				if (buffer.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2(Arg::reserve = buffer.size());
			{
				buf2.push_back(buffer.front());

				const size_t count = (buffer.size() - 1);

				for (size_t i = 1; i < count; ++i)
				{
					const Float2 back = buffer[i - 1];
					const Float2 current = buffer[i];
					const Float2 next = buffer[(i + 1) % buffer.size()];

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					buf2.push_back(current);

					if ((not inner)
						&& (v1.dot(v2) > threshold))
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

						if (tangent.dot(line2) >= (-tangent).dot(line2))
						{
							buf2.push_back(current + tangent.normalized() * th2);
						}
						else if (tangent.dot(line2) <= (-tangent).dot(line2))
						{
							buf2.push_back(current + (-tangent).normalized() * th2);
						}
						else
						{
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.push_back(current + normal * 0.001f);
						}
					}
				}

				{
					buf2.push_back(buffer.back());
				}
			}

			const Vertex2D::IndexType newSize = static_cast<Vertex2D::IndexType>(buf2.size());
			const Vertex2D::IndexType vertexSize = (newSize * 2), indexSize = (6 * (newSize - 1));
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float thicknessHalf = (thickness * 0.5f);

			{
				const Float2 p0 = buf2[0];
				const Float2 p1 = buf2[1];
				const Float2 line = (p1 - p0).normalize();
				const Float2 vNormalBegin{ -line.y * thicknessHalf, line.x * thicknessHalf };
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[0].pos.set(p0 + vNormalBegin - lineHalf);
				pVertex[1].pos.set(p0 - vNormalBegin - lineHalf);
			}

			for (Vertex2D::IndexType i = 0; i < (newSize - 2); ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			{
				const Float2 p0 = buf2[newSize - 2];
				const Float2 p1 = buf2[newSize - 1];
				const Float2 line = (p1 - p0).normalize();
				const Float2 vNormalEnd{ -line.y * thicknessHalf, line.x * thicknessHalf };
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[newSize * 2 - 2].pos.set(p1 + vNormalEnd + lineHalf);
				pVertex[newSize * 2 - 1].pos.set(p1 - vNormalEnd + lineHalf);
			}

			if (offset)
			{
				const Float2 v = *offset;
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < vertexSize; ++i)
				{
					(pDst++)->pos.moveBy(v);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			{
				const Vertex2D::IndexType count = static_cast<Vertex2D::IndexType>(newSize - 1);

				for (Vertex2D::IndexType k = 0; k < count; ++k)
				{
					for (Vertex2D::IndexType i = 0; i < 6; ++i)
					{
						*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
					}
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildUncappedLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Vec2* points, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const float scale, float* startAngle0, float* startAngle1)
		{
			const float th2 = (0.01f / scale);
			const double th2D = th2;

			buffer.clear();
			{
				buffer.push_back(points[0]);

				for (size_t i = 1; i < (size - 1); ++i)
				{
					const Vec2 back = points[i - 1];
					const Vec2 current = points[i];

					if (back.distanceFromSq(current) < th2D)
					{
						continue;
					}

					buffer.push_back(current);
				}

				const Vec2 back = points[size - 2];
				const Vec2 current = points[size - 1];

				if (back != current)
				{
					buffer.push_back(current);
				}

				if (buffer.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2(Arg::reserve = buffer.size());
			{
				buf2.push_back(buffer.front());

				const size_t count = (buffer.size() - 1);

				for (size_t i = 1; i < count; ++i)
				{
					const Float2 back = buffer[i - 1];
					const Float2 current = buffer[i];
					const Float2 next = buffer[(i + 1) % buffer.size()];

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					buf2.push_back(current);

					if ((not inner)
						&& (v1.dot(v2) > threshold))
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

						if (tangent.dot(line2) >= (-tangent).dot(line2))
						{
							buf2.push_back(current + tangent.normalized() * th2);
						}
						else if (tangent.dot(line2) <= (-tangent).dot(line2))
						{
							buf2.push_back(current + (-tangent).normalized() * th2);
						}
						else
						{
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.push_back(current + normal * 0.001f);
						}
					}
				}

				{
					buf2.push_back(buffer.back());
				}
			}

			const Vertex2D::IndexType newSize = static_cast<Vertex2D::IndexType>(buf2.size());
			const Vertex2D::IndexType vertexSize = (newSize * 2), indexSize = (6 * (newSize - 1));
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float thicknessHalf = (thickness * 0.5f);

			{
				const Float2 p0 = buf2[0];
				const Float2 p1 = buf2[1];
				const Float2 line = (p1 - p0).normalize();
				const Float2 vNormalBegin{ -line.y * thicknessHalf, line.x * thicknessHalf };

				if (startAngle0)
				{
					*startAngle0 = std::atan2(vNormalBegin.x, -vNormalBegin.y);
				}

				pVertex[0].pos.set(p0 + vNormalBegin);
				pVertex[1].pos.set(p0 - vNormalBegin);
			}

			for (Vertex2D::IndexType i = 0; i < (newSize - 2); ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			{
				const Float2 p0 = buf2[newSize - 2];
				const Float2 p1 = buf2[newSize - 1];
				const Float2 line = (p1 - p0).normalize();
				const Float2 vNormalEnd{ -line.y * thicknessHalf, line.x * thicknessHalf };

				if (startAngle1)
				{
					*startAngle1 = std::atan2(vNormalEnd.x, -vNormalEnd.y);
				}

				pVertex[newSize * 2 - 2].pos.set(p1 + vNormalEnd);
				pVertex[newSize * 2 - 1].pos.set(p1 - vNormalEnd);
			}

			if (offset)
			{
				const Float2 v = *offset;
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < vertexSize; ++i)
				{
					(pDst++)->pos.moveBy(v);
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			{
				const Vertex2D::IndexType count = static_cast<Vertex2D::IndexType>(newSize - 1);

				for (Vertex2D::IndexType k = 0; k < count; ++k)
				{
					for (Vertex2D::IndexType i = 0; i < 6; ++i)
					{
						*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
					}
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildDefaultLineString(const BufferCreatorFunc& bufferCreator, const Vec2* points, const ColorF* colors, const size_t size, const Optional<Float2>& offset, const float thickness, const bool inner, const CloseRing closeRing, const float scale)
		{
			if ((size < 2)
				|| (32760 <= size)
				|| (thickness <= 0.0f)
				|| (not points))
			{
				return 0;
			}

			const float th2 = (0.01f / scale);
			const double th2D = th2;

			Array<std::pair<Float2, Float4>> buf(Arg::reserve = size);
			{
				buf.emplace_back(points[0], colors[0].toFloat4());

				for (size_t i = 1; i < (size - 1); ++i)
				{
					const Vec2 back = points[i - 1];
					const Vec2 current = points[i];

					if (back.distanceFromSq(current) < th2D)
					{
						continue;
					}

					buf.emplace_back(current, colors[i].toFloat4());
				}

				const Vec2 back = points[size - 2];
				const Vec2 current = points[size - 1];

				if (back.distanceFromSq(current) >= th2D)
				{
					buf.emplace_back(current, colors[size - 1].toFloat4());
				}

				if (closeRing
					&& (buf.size() >= 2)
					&& buf.back().first.distanceFromSq(buf.front().first) <= th2)
				{
					buf.pop_back();
				}

				if (buf.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<std::pair<Float2, Float4>> buf2(Arg::reserve = buf.size());
			{
				buf2.push_back(buf.front());

				const size_t count = (buf.size() - 1 + static_cast<bool>(closeRing));

				for (size_t i = 1; i < count; ++i)
				{
					const Float2 back = buf[i - 1].first;
					const Float2 current = buf[i].first;
					const Float2 next = buf[(i + 1) % buf.size()].first;
					const Float4 currentColor = buf[i].second;

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					buf2.emplace_back(current, currentColor);

					if ((not inner)
						&& (v1.dot(v2) > threshold))
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

						if (tangent.dot(line2) >= (-tangent).dot(line2))
						{
							buf2.emplace_back(current + tangent.normalized() * th2, currentColor);
						}
						else if (tangent.dot(line2) <= (-tangent).dot(line2))
						{
							buf2.emplace_back(current + (-tangent).normalized() * th2, currentColor);
						}
						else
						{
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.emplace_back(current + normal * 0.001f, currentColor);
						}
					}
				}

				if (closeRing)
				{
					const Float2 back = buf[buf.size() - 1].first;
					const Float2 current = buf[0].first;
					const Float2 next = buf[1].first;

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					if ((not inner)
						&& (v1.dot(v2) > threshold))
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);
						const Float4 currentColor = buf[0].second;

						if (tangent.dot(line2) >= (-tangent).dot(line2))
						{
							buf2.emplace_back(current - tangent.normalized() * th2, currentColor);
						}
						else if (tangent.dot(line2) <= (-tangent).dot(line2))
						{
							buf2.emplace_back(current - (-tangent).normalized() * th2, currentColor);
						}
						else
						{
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.emplace_back(current - normal * 0.001f, currentColor);
						}
					}
				}
				else
				{
					buf2.push_back(buf.back());
				}
			}

			const Vertex2D::IndexType newSize = static_cast<Vertex2D::IndexType>(buf2.size());
			const Vertex2D::IndexType vertexSize = (newSize * 2), indexSize = (6 * (newSize - 1) + (static_cast<bool>(closeRing) * 6));
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float thicknessHalf = (thickness * 0.5f);
			const bool hasCap = (not closeRing);

			if (closeRing)
			{
				const Float2 p0 = buf2.back().first;
				const Float2 p1 = buf2[0].first;
				const Float2 p2 = buf2[1].first;
				const Float4 c = buf2[0].second;
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[0].set(result0, c);
				pVertex[1].set(result1, c);
			}
			else
			{
				const Float2 p0 = buf2[0].first;
				const Float2 p1 = buf2[1].first;
				const Float4 c = buf2[0].second;
				const Float2 line = (p1 - p0).normalize();
				const Float2 vNormalBegin{ -line.y * thicknessHalf, line.x * thicknessHalf };
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[0].set(p0 + vNormalBegin - lineHalf * hasCap, c);
				pVertex[1].set(p0 - vNormalBegin - lineHalf * hasCap, c);
			}

			for (Vertex2D::IndexType i = 0; i < (newSize - 2); ++i)
			{
				const Float2 p0 = buf2[i].first;
				const Float2 p1 = buf2[i + 1].first;
				const Float2 p2 = buf2[i + 2].first;
				const Float4 c = buf2[i + 1].second;
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].set(result0, c);
				pVertex[i * 2 + 3].set(result1, c);
			}

			if (closeRing)
			{
				const Float2 p0 = buf2[newSize - 2].first;
				const Float2 p1 = buf2[newSize - 1].first;
				const Float2 p2 = buf2[0].first;
				const Float4 c = buf2[newSize - 1].second;
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[newSize * 2 - 2].set(result0, c);
				pVertex[newSize * 2 - 1].set(result1, c);
			}
			else
			{
				const Float2 p0 = buf2[newSize - 2].first;
				const Float2 p1 = buf2[newSize - 1].first;
				const Float4 c = buf2[newSize - 1].second;
				const Float2 line = (p1 - p0).normalize();
				const Float2 vNormalEnd{ -line.y * thicknessHalf, line.x * thicknessHalf };
				const Float2 lineHalf(line * thicknessHalf);

				pVertex[newSize * 2 - 2].set(p1 + vNormalEnd + lineHalf * hasCap, c);
				pVertex[newSize * 2 - 1].set(p1 - vNormalEnd + lineHalf * hasCap, c);
			}

			if (offset)
			{
				const Float2 v = *offset;
				Vertex2D* pDst = pVertex;

				for (Vertex2D::IndexType i = 0; i < vertexSize; ++i)
				{
					(pDst++)->pos.moveBy(v);
				}
			}

			{
				const Vertex2D::IndexType count = static_cast<Vertex2D::IndexType>(newSize - 1 + static_cast<bool>(closeRing));

				for (Vertex2D::IndexType k = 0; k < count; ++k)
				{
					for (Vertex2D::IndexType i = 0; i < 6; ++i)
					{
						*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
					}
				}
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
					const Float2 _offset = *offset;

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

			std::memcpy(pVertex, vertices, (vertexSize * sizeof(Vertex2D)));

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

		Vertex2D::IndexType BuildPolygonTransformed(const BufferCreatorFunc& bufferCreator, const Array<Float2>& vertices, const Array<TriangleIndex>& tirnagleIndices, const float s, const float c, const Float2& offset, const Float4& color)
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
				const Float2* pSrc		= vertices.data();
				const Float2* pSrcEnd	= (pSrc + vertices.size());
				const Float2 _offset	= offset;

				while (pSrc != pSrcEnd)
				{
					const Float2 v = *pSrc++;
					const float x = (v.x * c - v.y * s + _offset.x);
					const float y = (v.x * s + v.y * c + _offset.y);
					pVertex->pos.set(x, y);
					pVertex->color = color;
					++pVertex;
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

		Vertex2D::IndexType BuildPolygonFrame(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Float2* points, const size_t size, const float thickness, const Float4& color, const float scale)
		{
			if ((size < 3)
				|| (32760 <= size)
				|| (thickness <= 0.0f)
				|| (not points))
			{
				return 0;
			}

			const float th2 = (0.01f / scale);
			const double th2D = th2;

			buffer.clear();
			{
				buffer.push_back(points[0]);

				for (size_t i = 1; i < (size - 1); ++i)
				{
					const Vec2 back = points[i - 1];
					const Vec2 current = points[i];

					if (back.distanceFromSq(current) < th2D)
					{
						continue;
					}

					buffer.push_back(current);
				}

				const Vec2 back = points[size - 2];
				const Vec2 current = points[size - 1];

				if (back.distanceFromSq(current) >= th2D)
				{
					buffer.push_back(current);
				}

				if ((buffer.size() >= 2)
					&& buffer.back().distanceFromSq(buffer.front()) <= th2)
				{
					buffer.pop_back();
				}

				if (buffer.size() < 2)
				{
					return 0;
				}
			}

			const float threshold = 0.55f;

			Array<Float2> buf2(Arg::reserve = buffer.size());
			{
				buf2.push_back(buffer.front());

				const size_t count = buffer.size();

				for (size_t i = 1; i < count; ++i)
				{
					const Float2 back = buffer[i - 1];
					const Float2 current = buffer[i];
					const Float2 next = buffer[(i + 1) % count];

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					buf2.push_back(current);

					if (v1.dot(v2) > threshold)
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

						if (tangent.dot(line2) >= (-tangent).dot(line2))
						{
							buf2.push_back(current + tangent.normalized() * th2);
						}
						else if (tangent.dot(line2) <= (-tangent).dot(line2))
						{
							buf2.push_back(current + (-tangent).normalized() * th2);
						}
						else
						{
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.push_back(current + normal * 0.001f);
						}
					}
				}

				{
					const Float2 back = buffer[buffer.size() - 1];
					const Float2 current = buffer[0];
					const Float2 next = buffer[1];

					const Float2 v1 = (back - current).normalized();
					const Float2 v2 = (next - current).normalized();

					if (v1.dot(v2) > threshold)
					{
						const Float2 line = (current - back);
						const Float2 tangent = ((next - current).normalized() + (current - back).normalized()).normalized();
						const Float2 line2 = (next - current);

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
							const Float2 normal = Float2{ -line.y, line.x }.normalized();
							buf2.push_back(current - normal * 0.001f);
						}
					}
				}
			}

			const Vertex2D::IndexType newSize = static_cast<Vertex2D::IndexType>(buf2.size());
			const Vertex2D::IndexType vertexSize = (newSize * 2), indexSize = (6 * (newSize - 1) + 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			const float thicknessHalf = (thickness * 0.5f);

			{
				const Float2 p0 = buf2.back();
				const Float2 p1 = buf2[0];
				const Float2 p2 = buf2[1];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[0].pos.set(result0);
				pVertex[1].pos.set(result1);
			}

			for (Vertex2D::IndexType i = 0; i < (newSize - 2); ++i)
			{
				const Float2 p0 = buf2[i];
				const Float2 p1 = buf2[i + 1];
				const Float2 p2 = buf2[i + 2];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[i * 2 + 2].pos.set(result0);
				pVertex[i * 2 + 3].pos.set(result1);
			}

			{
				const Float2 p0 = buf2[newSize - 2];
				const Float2 p1 = buf2[newSize - 1];
				const Float2 p2 = buf2[0];
				const Float2 line = p1 - p0;
				const Float2 normal = Float2{ -line.y, line.x }.normalized();
				const Float2 v = (p2 - p1).normalized() + (p1 - p0).normalized();
				const Float2 tangent = (v.lengthSq() > 0.001f) ? v.normalized() : (p2 - p0).normalized();
				const Float2 miter = Float2{ -tangent.y, tangent.x };
				const float length = thicknessHalf / miter.dot(normal);
				const Float2 result0 = p1 + miter * length;
				const Float2 result1 = p1 - miter * length;

				pVertex[newSize * 2 - 2].pos.set(result0);
				pVertex[newSize * 2 - 1].pos.set(result1);
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
			}

			{
				const Vertex2D::IndexType count = static_cast<Vertex2D::IndexType>(newSize);

				for (Vertex2D::IndexType k = 0; k < count; ++k)
				{
					for (Vertex2D::IndexType i = 0; i < 6; ++i)
					{
						*pIndex++ = (indexOffset + (detail::RectIndexTable[i] + k * 2) % vertexSize);
					}
				}
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildTextureRegion(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4& color)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, uv.left, uv.top, color);
			pVertex[1].set(rect.right, rect.top, uv.right, uv.top, color);
			pVertex[2].set(rect.left, rect.bottom, uv.left, uv.bottom, color);
			pVertex[3].set(rect.right, rect.bottom, uv.right, uv.bottom, color);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildTextureRegion(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(rect.left, rect.top, uv.left, uv.top, colors[0]);
			pVertex[1].set(rect.right, rect.top, uv.right, uv.top, colors[1]);
			pVertex[2].set(rect.left, rect.bottom, uv.left, uv.bottom, colors[3]);
			pVertex[3].set(rect.right, rect.bottom, uv.right, uv.bottom, colors[2]);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildTexturedCircle(const BufferCreatorFunc& bufferCreator, const Circle& circle, const FloatRect& uv, const Float4& color, const float scale)
		{
			const float rf = static_cast<float>(circle.r);
			const float absR = Abs(rf);
			const Vertex2D::IndexType quality = detail::CalculateCircleQuality(absR * scale);
			const Vertex2D::IndexType vertexSize = (quality + 1), indexSize = (quality * 3);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			// 中心
			const float centerX = static_cast<float>(circle.x);
			const float centerY = static_cast<float>(circle.y);
			
			const float centerU = (uv.left + uv.right) * 0.5f;
			const float centerV = (uv.top + uv.bottom) * 0.5f;
			const float rU = (uv.right - uv.left) * 0.5f;
			const float rV = (uv.bottom - uv.top) * 0.5f;
			
			pVertex[0].set(centerX, centerY, centerU, centerV);

			// 周
			{
				const float radDelta = (Math::TwoPiF / quality);
				Vertex2D* pDst = &pVertex[1];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					(pDst++)->set((centerX + rf * c), (centerY - rf * s), (centerU + rU * c), (centerV - rV * s));
				}
			}

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = color;
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

		Vertex2D::IndexType BuildTexturedQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
		{
			constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			pVertex[0].set(quad.p[0], uv.left, uv.top, color);
			pVertex[1].set(quad.p[1], uv.right, uv.top, color);
			pVertex[2].set(quad.p[3], uv.left, uv.bottom, color);
			pVertex[3].set(quad.p[2], uv.right, uv.bottom, color);

			for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
			{
				*pIndex++ = (indexOffset + detail::RectIndexTable[i]);
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildTexturedRoundRect(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const FloatRect& rect, const float w, const float h, const float r, const FloatRect& uvRect, const Float4& color, const float scale)
		{
			const float rr = Min({ w * 0.5f, h * 0.5f, Max(0.0f, r) });
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(rr * scale);

			buffer.resize(quality);
			{
				const float radDelta = (Math::HalfPiF / (quality - 1));

				for (int32 i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);
					buffer[i].set(s * rr, -c * rr);
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

			const Vertex2D::IndexType vertexSize = (quality - uniteV + quality - uniteH) * 2;
			const Vertex2D::IndexType indexSize = (vertexSize - 2) * 3;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
			{
				return 0;
			}

			{
				Vertex2D* pDst = pVertex;

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[0] + buffer[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[1] + Float2{ buffer[quality - i - 1].x, -buffer[quality - i - 1].y };
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					pDst->pos = centers[2] - buffer[i];
					++pDst;
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					pDst->pos = centers[3] + Float2{ -buffer[quality - i - 1].x, buffer[quality - i - 1].y };
					++pDst;
				}
			}

			{
				Vertex2D* pDst = pVertex;

				for (size_t i = 0; i < vertexSize; ++i)
				{
					(pDst++)->color = color;
				}
			}

			{
				const float uOffst = uvRect.left;
				const float vOffst = uvRect.top;
				const float left = rect.left;
				const float ws = (uvRect.right - uvRect.left) / w;
				const float top = rect.top;
				const float hs = (uvRect.bottom - uvRect.top) / h;

				Vertex2D* pDst = pVertex;

				for (size_t i = 0; i < vertexSize; ++i)
				{
					const float u = uOffst + (pDst->pos.x - left) * ws;
					const float v = vOffst + (pDst->pos.y - top) * hs;
					(pDst++)->tex.set(u, v);
				}
			}

			for (Vertex2D::IndexType i = 0; i < (vertexSize - 2); ++i)
			{
				*pIndex++ = indexOffset;
				*pIndex++ = (indexOffset + i + 1);
				*pIndex++ = (indexOffset + ((i + 2 < vertexSize) ? (i + 2) : 0));
			}

			return indexSize;
		}

		Vertex2D::IndexType BuildTexturedVertices(const BufferCreatorFunc& bufferCreator, const Vertex2D* vertices, const size_t vertexCount, const TriangleIndex* indices, const size_t num_triangles)
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

			std::memcpy(pVertex, vertices, (vertexSize * sizeof(Vertex2D)));

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

		Vertex2D::IndexType BuildRectShadow(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, float blur, const Float4& color, const bool fill)
		{
			constexpr Vertex2D::IndexType vertexCount = 16, indexCount = 54;
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexCount, indexCount);

			if (not pVertex)
			{
				return 0;
			}

			// 頂点情報の書き込み
			{
				// ぼかしサイズの半分
				const float halfBlur = (blur * 0.5f);
				const float xs[4] =
				{
					static_cast<float>(rect.left - halfBlur),
					static_cast<float>(rect.left + halfBlur),
					static_cast<float>(rect.right - halfBlur),
					static_cast<float>(rect.right + halfBlur)
				};
				const float ys[4] =
				{
					static_cast<float>(rect.top - halfBlur),
					static_cast<float>(rect.top + halfBlur),
					static_cast<float>(rect.bottom - halfBlur),
					static_cast<float>(rect.bottom + halfBlur)
				};
				const float uvs[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

				for (int32 i = 0; i < 16; ++i)
				{
					pVertex->pos.set(xs[i % 4], ys[i / 4]);
					pVertex->tex.set(uvs[i % 4], uvs[i / 4]);
					pVertex->color = color;
					++pVertex;
				}
			}

			// インデックス情報の書き込み
			{
				Vertex2D::IndexType* pBase = pIndex;

				for (Vertex2D::IndexType ty = 0; ty < 3; ++ty)
				{
					for (Vertex2D::IndexType tx = 0; tx < 3; ++tx)
					{
						const Vertex2D::IndexType base = (((ty * 4) + tx) + indexOffset);

						*pIndex++ = base;
						*pIndex++ = (base + 1);
						*pIndex++ = (base + 4);

						*pIndex++ = (base + 4);
						*pIndex++ = (base + 1);
						*pIndex++ = (base + 5);
					}
				}

				if (not fill)
				{
					// 縮退三角形
					pBase[29] = pBase[28] = pBase[27] = pBase[26] = pBase[25] = pBase[24];
				}
			}

			return indexCount;
		}

		Vertex2D::IndexType BuildCircleShadow(const BufferCreatorFunc& bufferCreator, const Circle& circle, const float blur, const Float4& color, const float scale)
		{
			// ベースとなる円の半径
			const float absR = Abs(static_cast<float>(circle.r));

			// ぼかしサイズの半分
			const float halfBlur = (blur * 0.5f);

			// 影の開始半径
			const float innerShadowR = static_cast<float>(absR - halfBlur);
			
			// 影の終了半径
			const float outerShadowR = static_cast<float>(absR + halfBlur);
			
			// 円の品質
			const Vertex2D::IndexType quality = detail::CalculateCircleQuality(outerShadowR * scale);

			// ぼかし外円の頂点数
			const Vertex2D::IndexType outerVertexCount = quality;

			// ぼかし内円の頂点数
			const Vertex2D::IndexType innerVertexCount = quality;

			// 頂点数（ぼかし外円 + ぼかし内円 + 中心）
			const Vertex2D::IndexType vertexCount = (outerVertexCount + innerVertexCount + 1);

			// ぼかし部分のトライアングル数
			const Vertex2D::IndexType outerTriangleCount = (quality * 2);

			// 非ぼかし部分のトライアングル数
			const Vertex2D::IndexType innerTriangleCount = quality;

			// 総トライアングル数
			const Vertex2D::IndexType triangleCount = (outerTriangleCount + innerTriangleCount);

			// インデックス数
			const Vertex2D::IndexType indexCount = (triangleCount * 3);

			// バッファを確保する
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexCount, indexCount);

			if (not pVertex)
			{
				return 0;
			}

			// 頂点情報の書き込み（外円→内円→中心）
			{
				const float centerX = static_cast<float>(circle.x);
				const float centerY = static_cast<float>(circle.y);
				const float radDelta = (Math::TwoPiF / quality);
				Vertex2D* pOuterVertex = &pVertex[0];
				Vertex2D* pInnerVertex = &pVertex[outerVertexCount];

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const float rad = (radDelta * i);
					const auto [s, c] = FastMath::SinCos(rad);

					pOuterVertex->pos.set((centerX + outerShadowR * c), (centerY - outerShadowR * s));
					pOuterVertex->tex.set(0.0f, 0.5f);
					pOuterVertex->color = color;

					pInnerVertex->pos.set((centerX + innerShadowR * c), (centerY - innerShadowR * s));
					pInnerVertex->tex.set(0.5f, 0.5f);
					pInnerVertex->color = color;

					++pOuterVertex;
					++pInnerVertex;
				}

				Vertex2D* pCenterVertex = &pVertex[vertexCount - 1];
				pCenterVertex->pos.set(centerX, centerY);
				pCenterVertex->tex.set(0.5f, 0.5f);
				pCenterVertex->color = color;
			}

			// インデックス情報の書き込み
			{
				const Vertex2D::IndexType centerIndex = ((vertexCount - 1) + indexOffset);

				for (Vertex2D::IndexType i = 0; i < quality; ++i)
				{
					const Vertex2D::IndexType t0 = (i + indexOffset);
					const Vertex2D::IndexType t1 = (((i + 1) % outerVertexCount) + indexOffset);
					const Vertex2D::IndexType t2 = (t0 + outerVertexCount);
					const Vertex2D::IndexType t3 = (t1 + outerVertexCount);

					*pIndex++ = t0;
					*pIndex++ = t1;
					*pIndex++ = t2;

					*pIndex++ = t2;
					*pIndex++ = t1;
					*pIndex++ = t3;

					*pIndex++ = t2;
					*pIndex++ = t3;
					*pIndex++ = centerIndex;
				}
			}

			return indexCount;
		}

		Vertex2D::IndexType BuildRoundRectShadow(const BufferCreatorFunc& bufferCreator, const RoundRect& roundRect, const float blur, const Float4& color, const float scale, const bool fill)
		{
			const float baseRadius = static_cast<float>(roundRect.r);
			const float nearRadius = Max(baseRadius - (blur * 0.5f), 0.0f);
			const float farRadius = (baseRadius + (blur * 0.5f));
			const FloatRect innerRect{ (roundRect.x + baseRadius), (roundRect.y + baseRadius), (roundRect.x + roundRect.w - baseRadius), (roundRect.y + roundRect.h - baseRadius) };
			const Vertex2D::IndexType quality = static_cast<uint16>(detail::CaluculateFanQuality(farRadius * scale));

			const Vertex2D::IndexType fanVertexCount = quality;
			const Vertex2D::IndexType roundVertexCount = (fanVertexCount + fanVertexCount + 1);
			
			// 頂点数
			const Vertex2D::IndexType vertexCount = (roundVertexCount * 4);

			const Vertex2D::IndexType outerFanTriangleCount = ((quality - 1) * 2);
			const Vertex2D::IndexType innerFanTriangleCount = (quality - 1);
			const Vertex2D::IndexType connectionTriangleCount = 18;
			
			// 総トライアングル数
			const Vertex2D::IndexType triangleCount = ((outerFanTriangleCount + innerFanTriangleCount) * 4 + connectionTriangleCount);
			
			// インデックス数
			const Vertex2D::IndexType indexCount = (triangleCount * 3);

			// バッファを確保する
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexCount, indexCount);

			if (not pVertex)
			{
				return 0;
			}

			// 頂点情報の書き込み（左上（外円→内円→中心）→右上→右下→左下）
			{
				const float radDelta = (Math::HalfPiF / (quality - 1));

				// 左上
				{
					const float centerX = innerRect.left;
					const float centerY = innerRect.top;
					Vertex2D* pOuterVertex = &pVertex[0];
					Vertex2D* pInnerVertex = (pOuterVertex + fanVertexCount);
					Vertex2D* pCenterVertex = (pInnerVertex + fanVertexCount);

					for (Vertex2D::IndexType i = 0; i < quality; ++i)
					{
						const float rad = (radDelta * i);
						const auto [s, c] = FastMath::SinCos(rad - 180_deg);

						pOuterVertex->pos.set((centerX + farRadius * c), (centerY + farRadius * s));
						pOuterVertex->tex.set(0.0f, 0.5f);
						pOuterVertex->color = color;

						pInnerVertex->pos.set((centerX + nearRadius * c), (centerY + nearRadius * s));
						pInnerVertex->tex.set(0.5f, 0.5f);
						pInnerVertex->color = color;

						++pOuterVertex;
						++pInnerVertex;
					}

					pCenterVertex->pos.set(centerX, centerY);
					pCenterVertex->tex.set(0.5f, 0.5f);
					pCenterVertex->color = color;
				}

				// 右上
				{
					const float centerX = innerRect.right;
					const float centerY = innerRect.top;
					Vertex2D* pOuterVertex = &pVertex[roundVertexCount];
					Vertex2D* pInnerVertex = (pOuterVertex + fanVertexCount);
					Vertex2D* pCenterVertex = (pInnerVertex + fanVertexCount);

					for (Vertex2D::IndexType i = 0; i < quality; ++i)
					{
						const float rad = (radDelta * i);
						const auto [s, c] = FastMath::SinCos(rad - 90_deg);

						pOuterVertex->pos.set((centerX + farRadius * c), (centerY + farRadius * s));
						pOuterVertex->tex.set(0.0f, 0.5f);
						pOuterVertex->color = color;

						pInnerVertex->pos.set((centerX + nearRadius * c), (centerY + nearRadius * s));
						pInnerVertex->tex.set(0.5f, 0.5f);
						pInnerVertex->color = color;

						++pOuterVertex;
						++pInnerVertex;
					}

					pCenterVertex->pos.set(centerX, centerY);
					pCenterVertex->tex.set(0.5f, 0.5f);
					pCenterVertex->color = color;
				}

				// 右下
				{
					const float centerX = innerRect.right;
					const float centerY = innerRect.bottom;
					Vertex2D* pOuterVertex = &pVertex[roundVertexCount * 2];
					Vertex2D* pInnerVertex = (pOuterVertex + fanVertexCount);
					Vertex2D* pCenterVertex = (pInnerVertex + fanVertexCount);

					for (Vertex2D::IndexType i = 0; i < quality; ++i)
					{
						const float rad = (radDelta * i);
						const auto [s, c] = FastMath::SinCos(rad);

						pOuterVertex->pos.set((centerX + farRadius * c), (centerY + farRadius * s));
						pOuterVertex->tex.set(0.0f, 0.5f);
						pOuterVertex->color = color;

						pInnerVertex->pos.set((centerX + nearRadius * c), (centerY + nearRadius * s));
						pInnerVertex->tex.set(0.5f, 0.5f);
						pInnerVertex->color = color;

						++pOuterVertex;
						++pInnerVertex;
					}

					pCenterVertex->pos.set(centerX, centerY);
					pCenterVertex->tex.set(0.5f, 0.5f);
					pCenterVertex->color = color;
				}

				// 左下
				{
					const float centerX = innerRect.left;
					const float centerY = innerRect.bottom;
					Vertex2D* pOuterVertex = &pVertex[roundVertexCount * 3];
					Vertex2D* pInnerVertex = (pOuterVertex + fanVertexCount);
					Vertex2D* pCenterVertex = (pInnerVertex + fanVertexCount);

					for (Vertex2D::IndexType i = 0; i < quality; ++i)
					{
						const float rad = (radDelta * i);
						const auto [s, c] = FastMath::SinCos(rad + 90_deg);

						pOuterVertex->pos.set((centerX + farRadius * c), (centerY + farRadius * s));
						pOuterVertex->tex.set(0.0f, 0.5f);
						pOuterVertex->color = color;

						pInnerVertex->pos.set((centerX + nearRadius * c), (centerY + nearRadius * s));
						pInnerVertex->tex.set(0.5f, 0.5f);
						pInnerVertex->color = color;

						++pOuterVertex;
						++pInnerVertex;
					}

					pCenterVertex->pos.set(centerX, centerY);
					pCenterVertex->tex.set(0.5f, 0.5f);
					pCenterVertex->color = color;
				}
			}

			// インデックス情報の書き込み（左上→右上→右下→左下→中心）
			{
				for (Vertex2D::IndexType i = 0; i < indexCount; ++i)
				{
					pIndex[i] = 0;
				}

				// 左上
				{
					const Vertex2D::IndexType tCenter = ((roundVertexCount - 1) + indexOffset);

					for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
					{
						const Vertex2D::IndexType t0 = (i + indexOffset);
						const Vertex2D::IndexType t1 = (t0 + 1);
						const Vertex2D::IndexType t2 = (t0 + fanVertexCount);
						const Vertex2D::IndexType t3 = (t2 + 1);

						*pIndex++ = t0;
						*pIndex++ = t1;
						*pIndex++ = t2;

						*pIndex++ = t2;
						*pIndex++ = t1;
						*pIndex++ = t3;

						*pIndex++ = t2;
						*pIndex++ = t3;
						*pIndex++ = tCenter;
					}
				}

				// 左上→右上接続
				{
					const Vertex2D::IndexType t0 = (indexOffset + (fanVertexCount - 1));
					const Vertex2D::IndexType t1 = (t0 + fanVertexCount);
					const Vertex2D::IndexType t2 = (t1 + 1);

					const Vertex2D::IndexType t3 = (indexOffset + roundVertexCount);
					const Vertex2D::IndexType t4 = (t3 + fanVertexCount);
					const Vertex2D::IndexType t5 = (t4 + fanVertexCount);

					*pIndex++ = t0;
					*pIndex++ = t3;
					*pIndex++ = t1;

					*pIndex++ = t1;
					*pIndex++ = t3;
					*pIndex++ = t4;

					*pIndex++ = t1;
					*pIndex++ = t4;
					*pIndex++ = t2;

					*pIndex++ = t2;
					*pIndex++ = t4;
					*pIndex++ = t5;
				}

				// 右上
				{
					const Vertex2D::IndexType tCenter = ((2 * roundVertexCount - 1) + indexOffset);

					for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
					{
						const Vertex2D::IndexType t0 = (i + roundVertexCount + indexOffset);
						const Vertex2D::IndexType t1 = (t0 + 1);
						const Vertex2D::IndexType t2 = (t0 + fanVertexCount);
						const Vertex2D::IndexType t3 = (t2 + 1);

						*pIndex++ = t0;
						*pIndex++ = t1;
						*pIndex++ = t2;

						*pIndex++ = t2;
						*pIndex++ = t1;
						*pIndex++ = t3;

						*pIndex++ = t2;
						*pIndex++ = t3;
						*pIndex++ = tCenter;
					}
				}

				// 右上→右下接続
				{
					const Vertex2D::IndexType t0 = (indexOffset + roundVertexCount + (fanVertexCount - 1));
					const Vertex2D::IndexType t1 = (t0 + fanVertexCount);
					const Vertex2D::IndexType t2 = (t1 + 1);

					const Vertex2D::IndexType t3 = (indexOffset + roundVertexCount * 2);
					const Vertex2D::IndexType t4 = (t3 + fanVertexCount);
					const Vertex2D::IndexType t5 = (t4 + fanVertexCount);

					*pIndex++ = t0;
					*pIndex++ = t3;
					*pIndex++ = t1;

					*pIndex++ = t1;
					*pIndex++ = t3;
					*pIndex++ = t4;

					*pIndex++ = t1;
					*pIndex++ = t4;
					*pIndex++ = t2;

					*pIndex++ = t2;
					*pIndex++ = t4;
					*pIndex++ = t5;
				}

				// 右下
				{
					const Vertex2D::IndexType tCenter = ((3 * roundVertexCount - 1) + indexOffset);

					for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
					{
						const Vertex2D::IndexType t0 = (i + roundVertexCount * 2 + indexOffset);
						const Vertex2D::IndexType t1 = (t0 + 1);
						const Vertex2D::IndexType t2 = (t0 + fanVertexCount);
						const Vertex2D::IndexType t3 = (t2 + 1);

						*pIndex++ = t0;
						*pIndex++ = t1;
						*pIndex++ = t2;

						*pIndex++ = t2;
						*pIndex++ = t1;
						*pIndex++ = t3;

						*pIndex++ = t2;
						*pIndex++ = t3;
						*pIndex++ = tCenter;
					}
				}

				// 右下→左下接続
				{
					const Vertex2D::IndexType t0 = (indexOffset + roundVertexCount * 2 + (fanVertexCount - 1));
					const Vertex2D::IndexType t1 = (t0 + fanVertexCount);
					const Vertex2D::IndexType t2 = (t1 + 1);

					const Vertex2D::IndexType t3 = (indexOffset + roundVertexCount * 3);
					const Vertex2D::IndexType t4 = (t3 + fanVertexCount);
					const Vertex2D::IndexType t5 = (t4 + fanVertexCount);

					*pIndex++ = t0;
					*pIndex++ = t3;
					*pIndex++ = t1;

					*pIndex++ = t1;
					*pIndex++ = t3;
					*pIndex++ = t4;

					*pIndex++ = t1;
					*pIndex++ = t4;
					*pIndex++ = t2;

					*pIndex++ = t2;
					*pIndex++ = t4;
					*pIndex++ = t5;
				}

				// 左下
				{
					const Vertex2D::IndexType tCenter = ((4 * roundVertexCount - 1) + indexOffset);

					for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i)
					{
						const Vertex2D::IndexType t0 = (i + roundVertexCount * 3 + indexOffset);
						const Vertex2D::IndexType t1 = (t0 + 1);
						const Vertex2D::IndexType t2 = (t0 + fanVertexCount);
						const Vertex2D::IndexType t3 = (t2 + 1);

						*pIndex++ = t0;
						*pIndex++ = t1;
						*pIndex++ = t2;

						*pIndex++ = t2;
						*pIndex++ = t1;
						*pIndex++ = t3;

						*pIndex++ = t2;
						*pIndex++ = t3;
						*pIndex++ = tCenter;
					}
				}

				// 左下→左上接続
				{
					const Vertex2D::IndexType t0 = (indexOffset + roundVertexCount * 3 + (fanVertexCount - 1));
					const Vertex2D::IndexType t1 = (t0 + fanVertexCount);
					const Vertex2D::IndexType t2 = (t1 + 1);

					const Vertex2D::IndexType t3 = (indexOffset);
					const Vertex2D::IndexType t4 = (t3 + fanVertexCount);
					const Vertex2D::IndexType t5 = (t4 + fanVertexCount);

					*pIndex++ = t0;
					*pIndex++ = t3;
					*pIndex++ = t1;

					*pIndex++ = t1;
					*pIndex++ = t3;
					*pIndex++ = t4;

					*pIndex++ = t1;
					*pIndex++ = t4;
					*pIndex++ = t2;

					*pIndex++ = t2;
					*pIndex++ = t4;
					*pIndex++ = t5;
				}

				// 中心
				if (fill)
				{
					const Vertex2D::IndexType t0 = (indexOffset + roundVertexCount - 1);
					const Vertex2D::IndexType t1 = (t0 + roundVertexCount);
					const Vertex2D::IndexType t2 = (t1 + roundVertexCount);
					const Vertex2D::IndexType t3 = (t2 + roundVertexCount);

					*pIndex++ = t0;
					*pIndex++ = t1;
					*pIndex++ = t3;

					*pIndex++ = t3;
					*pIndex++ = t1;
					*pIndex++ = t2;
				}
				else
				{
					const Vertex2D::IndexType t0 = (indexOffset + roundVertexCount - 1);

					// 縮退三角形
					*pIndex++ = t0;
					*pIndex++ = t0;
					*pIndex++ = t0;

					// 縮退三角形
					*pIndex++ = t0;
					*pIndex++ = t0;
					*pIndex++ = t0;
				}
			}

			return indexCount;
		}

		Vertex2D::IndexType BuildTexturedParticles(const BufferCreatorFunc& bufferCreator, const Array<Particle2D>& particles,
			const ParticleSystem2DParameters::SizeOverLifeTimeFunc& sizeOverLifeTimeFunc, const ParticleSystem2DParameters::ColorOverLifeTimeFunc& colorOverLifeTimeFunc)
		{
			const Vertex2D::IndexType vertexSize = static_cast<Vertex2D::IndexType>(particles.size() * 4);
			const Vertex2D::IndexType indexSize = static_cast<Vertex2D::IndexType>(particles.size() * 6);
			auto [pVertex, pIndex, indexOffset] = bufferCreator(vertexSize, indexSize);

			if (not pVertex)
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
				const auto [s, c] = FastMath::SinCos(particle.rotation);
				const float xc = x * c;
				const float xs = x * s;

				pVertex[0].set({ -xc + xs + cx, -xs - xc + cy }, 0.0f, 0.0f, color);
				pVertex[1].set({ xc + xs + cx, xs - xc + cy }, 1.0f, 0.0f, color);
				pVertex[2].set({ -xc - xs + cx, -xs + xc + cy }, 0.0f, 1.0f, color);
				pVertex[3].set({ xc - xs + cx, xs + xc + cy }, 1.0f, 1.0f, color);
				pVertex += 4;
			}

			{
				Vertex2D::IndexType indexBase = indexOffset;

				for (Vertex2D::IndexType n = 0; n < particles.size(); ++n)
				{
					for (Vertex2D::IndexType i = 0; i < 6; ++i)
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
