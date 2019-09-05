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

# pragma once
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Uncopyable.hpp"
# include "Color.hpp"
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "SamplerState.hpp"
# include "Rectangle.hpp"
# include "Mat3x2.hpp"
# include "PixelShader.hpp"
# include "ConstantBuffer.hpp"
# include "RenderTexture.hpp"

namespace s3d
{
	namespace Graphics2D
	{
		// シザー矩形を設定
		// *RasterizerState で有効化
		void SetScissorRect(const Rect& rect);

		// 現在のシザー矩形を取得
		[[nodiscard]] Rect GetScissorRect();
		
		void SetLocalTransform(const Mat3x2& transform);

		[[nodiscard]] const Mat3x2& GetLocalTransform();

		void SetCameraTransform(const Mat3x2& transform);

		[[nodiscard]] const Mat3x2& GetCameraTransform();

		// 現在の描画の拡大率係数を取得
		[[nodiscard]] double GetMaxScaling();

		// SDF 描画用のパラメータを設定
		void SetSDFParameters(const Float4& parameters);

		// 現在の SDF 描画用のパラメータを取得
		[[nodiscard]] Float4 GetSDFParameters();

		namespace Internal
		{
			void SetColorMul(const ColorF& color);

			[[nodiscard]] ColorF GetColorMul();

			void SetColorAdd(const ColorF& color);

			[[nodiscard]] ColorF GetColorAdd();

			void SetBlendState(const BlendState& blendState);

			[[nodiscard]] BlendState GetBlendState();

			void SetRasterizerState(const RasterizerState& rasterizerState);

			[[nodiscard]] RasterizerState GetRasterizerState();

			void SetSamplerState(uint32 slot, const SamplerState& samplerState);

			void SetSamplerState(const SamplerState& samplerState);

			[[nodiscard]] SamplerState GetSamplerState(uint32 slot = 0);

			void SetViewport(const Optional<Rect>& viewport);

			[[nodiscard]] Optional<Rect> GetViewport();

			void SetCustomPixelShader(const Optional<PixelShader>& ps);

			[[nodiscard]] Optional<PixelShader> GetCustomPixelShader();

			void SetConstantBuffer(ShaderStage stage, uint32 slot, const detail::ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		
			void SetRenderTarget(const Optional<RenderTexture>& rt);

			[[nodiscard]] Optional<RenderTexture> GetRenderTarget();
		}

		// 定数バッファを設定
		template <class Type>
		inline void SetConstantBuffer(ShaderStage stage, const ConstantBuffer<Type>& buffer)
		{
			Internal::SetConstantBuffer(stage, buffer.BindingPoint(), buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(Float4));
		}
	}
}
