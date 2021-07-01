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
		explicit GL4Mesh(const MeshData& meshData);

		SIV3D_NODISCARD_CXX20
		GL4Mesh(const Array<Vertex3D>& vertices, const Array<TriangleIndex32>& indices);

		~GL4Mesh();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		uint32 getVertexCount() const noexcept;

		[[nodiscard]]
		uint32 getIndexCount() const noexcept;

		void bindToContext();

	private:

		GLuint m_vao = 0;
		
		GLuint m_vertexBuffer = 0;

		GLuint m_indexBuffer = 0;

		uint32 m_vertexCount = 0;

		uint32 m_indexCount = 0;

		uint32 m_vertexStride = 0;

		bool m_initialized = false;
	};
}
