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

# include <Siv3D/DynamicMesh.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	DynamicMesh::DynamicMesh(const size_t vertexCount, const size_t triangleCount)
		: Mesh{ Mesh::Dynamic{}, vertexCount, triangleCount } {}

	DynamicMesh::DynamicMesh(const MeshData& meshData)
		: Mesh{ Mesh::Dynamic{}, meshData } {}

	bool DynamicMesh::fill(const MeshData& meshData)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Mesh)->fill(m_handle->id(), meshData);
	}

	bool DynamicMesh::fill(const Array<Vertex3D>& vertices)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Mesh)->fill(m_handle->id(), 0, vertices.data(), vertices.size());
	}

	bool DynamicMesh::fillSubRange(const size_t offset, const Array<Vertex3D>& vertices)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Mesh)->fill(m_handle->id(), offset, vertices.data(), vertices.size());
	}

	bool DynamicMesh::fillSubRange(const size_t offset, const Vertex3D* vertices, const size_t count)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Mesh)->fill(m_handle->id(), offset, vertices, count);
	}

	bool DynamicMesh::fill(const Array<TriangleIndex32>& indices)
	{
		if (isEmpty())
		{
			return false;
		}

		return SIV3D_ENGINE(Mesh)->fill(m_handle->id(), indices);
	}

	void DynamicMesh::swap(DynamicMesh& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
