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

# include <Siv3D/ConstantBuffer.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

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
			
			explicit ConstantBufferDetail(size_t size);
			
			~ConstantBufferDetail();
			
			bool update(const void* data, size_t size);
			
			GLuint getHandle() const;
		};
	}
}
