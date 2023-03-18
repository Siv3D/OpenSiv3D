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
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex3D.hpp>
# include <Siv3D/TriangleIndex.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class GL4Mesh
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit GL4Mesh(const MeshData& meshData, bool isDynamic);

		SIV3D_NODISCARD_CXX20
		GL4Mesh(size_t vertexCount, size_t triangleCount);

		SIV3D_NODISCARD_CXX20
		GL4Mesh(const Array<Vertex3D>& vertices, const Array<TriangleIndex32>& indices, bool isDynamic);

		~GL4Mesh();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		uint32 getVertexCount() const noexcept;

		[[nodiscard]]
		uint32 getIndexCount() const noexcept;

		[[nodiscard]]
		const Sphere& getBoundingSphere() const noexcept;

		[[nodiscard]]
		const Box& getBoundingBox() const noexcept;

		bool fill(const MeshData& meshData);

		bool fill(size_t offset, const Vertex3D* vertices, size_t count);

		bool fill(const Array<TriangleIndex32>& indices);

		void bindToContext();

	private:

		GLuint m_vao = 0;
		
		GLuint m_vertexBuffer = 0;

		GLuint m_indexBuffer = 0;

		uint32 m_vertexCount = 0;

		uint32 m_indexCount = 0;

		uint32 m_vertexStride = 0;

		Sphere m_boundingSphere{ 0.0 };

		Box m_boundingBox{ 0.0 };

		bool m_isDynamic = false;

		bool m_initialized = false;
	};
}
