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

# include "CMesh_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CMesh_GL4::CMesh_GL4()
	{
		// do nothing
	}

	CMesh_GL4::~CMesh_GL4()
	{
		LOG_SCOPED_TRACE(U"CMesh_GL4::~CMesh_GL4()");

		m_meshes.destroy();
	}

	void CMesh_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CMesh_D3D11::init()");

		// null Mesh を管理に登録
		{
			// null Mesh を作成
			auto nullMesh = std::make_unique<GL4Mesh>(MeshData::TwoSidedPlane(Float3{ 0,0,0 }, Float2{ 16.0f, 16.0f }));

			if (not nullMesh->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null Mesh initialization failed" };
			}

			// 管理に登録
			m_meshes.setNullData(std::move(nullMesh));
		}
	}

	Mesh::IDType CMesh_GL4::create(const MeshData& meshData)
	{
		if ((not meshData.vertices) || (not meshData.indices))
		{
			return Mesh::IDType::NullAsset();
		}

		auto mesh = std::make_unique<GL4Mesh>(meshData);

		if (not mesh->isInitialized())
		{
			return Mesh::IDType::NullAsset();
		}

		const String info = U"(type: Default, vertex count:{0}, triangle count: {1})"_fmt(meshData.vertices.size(), meshData.indices.size());
		return m_meshes.add(std::move(mesh), info);
	}

	void CMesh_GL4::release(const Mesh::IDType handleID)
	{
		m_meshes.erase(handleID);
	}

	size_t CMesh_GL4::getIndexCount(const Mesh::IDType handleID)
	{
		return m_meshes[handleID]->getIndexCount();
	}

	void CMesh_GL4::bindMeshToContext(const Mesh::IDType handleID)
	{
		m_meshes[handleID]->bindToContext();
	}
}
