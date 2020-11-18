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
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Renderer2D/Vertex2DBufferPointer.hpp>
# import <Metal/Metal.h>
# include "MetalRenderer2DCommand.hpp"

namespace s3d
{
	struct VIBuffer
	{
		id<MTLBuffer> vertexBuffer;
		id<MTLBuffer> indexBuffer;
		
		size_t vertexBufferWritePos = 0;
		size_t indexBufferWritePos = 0;
		
		void resetWritePos()
		{
			vertexBufferWritePos = 0;
			indexBufferWritePos = 0;
		}
	};

	class MetalVertex2DBatch
	{
	private:
		
		using IndexType = Vertex2D::IndexType;

		static constexpr size_t MaxInflightBuffers = 3;

		dispatch_semaphore_t m_frameBoundarySemaphore = dispatch_semaphore_create(MaxInflightBuffers);
		size_t m_currentVIBufferIndex = 0;
		bool m_isActive = false;

		std::array<VIBuffer, MaxInflightBuffers> m_viBuffers;
		
		static constexpr uint32 VertexBufferSize		= 65535;// 65535;
		static constexpr uint32 IndexBufferSize			= ((VertexBufferSize + 1) * 4); // 524,288
		
		static_assert(VertexBufferSize <= Largest<Vertex2D::IndexType>);
		
	public:
		
		bool init(id<MTLDevice> device);
		
		void begin();
		
		void end();
		
		[[nodiscard]]
		id<MTLBuffer> getCurrentVertexBuffer() const;
		
		[[nodiscard]]
		id<MTLBuffer> getCurrentIndexBuffer() const;
		
		[[nodiscard]]
		dispatch_semaphore_t getSemaphore() const;

		[[nodiscard]]
		Vertex2DBufferPointer requestBuffer(uint16 vertexSize, uint32 indexSize, MetalRenderer2DCommandManager& commandManager);
	};
}
