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
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Shader/GL4/CShader_GL4.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "GL4Vertex2DBatch.hpp"

namespace s3d
{
	class GL4Renderer2DCommand {};

	struct GL4StandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		bool ok() const
		{
			return sprite
				&& fullscreen_triangle;
		}
	};

	struct GL4StandardPS2D
	{
		PixelShader shape;
		PixelShader fullscreen_triangle;

		bool ok()
		{
			return shape
				&& fullscreen_triangle;
		}
	};

	struct GL4VSConstants2D
	{
		Float4 transform[2];

		Float4 colorMul;
	};

	struct GL4PSConstants2D
	{
		Float4 colorAdd = Float4(0, 0, 0, 0);

		Float4 sdfParam = Float4(0, 0, 0, 0);

		Float4 internalParam = Float4(0, 0, 0, 0);
	};

	class CRenderer2D_GL4 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_GL4* pRenderer = nullptr;
		CShader_GL4* pShader = nullptr;

		std::unique_ptr<GL4StandardVS2D> m_standardVS;
		std::unique_ptr<GL4StandardPS2D> m_standardPS;

		ConstantBuffer<GL4VSConstants2D> m_vsConstants2D;
		ConstantBuffer<GL4PSConstants2D> m_psConstants2D;

		GL4Vertex2DBatch m_batches;
		GL4Renderer2DCommand m_command;
		uint32 m_draw_indexCount = 0;

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////
		GLuint m_vertexArray		= 0;
		GLuint m_sampler			= 0;

	public:

		CRenderer2D_GL4();

		~CRenderer2D_GL4() override;

		void init() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;

		void flush();

		void drawFullScreenTriangle(TextureFilter textureFilter);
	};
}
