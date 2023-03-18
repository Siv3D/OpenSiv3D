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

# include <Siv3D/Buffer2D.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Shape2D.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	Buffer2D::Buffer2D(const size_t vertexSize, const size_t indexSize)
		: vertices(vertexSize)
		, indices(indexSize) {}

	Buffer2D::Buffer2D(Array<Vertex2D> _vertices, Array<TriangleIndex> _indices)
		: vertices(_vertices)
		, indices(_indices) {}

	Buffer2D::Buffer2D(const Polygon& polygon, const Vec2& _uvOrigin, const Vec2& _uvScale)
		: vertices(polygon.vertices().size())
		, indices(polygon.indices())
	{
		Vertex2D* pDst = vertices.data();
		const Vertex2D* const pDstEnd = (pDst + vertices.size());
		const Float2* pSrc = polygon.vertices().data();

		const Float2 uvOrigin{ _uvOrigin };
		const Float2 uvScale{ 1.0 / _uvScale.x, 1.0 / _uvScale.y };
		constexpr Float4 color{ 1.0f,1.0f,1.0f,1.0f };

		while (pDst != pDstEnd)
		{
			const Float2 pos = *pSrc;
			const Float2 uv = ((pos - uvOrigin) * uvScale);
			pDst->pos	= pos;
			pDst->color	= color;
			pDst->tex	= uv;
			++pSrc;
			++pDst;
		}
	}

	Buffer2D::Buffer2D(const Polygon& polygon, const Mat3x2& uvMat)
		: vertices(polygon.vertices().size())
		, indices(polygon.indices())
	{
		Vertex2D* pDst = vertices.data();
		const Vertex2D* const pDstEnd = (pDst + vertices.size());
		const Float2* pSrc = polygon.vertices().data();

		constexpr Float4 color{ 1.0f,1.0f,1.0f,1.0f };

		while (pDst != pDstEnd)
		{
			const Float2 pos = *pSrc;
			const Float2 uv = uvMat.transformPoint(pos);
			pDst->pos	= pos;
			pDst->color	= color;
			pDst->tex	= uv;
			++pSrc;
			++pDst;
		}
	}

	Buffer2D::Buffer2D(const Polygon& polygon, const Arg::center_<Vec2> uvCenter, const Vec2& uvScale)
		: Buffer2D{ polygon, uvCenter->movedBy(uvScale * -0.5), uvScale } {}

	Buffer2D::Buffer2D(const Polygon& polygon, const Arg::center_<Vec2> uvCenter, const Vec2& uvScale, const double uvRotation)
		: Buffer2D{ polygon, Mat3x2::Translate((uvScale * 0.5) - *uvCenter).scaled(1.0 / uvScale.x, 1.0 / uvScale.y).rotated(-uvRotation, Vec2{ 0.5, 0.5 }) } {}

	Buffer2D::Buffer2D(const Shape2D& shape2D, const Vec2& _uvOrigin, const Vec2& _uvScale)
		: vertices(shape2D.vertices().size())
		, indices(shape2D.indices())
	{
		Vertex2D* pDst = vertices.data();
		const Vertex2D* const pDstEnd = (pDst + vertices.size());
		const Float2* pSrc = shape2D.vertices().data();

		const Float2 uvOrigin{ _uvOrigin };
		const Float2 uvScale{ 1.0 / _uvScale.x, 1.0 / _uvScale.y };
		constexpr Float4 color{ 1.0f,1.0f,1.0f,1.0f };

		while (pDst != pDstEnd)
		{
			const Float2 pos = *pSrc;
			const Float2 uv = ((pos - uvOrigin) * uvScale);
			pDst->pos	= pos;
			pDst->color	= color;
			pDst->tex	= uv;
			++pSrc;
			++pDst;
		}
	}

	Buffer2D::Buffer2D(const Shape2D& shape2D, const Mat3x2& uvMat)
		: vertices(shape2D.vertices().size())
		, indices(shape2D.indices())
	{
		Vertex2D* pDst = vertices.data();
		const Vertex2D* const pDstEnd = (pDst + vertices.size());
		const Float2* pSrc = shape2D.vertices().data();

		constexpr Float4 color{ 1.0f,1.0f,1.0f,1.0f };

		while (pDst != pDstEnd)
		{
			const Float2 pos = *pSrc;
			const Float2 uv = uvMat.transformPoint(pos);
			pDst->pos	= pos;
			pDst->color	= color;
			pDst->tex	= uv;
			++pSrc;
			++pDst;
		}
	}

	Buffer2D::Buffer2D(const Shape2D& shape2D, const Arg::center_<Vec2> uvCenter, const Vec2& uvScale)
		: Buffer2D{ shape2D, uvCenter->movedBy(uvScale * -0.5), uvScale } {}

	Buffer2D::Buffer2D(const Shape2D& shape2D, const Arg::center_<Vec2> uvCenter, const Vec2& uvScale, const double uvRotation)
		: Buffer2D{ shape2D, Mat3x2::Translate((uvScale * 0.5) - *uvCenter).scaled(1.0 / uvScale.x, 1.0 / uvScale.y).rotated(-uvRotation, Vec2{ 0.5, 0.5 }) } {}

	void Buffer2D::draw() const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygon(vertices.data(), vertices.size(), indices.data(), indices.size());
	}

	void Buffer2D::draw(const Texture& texture) const
	{
		SIV3D_ENGINE(Renderer2D)->addTexturedVertices(texture, vertices.data(), vertices.size(), indices.data(), indices.size());
	}

	void Buffer2D::drawSubset(const size_t startTriangle, size_t triangleCount) const
	{
		if (indices.size() <= startTriangle)
		{
			return;
		}

		if (indices.size() < (startTriangle + triangleCount))
		{
			triangleCount = (indices.size() - startTriangle);
		}

		SIV3D_ENGINE(Renderer2D)->addPolygon(vertices.data(), vertices.size(), (indices.data() + startTriangle), triangleCount);
	}

	void Buffer2D::drawSubset(const size_t startTriangle, size_t triangleCount, const Texture& texture) const
	{
		if (indices.size() <= startTriangle)
		{
			return;
		}

		if (indices.size() < (startTriangle + triangleCount))
		{
			triangleCount = (indices.size() - startTriangle);
		}

		SIV3D_ENGINE(Renderer2D)->addTexturedVertices(texture, vertices.data(), vertices.size(), (indices.data() + startTriangle), triangleCount);
	}
}
