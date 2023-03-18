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
# include <Siv3D/Mesh.hpp>
# include <Siv3D/MeshData.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DMesh
	{
	public:

		static ISiv3DMesh* Create();

		virtual ~ISiv3DMesh() = default;

		virtual void init() = 0;

		virtual Mesh::IDType create(const MeshData& meshData) = 0;

		virtual Mesh::IDType createDynamic(size_t vertexCount, size_t triangleCount) = 0;

		virtual Mesh::IDType createDynamic(const MeshData& meshData) = 0;

		virtual void release(Mesh::IDType handleID) = 0;

		virtual size_t getVertexCount(Mesh::IDType handleID) = 0;

		virtual size_t getIndexCount(Mesh::IDType handleID) = 0;

		virtual Sphere getBoundingSphere(Mesh::IDType handleID) = 0;

		virtual Box getBoundingBox(Mesh::IDType handleID) = 0;

		virtual bool fill(Mesh::IDType handleID, const MeshData& meshData) = 0;

		virtual bool fill(Mesh::IDType handleID, size_t offset, const Vertex3D* vertices, size_t count) = 0;

		virtual bool fill(Mesh::IDType handleID, const Array<TriangleIndex32>& indices) = 0;

		virtual void bindMeshToContext(Mesh::IDType handleID) = 0;
	};
}
