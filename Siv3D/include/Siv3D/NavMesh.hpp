//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "NavMeshConfig.hpp"
# include "TriangleIndex.hpp"
# include "Polygon.hpp"

namespace s3d
{
	class NavMesh
	{
	public:

		NavMesh();

		~NavMesh();

		bool build(const Polygon& polygon, const NavMeshConfig& config = NavMeshConfig::Default());

		bool build(const Polygon& polygon, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = NavMeshConfig::Default());

		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = NavMeshConfig::Default());

		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		[[nodiscard]]
		Array<Vec2> query(const Vec2& start, const Vec2& end, const Array<std::pair<int, double>>& areaCosts = {}) const;

		[[nodiscard]]
		Array<Vec3> query(const Vec3& start, const Vec3& end, const Array<std::pair<int, double>>& areaCosts = {}) const;
	
	private:

		class NavMeshDetail;

		std::shared_ptr<NavMeshDetail> pImpl;
	};
}
