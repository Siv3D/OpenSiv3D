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
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Renderer2D/Vertex2DBufferPointer.hpp>
# include <Siv3D/Renderer2D/Renderer2DCommon.hpp>
# import <Metal/Metal.h>
# include "MetalRenderer2DCommand.hpp"

namespace s3d
{
	struct VIBuffer
	{
		id<MTLBuffer> vertexBuffer;
		id<MTLBuffer> indexBuffer;
		
		uint32 vertexBufferWritePos = 0;
		uint32 indexBufferWritePos = 0;
		
		void resetWritePos() noexcept
		{
			vertexBufferWritePos = 0;
			indexBufferWritePos = 0;
		}
	};

	class MetalVertex2DBatch
	{
	private:
		
		using IndexType = Vertex2D::IndexType;
		
		id<MTLDevice> m_device = nil;

		static constexpr size_t MaxInflightBuffers = 3;

		dispatch_semaphore_t m_frameBoundarySemaphore = dispatch_semaphore_create(MaxInflightBuffers);
		size_t m_currentVIBufferIndex = 0;
		bool m_isActive = false;

		std::array<Array<VIBuffer>, MaxInflightBuffers> m_viBuffers;
		size_t m_currentBatchIndex = 0;
		uint32 m_allVertexCount = 0;
		uint32 m_allIndexCount = 0;

		static constexpr uint32 VertexBufferSize	= 65535;// 65,535;
		static constexpr uint32 IndexBufferSize		= ((VertexBufferSize + 1) * 4); // 524,288
		
		static constexpr uint32 MaxVertexCount		= (65536 * 64); // 4,194,304
		static constexpr uint32 MaxIndexCount		= (65536 * 64); // 4,194,304
		
		static_assert(VertexBufferSize <= Largest<Vertex2D::IndexType>);
		
	public:
		
		bool init(id<MTLDevice> device);
		
		void begin();
		
		void end();
		
		[[nodiscard]]
		id<MTLBuffer> getCurrentVertexBuffer(size_t index) const;
		
		[[nodiscard]]
		id<MTLBuffer> getCurrentIndexBuffer(size_t index) const;
		
		[[nodiscard]]
		dispatch_semaphore_t getSemaphore() const;

		[[nodiscard]]
		Vertex2DBufferPointer requestBuffer(uint16 vertexSize, uint32 indexSize, MetalRenderer2DCommandManager& commandManager);
		
		[[nodiscard]]
		size_t num_batches() const noexcept;

		[[nodiscard]]
		BatchInfo2D updateBuffers(size_t batchIndex);
	};
}
