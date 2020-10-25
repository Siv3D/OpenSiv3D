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
# import <Metal/Metal.h>

namespace s3d
{
	class Renderer2DCommand_Metal{};

	class Vertex2DBatch_Metal
	{
	private:
		
		using IndexType = Vertex2D::IndexType;

		static constexpr size_t MaxInflightBuffers = 3;

		dispatch_semaphore_t m_frameBoundarySemaphore = dispatch_semaphore_create(MaxInflightBuffers);
		size_t m_currentBufferIndex = 0;
		bool m_isActive = false;

		std::array<id<MTLBuffer>, MaxInflightBuffers> m_vertexBuffers;
		size_t m_currentVertexBufferWritePos = 0;
		
		std::array<id<MTLBuffer>, MaxInflightBuffers> m_indexBuffers;
		size_t m_currentIndexBufferWritePos = 0;
		
		static constexpr uint32 VertexBufferSize		= 65535;// 65535;
		static constexpr uint32 IndexBufferSize			= ((VertexBufferSize + 1) * 4); // 524,288
		
	public:
		
		void init(id<MTLDevice> device);
		
		void begin();
		
		void end();
		
		[[nodiscard]]
		id<MTLBuffer> getCurrentVertexBuffer() const;
		
		[[nodiscard]]
		id<MTLBuffer> getCurrentIndexBuffer() const;
		
		[[nodiscard]]
		dispatch_semaphore_t getSemaphore() const;

		[[nodiscard]]
		std::tuple<Vertex2D*, IndexType*, IndexType> requestBuffer(uint16 vertexSize, uint32 indexSize, Renderer2DCommand_Metal& command);
	};
}
