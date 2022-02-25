//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Graphics3D
	{
		namespace Internal
		{
			void SetBlendState(const BlendState& blendState);

			void SetRasterizerState(const RasterizerState& rasterizerState);

			void SetDepthStencilState(const DepthStencilState& depthStencilState);

			void SetSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& samplerState);

			void SetViewport(const Optional<Rect>& viewport);

			void SetLocalTransform(const Mat4x4& matrix);

			void SetCustomVertexShader(const Optional<VertexShader>& vs);

			void SetCustomPixelShader(const Optional<PixelShader>& ps);

			void SetRenderTarget(const Optional<RenderTexture>& rt);

			void SetConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		}

		template <class Type>
		inline void SetVSConstantBuffer(const uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			SetConstantBuffer(ShaderStage::Vertex, slot, buffer);
		}

		template <class Type>
		inline void SetPSConstantBuffer(const uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			SetConstantBuffer(ShaderStage::Pixel, slot, buffer);
		}

		template <class Type>
		inline void SetConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			Internal::SetConstantBuffer(stage, slot, buffer.base(), buffer.data(), ConstantBuffer<Type>::NumVectors);
		}
	}
}
