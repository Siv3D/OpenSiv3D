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
# include <Siv3D/Optional.hpp>
# include <Siv3D/Rectangle.hpp>
# include "../IRenderer2D.hpp"
# include "GLSpriteBatch.hpp"
# include "GLRenderer2DCommandManager.hpp"

namespace s3d
{
	class ShaderProgram
	{
	private:
		
		GLuint m_programHandle = 0;
		
	public:
		
		bool init()
		{
			m_programHandle = ::glCreateProgram();
			
			return m_programHandle != 0;
		}
		
		void attach(const GLuint shader)
		{
			::glAttachShader(m_programHandle, shader);
		}
		
		bool link()
		{
			::glLinkProgram(m_programHandle);
			
			GLint status;
			::glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
			
			if (status == GL_FALSE)
			{
				return false;
			}
			
			return true;
		}
		
		void use()
		{
			::glUseProgram(m_programHandle);
		}
		
		GLuint getUniformBlockIndex(const char* const name)
		{
			return ::glGetUniformBlockIndex(m_programHandle, name);
		}
		
		~ShaderProgram()
		{
			if (m_programHandle)
			{
				::glDeleteProgram(m_programHandle);
			}
		}
	};
	
	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:

		GLuint m_vertexShader = 0;
		
		GLuint m_pixelShader = 0;
		
		ShaderProgram m_shaderProgram;
		
		GLuint m_uniform_buffer = 0;
		
		GLuint m_uniformBlockIndex = 0;
		
		GLSpriteBatch m_spriteBatch;
		
		GLRender2DCommandManager m_commandManager;

		bool m_initialized = false;
		
	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		bool init();

		void flush() override;

		void setBlendState(const BlendState& state) override;

		BlendState getBlendState() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;

		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;
		
		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addEllipse(const Float2& center, float a, float b, const Float4& color) override;

		void addEllipseFrame(const Float2& center, float a, float b, float thickness, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;
		
		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;
	};
}

# endif
