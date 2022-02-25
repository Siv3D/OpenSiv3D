//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Mesh.hpp"
# include "MeshData.hpp"

namespace s3d
{
	class DynamicMesh : public Mesh
	{
	public:

		SIV3D_NODISCARD_CXX20
		DynamicMesh() = default;

		SIV3D_NODISCARD_CXX20
		DynamicMesh(size_t vertexCount, size_t triangleCount);

		SIV3D_NODISCARD_CXX20
		explicit DynamicMesh(const MeshData& meshData);

		bool fill(const MeshData& meshData);

		bool fill(const Array<Vertex3D>& vertices);

		bool fillSubRange(size_t offset, const Array<Vertex3D>& vertices);

		bool fillSubRange(size_t offset, const Vertex3D* vertices, size_t count);

		bool fill(const Array<TriangleIndex32>& indices);

		void swap(DynamicMesh& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::DynamicMesh& a, s3d::DynamicMesh& b) noexcept;

# include "detail/DynamicMesh.ipp"
