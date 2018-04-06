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

	void NavMesh::build(const Array<Triangle3D>& triangles, const uint8 areaID)
	{
		pImpl = std::make_shared<CNavMesh>();

		pImpl->build(triangles, areaID);
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
