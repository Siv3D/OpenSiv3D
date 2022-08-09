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

# include <Siv3D/NavMesh.hpp>
# include "NavMeshDetail.hpp"

namespace s3d
{
	NavMesh::NavMesh()
		: pImpl{ std::make_shared<NavMeshDetail>() }
	{

	}

	NavMesh::NavMesh(const Polygon& polygon, const NavMeshConfig& config)
		: NavMesh{}
	{
		build(polygon, config);
	}

	NavMesh::NavMesh(const Polygon& polygon, const Array<uint8>& areaIDs, const NavMeshConfig& config)
		: NavMesh{}
	{
		build(polygon, areaIDs, config);
	}

	NavMesh::NavMesh(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config)
		: NavMesh{}
	{
		build(vertices, indices, config);
	}

	NavMesh::NavMesh(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config)
		: NavMesh{}
	{
		build(vertices, indices, areaIDs, config);
	}

	NavMesh::NavMesh(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config)
		: NavMesh{}
	{
		build(vertices, indices, config);
	}

	NavMesh::NavMesh(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config)
		: NavMesh{}
	{
		build(vertices, indices, areaIDs, config);
	}

	NavMesh::~NavMesh()
	{

	}

	bool NavMesh::isValid() const noexcept
	{
		return pImpl->isValid();
	}

	NavMesh::operator bool() const noexcept
	{
		return isValid();
	}

	bool NavMesh::build(const Polygon& polygon, const NavMeshConfig& config)
	{
		return pImpl->build(polygon.vertices(), polygon.indices(), Array<uint8>(polygon.indices().size(), 1), config);
	}

	bool NavMesh::build(const Polygon& polygon, const Array<uint8>& areaIDs, const NavMeshConfig& config)
	{
		return pImpl->build(polygon.vertices(), polygon.indices(), areaIDs, config);
	}

	bool NavMesh::build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config)
	{
		return pImpl->build(vertices, indices, Array<uint8>(indices.size(), 1), config);
	}

	bool NavMesh::build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config)
	{
		return pImpl->build(vertices, indices, areaIDs, config);
	}

	bool NavMesh::build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config)
	{
		return pImpl->build(vertices, indices, Array<uint8>(indices.size(), 1), config);
	}

	bool NavMesh::build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config)
	{
		return pImpl->build(vertices, indices, areaIDs, config);
	}

	Array<Vec2> NavMesh::query(const Vec2& start, const Vec2& end, const Array<std::pair<int32, double>>& areaCosts) const
	{
		Array<Vec2> dst;
		
		pImpl->query(start, end, areaCosts, dst);
		
		return dst;
	}

	void NavMesh::query(const Vec2& start, const Vec2& end, Array<Vec2>& dst, const Array<std::pair<int32, double>>& areaCosts) const
	{
		pImpl->query(start, end, areaCosts, dst);
	}

	Array<Vec3> NavMesh::query(const Vec3& start, const Vec3& end, const Array<std::pair<int32, double>>& areaCosts) const
	{
		Array<Vec3> dst;

		pImpl->query(start, end, areaCosts, dst);

		return dst;
	}

	void NavMesh::query(const Vec3& start, const Vec3& end, Array<Vec3>& dst, const Array<std::pair<int32, double>>& areaCosts) const
	{
		pImpl->query(start, end, areaCosts, dst);
	}
}
