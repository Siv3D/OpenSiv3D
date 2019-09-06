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
# include <Siv3D/ShaderCommon.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	class VertexShader_GL
	{
	private:
		
		GLuint m_vsProgram = 0;
		
		bool m_initialized = false;
		
	public:
		
		struct Null {};
		
		VertexShader_GL() = default;
		
		VertexShader_GL(Null);
		
		~VertexShader_GL();
		
		VertexShader_GL(const String& source);
		
		bool isInitialized() const noexcept;
		
		GLint getProgram() const;

		void setUniformBlockBinding(const String& name, GLuint index);
		
		void setUniformBlockBindings(const Array<BindingPoint>& bindingPoints);
	};
}
