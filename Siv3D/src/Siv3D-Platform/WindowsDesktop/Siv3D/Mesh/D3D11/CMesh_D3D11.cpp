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

# include "CMesh_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CMesh_D3D11::CMesh_D3D11()
	{
		// do nothing
	}

	CMesh_D3D11::~CMesh_D3D11()
	{
		LOG_SCOPED_TRACE(U"CMesh_D3D11::~CMesh_D3D11()");

		m_meshes.destroy();
	}

	void CMesh_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CMesh_D3D11::init()");

		pRenderer	= static_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer));
		m_device	= pRenderer->getDevice();
		m_context	= pRenderer->getContext();

		// null Mesh を管理に登録
		{
			// null Mesh を作成
			auto nullMesh = std::make_unique<D3D11Mesh>(m_device, MeshData::TwoSidedPlane(Float3{ 0,0,0 }, Float2{ 16.0f, 16.0f }), false);

			if (not nullMesh->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null Mesh initialization failed" };
			}

			// 管理に登録
			m_meshes.setNullData(std::move(nullMesh));
		}
	}

	Mesh::IDType CMesh_D3D11::create(const MeshData& meshData)
	{
		if ((not meshData.vertices) || (not meshData.indices))
		{
			return Mesh::IDType::NullAsset();
		}

		auto mesh = std::make_unique<D3D11Mesh>(m_device, meshData, false);

		if (not mesh->isInitialized())
		{
			return Mesh::IDType::NullAsset();
		}

		const String info = U"(type: Default, vertex count:{0}, triangle count: {1})"_fmt(meshData.vertices.size(), meshData.indices.size());
		return m_meshes.add(std::move(mesh), info);
	}

	Mesh::IDType CMesh_D3D11::createDynamic(const size_t vertexCount, const size_t triangleCount)
	{
		if ((vertexCount == 0) || (triangleCount == 0))
		{
			return Mesh::IDType::NullAsset();
		}

		auto mesh = std::make_unique<D3D11Mesh>(m_device, vertexCount, triangleCount);

		if (not mesh->isInitialized())
		{
			return Mesh::IDType::NullAsset();
		}

		const String info = U"(type: Dynamic, vertex count:{0}, triangle count: {1})"_fmt(vertexCount, triangleCount);
		return m_meshes.add(std::move(mesh), info);
	}

	Mesh::IDType CMesh_D3D11::createDynamic(const MeshData& meshData)
	{
		if ((not meshData.vertices) || (not meshData.indices))
		{
			return Mesh::IDType::NullAsset();
		}

		auto mesh = std::make_unique<D3D11Mesh>(m_device, meshData, true);

		if (not mesh->isInitialized())
		{
			return Mesh::IDType::NullAsset();
		}

		const String info = U"(type: Dynamic, vertex count:{0}, triangle count: {1})"_fmt(meshData.vertices.size(), meshData.indices.size());
		return m_meshes.add(std::move(mesh), info);
	}

	void CMesh_D3D11::release(const Mesh::IDType handleID)
	{
		m_meshes.erase(handleID);
	}

	size_t CMesh_D3D11::getVertexCount(const Mesh::IDType handleID)
	{
		return m_meshes[handleID]->getVertexCount();
	}

	size_t CMesh_D3D11::getIndexCount(const Mesh::IDType handleID)
	{
		return m_meshes[handleID]->getIndexCount();
	}

	Sphere CMesh_D3D11::getBoundingSphere(const Mesh::IDType handleID)
	{
		return m_meshes[handleID]->getBoundingSphere();
	}

	Box CMesh_D3D11::getBoundingBox(const Mesh::IDType handleID)
	{
		return m_meshes[handleID]->getBoundingBox();
	}

	bool CMesh_D3D11::fill(const Mesh::IDType handleID, const MeshData& meshData)
	{
		return m_meshes[handleID]->fill(m_context, meshData);
	}

	bool CMesh_D3D11::fill(const Mesh::IDType handleID, const size_t offset, const Vertex3D* vertices, const size_t count)
	{
		return m_meshes[handleID]->fill(m_context, offset, vertices, count);
	}

	bool CMesh_D3D11::fill(const Mesh::IDType handleID, const Array<TriangleIndex32>& indices)
	{
		return m_meshes[handleID]->fill(m_context, indices);
	}

	void CMesh_D3D11::bindMeshToContext(const Mesh::IDType handleID)
	{
		m_meshes[handleID]->bindToContext(m_context);
	}
}
