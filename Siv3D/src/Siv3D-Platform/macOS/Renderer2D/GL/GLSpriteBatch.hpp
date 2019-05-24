//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include "GLRenderer2DCommand.hpp"

namespace s3d
{
	using IndexType = Vertex2D::IndexType;
	
	struct BatchInfo
	{
		uint32 indexCount = 0;
		
		uint32 startIndexLocation = 0;
		
		uint32 baseVertexLocation = 0;
	};
	
	class GLSpriteBatch
	{
	private:
	
		struct BatchBufferPos
		{
			uint16 vertexPos = 0;
			
			uint32 indexPos = 0;
		};
		
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
		static constexpr uint32 InitialIndexArraySize	= 4096 * 8; // 32768
		
		static constexpr uint32 MaxVertexArraySize		= 65536 * 64; // 4,194,304
		static constexpr uint32 MaxIndexArraySize		= 65536 * 64; // 4,194,304
		
		static constexpr uint32 VertexBufferSize		= 65536;// 65536;
		static constexpr uint32 IndexBufferSize			= VertexBufferSize * 4; // 524,288
		
	public:
		
		GLSpriteBatch();
		
		~GLSpriteBatch();
		
		[[nodiscard]] bool init();
		
		[[nodiscard]] std::tuple<Vertex2D*, IndexType*, IndexType> getBuffer(const uint16 vertexSize, const uint32 indexSize, GLRenderer2DCommand& command);
		
		[[nodiscard]] size_t num_batches() const noexcept;
		
		void reset();
		
		//void setBuffers();
		
		[[nodiscard]] BatchInfo updateBuffers(size_t batchIndex);
	};
}
