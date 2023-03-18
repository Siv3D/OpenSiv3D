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
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Renderer3D/Renderer3DCommon.hpp>
# include <Siv3D/Renderer3D/VertexLine3D.hpp>
# include "GLES3Renderer3DCommand.hpp"

namespace s3d
{
	class GLES3Line3DBatch
	{
	private:

		struct BatchBufferPos
		{
			VertexLine3D::IndexType vertexPos = 0;

			uint32 indexPos = 0;

			void advance(VertexLine3D::IndexType vertexSize, uint32 indexSize) noexcept
			{
				vertexPos += vertexSize;
				indexPos += indexSize;
			}
		};

		GLuint m_vao = 0;

		GLuint m_vertexBuffer = 0;
		uint32 m_vertexBufferWritePos = 0;

		GLuint m_indexBuffer = 0;
		uint32 m_indexBufferWritePos = 0;

		Array<VertexLine3D> m_vertexArray;
		uint32 m_vertexArrayWritePos = 0;

		Array<VertexLine3D::IndexType> m_indexArray;
		uint32 m_indexArrayWritePos = 0;

		Array<BatchBufferPos> m_batches;

		static constexpr uint32 InitialVertexArraySize	= 4096;			// 4,096
		static constexpr uint32 InitialIndexArraySize	= (4096 * 8);	// 32,768

		static constexpr uint32 MaxVertexArraySize		= (65536 * 64); // 4,194,304
		static constexpr uint32 MaxIndexArraySize		= (65536 * 64); // 4,194,304

		static constexpr uint32 VertexBufferSize		= 65536;				// 65,536
		static constexpr uint32 IndexBufferSize			= VertexBufferSize;		// 65,536

		void advanceArrayWritePos(VertexLine3D::IndexType vertexSize, uint32 indexSize) noexcept;

	public:

		GLES3Line3DBatch();

		~GLES3Line3DBatch();

		[[nodiscard]]
		bool init();

		[[nodiscard]]
		VertexLine3DBufferPointer requestBuffer(VertexLine3D::IndexType vertexSize, uint32 indexSize, GLES3Renderer3DCommandManager& commandManager);

		[[nodiscard]]
		size_t num_batches() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		void reset();

		void setBuffers();

		[[nodiscard]]
		BatchInfoLine3D updateBuffers(size_t batchIndex);
	};
}
