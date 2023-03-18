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
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Renderer2D/Vertex2DBufferPointer.hpp>
# include <Siv3D/Renderer2D/Renderer2DCommon.hpp>
# include "WebGPURenderer2DCommand.hpp"

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUVertex2DBatch
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

		wgpu::Buffer m_vertexBuffer = nullptr;
		uint32 m_vertexBufferWritePos = 0;

		wgpu::Buffer m_indexBuffer = nullptr;
		uint32 m_indexBufferWritePos = 0;

		Array<Vertex2D> m_vertexArray;
		uint32 m_vertexArrayWritePos = 0;

		Array<Vertex2D::IndexType> m_indexArray;
		uint32 m_indexArrayWritePos = 0;

		Array<BatchBufferPos> m_batches;

		static constexpr uint32 InitialVertexArraySize	= 4096;
		static constexpr uint32 InitialIndexArraySize	= (4096 * 8); // 32,768

		static constexpr uint32 MaxVertexArraySize		= (65536 * 64); // 4,194,304
		static constexpr uint32 MaxIndexArraySize		= (65536 * 64); // 4,194,304

		static constexpr uint32 VertexBufferSize		= 65535;// 65,535;
		static constexpr uint32 IndexBufferSize			= ((VertexBufferSize + 1) * 4); // 524,288

		void advanceArrayWritePos(uint16 vertexSize, uint32 indexSize) noexcept;

	public:

		WebGPUVertex2DBatch();

		~WebGPUVertex2DBatch();

		[[nodiscard]]
		bool init(const wgpu::Device& device);

		[[nodiscard]]
		Vertex2DBufferPointer requestBuffer(uint16 vertexSize, uint32 indexSize, WebGPURenderer2DCommandManager& commandManager);

		[[nodiscard]]
		size_t num_batches() const noexcept;

		void reset();

		void setBuffers(const wgpu::RenderPassEncoder& pass);

		[[nodiscard]]
		BatchInfo2D updateBuffers(const wgpu::Device& device, size_t batchIndex);
	};
}
