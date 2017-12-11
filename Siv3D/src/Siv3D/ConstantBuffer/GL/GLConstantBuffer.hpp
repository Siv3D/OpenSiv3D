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
		
			size_t m_bufferSize = 0;
			
			mutable GLuint m_uniformBufferHandle = 0;
			
			void init() const;
				
		public:

			explicit ConstantBufferDetail(const size_t size);

			~ConstantBufferDetail();
		
			bool update(const void* const data, const size_t size);
		
			GLuint getHandle() const;
		};
	}
}

# endif
