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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/ConstantBuffer.hpp>

namespace s3d
{
	namespace detail
	{
		class ConstantBufferBase::ConstantBufferDetail
		{
		private:
		
			GLuint m_uniformBufferHandle = 0;
				
		public:

			explicit ConstantBufferDetail(size_t)
			{
				::glGenBuffers(1, &m_uniformBufferHandle);
			}

			~ConstantBufferDetail()
			{
				if (m_uniformBufferHandle)
				{
					::glDeleteBuffers(1, &m_uniformBufferHandle);
				}
			}
		
			bool update(const void* const data, const size_t size)
			{
				if (!m_uniformBufferHandle)
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
	}
}

# endif
