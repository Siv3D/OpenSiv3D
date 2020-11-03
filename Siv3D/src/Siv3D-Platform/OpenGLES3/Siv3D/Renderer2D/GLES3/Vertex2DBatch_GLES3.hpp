//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class Renderer2DCommand_GLES3;

	struct BatchInfo_GLES3
	{
		uint32 indexCount = 0;

		uint32 startIndexLocation = 0;

		uint32 baseVertexLocation = 0;
	};

	class Vertex2DBatch_GLES3
	{
	private:

		struct BatchBufferPos
		{
			uint16 vertexPos = 0;

			uint32 indexPos = 0;

			void advance(uint16 vertexSize, uint32 indexSize) noexcept
			{
				vertexPos += vertexSize;
				indexPos += indexSize;
			}
		};

		using IndexType = Vertex2D::IndexType;

		GLuint m_vao = 0;

		GLuint m_vertexBuffer = 0;
		uint32 m_vertexBufferWritePos = 0;

		GLuint m_indexBuffer = 0;
		uint32 m_indexBufferWritePos = 0;

		Array<Vertex2D> m_vertexArray;
		uint32 m_vertexArrayWritePos = 0;

		Array<IndexType> m_indexArray;
		uint32 m_indexArrayWritePos = 0;

		Array<BatchBufferPos> m_batches;

		static constexpr uint32 InitialVertexArraySize	= 4096;
		static constexpr uint32 InitialIndexArraySize	= (4096 * 8); // 32768

		static constexpr uint32 MaxVertexArraySize		= (65536 * 64); // 4,194,304
		static constexpr uint32 MaxIndexArraySize		= (65536 * 64); // 4,194,304

		static constexpr uint32 VertexBufferSize		= 65535;// 65535;
		static constexpr uint32 IndexBufferSize			= ((VertexBufferSize + 1) * 4); // 524,288

		void advanceArrayWritePos(uint16 vertexSize, uint32 indexSize) noexcept;

	public:

		Vertex2DBatch_GLES3();

		~Vertex2DBatch_GLES3();

		[[nodiscard]]
		bool init();

		[[nodiscard]]
		std::tuple<Vertex2D*, IndexType*, IndexType> requestBuffer(uint16 vertexSize, uint32 indexSize, Renderer2DCommand_GLES3& command);

		[[nodiscard]]
		size_t num_batches() const noexcept;

		void reset();

		[[nodiscard]]
		BatchInfo_GLES3 updateBuffers(size_t batchIndex);
	};
}
