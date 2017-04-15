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

namespace s3d
{
	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:

		GLuint m_vertexShader = 0;
		
		GLuint m_pixelShader = 0;
		
		GLuint m_programHandle = 0;
		
		GLuint m_vao = 0;
		
		GLuint m_vertexBuffer = 0;
		
		GLuint m_indexBuffer = 0;
		
		uint32 m_vertexWritePos = 0;

		uint32 m_indexWritePos = 0;
		
		bool m_initialized = false;
		
		static constexpr uint32 VertexBufferSize = 65536;

		static constexpr uint32 IndexBufferSize = 65536;
		
	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		bool init();

		void flush() override;

		void addRect(const FloatRect& rect, const Float4& color) override {}
	};
}

# endif
