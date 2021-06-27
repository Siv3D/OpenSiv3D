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
	
	Mesh::IDType CMesh_Null::create(const Array<Vertex3D>&, const Array<Vertex3D::IndexType>&)
	{
		return Mesh::IDType::NullAsset();
	}

	void CMesh_Null::release(Mesh::IDType) {}
	
	size_t CMesh_Null::getIndexCount(Mesh::IDType)
	{
		return 0;
	}

	void CMesh_Null::bindMeshToContext(Mesh::IDType) {}
}
