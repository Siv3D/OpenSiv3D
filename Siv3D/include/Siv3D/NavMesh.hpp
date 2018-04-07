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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "Triangle.hpp"

namespace s3d
{
	class NavMesh
	{
	private:

		class CNavMesh;

		std::shared_ptr<CNavMesh> pImpl;

	public:

		NavMesh();

		~NavMesh();

		bool build(const Array<Float3>& vertices, const Array<uint16>& indices, uint8 areaID = 1);

		bool build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs);

		Array<Vec3> query(const Vec3& start, const Vec3& end) const;
	};
}
