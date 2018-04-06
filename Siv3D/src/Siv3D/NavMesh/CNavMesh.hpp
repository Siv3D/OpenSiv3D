//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/NavMesh.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Triangle.hpp>
# include "../../ThirdParty/Recast/Recast.h"
# include "../../ThirdParty/Detour/DetourCommon.h"
# include "../../ThirdParty/Detour/DetourNavMesh.h"
# include "../../ThirdParty/Detour/DetourNavMeshBuilder.h"
# include "../../ThirdParty/Detour/DetourNavMeshQuery.h"

# include <Siv3D/Print.hpp>

namespace s3d
{
	struct TriangleF
	{
		Float3 t0, t1, t2;
	};

	class NavMesh::CNavMesh
	{
	private:

		float m_cellSize;
		
		float m_cellHeight;
		
		float m_agentMaxSlope;
		
		float m_agentHeight;
		
		float m_agentMaxClimb;
		
		float m_agentRadius;
		
		float m_edgeMaxLen;
		
		float m_edgeMaxError;
		
		float m_regionMinSize;
		
		float m_regionMergeSize;
		
		int32 m_vertsPerPoly;
		
		float m_detailSampleDist;
		
		float m_detailSampleMaxError;

		rcContext m_ctx;
		
		rcHeightfield* m_hf = nullptr;
		
		rcCompactHeightfield* m_chf = nullptr;
		
		rcContourSet* m_cset = nullptr;
		
		rcPolyMesh* m_mesh = nullptr;
		
		rcPolyMeshDetail* m_dmesh = nullptr;
		
		std::shared_ptr<dtNavMesh> m_navmesh;

		float bmin[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
		float bmax[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

		unsigned char* m_navData = nullptr;

		int32 m_navDataSize = 0;

		Array<std::pair<TriangleF, uint8>> m_riangles;

		static void toRecastVertex(Float3 const & v1, float * v2)
		{
			v2[0] = v1.x;
			v2[1] = v1.y;
			v2[2] = v1.z;
		}

		void updateAabb(Float3 const & v)
		{
			bmin[0] = std::min(bmin[0], v.x);
			bmin[1] = std::min(bmin[1], v.y);
			bmin[2] = std::min(bmin[2], v.z);

			bmax[0] = std::max(bmax[0], v.x);
			bmax[1] = std::max(bmax[1], v.y);
			bmax[2] = std::max(bmax[2], v.z);
		}

		void Free()
		{
			m_navmesh.reset();

			if (m_dmesh)
			{
				rcFreePolyMeshDetail(m_dmesh);
				m_dmesh = nullptr;
			}

			if (m_mesh)
			{
				rcFreePolyMesh(m_mesh);
				m_mesh = nullptr;
			}

			if (m_cset)
			{
				rcFreeContourSet(m_cset);
				m_cset = nullptr;
			}

			if (m_chf)
			{
				rcFreeCompactHeightfield(m_chf);
				m_chf = nullptr;
			}

			if (m_hf)
			{
				rcFreeHeightField(m_hf);
				m_hf = nullptr;
			}
		}

		void Alloc()
		{
			try
			{
				m_hf = rcAllocHeightfield();

				if (!m_hf) throw std::bad_alloc();

				m_chf = rcAllocCompactHeightfield();

				if (!m_chf) throw std::bad_alloc();

				m_cset = rcAllocContourSet();

				if (!m_cset) throw std::bad_alloc();

				m_mesh = rcAllocPolyMesh();

				if (!m_mesh) throw std::bad_alloc();

				m_dmesh = rcAllocPolyMeshDetail();

				if (!m_dmesh) throw std::bad_alloc();

				m_navmesh = std::shared_ptr<dtNavMesh>(dtAllocNavMesh(), dtFreeNavMesh);

				if (!m_navmesh) throw std::bad_alloc();
			}
			catch (...)
			{
				Free();
				throw;
			}
		}

		void reset()
		{
			Free();
			Alloc();
		}

		void build()
		{
			rcConfig cfg = {};
			cfg.cs = m_cellSize;
			cfg.ch = m_cellHeight;
			cfg.walkableSlopeAngle = m_agentMaxSlope;
			cfg.walkableHeight = (int32)ceilf(m_agentHeight / cfg.ch);
			cfg.walkableClimb = (int32)floorf(m_agentMaxClimb / cfg.ch);
			cfg.walkableRadius = (int32)ceilf(m_agentRadius / cfg.cs);
			cfg.maxEdgeLen = (int32)(m_edgeMaxLen / m_cellSize);
			cfg.maxSimplificationError = m_edgeMaxError;
			cfg.minRegionArea = (int32)(m_regionMinSize*m_regionMinSize);		// Note: area = size*size
			cfg.mergeRegionArea = (int32)(m_regionMergeSize*m_regionMergeSize);	// Note: area = size*size
			cfg.maxVertsPerPoly = m_vertsPerPoly;
			cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
			cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;

			rcVcopy(cfg.bmin, bmin);
			rcVcopy(cfg.bmax, bmax);
			cfg.bmin[0] -= cfg.borderSize * cfg.cs;
			cfg.bmin[2] -= cfg.borderSize * cfg.cs;
			cfg.bmax[0] += cfg.borderSize * cfg.cs;
			cfg.bmax[2] += cfg.borderSize * cfg.cs;

			rcCalcGridSize(cfg.bmin, cfg.bmax, cfg.cs, &cfg.width, &cfg.height);

			if (cfg.maxVertsPerPoly > DT_VERTS_PER_POLYGON)
				throw std::range_error("maxVertsPerPoly > 6");

			cfg.width = static_cast<int32>((cfg.bmax[0] - cfg.bmin[0]) / cfg.cs + 1);
			cfg.height = static_cast<int32>((cfg.bmax[2] - cfg.bmin[2]) / cfg.cs + 1);

			reset();

			if (!rcCreateHeightfield(&m_ctx, *m_hf, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs, cfg.ch))
				throw std::bad_alloc();

			for (const auto & triangle : m_riangles)
			{
				const int32 flagMergeThreshold = 0;

				rcRasterizeTriangle(&m_ctx, &triangle.first.t0.x, &triangle.first.t1.x, &triangle.first.t2.x, triangle.second, *m_hf, flagMergeThreshold);
			}

			rcFilterLowHangingWalkableObstacles(&m_ctx, cfg.walkableClimb, *m_hf);
			rcFilterLedgeSpans(&m_ctx, cfg.walkableHeight, cfg.walkableClimb, *m_hf);
			rcFilterWalkableLowHeightSpans(&m_ctx, cfg.walkableHeight, *m_hf);

			if (!rcBuildCompactHeightfield(&m_ctx, cfg.walkableHeight, cfg.walkableClimb, *m_hf, *m_chf))
				throw std::bad_alloc();

			if (!rcErodeWalkableArea(&m_ctx, cfg.walkableRadius, *m_chf))
				throw std::bad_alloc();

			if (!rcBuildDistanceField(&m_ctx, *m_chf))
				throw std::bad_alloc();

			if (!rcBuildRegions(&m_ctx, *m_chf, 0 /* border size */, cfg.minRegionArea, cfg.mergeRegionArea))
				throw std::bad_alloc();

			if (!rcBuildContours(&m_ctx, *m_chf, cfg.maxSimplificationError, cfg.maxEdgeLen, *m_cset))
				throw std::bad_alloc();

			if (!rcBuildPolyMesh(&m_ctx, *m_cset, cfg.maxVertsPerPoly, *m_mesh))
				throw std::bad_alloc();

			if (!rcBuildPolyMeshDetail(&m_ctx, *m_mesh, *m_chf, cfg.detailSampleDist, cfg.detailSampleMaxError, *m_dmesh))
				throw std::bad_alloc();

			// TODO: changer les flags cf Sample_SoloMesh.cpp:594
			for (int32 i = 0; i < m_mesh->npolys; ++i)
			{
				m_mesh->flags[i] = 1;
			}

			dtNavMeshCreateParams params;
			memset(&params, 0, sizeof(params));

			params.verts = m_mesh->verts;
			params.vertCount = m_mesh->nverts;
			params.polys = m_mesh->polys;
			params.polyAreas = m_mesh->areas;
			params.polyFlags = m_mesh->flags;
			params.polyCount = m_mesh->npolys;
			params.nvp = m_mesh->nvp;

			params.detailMeshes = m_dmesh->meshes;
			params.detailVerts = m_dmesh->verts;
			params.detailVertsCount = m_dmesh->nverts;
			params.detailTris = m_dmesh->tris;
			params.detailTriCount = m_dmesh->ntris;

			params.walkableHeight = static_cast<float>(cfg.walkableHeight);
			params.walkableClimb = static_cast<float>(cfg.walkableClimb);
			rcVcopy(params.bmin, m_mesh->bmin);
			rcVcopy(params.bmax, m_mesh->bmax);
			params.cs = cfg.cs;
			params.ch = cfg.ch;
			params.buildBvTree = true;

			if (!dtCreateNavMeshData(&params, &m_navData, &m_navDataSize))
				throw std::bad_alloc();

			m_navmesh->init(m_navData, m_navDataSize, DT_TILE_FREE_DATA);
		}

	public:

		CNavMesh();

		~CNavMesh();

		void build(const Array<Triangle3D>& triangles, uint8 areaID)
		{
			assert(InRange<uint8>(areaID, 0, RC_WALKABLE_AREA));

			for (const auto& triangle : triangles)
			{
				TriangleF t{ triangle.p0.xyz(), triangle.p1.xyz(), triangle.p2.xyz() };

				m_riangles.emplace_back(t, areaID);

				updateAabb(t.t0);
				updateAabb(t.t1);
				updateAabb(t.t2);
			}

			build();
		}

		Array<Vec3> query(const Vec3& start, const Vec3& end) const
		{
			Float3 startF(start), endF(end), extent(2.0f, 4.0f, 2.0f);

			dtNavMeshQuery navmeshquery;

			if (dtStatusFailed(navmeshquery.init(m_navmesh.get(), 2048)))
			{
				throw std::bad_alloc();
			}

			dtPolyRef startpoly, endpoly;
			dtQueryFilter filter;

			if (dtStatusFailed(navmeshquery.findNearestPoly(&startF.x, &extent.x, &filter, &startpoly, 0)))
			{
				//std::cerr << "Warning: cannot find start poly (" << start[0] << ", " << start[1] << ", " << start[2] << ")\n";
				return{};
			}

			if (dtStatusFailed(navmeshquery.findNearestPoly(&endF.x, &extent.x, &filter, &endpoly, 0)))
			{
				//std::cerr << "Warning: cannot find end poly (" << end[0] << ", " << end[1] << ", " << end[2] << ")\n";
				return{};
			}

			if (startpoly == 0)
			{
				//std::cerr << "Warning: cannot find start poly (" << start[0] << ", " << start[1] << ", " << start[2] << ")\n";
				return{};
			}

			if (endpoly == 0)
			{
				//std::cerr << "Warning: cannot find end poly (" << end[0] << ", " << end[1] << ", " << end[2] << ")\n";
				return{};
			}

			const int32 buffersize = 10000;

			int32 npolys = 0;

			Array<dtPolyRef> polys(buffersize);

			dtStatus sta;

			if (dtStatusFailed(sta = navmeshquery.findPath(startpoly, endpoly, &startF.x, &endF.x, &filter, polys.data(), &npolys, buffersize)))
			{
				//std::cerr << "Warning: findPath failed, status = " << sta << "\n";
				return{};
			}

			Array<Vec3> vertices;

			if (npolys > 0)
			{
				float end2[3] = { endF.x, endF.y, endF.z };

				if (polys[npolys - 1] != endpoly)
				{
					bool posOverPoly;
					navmeshquery.closestPointOnPoly(polys[npolys - 1], &endF.x, end2, &posOverPoly);
				}

				constexpr int32 maxvertices = 8192;

				Array<float> buffer(maxvertices * 3);

				int32 nvertices = 0;

				navmeshquery.findStraightPath(&startF.x, end2, polys.data(), npolys, buffer.data(), 0, 0, &nvertices, maxvertices);

				vertices.resize(nvertices);

				for (int32 i = 0; i < nvertices; ++i)
				{
					vertices[i].set(buffer[3 * i], buffer[3 * i + 1], buffer[3 * i + 2]);
				}
			}

			return vertices;
		}
	};
}
