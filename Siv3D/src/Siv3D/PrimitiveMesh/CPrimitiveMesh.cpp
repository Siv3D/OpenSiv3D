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

# include "CPrimitiveMesh.hpp"
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

		m_meshes.reserve(9);
		{
			Array<Vertex3D> vertices =
			{
				{ .pos = { -0.5f, 0.0f,  0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
				{ .pos = {  0.5f, 0.0f,  0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
				{ .pos = { -0.5f, 0.0f, -0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
				{ .pos = {  0.5f, 0.0f, -0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
			};
			m_meshes << Mesh{ vertices, { 0,1,2, 2,1,3 } };
		}
		{
			Array<Vertex3D> vertices =
			{
				{ .pos = { -0.5f, 0.0f,  0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
				{ .pos = {  0.5f, 0.0f,  0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
				{ .pos = { -0.5f, 0.0f, -0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
				{ .pos = {  0.5f, 0.0f, -0.5f }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },

				{ .pos = {  0.5f, 0.0f,  0.5f }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
				{ .pos = { -0.5f, 0.0f,  0.5f }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
				{ .pos = {  0.5f, 0.0f, -0.5f }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
				{ .pos = { -0.5f, 0.0f, -0.5f }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },		
			};
			m_meshes << Mesh{ vertices, { 0,1,2, 2,1,3, 4,5,6, 6,5,7 } };
		}
		m_meshes << Mesh{ Box{ {0,0,0}, {1,1,1} } };
		m_meshes << Mesh{ Sphere{{0,0,0}, 1}, 24 };
		m_meshes << Mesh{};
		m_meshes << Mesh{};
		m_meshes << Mesh{};
		m_meshes << Mesh{};
		m_meshes << Mesh{};
	}

	const Mesh& CPrimitiveMesh::getMesh(const PrimitiveMeshType meshType) const noexcept
	{
		return m_meshes[FromEnum(meshType)];
	}
}
