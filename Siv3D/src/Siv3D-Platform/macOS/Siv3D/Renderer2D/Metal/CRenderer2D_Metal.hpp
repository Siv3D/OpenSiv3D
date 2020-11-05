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
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# import <Metal/Metal.h>
# import <QuartzCore/CAMetalLayer.h>
# include "Vertex2DBatch_Metal.hpp"

namespace s3d
{
	struct MetalStandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		bool ok() const
		{
			return sprite
				&& fullscreen_triangle;
		}
	};

	struct MetalStandardPS2D
	{
		PixelShader shape;
		PixelShader fullscreen_triangle;

		bool ok()
		{
			return shape
				&& fullscreen_triangle;
		}
	};

	struct MetalVSConstants2D
	{
		Float4 transform[2];
		Float4 colorMul = Float4(1, 1, 1, 1);
	};

	struct MetalPSConstants2D
	{
		Float4 colorAdd = Float4(0, 0, 0, 0);
		Float4 sdfParam = Float4(0, 0, 0, 0);
		Float4 internal = Float4(0, 0, 0, 0);
	};

	class CRenderer_Metal;
	class CShader_Metal;

	class CRenderer2D_Metal final : public ISiv3DRenderer2D
	{
	private:
		
		CRenderer_Metal* pRenderer = nullptr;
		CShader_Metal* pShader = nullptr;
		id<MTLDevice> m_device = nil;
		id<MTLCommandQueue> m_commandQueue = nil;
		CAMetalLayer* m_swapchain = nullptr;
				
		id<MTLRenderPipelineState> m_sceneRenderPipelineState = nil;
		id<MTLRenderPipelineState> m_fullscreenTriangleRenderPipelineState = nil;
		MTLRenderPassDescriptor* m_renderPassDescriptor;
		
		std::unique_ptr<MetalStandardVS2D> m_standardVS;
		std::unique_ptr<MetalStandardPS2D> m_standardPS;
		
		ConstantBuffer<MetalVSConstants2D> m_vsConstants2D;
		ConstantBuffer<MetalPSConstants2D> m_psConstants2D;
		
		Vertex2DBatch_Metal m_batches;
		Renderer2DCommand_Metal m_command;
		uint32 m_draw_indexCount = 0;

	public:

		CRenderer2D_Metal();

		~CRenderer2D_Metal() override;

		void init() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;
		
		void flush(id<MTLCommandBuffer> commandBuffer);

		void drawFullScreenTriangle(id<MTLCommandBuffer> commandBuffer, TextureFilter textureFilter);
		
		void begin();
	};
}
