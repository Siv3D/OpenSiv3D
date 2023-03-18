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
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>

# include <webgpu/webgpu_cpp.h>

namespace s3d
{
	class WebGPUUniformState
	{
    public:

        WebGPUUniformState();

		void init(const wgpu::Device& device);

        void bindUniformBindGroup(const wgpu::RenderPassEncoder& pass, uint32 groupId, const wgpu::RenderPipeline& pipeline, const s3d::Array<wgpu::BindGroupEntry>& binding);

	private:

		wgpu::Device m_device;

        HashTable<size_t, wgpu::BindGroup> m_bindGroups;
    };
}
