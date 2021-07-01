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

		virtual void init() = 0;

		virtual Mesh::IDType create(const MeshData& meshData) = 0;

		virtual void release(Mesh::IDType handleID) = 0;

		virtual size_t getIndexCount(Mesh::IDType handleID) = 0;

		virtual void bindMeshToContext(Mesh::IDType handleID) = 0;
	};
}
