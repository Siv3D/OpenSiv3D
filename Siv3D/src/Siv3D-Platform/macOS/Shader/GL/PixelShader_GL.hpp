//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Array.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class PixelShader_GL
	{
	private:

		GLuint m_psProgram = 0;
		
		Array<std::pair<uint32, GLint>> m_textureIndices;
		
		bool m_initialized = false;
		
	public:

		struct Null {};
		
		PixelShader_GL() = default;
		
		PixelShader_GL(Null);
		
		~PixelShader_GL();
		
		PixelShader_GL(const String& source);
		
		bool isInitialized() const noexcept;
		
		GLint getProgram() const;
		
		void setPSSamplerUniform();
		
		GLuint getUniformBlockIndex(const char* const name);
		
		void setUniformBlockBinding(const char* const name, GLuint index);
	};
}
