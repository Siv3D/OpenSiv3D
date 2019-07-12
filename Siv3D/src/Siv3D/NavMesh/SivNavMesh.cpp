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

# include <Siv3D/NavMesh.hpp>
# include "NavMeshDetail.hpp"

namespace s3d
{
	NavMesh::NavMesh()
	{

	}

	NavMesh::~NavMesh()
	{

	}

	bool NavMesh::build(const Array<Float3>& vertices, const Array<uint16>& indices, const NavMeshConfig& config)
	{
		return build(vertices, indices, Array<uint8>(indices.size() / 3, 1), config);
	}

	bool NavMesh::build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config)
	{
		pImpl = std::make_shared<NavMeshDetail>();

		return pImpl->build(vertices, indices, areaIDs, config);
	}

	Array<Vec3> NavMesh::query(const Vec3& start, const Vec3& end) const
	{
		if (!pImpl)
		{
			return{};
		}

		return pImpl->query(start, end);
	}
}
