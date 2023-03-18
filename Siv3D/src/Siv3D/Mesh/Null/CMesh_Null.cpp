//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CMesh_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CMesh_Null::CMesh_Null()
	{
		// do nothing
	}

	CMesh_Null::~CMesh_Null()
	{
		LOG_SCOPED_TRACE(U"CMesh_Null::~CMesh_Null()");
	}

	void CMesh_Null::init()
	{
		LOG_SCOPED_TRACE(U"CMesh_Null::init()");
	}

	Mesh::IDType CMesh_Null::create(const MeshData&)
	{
		return Mesh::IDType::NullAsset();
	}

	Mesh::IDType CMesh_Null::createDynamic(size_t, size_t)
	{
		return Mesh::IDType::NullAsset();
	}

	Mesh::IDType CMesh_Null::createDynamic(const MeshData&)
	{
		return Mesh::IDType::NullAsset();
	}

	void CMesh_Null::release(Mesh::IDType) {}
		
	size_t CMesh_Null::getVertexCount(Mesh::IDType)
	{
		return 0;
	}

	size_t CMesh_Null::getIndexCount(Mesh::IDType)
	{
		return 0;
	}

	Sphere CMesh_Null::getBoundingSphere(Mesh::IDType)
	{
		return Sphere{ 0.0 };
	}

	Box CMesh_Null::getBoundingBox(Mesh::IDType)
	{
		return Box{ 0.0 };
	}

	bool CMesh_Null::fill(Mesh::IDType, const MeshData&)
	{
		return false;
	}

	bool CMesh_Null::fill(Mesh::IDType, size_t, const Vertex3D*, size_t)
	{
		return false;
	}

	bool CMesh_Null::fill(Mesh::IDType, const Array<TriangleIndex32>&)
	{
		return false;
	}

	void CMesh_Null::bindMeshToContext(Mesh::IDType) {}
}
