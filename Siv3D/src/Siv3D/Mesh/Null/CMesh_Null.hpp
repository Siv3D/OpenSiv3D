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

namespace s3d
{
	class CMesh_Null final : public ISiv3DMesh
	{
	public:

		CMesh_Null();

		~CMesh_Null() override;

		virtual void init() override;

		Mesh::IDType create(const MeshData& meshData) override;

		void release(Mesh::IDType handleID) override;

		size_t getVertexCount(Mesh::IDType handleID) override;

		size_t getIndexCount(Mesh::IDType handleID) override;

		void bindMeshToContext(Mesh::IDType handleID) override;

	private:

	};
}
