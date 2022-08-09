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
# include <cfloat>
# include <Siv3D/NavMesh.hpp>
# include <RecastDetour/Recast.h>
# include <RecastDetour/DetourCommon.h>
# include <RecastDetour/DetourNavMesh.h>
# include <RecastDetour/DetourNavMeshBuilder.h>
# include <RecastDetour/DetourNavMeshQuery.h>

namespace s3d
{
	struct NavMeshAABB
	{
		float bmin[3] = { FLT_MAX, FLT_MAX, FLT_MAX };

		float bmax[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
	};

	class NavMesh::NavMeshDetail
	{
	public:

		NavMeshDetail();

		~NavMeshDetail();

		bool isValid() const noexcept;

		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config);

		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config);

		void query(const Float2& start, const Float2& end, const Array<std::pair<int32, double>>& areaCosts, Array<Vec2>& dst) const;

		void query(const Float3& start, const Float3& end, const Array<std::pair<int32, double>>& areaCosts, Array<Vec3>& dst) const;

	private:

		static constexpr int32 MaxVertices = 8192;

		static constexpr int32 PolygonBufferSize = 8192;

		struct Data
		{
			rcContext ctx;

			rcHeightfield* hf = nullptr;

			rcCompactHeightfield* chf = nullptr;

			rcContourSet* cset = nullptr;

			rcPolyMesh* mesh = nullptr;

			rcPolyMeshDetail* dmesh = nullptr;

			std::shared_ptr<dtNavMesh> navmesh;

			dtNavMeshQuery navmeshQuery;

		} m_data;

		unsigned char* m_navData = nullptr;

		int32 m_navDataSize = 0;

		bool m_built = false;

		mutable Array<Float3> m_buffer;

		mutable Array<dtPolyRef> m_polygonBuffer;

		bool build(const NavMeshConfig& config, const NavMeshAABB& aabb,
			const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs);

		void init();

		void release();
	};
}
