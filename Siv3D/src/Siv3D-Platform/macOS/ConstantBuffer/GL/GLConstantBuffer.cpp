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

# include "GLConstantBuffer.hpp"

namespace s3d
{
	namespace detail
	{
		ConstantBufferBase::ConstantBufferDetail::ConstantBufferDetail(const size_t size)
		: m_bufferSize(size)
		{
			
		}
		
		ConstantBufferBase::ConstantBufferDetail::~ConstantBufferDetail()
		{
			if (m_uniformBuffer)
			{
				::glDeleteBuffers(1, &m_uniformBuffer);
				m_uniformBuffer = 0;
			}
		}
		
		bool ConstantBufferBase::ConstantBufferDetail::update(const void* const data, const size_t size)
		{
			if (!m_uniformBuffer)
			{
				::glGenBuffers(1, &m_uniformBuffer);
			}
			
			assert(size <= m_bufferSize);
			
			::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
			::glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
			::glBindBuffer(GL_UNIFORM_BUFFER, 0);
			
			return true;
		}
		
		GLuint ConstantBufferBase::ConstantBufferDetail::getHandle() const
		{
			if (!m_uniformBuffer)
			{
				::glGenBuffers(1, &m_uniformBuffer);
			}
			
			return m_uniformBuffer;
		}
	}
}
