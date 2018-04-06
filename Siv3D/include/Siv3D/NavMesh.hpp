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
	struct alignas(16) Triangle3D
	{
	S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct { Float4 p0, p1, p2; };
			struct { Float4 p[3]; };
		};
	
	S3D_DISABLE_MSVC_WARNINGS_POP()

		Triangle3D() = default;

		Triangle3D(const Float4& _p0, const Float4& _p1, const Float4& _p2)
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		Triangle3D(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2)
			: p0(_p0, 0.0f)
			, p1(_p1, 0.0f)
			, p2(_p2, 0.0f) {}
	};

	class NavMesh
	{
	private:

		class CNavMesh;

		std::shared_ptr<CNavMesh> pImpl;

	public:

		NavMesh();

		~NavMesh();

		void build(const Array<Triangle3D>& triangles, uint8 areaID = 1);

		Array<Vec3> query(const Vec3& start, const Vec3& end) const;
	};
}
