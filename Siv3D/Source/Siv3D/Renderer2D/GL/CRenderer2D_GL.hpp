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
	
	class ConstantBufferBase
	{
	private:
		
		class ConstantBufferDetail;
		
		std::shared_ptr<ConstantBufferDetail> m_detail;
		
	public:
		
		ConstantBufferBase();

		bool _internal_update(const void* data, size_t size);
		
		const ConstantBufferDetail* _detail() const;
	};
	

	class ConstantBufferBase::ConstantBufferDetail
	{
	private:
		
		GLuint m_uniformBufferHandle = 0;
		
		bool initBuffer()
		{
			if (m_uniformBufferHandle)
			{
				return true;
			}
			
			::glGenBuffers(1, &m_uniformBufferHandle);
			
			return true;
		}
		
	public:

		~ConstantBufferDetail()
		{
			if (m_uniformBufferHandle)
			{
				::glDeleteBuffers(1, &m_uniformBufferHandle);
			}
		}
		
		bool update(const void* const data, const size_t size)
		{
			if (!initBuffer())
			{
				return false;
			}
			
			::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferHandle);
			
			::glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
			
			::glBindBuffer(GL_UNIFORM_BUFFER, 0);
			
			return true;
		}
		
		GLuint getHandle() const
		{
			return m_uniformBufferHandle;
		}
	};
			
	template <class Type>
	class ConstantBuffer
	{
	private:
		
		static constexpr size_t Size = sizeof(Type);
		
		static_assert(Size <= 16 * 4096); // <= 64KB
		
		static_assert(Size % 16 == 0);
		
		ConstantBufferBase m_base;
		
		Type* const m_data = AlignedMalloc<Type>();
		
	public:
		
		static const char* Name()
		{
			return Type::Name();
		}
		
		static uint32 BindingPoint()
		{
			return Type::BindingPoint();
		}
		
		ConstantBuffer() = default;
		
		explicit ConstantBuffer(const Type& data)
			: ConstantBuffer()
		{
			*m_data = data;
		}
		
		~ConstantBuffer()
		{
			AlignedFree(m_data);
		}
		
		constexpr size_t getDataSize() const noexcept
		{
			return Size;
		}
		
		const float* getPtr() const
		{
			return static_cast<const float*>(static_cast<const void*>(m_data));
		}
		
		Type& get()
		{
			return *m_data;
		}
		
		const Type& get() const
		{
			return *m_data;
		}

		bool _internal_update()
		{
			return m_base._internal_update(m_data, Size);
		}
		
		const ConstantBufferBase& base() const
		{
			return m_base;
		}
		
		Type& operator *()
		{
			return *m_data;
		}
		
		const Type& operator *() const
		{
			return *m_data;
		}
		
		Type* operator ->()
		{
			return m_data;
		}
		
		const Type* operator ->() const
		{
			return *m_data;
		}
	};
	
	struct SpriteCB
	{
		static const char* Name()
		{
			return "SpriteCB";
		}
		
		static uint32 BindingPoint()
		{
			return 0;
		}
		
		Float4 transform[2];
	};
	
	static_assert(sizeof(SpriteCB) == 32);

	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:

		GLuint m_vertexShader = 0;
		
		GLuint m_pixelShader = 0;
		
		ShaderProgram m_shaderProgram;

		ConstantBuffer<SpriteCB> m_cbSprite;
		
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
