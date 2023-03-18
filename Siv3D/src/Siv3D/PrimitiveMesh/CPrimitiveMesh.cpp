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

# include "CPrimitiveMesh.hpp"
# include <Siv3D/MeshData.hpp>
# include <Siv3D/Box.hpp>
# include <Siv3D/Sphere.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CPrimitiveMesh::CPrimitiveMesh() {}

	CPrimitiveMesh::~CPrimitiveMesh()
	{
		LOG_SCOPED_TRACE(U"CPrimitiveMesh::~CPrimitiveMesh()");
	}

	void CPrimitiveMesh::init()
	{
		LOG_SCOPED_TRACE(U"CPrimitiveMesh::init()");

		m_meshes.reserve(7);
		m_meshes << Mesh{ MeshData::OneSidedPlane({0,0,0}, {1.0f,1.0f}) };
		m_meshes << Mesh{ MeshData::TwoSidedPlane({0,0,0}, {1.0f,1.0f}) };
		m_meshes << Mesh{ MeshData::Box({0,0,0}, {1,1,1}) };
		m_meshes << Mesh{ MeshData::Sphere({0,0,0}, 1.0, 20) };
		m_meshes << Mesh{ MeshData::Disc({0,0,0}, 1.0, 40) };
		m_meshes << Mesh{ MeshData::Cylinder({0,0,0}, 1.0, 1.0, 40) };
		m_meshes << Mesh{ MeshData::Cone({0,0,0}, 1.0, 1.0, 64) };
		m_meshes << Mesh{ MeshData::Hemisphere({0,0,0}, 1.0, 40, 20) };
	}

	const Mesh& CPrimitiveMesh::getMesh(const PrimitiveMeshType meshType) const noexcept
	{
		return m_meshes[FromEnum(meshType)];
	}
}
