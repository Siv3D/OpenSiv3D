//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	enum class Subdivision2DPointLocation : int32
	{
		/// @brief エラー
		Error = -2,

		/// @brief Subdivision bounding rect の外
		OutsideRect = -1,

		/// @brief Facet 内
		Inside = 0,

		/// @brief 頂点の重複
		Vertex = 1,

		/// @brief Edge 上
		OnEdge = 2,
	};

	enum class Subdivision2DEdgeType : int32
	{
		NextAroundOrgin = 0x00,

		NextAroundDst = 0x22,

		PreviousAroundOrigin = 0x11,

		PreviousAroundDst = 0x33,

		NextAroundLeft = 0x13,

		NextAroundRight = 0x31,

		PreviousAroundLeft = 0x20,

		PreviousAroundRight = 0x02
	};

	struct VoronoiFacet
	{
		Array<Vec2> points;

		Vec2 center;
	};

	class Subdivision2D
	{
	public:

		using EdgeID = int32;
		using VertexID = int32;

		SIV3D_NODISCARD_CXX20
		Subdivision2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit Subdivision2D(const RectF& rect);

		SIV3D_NODISCARD_CXX20
		explicit Subdivision2D(const RectF& rect, const Array<Vec2>& points);

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void initDelaunay(const RectF& rect);

		int32 addPoint(const Vec2& point);

		void addPoints(const Array<Vec2>& points);

		Optional<VertexID> findNearest(const Vec2& point, Vec2* nearestPt = nullptr);

		[[nodiscard]]
		Array<Line> calculateEdges() const;

		// each edge as a Line
		void calculateEdges(Array<Line>& edgeList) const;

		[[nodiscard]]
		Array<EdgeID> calculateLeadingEdges() const;

		// one edge ID for each triangle
		void calculateLeadingEdges(Array<EdgeID>& leadingEdgeList) const;

		[[nodiscard]]
		Array<Triangle> calculateTriangles() const;

		void calculateTriangles(Array<Triangle>& triangleList) const;

		[[nodiscard]]
		Array<VoronoiFacet> calculateVoronoiFacets();

		void calculateVoronoiFacets(Array<VoronoiFacet>& facets);

		void calculateVoronoiFacets(const Array<VertexID>& indices, Array<VoronoiFacet>& facets);

		[[nodiscard]]
		Vec2 getVertex(VertexID vertex, EdgeID* firstEdge = nullptr) const;

		[[nodiscard]]
		EdgeID getEdge(EdgeID edge, Subdivision2DEdgeType nextEdgeType) const;

		[[nodiscard]]
		EdgeID nextEdge(EdgeID edge) const;

		[[nodiscard]]
		EdgeID rotateEdge(EdgeID edge, int32 rotate) const;

		[[nodiscard]]
		EdgeID symEdge(EdgeID edge) const;

		VertexID edgeBegin(EdgeID edge, Vec2* beginPos = nullptr) const;

		VertexID edgeEnd(EdgeID edge, Vec2* endPos = nullptr) const;

	private:

		struct Vertex
		{
			int32 firstEdge = 0;

			int32 type = -1;

			Vec2 pt;

			Vertex() = default;

			constexpr Vertex(const Vec2& _pt, bool _isvirtual, int32 _firstEdge = 0);

			[[nodiscard]]
			constexpr bool isvirtual() const noexcept;

			[[nodiscard]]
			constexpr bool isfree() const noexcept;
		};

		struct QuadEdge
		{
			int32 next[4] = {};

			int32 pt[4] = {};

			QuadEdge() = default;

			explicit constexpr QuadEdge(int32 edgeidx);

			[[nodiscard]]
			constexpr bool isfree() const noexcept;
		};

		Array<Vertex> m_vertices;

		size_t m_addedPoints = 0;

		Array<QuadEdge> m_qEdges;

		int32 m_freeQEdge = 0;

		int32 m_freePoint = 0;

		bool m_validGeometry = false;

		int32 m_recentEdge = 0;

		RectF m_rect = RectF{ 0, 0 };

		Vec2 m_bottomRight = Vec2{ 0, 0 };

		Subdivision2DPointLocation locate(const Vec2& pt, int32& _edge, int32& _vertex);

		int32 newEdge();

		void deleteEdge(int32 edge);

		int32 newPoint(const Vec2& pt, bool isvirtual, int32 firstEdge = 0);

		void deletePoint(int32 vidx);

		void setEdgePoints(int32 edge, int32 orgPt, int32 dstPt);

		void splice(int32 edgeA, int32 edgeB);

		int32 connectEdges(int32 edgeA, int32 edgeB);

		void swapEdges(int32 edge);

		int32 isRightOf(const Vec2& pt, int32 edge) const;

		void calcVoronoi();

		void clearVoronoi();
	};
}

# include "detail/Subdivision2D.ipp"
