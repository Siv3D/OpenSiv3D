//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "ConstantBufferDetail_GLES3.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	ConstantBufferDetail_GLES3::ConstantBufferDetail_GLES3(const size_t size)
		: m_bufferSize{ size }
	{
		// do nothing
	}

	ConstantBufferDetail_GLES3::~ConstantBufferDetail_GLES3()
	{
		if (m_uniformBuffer)
		{
			::glDeleteBuffers(1, &m_uniformBuffer);
			m_uniformBuffer = 0;
		}
	}

	bool ConstantBufferDetail_GLES3::update(const void* const data, const size_t size)
	{
		if (not m_uniformBuffer)
		{
			initBuffer();
		}

		assert(size <= m_bufferSize);

		::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
		::glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
		::glBindBuffer(GL_UNIFORM_BUFFER, 0);

		return true;
	}

	GLuint ConstantBufferDetail_GLES3::getHandle() const
	{
		if (not m_uniformBuffer)
		{
			initBuffer();
		}

		return m_uniformBuffer;
	}

	void ConstantBufferDetail_GLES3::initBuffer() const
	{
		::glGenBuffers(1, &m_uniformBuffer);
		::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
		::glBufferData(GL_UNIFORM_BUFFER, m_bufferSize, nullptr, GL_DYNAMIC_DRAW);
		::glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
