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

# include <Siv3D/NavMesh.hpp>
# include "CNavMesh.hpp"

namespace s3d
{
	NavMesh::NavMesh()
	{

	}

	NavMesh::~NavMesh()
	{

	}

	bool NavMesh::build(const Array<Float3>& vertices, const Array<uint16>& indices, const uint8 areaID)
	{
		return build(vertices, indices, Array<uint8>(indices.size() / 3, areaID));
	}

	bool NavMesh::build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs)
	{
		pImpl = std::make_shared<CNavMesh>();

		return pImpl->build(vertices, indices, areaIDs);
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
