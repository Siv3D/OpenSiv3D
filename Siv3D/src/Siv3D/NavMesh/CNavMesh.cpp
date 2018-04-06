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
		Free();
	}
}
