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

# include <Siv3D/Shape2D.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Buffer2D.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Shape2D::Shape2D(Array<Float2> vertices, Array<TriangleIndex> indices)
		: m_vertices{ std::move(vertices) }
		, m_indices{ std::move(indices) } {}

	Shape2D Shape2D::Cross(const double r, const double width, const Vec2& center, const double angle)
	{
		return Plus(r, width, center, (angle + Math::QuarterPi));
	}

	Shape2D Shape2D::Plus(const double r, const double width, const Vec2& center, const double angle)
	{
		if ((r <= 0.0)
			|| (width <= 0.0))
		{
			return{};
		}

		const float w = static_cast<float>(width) * 0.5f;
		const float af = static_cast<float>(angle);
		const Float2 n = Float2{ w, w }.rotated(af), a = Float2{ r, w }.rotated(af), b = Float2{ w, r }.rotated(af);

		Array<Float2> vertices(12, center);
		Float2* pPos = vertices.data();
		(pPos++)->moveBy(a.x, a.y);
		(pPos++)->moveBy(n.x, n.y);
		(pPos++)->moveBy(b.x, b.y);
		(pPos++)->moveBy(-a.y, a.x);
		(pPos++)->moveBy(-n.y, n.x);
		(pPos++)->moveBy(-b.y, b.x);
		(pPos++)->moveBy(-a.x, -a.y);
		(pPos++)->moveBy(-n.x, -n.y);
		(pPos++)->moveBy(-b.x, -b.y);
		(pPos++)->moveBy(a.y, -a.x);
		(pPos++)->moveBy(n.y, -n.x);
		(pPos++)->moveBy(b.y, -b.x);

		Array<TriangleIndex> indices = { {6, 11, 5}, {5, 11, 0}, {8, 9, 7}, {7, 9, 10}, {4, 1, 3}, {3, 1, 2} };

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Pentagon(const double r, const Vec2& center, const double angle)
	{
		return Ngon(5, r, center, angle);
	}

	Shape2D Shape2D::Hexagon(const double r, const Vec2& center, const double angle)
	{
		return Ngon(6, r, center, angle);
	}

	Shape2D Shape2D::Ngon(const uint32 n, const double r, const Vec2& center, const double angle)
	{
		if ((n < 3)
			|| (r <= 0.0))
		{
			return{};
		}

		Array<Float2> vertices(n, center);
		const Float2 offset(center);
		Float2* pPos = vertices.data();

		for (uint32 i = 0; i < n; ++i)
		{
			*pPos++ += Circular{ r, angle + i * (Math::TwoPi / n) }.toFloat2();
		}

		Array<TriangleIndex> indices(n - 2);
		{
			TriangleIndex* pDst = indices.data();
			const TriangleIndex* const pDstEnd = (pDst + indices.size());

			for (Vertex2D::IndexType i = 0; pDst != pDstEnd; ++i)
			{
				pDst->i0 = 0;
				pDst->i1 = (i + 1);
				pDst->i2 = (i + 2);
				++pDst;
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Star(const double r, const Vec2& center, const double angle)
	{
		constexpr double innerScale = 0.38196601125010515; // 2 / (3 + sqrt(5)) 

		return NStar(5, r, (r * innerScale), center, angle);
	}

	Shape2D Shape2D::NStar(const uint32 n, const double rOuter, const double rInner, const Vec2& center, const double angle)
	{
		if (n < 2)
		{
			return{};
		}

		Array<Float2> vertices((n * 2), center);
		Float2* pPos = vertices.data();

		for (uint32 i = 0; i < n * 2; ++i)
		{
			(*pPos++) += Circular(i % 2 ? rInner : rOuter, angle + i * (Math::Pi / n)).fastToFloat2();
		}

		Array<TriangleIndex> indices(2 * n - 2);
		{
			TriangleIndex* pDst = indices.data();

			for (Vertex2D::IndexType i = 0; i < n; ++i)
			{
				pDst->i0 = i * 2 + 1;
				pDst->i1 = (i * 2 + 2) % (n * 2);
				pDst->i2 = (i * 2 + 3) % (n * 2);
				++pDst;
			}

			for (Vertex2D::IndexType i = 0; i < n - 2; ++i)
			{
				pDst->i0 = 1;
				pDst->i1 = (i * 2 + 3);
				pDst->i2 = (i * 2 + 5);
				++pDst;
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Arrow(const Vec2& from, const Vec2& to, const double width, const Vec2& headSize)
	{
		const double length = to.distanceFrom(from);

		if ((length == 0.0)
			|| (width <= 0.0)
			|| (headSize.x <= 0.0)
			|| (headSize.y <= 0.0))
		{
			return{};
		}

		const double clampedRatio = (Min(headSize.y, length) / headSize.y);
		const Float2 direction = ((to - from) / length);
		const Float2 normalDirection{ direction.y, -direction.x };
		const Float2 leftOffset = (normalDirection * static_cast<float>(width) * 0.5f);
		const Float2 clampedHeadSize = (clampedRatio * headSize);
		const Float2 gutterOffset = (direction * clampedHeadSize.y);
		const Float2 edgeOffset = (normalDirection * clampedHeadSize.x * 0.5f);

		Array<Float2> vertices(7, to);
		{
			Float2* pPos = vertices.data();
			pPos[0] = (from + leftOffset);
			pPos[1] += (leftOffset - gutterOffset);
			pPos[2] += (leftOffset - gutterOffset + edgeOffset);
			pPos[4] += (-leftOffset - gutterOffset - edgeOffset);
			pPos[5] += (-leftOffset - gutterOffset);
			pPos[6] = (from - leftOffset);
		}

		Array<TriangleIndex> indices = { {1, 5, 0}, {0, 5, 6}, {3, 4, 2} };

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Arrow(const Line& line, const double width, const Vec2& headSize)
	{
		return Arrow(line.begin, line.end, width, headSize);
	}

	Shape2D Shape2D::DoubleHeadedArrow(const Vec2& from, const Vec2& to, double width, const Vec2& headSize)
	{
		const double length = to.distanceFrom(from);

		if ((length == 0.0)
			|| (width <= 0.0)
			|| (headSize.x <= 0.0)
			|| (headSize.y <= 0.0))
		{
			return{};
		}

		const double clampedRatio = (Min(headSize.y * 2, length) / (headSize.y * 2));
		const Float2 direction = ((to - from) / length);
		const Float2 normalDirection{ direction.y, -direction.x };
		const Float2 leftOffset = (normalDirection * static_cast<float>(width) * 0.5f);
		const Float2 clampedHeadSize = (clampedRatio * headSize);
		const Float2 gutterOffset = (direction * clampedHeadSize.y);
		const Float2 edgeOffset = (normalDirection * clampedHeadSize.x * 0.5f);

		Array<Float2> vertices(10);
		{
			Float2* pPos = vertices.data();
			pPos[0] = (from + leftOffset + gutterOffset);
			pPos[1] = (to + leftOffset - gutterOffset);
			pPos[2] = (to + leftOffset - gutterOffset + edgeOffset);
			pPos[3] = to;
			pPos[4] = (to - leftOffset - gutterOffset - edgeOffset);
			pPos[5] = (to - leftOffset - gutterOffset);
			pPos[6] = (from - leftOffset + gutterOffset);
			pPos[7] = (from - leftOffset + gutterOffset - edgeOffset);
			pPos[8] = from;
			pPos[9] = (from + leftOffset + gutterOffset + edgeOffset);
		}

		Array<TriangleIndex> indices = { {8, 9, 7}, {0, 1, 6}, {6, 1, 5}, {3, 4, 2} };

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::DoubleHeadedArrow(const Line& line, double width, const Vec2& headSize)
	{
		return DoubleHeadedArrow(line.begin, line.end, width, headSize);
	}

	Shape2D Shape2D::Rhombus(const double w, const double h, const Vec2& center, const double angle)
	{
		if ((w <= 0.0)
			|| (h <= 0.0))
		{
			return{};
		}

		const float halfW = (static_cast<float>(w) * 0.5f);
		const float halfH = (static_cast<float>(h) * 0.5f);
		const float angleF = static_cast<float>(angle);
		const float s = std::sin(angleF);
		const float c = std::cos(angleF);

		Array<Float2> vertices(4, center);
		Float2* pPos = vertices.data();
		(pPos++)->moveBy(halfH * s, -halfH * c);
		(pPos++)->moveBy(halfW * c, halfW * s);
		(pPos++)->moveBy(-halfH * s, halfH * c);
		(pPos++)->moveBy(-halfW * c, -halfW * s);

		Array<TriangleIndex> indices = { {0, 1, 3}, {2, 3, 1} };

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::RectBalloon(const RectF& rect, const Vec2& target, const double _pointingRootRatio)
	{
		const Float2 center = rect.center();
		const float h = static_cast<float>(rect.h);
		const float w = static_cast<float>(rect.w);
		const float prf = static_cast<float>(_pointingRootRatio);

		constexpr std::array<int32, 2> sign{ { 1, -1 } };
		const float firstAngle = std::atan2(h, w);
		const Float2 direction = target - center;
		const float flagAngle = std::fmod(std::atan2(direction.y, direction.x) + Math::TwoPiF, Math::TwoPiF);
		const float remainderAngle = std::fmod(flagAngle + Math::HalfPiF, Math::HalfPiF);
		const int32 dividedAngleIndex = static_cast<int32>(flagAngle / Math::HalfPiF);
		const int32 a = ((dividedAngleIndex % 2 == 0) ? (remainderAngle > firstAngle) : (remainderAngle > Math::HalfPiF - firstAngle)) + dividedAngleIndex * 2;
		const Float2 pointingRootCenter(sign[((a + 2) / 4) % 2] * w * 0.25f * (1.0f + ((a + 3) / 2) % 2), sign[((a) / 4) % 2] * h * 0.25f * (1.0f + ((a + 1) / 2) % 2));
		const Float2 offset = sign[(((a + 3) % 8) / 4) % 2] * ((((a + 1) / 2) % 2) ? Float2{ w * 0.25f * prf, 0.0f } : Float2{ 0.0f, h * 0.25f * prf });
		const Vertex2D::IndexType indexOffset = ((a + 1) / 2) % 4;

		Array<Float2> vertices(7, center);
		std::array<Vertex2D::IndexType, 4> rectIndices;
		{
			vertices[0 + indexOffset] += pointingRootCenter - offset;
			vertices[1 + indexOffset] = target;
			vertices[2 + indexOffset] += pointingRootCenter + offset;

			Vertex2D::IndexType i = 0;

			for (size_t rectIndex = 0; rectIndex < 4; ++rectIndex)
			{
				if (indexOffset == rectIndex)
				{
					i += 3;
				}

				rectIndices[rectIndex] = i;

				vertices[i++] += Float2{ sign[((rectIndex + 1) / 2) % 2] * w * 0.5f, sign[((rectIndex) / 2) % 2] * h * 0.5f };
			}
		}

		Array<TriangleIndex> indices =
		{
			{ indexOffset, Vertex2D::IndexType(indexOffset + 1), Vertex2D::IndexType(indexOffset + 2)},
			{ rectIndices[0], rectIndices[1], rectIndices[2] },
			{ rectIndices[0], rectIndices[2], rectIndices[3] }
		};

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Stairs(const Vec2& base, const double w, const double h, const uint32 steps, const bool upStairs)
	{
		if ((steps <= 0)
			|| (w <= 0.0)
			|| (h <= 0.0))
		{
			return{};
		}

		const float offsetX = static_cast<float>(w / steps);
		const float offsetY = static_cast<float>(h / steps);
		const Float2 base2 = (base + Float2{ upStairs ? -w : w, 0 });

		Array<Float2> vertices(2 + 2 * steps);
		{
			Float2* pPos = vertices.data();
			*pPos++ = base;
			*pPos++ = base2;

			for (Vertex2D::IndexType i = 0; i < steps; ++i)
			{
				const int32 offsetIndex = i + 1;
				*pPos++ = base2 + Float2{ upStairs ? offsetX * i : -offsetX * i, -offsetY * offsetIndex };
				*pPos++ = base2 + Float2{ upStairs ? offsetX * offsetIndex : -offsetX * offsetIndex, -offsetY * offsetIndex };
			}
		}

		Array<TriangleIndex> indices(2 * steps);
		{
			TriangleIndex* pDst = indices.data();

			if (upStairs)
			{
				for (Vertex2D::IndexType i = 0; i < steps; ++i)
				{
					pDst->i0 = 0;
					pDst->i1 = 2 * i + 1;
					pDst->i2 = 2 * i + 2;
					++pDst;

					pDst->i0 = 0;
					pDst->i1 = 2 * i + 2;
					pDst->i2 = 2 * i + 3;
					++pDst;
				}
			}
			else
			{
				for (Vertex2D::IndexType i = 0; i < steps; ++i)
				{
					pDst->i0 = 0;
					pDst->i1 = 2 * i + 2;
					pDst->i2 = 2 * i + 1;
					++pDst;

					pDst->i0 = 0;
					pDst->i1 = 2 * i + 3;
					pDst->i2 = 2 * i + 2;
					++pDst;
				}
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Heart(const double r, const Vec2& center, const double angle)
	{
		//-----------------------------------------------
		//	Authors (OpenSiv3D challenge #03 participants)
		//	- 野菜ジュース
		//	- sthairno
		//-----------------------------------------------

		if (r <= 0.0)
		{
			return{};
		}

		const float rf = static_cast<float>(r);
		const float innerR = (1.121320307254791259765625f * rf);

		const int32 quality = (8 + Min(static_cast<int32>(r / 14) * 2, 100));
		const size_t vsize = (12 + quality);

		Array<Float2> vertices(vsize);
		{
			Float2* pDst = vertices.data();

			// 前半
			// 最下点の点は固定
			*pDst++ = Float2{ 0, 0 };
			*pDst++ = Float2{ (-0.915f / Math::Sqrt2_v<float> * innerR), (-0.9f / Math::Sqrt2_v<float> * innerR) };
			{
				const int32 offs = ((quality / 20 - 2) * 2);	// 図形内部に頂点ができないようにする処理
				const Float2 offsetCenter{ (-0.5f / Math::Sqrt2_v<float> * innerR), (-1.5f / Math::Sqrt2_v<float> * innerR) };
				const float halfInnerR = (0.5f * innerR);
				constexpr float deg235 = static_cast<float>(235_deg);
				const float d = (Math::TwoPiF / (vsize + offs));

				for (size_t i = 0; i < (vsize / 2 - 2); ++i)
				{
					*pDst++ = CircularF{ halfInnerR, deg235 + i * d }.fastToFloat2() + offsetCenter;
				}
			}
			// 後半
			// 中央上部の点は固定
			*pDst++ = Float2{ 0, (-2 / Math::Sqrt2_v<float> * innerR) };

			// y 軸反転でコピー
			{
				const Float2* pSrc = (pDst - 2);
				const Float2* const pSrcEnd = vertices.data();

				while (pSrc != pSrcEnd)
				{
					pDst->set(-pSrc->x, pSrc->y);
					++pDst;
					--pSrc;
				}
			}

			{
				const auto [s, c] = FastMath::SinCos(angle);
				const Float2 offset{ center.x, center.y };
				
				Float2* pVertex = vertices.data();
				const Float2* const pVertexEnd = (pVertex + vertices.size());

				while(pVertex != pVertexEnd)
				{
					pVertex->y += rf;
					pVertex->set((pVertex->x * c - pVertex->y * s) + offset.x, (pVertex->x * s + pVertex->y * c) + offset.y);
					++pVertex;
				}
			}
		}

		Array<TriangleIndex> indices(vsize - 2);
		{
			TriangleIndex* pDst = indices.data();
			const TriangleIndex* const pDstEnd = (pDst + indices.size());

			for (Vertex2D::IndexType i = 0; pDst != pDstEnd; ++i)
			{
				pDst->i0 = 0;
				pDst->i1 = (i + 1);
				pDst->i2 = (i + 2);
				++pDst;
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Squircle(const double r, const Vec2& center, const uint32 quality)
	{
		//-----------------------------------------------
		//	Authors (OpenSiv3D challenge #05 participants)
		//	- Ebishu
		//	- Ryoga.exe
		//-----------------------------------------------

		if (r <= 0.0)
		{
			return{};
		}

		// 8 の倍数
		const uint32 n = (quality + 7) / 8 * 8;

		Array<Float2> vertices(n);
		Float2* pPos = vertices.data();

		for (uint32 i = 0; i <= n / 8; ++i)
		{
			// 45°回転してから, x 座標を n/8 分割
			// 計算: https://www.desmos.com/calculator/0wrmga2lfk?lang=ja

			const float x = (n / 8 - i) * 4.0f / n;
			const float y = std::sqrt(-3 * x * x + std::sqrt(8 * x * x * x * x + 0.5f));

			pPos->x = -x + y;
			pPos->y = -x - y;
			++pPos;
		}

		for (uint32 i = n / 8 - 1; i >= 1; --i)
		{
			pPos->x = -vertices[i].y;
			pPos->y = -vertices[i].x;
			++pPos;
		}

		for (uint32 i = 0; i < n / 4; ++i)
		{
			pPos->x = -vertices[i].y;
			pPos->y = vertices[i].x;
			++pPos;
		}

		for (uint32 i = 0; i < n / 2; ++i)
		{
			pPos->x = -vertices[i].x;
			pPos->y = -vertices[i].y;
			++pPos;
		}

		const Float2 centerF{ center };
		const float rf = static_cast<float>(r);

		for (Float2& point : vertices)
		{
			point *= rf;
			point.moveBy(centerF);
		}

		Array<TriangleIndex> indices(n - 2);
		TriangleIndex* pIndex = indices.data();

		for (Vertex2D::IndexType i = 0; i < n - 2; ++i)
		{
			pIndex->i0 = 0;
			pIndex->i1 = (i + 1);
			pIndex->i2 = (i + 2);
			++pIndex;
		}

		return{ std::move(vertices), std::move(indices) };
	}

	Shape2D Shape2D::Astroid(const Vec2& center, const double a, const double b, const double angle, const double qualityScale)
	{
		const double majorAxis = Max(Math::Abs(a), Math::Abs(b));
		const Vertex2D::IndexType quality = (static_cast<Vertex2D::IndexType>(Clamp((majorAxis * qualityScale * 0.044 + 2.5), 2.0, 127.0)) * 2);
		assert(IsEven(quality));

		Array<Float2> vertices(quality * 4);
		{
			const float step = (90_degF / quality);
			float rad = 0.0_degF;

			Float2* pDst0 = vertices.data();
			Float2* pDst1 = (pDst0 + quality);
			Float2* pDst2 = (pDst0 + quality * 2);
			Float2* pDst3 = (pDst0 + quality * 3);

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				const auto [s, c] = FastMath::SinCos(rad);
				const float s3 = (s * s * s);
				const float c3 = (c * c * c);

				pDst0->set(c3, s3);
				pDst1->set(-s3, c3);
				pDst2->set(-c3, -s3);
				pDst3->set(s3, -c3);

				++pDst0;
				++pDst1;
				++pDst2;
				++pDst3;

				rad += step;
			}
		}

		{
			const auto [s, c] = FastMath::SinCos(static_cast<float>(angle));
			const float af = static_cast<float>(a);
			const float bf = static_cast<float>(b);
			const float cx = static_cast<float>(center.x);
			const float cy = static_cast<float>(center.y);

			Float2* pDst = vertices.data();
			const Float2* pDstEnd = (pDst + vertices.size());

			while (pDst != pDstEnd)
			{
				pDst->x *= af;
				pDst->y *= bf;

				const float x = pDst->x;
				const float y = pDst->y;

				pDst->x = (x * c - y * s + cx);
				pDst->y = (x * s + y * c + cy);

				++pDst;
			}
		}

		const size_t num_triangles = (4 * ((quality / 2) * 2 - 1) + 2);

		Array<TriangleIndex> indices(num_triangles);
		{
			const Vertex2D::IndexType midIndex = (quality / 2);
			const Vertex2D::IndexType fullIndex = (quality * 4);

			TriangleIndex* pDst = indices.data();

			for (Vertex2D::IndexType k = 0; k < 4; ++k)
			{
				const Vertex2D::IndexType baseIndex = (quality * k);

				for (Vertex2D::IndexType i = 0; i < midIndex; ++i)
				{
					if (i == 0)
					{
						pDst->i0 = (baseIndex + i);
						pDst->i1 = (baseIndex + i + 1);
						pDst->i2 = ((fullIndex + baseIndex - 1) % fullIndex);
						++pDst;
					}
					else
					{
						const Vertex2D::IndexType t0 = (baseIndex + i);
						const Vertex2D::IndexType t1 = (baseIndex + i + 1);
						const Vertex2D::IndexType t2 = ((fullIndex + baseIndex - i) % fullIndex);
						const Vertex2D::IndexType t3 = (t2 - 1);

						pDst->i0 = t0;
						pDst->i1 = t1;
						pDst->i2 = t2;
						++pDst;

						pDst->i0 = t2;
						pDst->i1 = t1;
						pDst->i2 = t3;
						++pDst;
					}
				}
			}

			const Vertex2D::IndexType t0 = (midIndex);
			const Vertex2D::IndexType t1 = (midIndex + quality);
			const Vertex2D::IndexType t2 = (midIndex + quality * 3);
			const Vertex2D::IndexType t3 = (midIndex + quality * 2);

			pDst->i0 = t0;
			pDst->i1 = t1;
			pDst->i2 = t2;
			++pDst;

			pDst->i0 = t2;
			pDst->i1 = t1;
			pDst->i2 = t3;
		}

		return{ std::move(vertices), std::move(indices) };
	}

	const Shape2D& Shape2D::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygon(m_vertices, m_indices, none, color.toFloat4());

		return *this;
	}

	const Shape2D& Shape2D::drawFrame(const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygonFrame(m_vertices.data(), m_vertices.size(),
			static_cast<float>(thickness), color.toFloat4());

		return *this;
	}

	const Shape2D& Shape2D::drawWireframe(const double thickness, const ColorF& color) const
	{
		const Float2* pVertex = m_vertices.data();
		const TriangleIndex* pIndex = m_indices.data();
		const TriangleIndex* const pIndexEnd = (pIndex + m_indices.size());
		const Float4 colorF = color.toFloat4();

		while (pIndex != pIndexEnd)
		{
			const Float2 points[3] = { pVertex[pIndex->i0], pVertex[pIndex->i1], pVertex[pIndex->i2] };

			SIV3D_ENGINE(Renderer2D)->addPolygonFrame(points, 3, static_cast<float>(thickness), colorF);

			++pIndex;
		}

		return *this;
	}

	Polygon Shape2D::asPolygon() const
	{
		return Polygon{ *this };
	}

	Buffer2D Shape2D::toBuffer2D(const Vec2& uvOrigin, const Vec2& uvScale) const
	{
		return Buffer2D{ *this, uvOrigin, uvScale };
	}

	Buffer2D Shape2D::toBuffer2D(const Arg::center_<Vec2> uvCenter, const Vec2& uvScale) const
	{
		return Buffer2D{ *this, uvCenter, uvScale };
	}

	Buffer2D Shape2D::toBuffer2D(const Arg::center_<Vec2> uvCenter, const Vec2& uvScale, const double uvRotation) const
	{
		return Buffer2D{ *this, uvCenter, uvScale, uvRotation };
	}

	Buffer2D Shape2D::toBuffer2D(const Mat3x2& uvMat) const
	{
		return Buffer2D{ *this, uvMat };
	}
}
