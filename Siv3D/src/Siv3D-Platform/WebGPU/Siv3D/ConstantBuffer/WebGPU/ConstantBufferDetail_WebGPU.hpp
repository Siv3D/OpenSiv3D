//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/ConstantBuffer/IConstantBufferDetail.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class ConstantBufferDetail_WebGPU final : public IConstantBufferDetail
	{
	private:

		mutable wgpu::Device m_device;

		size_t m_bufferSize = 0;

		size_t m_bufferOffset = 0;

		size_t m_bufferOffsetWritePos = 0;

		size_t m_allocatedBufferSize = 0;

		mutable wgpu::Buffer m_uniformBuffer = nullptr;

		bool init() const;

	public:

		explicit ConstantBufferDetail_WebGPU(size_t size);

		~ConstantBufferDetail_WebGPU();

		bool update(const void* data, size_t size) override;

		wgpu::Buffer getHandle() const;

		wgpu::BindGroupEntry getBindGroupEntry() const;
	};
}
