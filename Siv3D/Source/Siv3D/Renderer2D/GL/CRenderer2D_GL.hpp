//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../IRenderer2D.hpp"
# include "GLSpriteBatch.hpp"

namespace s3d
{
	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:

		GLuint m_vertexShader = 0;
		
		GLuint m_pixelShader = 0;
		
		GLuint m_programHandle = 0;
		
		GLSpriteBatch m_spriteBatch;
		
		uint32 m_drawIndexCount = 0;
		
		bool m_initialized = false;
		
	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		bool init();

		void flush() override;

		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;
		
		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;
		
		void addQuad(const FloatQuad& quad, const Float4& color) override;
		
		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;
	};
}

# endif
