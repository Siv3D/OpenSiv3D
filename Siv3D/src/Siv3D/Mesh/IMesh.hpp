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
# include <Siv3D/Mesh.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DMesh
	{
	public:

		static ISiv3DMesh* Create();

		virtual ~ISiv3DMesh() = default;

		virtual Mesh::IDType create(const Array<Vertex3D>& vertices, const Array<Vertex3D::IndexType>& indices) { return Mesh::IDType::NullAsset(); }
	
		virtual void release(Mesh::IDType handleID) {}

		virtual size_t getIndexCount(Mesh::IDType handleID) { return 0; }

		virtual void bindMeshToContext(Mesh::IDType handleID) {}
	};
}
