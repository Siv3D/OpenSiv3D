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

# include <cassert>
# include "GLConstantBuffer.hpp"

namespace s3d
{
	namespace detail
	{
		void ConstantBufferBase::ConstantBufferDetail::init() const
		{
			::glGenBuffers(1, &m_uniformBufferHandle);
		}
		
		ConstantBufferBase::ConstantBufferDetail::ConstantBufferDetail(const size_t size)
			: m_bufferSize(size)
		{
				
		}
			
		ConstantBufferBase::ConstantBufferDetail::~ConstantBufferDetail()
		{
			if (m_uniformBufferHandle)
			{
				::glDeleteBuffers(1, &m_uniformBufferHandle);
			}
		}
			
		bool ConstantBufferBase::ConstantBufferDetail::update(const void* const data, const size_t size)
		{
			if (!m_uniformBufferHandle)
			{
				init();
			}
				
			assert(size <= m_bufferSize);
				
			::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferHandle);
				
			::glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
				
			::glBindBuffer(GL_UNIFORM_BUFFER, 0);
				
			return true;
		}
			
		GLuint ConstantBufferBase::ConstantBufferDetail::getHandle() const
		{
			if (!m_uniformBufferHandle)
			{
				init();
			}
				
			return m_uniformBufferHandle;
		}
	}
}

# endif
