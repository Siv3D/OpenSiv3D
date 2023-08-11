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

# include "CTrailRenderer.hpp"
# include <Siv3D/Trail.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Float4 GetPoints(const Float2& current, const Float2& n, const float halfThickness) noexcept
		{
			const Float2 v{ (-n.y * halfThickness) , (n.x * halfThickness) };
			return{ (current - v), (current + v) };
		}

		[[nodiscard]]
		static Float4 GetPoints(const Float2& current, const Float2& n0, const Float2& n1, const float halfThickness) noexcept
		{
			const Float2 n = (n0 + n1).normalize();
			const Float2 v{ (-n.y * halfThickness) , (n.x * halfThickness) };
			return{ (current - v), (current + v) };
		}
	}

	void CTrailRenderer::draw(const Trail& trail)
	{
		drawImpl(trail, nullptr);
	}

	void CTrailRenderer::draw(const Trail& trail, const Texture& texture)
	{
		drawImpl(trail, &texture);
	}

	void CTrailRenderer::drawImpl(const Trail& trail, const Texture* pTexture)
	{
		if (trail.num_points() < 2)
		{
			return;
		}

		setBuffer(trail);

		const size_t num_triangles = ((trail.num_points() - 1) * 2);

		if (pTexture)
		{
			m_buffer.drawSubset(0, num_triangles, *pTexture);
		}
		else
		{
			m_buffer.drawSubset(0, num_triangles);
		}
	}

	void CTrailRenderer::setBuffer(const Trail& trail)
	{
		const size_t num_points = trail.num_points();
		const size_t num_vertices = (num_points * 2);

		if (m_buffer.vertices.size() < num_vertices)
		{
			resizeBuffer(num_vertices);
		}

		const float lifeTimeInv = (1.0f / trail.getLifeTime());
		const auto& scaleFunction = trail.getScaleFunction();
		const auto& alphaFunction = trail.getAlphaFunction();
		const Trail::Point* pCurrent = nullptr;
		const Trail::Point* pNext = nullptr;
		Float2 n0, n1;
		Vertex2D* pDst = m_buffer.vertices.data();

		// 始点
		{
			pCurrent = &trail.front();
			pNext = &trail.point(1);
			n1 = (pNext->pos - pCurrent->pos).normalize();

			const float t = (pCurrent->lifeTime * lifeTimeInv);
			const float halfThickness = (static_cast<float>(scaleFunction(t)) * pCurrent->halfThickness);
			const Float4 point = detail::GetPoints(pCurrent->pos, n1, halfThickness);
			Float4 color = pCurrent->color;
			color.w *= static_cast<float>(alphaFunction(t));

			pDst->pos = point.xy();
			pDst->color = color;
			pDst->tex.x = 0.0f;
			++pDst;

			pDst->pos = point.zw();
			pDst->color = color;
			pDst->tex.x = 0.0f;
			++pDst;
		}

		// 間の点
		for (size_t i = 1; i < (num_points - 1); ++i)
		{
			pCurrent = pNext;
			pNext = &trail.point(i + 1);
			n0 = n1;
			n1 = (pNext->pos - pCurrent->pos).normalize();

			const float t = (pCurrent->lifeTime * lifeTimeInv);
			const float halfThickness = (static_cast<float>(scaleFunction(t)) * pCurrent->halfThickness);
			const Float4 point = detail::GetPoints(pCurrent->pos, n0, n1, halfThickness);
			Float4 color = pCurrent->color;
			color.w *= static_cast<float>(alphaFunction(t));
			const float u = ((i == 1) ? 0.25f : (i == (num_points - 2)) ? 0.75f : 0.5f);

			pDst->pos = point.xy();
			pDst->color = color;
			pDst->tex.x = u;
			++pDst;

			pDst->pos = point.zw();
			pDst->color = color;
			pDst->tex.x = u;
			++pDst;
		}

		// 終点
		{
			pCurrent = pNext;

			const float t = (pCurrent->lifeTime * lifeTimeInv);
			const float halfThickness = (static_cast<float>(scaleFunction(t)) * pCurrent->halfThickness);
			const Float4 point = detail::GetPoints(pCurrent->pos, n1, halfThickness);
			Float4 color = pCurrent->color;
			color.w *= static_cast<float>(alphaFunction(t));

			pDst->pos = point.xy();
			pDst->color = color;
			pDst->tex.x = 1.0f;
			++pDst;

			pDst->pos = point.zw();
			pDst->color = color;
			pDst->tex.x = 1.0f;
		}
	}

	void CTrailRenderer::resizeBuffer(const size_t num_vertices)
	{
		size_t new_size = Max((m_buffer.vertices.size() * 2), MinVertexCount);

		while (new_size < num_vertices)
		{
			new_size *= 2;
		}

		m_buffer.vertices.resize(new_size);
		m_buffer.indices.resize(new_size - 2);

		// 頂点バッファの初期値をセット
		{
			Vertex2D* pDst = m_buffer.vertices.data();

			for (size_t i = 0; i < (new_size / 2); ++i)
			{
				pDst->tex = Float2{ 0.0f, 0.0f };
				++pDst;

				pDst->tex = Float2{ 0.0f, 1.0f };
				++pDst;
			}
		}

		// インデックスバッファの初期値をセット
		{
			static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 2, 1, 1, 2, 3 };

			const size_t num_rects = (m_buffer.indices.size() / 2);

			TriangleIndex* pDst = m_buffer.indices.data();

			for (uint16 i = 0; i < num_rects; ++i)
			{
				const uint16 base = (i * 2);
				pDst->i0 = (base + RectIndexTable[0]);
				pDst->i1 = (base + RectIndexTable[1]);
				pDst->i2 = (base + RectIndexTable[2]);
				++pDst;

				pDst->i0 = (base + RectIndexTable[3]);
				pDst->i1 = (base + RectIndexTable[4]);
				pDst->i2 = (base + RectIndexTable[5]);
				++pDst;
			}
		}
	}
}
