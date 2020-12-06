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
		/// @brief 
		/// @return 
		[[nodiscard]]
		Float4 GetColorMul();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Float4 GetColorAdd();

		/// @brief 
		/// @return 
		[[nodiscard]]
		BlendState GetBlendState();

		/// @brief 
		/// @return 
		[[nodiscard]]
		RasterizerState GetRasterizerState();

		/// @brief 
		/// @param shaderStage 
		/// @param slot 
		/// @return 
		[[nodiscard]]
		SamplerState GetSamplerState(ShaderStage shaderStage = ShaderStage::Pixel, uint32 slot = 0);

		/// @brief 
		/// @return 
		[[nodiscard]]
		Optional<VertexShader> GetCustomVertexShader();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Optional<PixelShader> GetCustomPixelShader();

		/// @brief 
		/// @return 
		[[nodiscard]]
		const Mat3x2& GetLocalTransform();

		/// @brief 
		/// @return 
		[[nodiscard]]
		const Mat3x2& GetCameraTransform();

		/// @brief 
		/// @return 
		[[nodiscard]]
		float GetMaxScaling() noexcept;

		/// @brief 
		/// @param count 
		void DrawTriangles(uint32 count);

		namespace Internal
		{
			void SetColorMul(const Float4& color);

			void SetColorAdd(const Float4& color);

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
