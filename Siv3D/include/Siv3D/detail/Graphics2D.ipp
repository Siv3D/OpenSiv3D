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

# pragma once

namespace s3d
{
	namespace Graphics2D
	{
		namespace Internal
		{
			void SetColorMul(const Float4& color);

			void SetColorAdd(const Float4& color);

			void SetBlendState(const BlendState& blendState);

			void SetRasterizerState(const RasterizerState& rasterizerState);

			void SetSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& samplerState);

			void SetViewport(const Optional<Rect>& viewport);

			void SetCustomVertexShader(const Optional<VertexShader>& vs);

			void SetCustomPixelShader(const Optional<PixelShader>& ps);

			void SetLocalTransform(const Mat3x2& transform);

			void SetCameraTransform(const Mat3x2& transform);

			void SetConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		}

		template <class Type>
		inline void SetConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			Internal::SetConstantBuffer(stage, slot, buffer.base(), buffer.data(), ConstantBuffer<Type>::NumVectors);
		}
	}
}
