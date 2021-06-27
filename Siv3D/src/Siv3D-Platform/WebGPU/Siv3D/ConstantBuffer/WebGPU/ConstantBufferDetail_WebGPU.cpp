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

# include "ConstantBufferDetail_WebGPU.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	ConstantBufferDetail_WebGPU::ConstantBufferDetail_WebGPU(const size_t size)
		: m_bufferSize(size)
	{

	}

	ConstantBufferDetail_WebGPU::~ConstantBufferDetail_WebGPU()
	{
		if (m_uniformBuffer)
		{
			::glDeleteBuffers(1, &m_uniformBuffer);
			m_uniformBuffer = 0;
		}
	}

	bool ConstantBufferDetail_WebGPU::update(const void* const data, const size_t size)
	{
		if (not m_uniformBuffer)
		{
			::glGenBuffers(1, &m_uniformBuffer);
		}

		assert(size <= m_bufferSize);

		::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
		::glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
		::glBindBuffer(GL_UNIFORM_BUFFER, 0);

		return true;
	}

	GLuint ConstantBufferDetail_WebGPU::getHandle() const
	{
		if (not m_uniformBuffer)
		{
			::glGenBuffers(1, &m_uniformBuffer);
		}

		return m_uniformBuffer;
	}
}
