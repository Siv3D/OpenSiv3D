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
# include <Siv3D/Common.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "GLES3Mesh.hpp"

namespace s3d
{
	class CMesh_GLES3 final : public ISiv3DMesh
	{
	public:

		CMesh_GLES3();

		~CMesh_GLES3() override;

		void init() override;

		Mesh::IDType create(const Array<Vertex3D>& vertices, const Array<Vertex3D::IndexType>& indices) override;

		void release(Mesh::IDType handleID) override;

		size_t getIndexCount(Mesh::IDType handleID) override;

		void bindMeshToContext(Mesh::IDType handleID) override;

	private:

		// Mesh の管理
		AssetHandleManager<Mesh::IDType, GLES3Mesh> m_meshes{ U"Mesh" };
	};
}
