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
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/GLES3/CRenderer_GLES3.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "GLES3Vertex2DBatch.hpp"

namespace s3d
{
	class GLES3Renderer2DCommand {};

	class CRenderer2D_GLES3 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_GLES3* pRenderer = nullptr;

		GLuint m_vertexShader = 0;
		GLuint m_pixelShader = 0;
		GLuint m_program = 0;
		GLuint m_uniformBuffer = 0;

		GLES3Vertex2DBatch m_batches;
		GLES3Renderer2DCommand m_command;
		uint32 m_draw_indexCount = 0;

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////

		GLuint m_copyProgram		= 0;
		GLuint m_vertexArray		= 0;
		GLuint m_sampler			= 0;
		GLuint m_locationTexture	= 0;

	public:

		CRenderer2D_GLES3();

		~CRenderer2D_GLES3() override;

		void init() override;

		void flush() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;

		void drawFullScreenTriangle(TextureFilter textureFilter) override;
	};
}
