//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Optional.hpp"
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "SamplerState.hpp"
# include "ShaderStatge.hpp"
# include "VertexShader.hpp"
# include "PixelShader.hpp"
# include "Mat3x2.hpp"

namespace s3d
{
	namespace Graphics2D
	{
		[[nodiscard]]
		BlendState GetBlendState();

		[[nodiscard]]
		RasterizerState GetRasterizerState();

		[[nodiscard]]
		SamplerState GetSamplerState(ShaderStage shaderStage = ShaderStage::Pixel, uint32 slot = 0);

		[[nodiscard]]
		Optional<VertexShader> GetCustomVertexShader();

		[[nodiscard]]
		Optional<PixelShader> GetCustomPixelShader();

		[[nodiscard]]
		const Mat3x2& GetLocalTransform();

		[[nodiscard]]
		const Mat3x2& GetCameraTransform();

		[[nodiscard]]
		float GetMaxScaling() noexcept;

		void DrawTriangles(uint32 count);

		namespace Internal
		{
			void SetBlendState(const BlendState& blendState);

			void SetRasterizerState(const RasterizerState& rasterizerState);

			void SetSamplerState(ShaderStage shaderStage, uint32 slot, const SamplerState& samplerState);

			void SetCustomVertexShader(const Optional<VertexShader>& vs);

			void SetCustomPixelShader(const Optional<PixelShader>& ps);

			void SetLocalTransform(const Mat3x2& transform);

			void SetCameraTransform(const Mat3x2& transform);
		}
	}
}
