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

# include "CNavMesh.hpp"

namespace s3d
{
	NavMesh::CNavMesh::CNavMesh()
		: m_cellSize(0.3f)
		, m_cellHeight(0.1f)
		, m_agentMaxSlope(static_cast<float>(45_deg))
		, m_agentHeight(2.0f)
		, m_agentMaxClimb(0.9f)
		, m_agentRadius(0.1f)
		, m_edgeMaxLen(12)
		, m_edgeMaxError(1.3f)
		, m_regionMinSize(8)
		, m_regionMergeSize(20)
		, m_vertsPerPoly(6)
		, m_detailSampleDist(6)
		, m_detailSampleMaxError(1) {}

	NavMesh::CNavMesh::~CNavMesh()
	{
		destroy();
	}

	bool NavMesh::CNavMesh::build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs)
	{
		m_built = false;

		if (vertices.isEmpty() || indices.isEmpty() || areaIDs.isEmpty())
		{
			return false;
		}

		if ((indices.size() / 3) != areaIDs.size())
		{
			return false;
		}

		if (!areaIDs.all(LessThanEqual(RC_WALKABLE_AREA)))
		{
			return false;
		}

		m_vertices = vertices;

		m_indices = indices;

		m_areaIDs = areaIDs;

		for (const auto& vertex : m_vertices)
		{
			updateAABB(vertex);
		}

		try
		{
			build();
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	Array<Vec3> NavMesh::CNavMesh::query(const Vec3& start, const Vec3& end) const
	{
		if (!m_built)
		{
			return{};
		}

		Float3 startF(start), endF(end), extent(2.0f, 4.0f, 2.0f);

		dtNavMeshQuery navmeshquery;

		if (dtStatusFailed(navmeshquery.init(m_navmesh.get(), 2048)))
		{
			return{};
		}

		dtPolyRef startpoly, endpoly;
		dtQueryFilter filter;

		if (dtStatusFailed(navmeshquery.findNearestPoly(&startF.x, &extent.x, &filter, &startpoly, 0)))
		{
			return{};
		}

		if (dtStatusFailed(navmeshquery.findNearestPoly(&endF.x, &extent.x, &filter, &endpoly, 0)))
		{
			return{};
		}

		if (startpoly == 0)
		{
			return{};
		}

		if (endpoly == 0)
		{
			return{};
		}

		constexpr int32 buffersize = 8192;

		int32 npolys = 0;

		Array<dtPolyRef> polys(buffersize);

		if (dtStatus status = navmeshquery.findPath(startpoly, endpoly, &startF.x, &endF.x, &filter, polys.data(), &npolys, buffersize); dtStatusFailed(status))
		{
			return{};
		}

		if (npolys <= 0)
		{
			return{};
		}

		float end2[3] = { endF.x, endF.y, endF.z };

		if (polys[npolys - 1] != endpoly)
		{
			bool posOverPoly;
			navmeshquery.closestPointOnPoly(polys[npolys - 1], &endF.x, end2, &posOverPoly);
		}

		constexpr int32 maxvertices = 8192;

		Array<Float3> buffer(maxvertices);

		int32 nvertices = 0;

		navmeshquery.findStraightPath(&startF.x, end2, polys.data(), npolys, &buffer[0].x, 0, 0, &nvertices, maxvertices);

		Array<Vec3> vertices(nvertices);

		for (int32 i = 0; i < nvertices; ++i)
		{
			vertices[i] = buffer[i];
		}

		return vertices;
	}

	void NavMesh::CNavMesh::updateAABB(const Float3& v)
	{
		m_bmin[0] = std::min(m_bmin[0], v.x);
		m_bmin[1] = std::min(m_bmin[1], v.y);
		m_bmin[2] = std::min(m_bmin[2], v.z);

		m_bmax[0] = std::max(m_bmax[0], v.x);
		m_bmax[1] = std::max(m_bmax[1], v.y);
		m_bmax[2] = std::max(m_bmax[2], v.z);
	}

	void NavMesh::CNavMesh::destroy()
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

	void NavMesh::CNavMesh::create()
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
			destroy();
			throw;
		}
	}

	void NavMesh::CNavMesh::reset()
	{
		destroy();

		create();
	}

	bool NavMesh::CNavMesh::build()
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

		rcVcopy(cfg.bmin, m_bmin);
		rcVcopy(cfg.bmax, m_bmax);
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

		const int32 flagMergeThreshold = 0;

		rcRasterizeTriangles(&m_ctx, &m_vertices[0].x, static_cast<int32>(m_vertices.size()),
			m_indices.data(), m_areaIDs.data(), static_cast<int32>(m_areaIDs.size()), *m_hf, flagMergeThreshold);

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

		m_built = true;

		return true;
	}
}
