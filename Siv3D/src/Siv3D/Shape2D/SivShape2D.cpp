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

# include <Siv3D/Shape2D.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Shape2D::Shape2D()
	{

	}

	Shape2D::Shape2D(Array<Float2> vertices, Array<TriangleIndex> indices)
		: m_vertices(std::move(vertices))
		, m_indices(std::move(indices))
	{

	}

	Shape2D::~Shape2D()
	{

	}

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



	Shape2D Shape2D::Heart(const double r, const Vec2& center, const double angle)
	{
		//-----------------------------------------------
		//	Authors (OpenSiv3D challenge paricipants)
		//	- 野菜ジュース
		//	- てゃいの
		//-----------------------------------------------

		if (r <= 0.0)
		{
			return{};
		}

		const float rf = static_cast<float>(r);
		const float innerR = static_cast<float>(1.121320307254791259765625 * rf);

		const int32 quality = (8 + Min(static_cast<int32>(r / 16) * 2, 100));
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

	const Shape2D& Shape2D::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygon(m_vertices, m_indices, none, color.toFloat4());

		return *this;
	}




	Polygon Shape2D::asPolygon() const
	{
		return Polygon{ *this };
	}
}
