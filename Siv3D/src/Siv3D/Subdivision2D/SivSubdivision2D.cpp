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

# include <cfloat>
# include <Siv3D/Subdivision2D.hpp>

namespace s3d
{
	///////////////////////////////////////////////////////////////
	//
	//	https://github.com/opencv/opencv/blob/master/modules/imgproc/src/subdivision2d.cpp
	//

	/*M///////////////////////////////////////////////////////////////////////////////////////
	//
	//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
	//
	//  By downloading, copying, installing or using the software you agree to this license.
	//  If you do not agree to this license, do not download, install,
	//  copy or use the software.
	//
	//
	//                        Intel License Agreement
	//                For Open Source Computer Vision Library
	//
	// Copyright (C) 2000, Intel Corporation, all rights reserved.
	// Third party copyrights are property of their respective owners.
	//
	// Redistribution and use in source and binary forms, with or without modification,
	// are permitted provided that the following conditions are met:
	//
	//   * Redistribution's of source code must retain the above copyright notice,
	//     this list of conditions and the following disclaimer.
	//
	//   * Redistribution's in binary form must reproduce the above copyright notice,
	//     this list of conditions and the following disclaimer in the documentation
	//     and/or other materials provided with the distribution.
	//
	//   * The name of Intel Corporation may not be used to endorse or promote products
	//     derived from this software without specific prior written permission.
	//
	// This software is provided by the copyright holders and contributors "as is" and
	// any express or implied warranties, including, but not limited to, the implied
	// warranties of merchantability and fitness for a particular purpose are disclaimed.
	// In no event shall the Intel Corporation or contributors be liable for any direct,
	// indirect, incidental, special, exemplary, or consequential damages
	// (including, but not limited to, procurement of substitute goods or services;
	// loss of use, data, or profits; or business interruption) however caused
	// and on any theory of liability, whether in contract, strict liability,
	// or tort (including negligence or otherwise) arising in any way out of
	// the use of this software, even if advised of the possibility of such damage.
	//
	//M*/

	namespace detail
	{
		[[nodiscard]]
		static constexpr double TriangleArea(const Vec2& a, const Vec2& b, const Vec2& c)
		{
			return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
		}

		[[nodiscard]]
		static constexpr int32 IsPtInCircle3(const Vec2& pt, const Vec2& a, const Vec2& b, const Vec2& c)
		{
			const double eps = FLT_EPSILON * 0.125;
			double val = (a.x * a.x + a.y * a.y) * TriangleArea(b, c, pt);
			val -= (b.x * b.x + b.y * b.y) * TriangleArea(a, c, pt);
			val += (c.x * c.x + c.y * c.y) * TriangleArea(a, b, pt);
			val -= (pt.x * pt.x + pt.y * pt.y) * TriangleArea(a, b, c);

			return (val > eps) ? 1 : (val < -eps) ? -1 : 0;
		}

		[[nodiscard]]
		static constexpr Vec2 ComputeVoronoiPoint(const Vec2& org0, const Vec2& dst0, const Vec2& org1, const Vec2& dst1)
		{
			double a0 = dst0.x - org0.x;
			double b0 = dst0.y - org0.y;
			double c0 = -0.5 * (a0 * (dst0.x + org0.x) + b0 * (dst0.y + org0.y));

			double a1 = dst1.x - org1.x;
			double b1 = dst1.y - org1.y;
			double c1 = -0.5 * (a1 * (dst1.x + org1.x) + b1 * (dst1.y + org1.y));

			if (double det = a0 * b1 - a1 * b0;
				det != 0)
			{
				det = 1. / det;
				return Vec2((b0 * c1 - b1 * c0) * det, (a1 * c0 - a0 * c1) * det);
			}

			return Vec2(FLT_MAX, FLT_MAX);
		}

		[[nodiscard]]
		static constexpr int32 IsRightOf2(const Vec2& pt, const Vec2& org, const Vec2& diff)
		{
			double cw_area = (org.x - pt.x) * diff.y - (org.y - pt.y) * diff.x;
			return ((cw_area > 0) - (cw_area < 0));
		}
	}

	Subdivision2D::Subdivision2D(const RectF& rect)
	{
		initDelaunay(rect);
	}

	Subdivision2D::Subdivision2D(const RectF& rect, const Array<Vec2>& points)
		: Subdivision2D{ rect }
	{
		addPoints(points);
	}

	void Subdivision2D::initDelaunay(const RectF& rect)
	{
		m_internal.clear();

		const double big_coord = 3.0 * Max(rect.w, rect.h);
		const double rx = rect.x;
		const double ry = rect.y;

		m_internal.rect = rect;
		m_internal.bottomRight = Vec2(rx + rect.w, ry + rect.h);

		Vec2 ppA(rx + big_coord, ry);
		Vec2 ppB(rx, ry + big_coord);
		Vec2 ppC(rx - big_coord, ry - big_coord);

		m_internal.vertices.emplace_back();
		m_internal.qEdges.emplace_back();

		int32 pA = newPoint(ppA, false);
		int32 pB = newPoint(ppB, false);
		int32 pC = newPoint(ppC, false);

		int32 edge_AB = newEdge();
		int32 edge_BC = newEdge();
		int32 edge_CA = newEdge();

		setEdgePoints(edge_AB, pA, pB);
		setEdgePoints(edge_BC, pB, pC);
		setEdgePoints(edge_CA, pC, pA);

		splice(edge_AB, symEdge(edge_CA));
		splice(edge_BC, symEdge(edge_AB));
		splice(edge_CA, symEdge(edge_BC));

		m_internal.recentEdge = edge_AB;
	}

	int32 Subdivision2D::addPoint(const Vec2& point)
	{
		// If a point with the same coordinates exists already, no new point is added.
		// returns the ID of the point.

		int32 curr_point = 0, curr_edge = 0, deleted_edge = 0;
		Subdivision2DPointLocation location = locate(point, curr_edge, curr_point);

		if (location == Subdivision2DPointLocation::Error)
		{
			throw Error(U"Subdiv2D::insert(): Error");
		}
		else if (location == Subdivision2DPointLocation::OutsideRect)
		{
			throw Error(U"Subdiv2D::insert(): The point is outside of the triangulation specified rect");
		}
		else if (location == Subdivision2DPointLocation::Vertex)
		{
			return curr_point;
		}
		else if (location == Subdivision2DPointLocation::OnEdge)
		{
			deleted_edge = curr_edge;
			m_internal.recentEdge = curr_edge = getEdge(curr_edge, Subdivision2DEdgeType::PreviousAroundOrigin);
			deleteEdge(deleted_edge);
		}
		else if (location == Subdivision2DPointLocation::Inside)
		{
			;
		}
		else
		{
			throw Error(U"Subdiv2D::insert(): Invalid location = {}"_fmt(FromEnum(location)));
		}

		assert(curr_edge != 0);
		m_internal.validGeometry = false;

		curr_point = newPoint(point, false);
		int32 base_edge = newEdge();
		int32 first_point = edgeBegin(curr_edge);
		setEdgePoints(base_edge, first_point, curr_point);
		splice(base_edge, curr_edge);

		do
		{
			base_edge = connectEdges(curr_edge, symEdge(base_edge));
			curr_edge = getEdge(base_edge, Subdivision2DEdgeType::PreviousAroundOrigin);
		} while (edgeEnd(curr_edge) != first_point);

		curr_edge = getEdge(base_edge, Subdivision2DEdgeType::PreviousAroundOrigin);

		const int32 max_edges = static_cast<int32>(m_internal.qEdges.size() * 4);

		for (int32 i = 0; i < max_edges; i++)
		{
			int32 temp_dst = 0, curr_org = 0, curr_dst = 0;
			int32 temp_edge = getEdge(curr_edge, Subdivision2DEdgeType::PreviousAroundOrigin);

			temp_dst = edgeEnd(temp_edge);
			curr_org = edgeBegin(curr_edge);
			curr_dst = edgeEnd(curr_edge);

			if (isRightOf(m_internal.vertices[temp_dst].pt, curr_edge) > 0 &&
				detail::IsPtInCircle3(m_internal.vertices[curr_org].pt, m_internal.vertices[temp_dst].pt,
					m_internal.vertices[curr_dst].pt, m_internal.vertices[curr_point].pt) < 0)
			{
				swapEdges(curr_edge);
				curr_edge = getEdge(curr_edge, Subdivision2DEdgeType::PreviousAroundOrigin);
			}
			else if (curr_org == first_point)
			{
				break;
			}
			else
			{
				curr_edge = getEdge(nextEdge(curr_edge), Subdivision2DEdgeType::PreviousAroundLeft);
			}
		}

		++m_internal.addedPoints;

		return curr_point;
	}

	void Subdivision2D::addPoints(const Array<Vec2>& points)
	{
		for (const Vec2& point : points)
		{
			addPoint(point);
		}
	}

	/** @brief Finds the subdivision vertex closest to the given point.
	@param pt Input point.
	@param nearestPt Output subdivision vertex point.
	The function is another function that locates the input point within the subdivision. It finds the
	subdivision vertex that is the closest to the input point. It is not necessarily one of vertices
	of the facet containing the input point, though the facet (located using locate() ) is used as a
	starting point.
	@returns vertex ID.
	 */
	Optional<Subdivision2D::VertexID> Subdivision2D::findNearest(const Vec2& point, Vec2* nearestPt)
	{
		if (isEmpty() || !m_internal.rect.contains(point))
		{
			return none;
		}

		if (not m_internal.validGeometry)
		{
			calcVoronoi();
		}

		int32 vertex = 0, edge = 0;
		Subdivision2DPointLocation loc = locate(point, edge, vertex);

		if (loc != Subdivision2DPointLocation::OnEdge
			&& loc != Subdivision2DPointLocation::Inside)
		{
			if (nearestPt && (loc == Subdivision2DPointLocation::Vertex))
			{
				*nearestPt = m_internal.vertices[vertex].pt;
			}

			return vertex;
		}

		vertex = 0;

		Vec2 start;
		edgeBegin(edge, &start);
		Vec2 diff = point - start;

		edge = rotateEdge(edge, 1);

		int32 total = static_cast<int32>(m_internal.vertices.size());

		for (int32 i = 0; i < total; i++)
		{
			Vec2 t;

			for (;;)
			{
				[[maybe_unused]] int32 r = edgeEnd(edge, &t);
				assert(r > 0);

				if (detail::IsRightOf2(t, start, diff) >= 0)
				{
					break;
				}

				edge = getEdge(edge, Subdivision2DEdgeType::NextAroundLeft);
			}

			for (;;)
			{
				[[maybe_unused]] int32 r = edgeBegin(edge, &t);
				assert(r > 0);

				if (detail::IsRightOf2(t, start, diff) < 0)
				{
					break;
				}

				edge = getEdge(edge, Subdivision2DEdgeType::PreviousAroundLeft);
			}

			Vec2 tempDiff;
			edgeEnd(edge, &tempDiff);
			edgeBegin(edge, &t);
			tempDiff -= t;

			if (detail::IsRightOf2(point, t, tempDiff) >= 0)
			{
				vertex = edgeBegin(rotateEdge(edge, 3));
				break;
			}

			edge = symEdge(edge);
		}

		if (nearestPt && vertex > 0)
		{
			*nearestPt = m_internal.vertices[vertex].pt;
		}

		return vertex;
	}

	Array<Line> Subdivision2D::calculateEdges() const
	{
		Array<Line> edges;

		calculateEdges(edges);

		return edges;
	}

	void Subdivision2D::calculateEdges(Array<Line>& edgeList) const
	{
		edgeList.clear();

		for (size_t i = 4; i < m_internal.qEdges.size(); ++i)
		{
			if (m_internal.qEdges[i].isfree())
			{
				continue;
			}

			if (m_internal.qEdges[i].pt[0] > 0 && m_internal.qEdges[i].pt[2] > 0)
			{
				const Vec2& org = m_internal.vertices[m_internal.qEdges[i].pt[0]].pt;
				const Vec2& dst = m_internal.vertices[m_internal.qEdges[i].pt[2]].pt;
				edgeList.emplace_back(org.x, org.y, dst.x, dst.y);
			}
		}
	}

	Array<Subdivision2D::EdgeID> Subdivision2D::calculateLeadingEdges() const
	{
		Array<Subdivision2D::EdgeID> edges;

		calculateLeadingEdges(edges);

		return edges;
	}

	void Subdivision2D::calculateLeadingEdges(Array<Subdivision2D::EdgeID>& leadingEdgeList) const
	{
		leadingEdgeList.clear();
		int32 total = static_cast<int32>(m_internal.qEdges.size() * 4);
		std::vector<bool> edgemask(total, false);

		for (int32 i = 4; i < total; i += 2)
		{
			if (edgemask[i])
			{
				continue;
			}

			int32 edge = i;
			edgemask[edge] = true;
			edge = getEdge(edge, Subdivision2DEdgeType::NextAroundLeft);
			edgemask[edge] = true;
			edge = getEdge(edge, Subdivision2DEdgeType::NextAroundLeft);
			edgemask[edge] = true;
			leadingEdgeList.push_back(i);
		}
	}

	Array<Triangle> Subdivision2D::calculateTriangles() const
	{
		Array<Triangle> triangles;

		calculateTriangles(triangles);

		return triangles;
	}

	void Subdivision2D::calculateTriangles(Array<Triangle>& triangleList) const
	{
		triangleList.clear();
		int32 total = static_cast<int32>(m_internal.qEdges.size() * 4);
		std::vector<bool> edgemask(total, false);

		for (int32 i = 4; i < total; i += 2)
		{
			if (edgemask[i])
			{
				continue;
			}

			Vec2 a, b, c;
			int32 edge_a = i;
			edgeBegin(edge_a, &a);
			if (not m_internal.rect.contains(a))
			{
				continue;
			}
			int32 edge_b = getEdge(edge_a, Subdivision2DEdgeType::NextAroundLeft);
			edgeBegin(edge_b, &b);
			if (not m_internal.rect.contains(b))
			{
				continue;
			}
			int32 edge_c = getEdge(edge_b, Subdivision2DEdgeType::NextAroundLeft);
			edgeBegin(edge_c, &c);
			if (not m_internal.rect.contains(c))
			{
				continue;
			}
			edgemask[edge_a] = true;
			edgemask[edge_b] = true;
			edgemask[edge_c] = true;
			triangleList.emplace_back(a.x, a.y, b.x, b.y, c.x, c.y);
		}
	}

	Array<VoronoiFacet> Subdivision2D::calculateVoronoiFacets()
	{
		Array<VoronoiFacet> facets;

		calculateVoronoiFacets({}, facets);

		return facets;
	}

	void Subdivision2D::calculateVoronoiFacets(Array<VoronoiFacet>& facets)
	{
		calculateVoronoiFacets({}, facets);
	}

	void Subdivision2D::calculateVoronoiFacets(const Array<VertexID>& indices, Array<VoronoiFacet>& facets)
	{
		calcVoronoi();
		facets.clear();

		size_t i, total;
		if (indices.isEmpty())
		{
			i = 4;
			total = m_internal.vertices.size();
		}
		else
		{
			i = 0;
			total = indices.size();
		}

		Array<Vec2> buf;

		for (; i < total; i++)
		{
			int32 k = indices.empty() ? static_cast<int32>(i) : indices[i];

			if (m_internal.vertices[k].isfree() || m_internal.vertices[k].isvirtual())
			{
				continue;
			}

			int32 edge = rotateEdge(m_internal.vertices[k].firstEdge, 1), t = edge;

			// gather points
			buf.clear();
			do
			{
				buf.push_back(m_internal.vertices[edgeBegin(t)].pt);
				t = getEdge(t, Subdivision2DEdgeType::NextAroundLeft);
			} while (t != edge);

			facets << VoronoiFacet{ buf, m_internal.vertices[k].pt };
		}
	}

	/** @brief Returns vertex location from vertex ID.
	@param vertex vertex ID.
	@param firstEdge Optional. The first edge ID which is connected to the vertex.
	@returns vertex (x,y)
	 */
	Vec2 Subdivision2D::getVertex(VertexID vertex, EdgeID* firstEdge) const
	{
		assert((size_t)vertex < m_internal.vertices.size());

		if (firstEdge)
		{
			*firstEdge = m_internal.vertices[vertex].firstEdge;
		}

		return m_internal.vertices[vertex].pt;
	}

	/** @brief Returns one of the edges related to the given edge.
	@param edge Subdivision edge ID.
	@param nextEdgeType Parameter specifying which of the related edges to return.
	The following values are possible:
	-   NextAroundOrgin next around the edge origin ( eOnext on the picture below if e is the input edge)
	-   NextAroundDst next around the edge vertex ( eDnext )
	-   PreviousAroundOrigin previous around the edge origin (reversed eRnext )
	-   PreviousAroundDst previous around the edge destination (reversed eLnext )
	-   NextAroundLeft next around the left facet ( eLnext )
	-   NextAroundRight next around the right facet ( eRnext )
	-   PreviousAroundLeft previous around the left facet (reversed eOnext )
	-   PreviousAroundRight previous around the right facet (reversed eDnext )
	![sample output](pics/quadedge.png)
	@returns edge ID related to the input edge.
	 */
	Subdivision2D::EdgeID Subdivision2D::getEdge(EdgeID edge, Subdivision2DEdgeType nextEdgeType) const
	{
		assert((size_t)(edge >> 2) < m_internal.qEdges.size());

		edge = m_internal.qEdges[edge >> 2].next[(edge + FromEnum(nextEdgeType)) & 3];

		return (edge & ~3) + ((edge + (FromEnum(nextEdgeType) >> 4)) & 3);
	}

	/** @brief Returns next edge around the edge origin.
	@param edge Subdivision edge ID.
	@returns an integer which is next edge ID around the edge origin: eOnext on the
	picture above if e is the input edge).
	 */
	Subdivision2D::EdgeID Subdivision2D::nextEdge(EdgeID edge) const
	{
		assert((size_t)(edge >> 2) < m_internal.qEdges.size());

		return m_internal.qEdges[edge >> 2].next[edge & 3];
	}

	/** @brief Returns another edge of the same quad-edge.
	@param edge Subdivision edge ID.
	@param rotate Parameter specifying which of the edges of the same quad-edge as the input
	one to return. The following values are possible:
	-   0 - the input edge ( e on the picture below if e is the input edge)
	-   1 - the rotated edge ( eRot )
	-   2 - the reversed edge (reversed e (in green))
	-   3 - the reversed rotated edge (reversed eRot (in green))
	@returns one of the edges ID of the same quad-edge as the input edge.
	 */
	Subdivision2D::EdgeID Subdivision2D::rotateEdge(EdgeID edge, int32 rotate) const
	{
		return (edge & ~3) + ((edge + rotate) & 3);
	}

	Subdivision2D::EdgeID Subdivision2D::symEdge(EdgeID edge) const
	{
		return edge ^ 2;
	}

	/** @brief Returns the edge origin.
	@param edge Subdivision edge ID.
	@param orgpt Output vertex location.
	@returns vertex ID.
	 */
	Subdivision2D::VertexID Subdivision2D::edgeBegin(EdgeID edge, Vec2* beginPos) const
	{
		assert((size_t)(edge >> 2) < m_internal.qEdges.size());

		int32 vidx = m_internal.qEdges[edge >> 2].pt[edge & 3];

		if (beginPos)
		{
			assert((size_t)vidx < m_internal.vertices.size());

			*beginPos = m_internal.vertices[vidx].pt;
		}

		return vidx;
	}

	/** @brief Returns the edge destination.
	@param edge Subdivision edge ID.
	@param dstpt Output vertex location.
	@returns vertex ID.
	 */
	Subdivision2D::VertexID Subdivision2D::edgeEnd(EdgeID edge, Vec2* endPos) const
	{
		assert((size_t)(edge >> 2) < m_internal.qEdges.size());

		int32 vidx = m_internal.qEdges[edge >> 2].pt[(edge + 2) & 3];

		if (endPos)
		{
			assert((size_t)vidx < m_internal.vertices.size());

			*endPos = m_internal.vertices[vidx].pt;
		}

		return vidx;
	}

	Subdivision2DPointLocation Subdivision2D::locate(const Vec2& pt, int32& _edge, int32& _vertex)
	{
		//@returns an integer which specify one of the following five cases for point location:
		//-  The point falls into some facet. The function returns #Inside and edge will contain one of
		//	edges of the facet.
		//-  The point falls onto the edge. The function returns #OnEdge and edge will contain this edge.
		//-  The point coincides with one of the subdivision vertices. The function returns #Vertex and
		//	vertex will contain a pointer to the vertex.
		//-  The point is outside the subdivision reference rectangle. The function returns #OutsideRect
		//	and no pointers are filled.
		//-  One of input arguments is invalid. A runtime error is raised or, if silent or "parent" error
		//	processing mode is selected, #Error is returned.

		int32 vertex = 0;

		int32 maxEdges = static_cast<int32>(m_internal.qEdges.size() * 4);

		if (m_internal.qEdges.size() < 4)
		{
			throw Error(U"Subdivision is empty");
		}

		if (pt.x < m_internal.rect.x || pt.y < m_internal.rect.y || pt.x >= m_internal.bottomRight.x || pt.y >= m_internal.bottomRight.y)
		{
			throw Error(U"Subdivision: point is out of bounds");
		}

		int32 edge = m_internal.recentEdge;
		assert(edge > 0);

		Subdivision2DPointLocation location = Subdivision2DPointLocation::Error;

		int32 right_of_curr = isRightOf(pt, edge);
		if (right_of_curr > 0)
		{
			edge = symEdge(edge);
			right_of_curr = -right_of_curr;
		}

		for (int32 i = 0; i < maxEdges; i++)
		{
			int32 onext_edge = nextEdge(edge);
			int32 dprev_edge = getEdge(edge, Subdivision2DEdgeType::PreviousAroundDst);

			int32 right_of_onext = isRightOf(pt, onext_edge);
			int32 right_of_dprev = isRightOf(pt, dprev_edge);

			if (right_of_dprev > 0)
			{
				if (right_of_onext > 0 || (right_of_onext == 0 && right_of_curr == 0))
				{
					location = Subdivision2DPointLocation::Inside;
					break;
				}
				else
				{
					right_of_curr = right_of_onext;
					edge = onext_edge;
				}
			}
			else
			{
				if (right_of_onext > 0)
				{
					if (right_of_dprev == 0 && right_of_curr == 0)
					{
						location = Subdivision2DPointLocation::Inside;
						break;
					}
					else
					{
						right_of_curr = right_of_dprev;
						edge = dprev_edge;
					}
				}
				else if (right_of_curr == 0 &&
					isRightOf(m_internal.vertices[edgeEnd(onext_edge)].pt, edge) >= 0)
				{
					edge = symEdge(edge);
				}
				else
				{
					right_of_curr = right_of_onext;
					edge = onext_edge;
				}
			}
		}

		m_internal.recentEdge = edge;

		if (location == Subdivision2DPointLocation::Inside)
		{
			Vec2 org_pt, dst_pt;
			edgeBegin(edge, &org_pt);
			edgeEnd(edge, &dst_pt);

			double t1 = std::abs(pt.x - org_pt.x);
			t1 += std::abs(pt.y - org_pt.y);
			double t2 = std::abs(pt.x - dst_pt.x);
			t2 += std::abs(pt.y - dst_pt.y);
			double t3 = std::abs(org_pt.x - dst_pt.x);
			t3 += std::abs(org_pt.y - dst_pt.y);

			if (t1 < FLT_EPSILON)
			{
				location = Subdivision2DPointLocation::Vertex;
				vertex = edgeBegin(edge);
				edge = 0;
			}
			else if (t2 < FLT_EPSILON)
			{
				location = Subdivision2DPointLocation::Vertex;
				vertex = edgeEnd(edge);
				edge = 0;
			}
			else if ((t1 < t3 || t2 < t3) &&
				std::abs(detail::TriangleArea(pt, org_pt, dst_pt)) < FLT_EPSILON)
			{
				location = Subdivision2DPointLocation::OnEdge;
				vertex = 0;
			}
		}

		if (location == Subdivision2DPointLocation::Error)
		{
			edge = 0;
			vertex = 0;
		}

		_edge = edge;
		_vertex = vertex;

		return location;
	}

	int32 Subdivision2D::newEdge()
	{
		if (m_internal.freeQEdge <= 0)
		{
			m_internal.qEdges.push_back(QuadEdge());
			m_internal.freeQEdge = (int32)(m_internal.qEdges.size() - 1);
		}
		int32 edge = m_internal.freeQEdge * 4;
		m_internal.freeQEdge = m_internal.qEdges[edge >> 2].next[1];
		m_internal.qEdges[edge >> 2] = QuadEdge(edge);
		return edge;
	}

	void Subdivision2D::deleteEdge(int32 edge)
	{
		assert((size_t)(edge >> 2) < (size_t)m_internal.qEdges.size());
		splice(edge, getEdge(edge, Subdivision2DEdgeType::PreviousAroundOrigin));
		int32 sedge = symEdge(edge);
		splice(sedge, getEdge(sedge, Subdivision2DEdgeType::PreviousAroundOrigin));

		edge >>= 2;
		m_internal.qEdges[edge].next[0] = 0;
		m_internal.qEdges[edge].next[1] = m_internal.freeQEdge;
		m_internal.freeQEdge = edge;
	}

	int32 Subdivision2D::newPoint(const Vec2& pt, bool isvirtual, int32 firstEdge)
	{
		if (m_internal.freePoint == 0)
		{
			m_internal.vertices.push_back(Vertex());
			m_internal.freePoint = (int32)(m_internal.vertices.size() - 1);
		}
		int32 vidx = m_internal.freePoint;
		m_internal.freePoint = m_internal.vertices[vidx].firstEdge;
		m_internal.vertices[vidx] = Vertex(pt, isvirtual, firstEdge);

		return vidx;
	}

	void Subdivision2D::deletePoint(int32 vidx)
	{
		assert((size_t)vidx < m_internal.vertices.size());
		m_internal.vertices[vidx].firstEdge = m_internal.freePoint;
		m_internal.vertices[vidx].type = -1;
		m_internal.freePoint = vidx;
	}

	void Subdivision2D::setEdgePoints(int32 edge, int32 orgPt, int32 dstPt)
	{
		m_internal.qEdges[edge >> 2].pt[edge & 3] = orgPt;
		m_internal.qEdges[edge >> 2].pt[(edge + 2) & 3] = dstPt;
		m_internal.vertices[orgPt].firstEdge = edge;
		m_internal.vertices[dstPt].firstEdge = edge ^ 2;
	}

	void Subdivision2D::splice(int32 edgeA, int32 edgeB)
	{
		int32& a_next = m_internal.qEdges[edgeA >> 2].next[edgeA & 3];
		int32& b_next = m_internal.qEdges[edgeB >> 2].next[edgeB & 3];
		int32 a_rot = rotateEdge(a_next, 1);
		int32 b_rot = rotateEdge(b_next, 1);
		int32& a_rot_next = m_internal.qEdges[a_rot >> 2].next[a_rot & 3];
		int32& b_rot_next = m_internal.qEdges[b_rot >> 2].next[b_rot & 3];
		std::swap(a_next, b_next);
		std::swap(a_rot_next, b_rot_next);
	}

	int32 Subdivision2D::connectEdges(int32 edgeA, int32 edgeB)
	{
		int32 edge = newEdge();

		splice(edge, getEdge(edgeA, Subdivision2DEdgeType::NextAroundLeft));
		splice(symEdge(edge), edgeB);

		setEdgePoints(edge, edgeEnd(edgeA), edgeBegin(edgeB));
		return edge;
	}

	void Subdivision2D::swapEdges(int32 edge)
	{
		int32 sedge = symEdge(edge);
		int32 a = getEdge(edge, Subdivision2DEdgeType::PreviousAroundOrigin);
		int32 b = getEdge(sedge, Subdivision2DEdgeType::PreviousAroundOrigin);

		splice(edge, a);
		splice(sedge, b);

		setEdgePoints(edge, edgeEnd(a), edgeEnd(b));

		splice(edge, getEdge(a, Subdivision2DEdgeType::NextAroundLeft));
		splice(sedge, getEdge(b, Subdivision2DEdgeType::NextAroundLeft));
	}

	int32 Subdivision2D::isRightOf(const Vec2& pt, int32 edge) const
	{
		Vec2 org, dst;
		edgeBegin(edge, &org);
		edgeEnd(edge, &dst);
		double cw_area = detail::TriangleArea(pt, dst, org);

		return (cw_area > 0) - (cw_area < 0);
	}

	void Subdivision2D::calcVoronoi()
	{
		if (m_internal.validGeometry)
		{
			return;
		}

		clearVoronoi();
		int32 total = static_cast<int32>(m_internal.qEdges.size());

		// loop through all quad-edges, except for the first 3 (#1, #2, #3 - 0 is reserved for "NULL" pointer)
		for (int32 i = 4; i < total; i++)
		{
			QuadEdge& quadedge = m_internal.qEdges[i];

			if (quadedge.isfree())
			{
				continue;
			}

			int32 edge0 = (i * 4);
			Vec2 org0, dst0, org1, dst1;

			if (!quadedge.pt[3])
			{
				int32 edge1 = getEdge(edge0, Subdivision2DEdgeType::NextAroundLeft);
				int32 edge2 = getEdge(edge1, Subdivision2DEdgeType::NextAroundLeft);

				edgeBegin(edge0, &org0);
				edgeEnd(edge0, &dst0);
				edgeBegin(edge1, &org1);
				edgeEnd(edge1, &dst1);

				Vec2 virt_point = detail::ComputeVoronoiPoint(org0, dst0, org1, dst1);

				if (std::abs(virt_point.x) < FLT_MAX * 0.5 &&
					std::abs(virt_point.y) < FLT_MAX * 0.5)
				{
					quadedge.pt[3] = m_internal.qEdges[edge1 >> 2].pt[3 - (edge1 & 2)] =
						m_internal.qEdges[edge2 >> 2].pt[3 - (edge2 & 2)] = newPoint(virt_point, true);
				}
			}

			if (!quadedge.pt[1])
			{
				int32 edge1 = getEdge(edge0, Subdivision2DEdgeType::NextAroundRight);
				int32 edge2 = getEdge(edge1, Subdivision2DEdgeType::NextAroundRight);

				edgeBegin(edge0, &org0);
				edgeEnd(edge0, &dst0);
				edgeBegin(edge1, &org1);
				edgeEnd(edge1, &dst1);

				Vec2 virt_point = detail::ComputeVoronoiPoint(org0, dst0, org1, dst1);

				if (std::abs(virt_point.x) < FLT_MAX * 0.5 &&
					std::abs(virt_point.y) < FLT_MAX * 0.5)
				{
					quadedge.pt[1] = m_internal.qEdges[edge1 >> 2].pt[1 + (edge1 & 2)] =
						m_internal.qEdges[edge2 >> 2].pt[1 + (edge2 & 2)] = newPoint(virt_point, true);
				}
			}
		}

		m_internal.validGeometry = true;
	}

	void Subdivision2D::clearVoronoi()
	{
		size_t total = m_internal.qEdges.size();

		for (size_t i = 0; i < total; i++)
		{
			m_internal.qEdges[i].pt[1] = m_internal.qEdges[i].pt[3] = 0;
		}

		total = m_internal.vertices.size();
		for (size_t i = 0; i < total; i++)
		{
			if (m_internal.vertices[i].isvirtual())
			{
				deletePoint((int32)i);
			}
		}

		m_internal.validGeometry = false;
	}

	//
	//
	///////////////////////////////////////////////////////////////

	void Subdivision2D::Internal::clear() noexcept
	{
		vertices.clear();
		qEdges.clear();
		addedPoints = 0;
		freeQEdge = 0;
		freePoint = 0;
		validGeometry = false;
		recentEdge = 0;
		rect = RectF::Empty();
		bottomRight = Vec2::Zero();
	}
}
