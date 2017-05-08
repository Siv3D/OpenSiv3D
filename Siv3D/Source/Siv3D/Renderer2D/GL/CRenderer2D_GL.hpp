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
# include <Siv3D/ConstantBuffer.hpp>
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
		
		void setUniformBlockBinding(const char* const name, GLuint index)
		{
			::glUniformBlockBinding(m_programHandle, getUniformBlockIndex(name), index);
		}
		
		~ShaderProgram()
		{
			if (m_programHandle)
			{
				::glDeleteProgram(m_programHandle);
			}
		}
	};
					
	struct SpriteCB
	{
		static const char* Name()
		{
			return "SpriteCB";
		}
		
		static constexpr uint32 BindingPoint()
		{
			return 0;
		}
		
		Float4 transform[2];
	};
	
	class GLVertexShader
	{
	private:
		
		GLuint m_vertexShader = 0;
		
	public:
		
		GLVertexShader() = default;
		
		~GLVertexShader()
		{
			if (m_vertexShader)
			{
				::glDeleteShader(m_vertexShader);
			}
		}
		
		bool createFromString(const String& source)
		{
			if (m_vertexShader)
			{
				return false;
			}
			
			m_vertexShader = ::glCreateShader(GL_VERTEX_SHADER);
			
			const std::string sourceUTF8 = source.toUTF8();
			
			const char* pSource = sourceUTF8.c_str();
			
			::glShaderSource(m_vertexShader, 1, &pSource, nullptr);
			
			::glCompileShader(m_vertexShader);
			
			GLint result;
			::glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
			
			if (result == GL_FALSE)
			{
				return false;
			}
			
			return true;
		}
		
		GLint getHandle() const
		{
			return m_vertexShader;
		}
	};
	
	class GLPixelShader
	{
	private:
		
		GLuint m_pixelShader = 0;
		
	public:
		
		GLPixelShader() = default;
		
		~GLPixelShader()
		{
			if (m_pixelShader)
			{
				::glDeleteShader(m_pixelShader);
			}
		}
		
		bool createFromString(const String& source)
		{
			if (m_pixelShader)
			{
				return false;
			}
			
			m_pixelShader = ::glCreateShader(GL_FRAGMENT_SHADER);
			
			const std::string sourceUTF8 = source.toUTF8();
			
			const char* pSource = sourceUTF8.c_str();
			
			::glShaderSource(m_pixelShader, 1, &pSource, nullptr);
			
			::glCompileShader(m_pixelShader);
			
			GLint result;
			::glGetShaderiv(m_pixelShader, GL_COMPILE_STATUS, &result);
			
			if (result == GL_FALSE)
			{
				return false;
			}
			
			return true;
		}
		
		GLint getHandle() const
		{
			return m_pixelShader;
		}
	};

	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:

		GLVertexShader m_vertexShader;
		
		GLPixelShader m_pixelShader;
		
		ShaderProgram m_shaderProgram;

		ConstantBuffer<SpriteCB> m_cbSprite;
		
		GLSpriteBatch m_spriteBatch;
		
		GLRender2DCommandManager m_commandManager;

	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		bool init();

		void flush() override;

		void setBlendState(const BlendState& state) override;

		BlendState getBlendState() const override;

		void setRasterizerState(const RasterizerState& state) override;

		RasterizerState getRasterizerState() const override;

		void setScissorRect(const Rect& rect) override;

		Rect getScissorRect() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;

		void addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;
		
		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;
		
		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) override;
		
		void addCircleArc(const Float2& center, float r, float startAngle, float angle, float thickness, const Float4& color) override;	
		
		void addEllipse(const Float2& center, float a, float b, const Float4& color) override;

		void addEllipseFrame(const Float2& center, float a, float b, float thickness, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;
		
		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;
		
		void addLineString(const Vec2* pts, uint32 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) override;
		
		void addShape2D(const Array<Float2>& vertices, const Array<uint32>& indices, const Float4& color) override;
		
		void addShape2DFrame(const Float2* pts, uint32 size, float thickness, const Float4& color) override;
	};
}

# endif
