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

# include <Siv3D/EngineLog.hpp>
# include "NavMeshDetail.hpp"

namespace s3d
{
	NavMesh::NavMeshDetail::NavMeshDetail()
	{
	
	}

	NavMesh::NavMeshDetail::~NavMeshDetail()
	{
		destroy();
	}

	bool NavMesh::NavMeshDetail::build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config)
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
			build(config);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	Array<Vec3> NavMesh::NavMeshDetail::query(const Float3& start, const Float3& end) const
	{
		if (!m_built)
		{
			return{};
		}

		Float3 extent(2.0f, 4.0f, 2.0f);

		dtNavMeshQuery navmeshquery;

		if (dtStatusFailed(navmeshquery.init(m_navmesh.get(), 2048)))
		{
			return{};
		}

		dtPolyRef startpoly, endpoly;
		dtQueryFilter filter;

		if (dtStatusFailed(navmeshquery.findNearestPoly(&start.x, &extent.x, &filter, &startpoly, 0)))
		{
			return{};
		}

		if (dtStatusFailed(navmeshquery.findNearestPoly(&end.x, &extent.x, &filter, &endpoly, 0)))
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

		if (dtStatus status = navmeshquery.findPath(startpoly, endpoly, &start.x, &end.x, &filter, polys.data(), &npolys, buffersize); dtStatusFailed(status))
		{
			return{};
		}

		if (npolys <= 0)
		{
			return{};
		}

		float end2[3] = { end.x, end.y, end.z };

		if (polys[npolys - 1] != endpoly)
		{
			bool posOverPoly;
			navmeshquery.closestPointOnPoly(polys[npolys - 1], &end.x, end2, &posOverPoly);
		}

		constexpr int32 maxvertices = 8192;

		Array<Float3> buffer(maxvertices);

		int32 nvertices = 0;

		navmeshquery.findStraightPath(&start.x, end2, polys.data(), npolys, &buffer[0].x, 0, 0, &nvertices, maxvertices);

		Array<Vec3> vertices(nvertices);

		for (int32 i = 0; i < nvertices; ++i)
		{
			vertices[i] = buffer[i];
		}

		return vertices;
	}

	void NavMesh::NavMeshDetail::updateAABB(const Float3& v)
	{
		m_bmin[0] = std::min(m_bmin[0], v.x);
		m_bmin[1] = std::min(m_bmin[1], v.y);
		m_bmin[2] = std::min(m_bmin[2], v.z);

		m_bmax[0] = std::max(m_bmax[0], v.x);
		m_bmax[1] = std::max(m_bmax[1], v.y);
		m_bmax[2] = std::max(m_bmax[2], v.z);
	}

	void NavMesh::NavMeshDetail::destroy()
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

	void NavMesh::NavMeshDetail::create()
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

	void NavMesh::NavMeshDetail::reset()
	{
		destroy();

		create();
	}

	bool NavMesh::NavMeshDetail::build(const NavMeshConfig& config)
	{
		const float cellSize		= static_cast<float>(config.cellSize);
		const float cellHeight		= static_cast<float>(config.cellHeight);
		const float agentMaxSlope	= static_cast<float>(config.agentMaxSlope);
		const float agentHeight		= static_cast<float>(config.agentHeight);
		const float agentMaxClimb	= static_cast<float>(config.agentMaxClimb);
		const float agentRadius		= static_cast<float>(config.agentRadius);

		constexpr float edgeMaxLen				= 12.0f;
		constexpr float detailSampleDist		= 6.0f;
		constexpr float detailSampleMaxError	= 1.0f;
		constexpr float regionMinSize			= 8.0f;
		constexpr float regionMergeSize			= 20.0f;

		rcConfig cfg
		{
			.cs						= cellSize,
			.ch						= cellHeight,
			.walkableSlopeAngle		= agentMaxSlope,
			.walkableHeight			= static_cast<int32>(std::ceil(agentHeight / cellHeight)),
			.walkableClimb			= static_cast<int32>(std::floor(agentMaxClimb / cellHeight)),
			.walkableRadius			= static_cast<int32>(std::ceil(agentRadius / cellSize)),
			.maxEdgeLen				= static_cast<int32>(edgeMaxLen / cellSize),
			.maxSimplificationError	= 1.3f,
			.minRegionArea			= static_cast<int32>(regionMinSize * regionMinSize),
			.mergeRegionArea		= static_cast<int32>(regionMergeSize * regionMergeSize),
			.maxVertsPerPoly		= 6,
			.detailSampleDist		= (detailSampleDist < 0.9f) ? 0 : cellSize * detailSampleDist,
			.detailSampleMaxError	= cellHeight * detailSampleMaxError
		};

		rcVcopy(cfg.bmin, m_bmin);
		rcVcopy(cfg.bmax, m_bmax);
		cfg.bmin[0] -= cfg.borderSize * cellSize;
		cfg.bmin[2] -= cfg.borderSize * cellSize;
		cfg.bmax[0] += cfg.borderSize * cellSize;
		cfg.bmax[2] += cfg.borderSize * cellSize;

		rcCalcGridSize(cfg.bmin, cfg.bmax, cellSize, &cfg.width, &cfg.height);

		//if (cfg.maxVertsPerPoly > DT_VERTS_PER_POLYGON)
		//{
		//	return false;
		//}

		cfg.width	= static_cast<int32>((cfg.bmax[0] - cfg.bmin[0]) / cellSize + 1);
		cfg.height	= static_cast<int32>((cfg.bmax[2] - cfg.bmin[2]) / cellSize + 1);

		reset();

		if (!rcCreateHeightfield(&m_ctx, *m_hf, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs, cfg.ch))
		{
			return false;
		}

		const int32 flagMergeThreshold = 0;

		rcRasterizeTriangles(&m_ctx, &m_vertices[0].x, static_cast<int32>(m_vertices.size()),
			m_indices.data(), m_areaIDs.data(), static_cast<int32>(m_areaIDs.size()), *m_hf, flagMergeThreshold);

		rcFilterLowHangingWalkableObstacles(&m_ctx, cfg.walkableClimb, *m_hf);
		rcFilterLedgeSpans(&m_ctx, cfg.walkableHeight, cfg.walkableClimb, *m_hf);
		rcFilterWalkableLowHeightSpans(&m_ctx, cfg.walkableHeight, *m_hf);

		if (!rcBuildCompactHeightfield(&m_ctx, cfg.walkableHeight, cfg.walkableClimb, *m_hf, *m_chf))
		{
			return false;
		}

		if (!rcErodeWalkableArea(&m_ctx, cfg.walkableRadius, *m_chf))
		{
			return false;
		}

		if (!rcBuildDistanceField(&m_ctx, *m_chf))
		{
			return false;
		}

		if (!rcBuildRegions(&m_ctx, *m_chf, 0 /* border size */, cfg.minRegionArea, cfg.mergeRegionArea))
		{
			return false;
		}

		if (!rcBuildContours(&m_ctx, *m_chf, cfg.maxSimplificationError, cfg.maxEdgeLen, *m_cset))
		{
			return false;
		}

		if (!rcBuildPolyMesh(&m_ctx, *m_cset, cfg.maxVertsPerPoly, *m_mesh))
		{
			return false;
		}

		if (!rcBuildPolyMeshDetail(&m_ctx, *m_mesh, *m_chf, cfg.detailSampleDist, cfg.detailSampleMaxError, *m_dmesh))
		{
			return false;
		}

		for (int32 i = 0; i < m_mesh->npolys; ++i)
		{
			m_mesh->flags[i] = 1;
		}

		dtNavMeshCreateParams params;
		memset(&params, 0, sizeof(params));

		params.verts		= m_mesh->verts;
		params.vertCount	= m_mesh->nverts;
		params.polys		= m_mesh->polys;
		params.polyAreas	= m_mesh->areas;
		params.polyFlags	= m_mesh->flags;
		params.polyCount	= m_mesh->npolys;
		params.nvp			= m_mesh->nvp;

		params.detailMeshes		= m_dmesh->meshes;
		params.detailVerts		= m_dmesh->verts;
		params.detailVertsCount = m_dmesh->nverts;
		params.detailTris		= m_dmesh->tris;
		params.detailTriCount	= m_dmesh->ntris;

		params.walkableHeight	= static_cast<float>(cfg.walkableHeight);
		params.walkableClimb	= static_cast<float>(cfg.walkableClimb);
		rcVcopy(params.bmin, m_mesh->bmin);
		rcVcopy(params.bmax, m_mesh->bmax);
		params.cs = cfg.cs;
		params.ch = cfg.ch;
		params.buildBvTree = true;

		if (!dtCreateNavMeshData(&params, &m_navData, &m_navDataSize))
		{
			return false;
		}

		m_navmesh->init(m_navData, m_navDataSize, DT_TILE_FREE_DATA);

		m_built = true;

		return true;
	}
}
