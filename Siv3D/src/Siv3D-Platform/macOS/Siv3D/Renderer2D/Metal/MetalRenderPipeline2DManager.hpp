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
# include <Siv3D/HashTable.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# import <Metal/Metal.h>

namespace s3d
{
	class CShader_Metal;

	struct MetalStandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		VertexShader::IDType spriteID;

		bool setup()
		{
			const bool result = sprite
				&& fullscreen_triangle;

			spriteID = sprite.id();

			return result;
		}
	};

	struct MetalStandardPS2D
	{
		PixelShader shape;
		PixelShader square_dot;
		PixelShader round_dot;
		PixelShader fullscreen_triangle;

		PixelShader::IDType shapeID;
		PixelShader::IDType square_dotID;
		PixelShader::IDType round_dotID;

		bool setup()
		{
			const bool result = shape
				&& square_dot
				&& round_dot
				&& fullscreen_triangle;

			shapeID = shape.id();
			square_dotID = square_dot.id();
			round_dotID = round_dot.id();

			return result;
		}
	};

	class MetalRenderPipeline2DManager
	{
	private:
		
		CShader_Metal* pShader = nullptr;
		
		id<MTLDevice> m_device = nil;
		
		MTLRenderPipelineDescriptor* m_renderPipelineDescriptor = nullptr;
		
		MTLVertexDescriptor* m_standardVertexDescriptor = nullptr;
		
		using KeyType = std::tuple<VertexShader::IDType, PixelShader::IDType, MTLPixelFormat, uint32, BlendState>;
		
		HashTable<KeyType, id<MTLRenderPipelineState>> m_pipelineStates;
		
	public:
	
		void init(CShader_Metal* _pShader, id<MTLDevice> device, const MetalStandardVS2D& standardVS, const MetalStandardPS2D& standardPS, MTLPixelFormat swapchainFormat, uint32 sampleCount);

		void add(VertexShader::IDType vsID, PixelShader::IDType psID, MTLPixelFormat pixelFormat, uint32 sampleCount, const BlendState& blendState);
		
		[[nodiscard]]
		id<MTLRenderPipelineState> get(VertexShader::IDType vsID, PixelShader::IDType psID, MTLPixelFormat pixelFormat, uint32 sampleCount, const BlendState& blendState);
	};
}
