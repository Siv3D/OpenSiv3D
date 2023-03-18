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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "D3D11Mesh.hpp"

namespace s3d
{
	class CMesh_D3D11 final : public ISiv3DMesh
	{
	public:

		CMesh_D3D11();

		~CMesh_D3D11() override;

		void init() override;

		Mesh::IDType create(const MeshData& meshData) override;

		Mesh::IDType createDynamic(size_t vertexCount, size_t triangleCount) override;

		Mesh::IDType createDynamic(const MeshData& meshData) override;

		void release(Mesh::IDType handleID) override;

		size_t getVertexCount(Mesh::IDType handleID) override;

		size_t getIndexCount(Mesh::IDType handleID) override;

		Sphere getBoundingSphere(Mesh::IDType handleID) override;

		Box getBoundingBox(Mesh::IDType handleID) override;

		bool fill(Mesh::IDType handleID, const MeshData& meshData) override;

		bool fill(Mesh::IDType handleID, size_t offset, const Vertex3D* vertices, size_t count) override;

		bool fill(Mesh::IDType handleID, const Array<TriangleIndex32>& indices) override;

		void bindMeshToContext(Mesh::IDType handleID) override;

	private:

		CRenderer_D3D11* pRenderer = nullptr;

		// device のコピー
		ID3D11Device* m_device = nullptr;

		// context のコピー
		ID3D11DeviceContext* m_context = nullptr;

		// Mesh の管理
		AssetHandleManager<Mesh::IDType, D3D11Mesh> m_meshes{ U"Mesh" };
	};
}
