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
# include <cfloat>
# include <Siv3D/NavMesh.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Triangle.hpp>
# include "../../ThirdParty/Recast/Recast.h"
# include "../../ThirdParty/Detour/DetourCommon.h"
# include "../../ThirdParty/Detour/DetourNavMesh.h"
# include "../../ThirdParty/Detour/DetourNavMeshBuilder.h"
# include "../../ThirdParty/Detour/DetourNavMeshQuery.h"

namespace s3d
{
	class NavMesh::CNavMesh
	{
	private:

		rcContext m_ctx;
		
		rcHeightfield* m_hf = nullptr;
		
		rcCompactHeightfield* m_chf = nullptr;
		
		rcContourSet* m_cset = nullptr;
		
		rcPolyMesh* m_mesh = nullptr;
		
		rcPolyMeshDetail* m_dmesh = nullptr;
		
		std::shared_ptr<dtNavMesh> m_navmesh;

		float m_bmin[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
		
		float m_bmax[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

		unsigned char* m_navData = nullptr;

		int32 m_navDataSize = 0;

		bool m_built = false;

		Array<Float3> m_vertices;

		Array<uint16> m_indices;

		Array<uint8> m_areaIDs;

		void updateAABB(const Float3& v);

		void destroy();

		void create();

		void reset();

		bool build(const NavMeshConfig& config);

	public:

		CNavMesh();

		~CNavMesh();

		bool build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config);

		Array<Vec3> query(const Float3& start, const Float3& end) const;
	};
}
