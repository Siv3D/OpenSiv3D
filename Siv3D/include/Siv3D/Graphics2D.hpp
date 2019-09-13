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
		// 現在のグローバル乗算カラーを取得
		[[nodiscard]] ColorF GetColorMul();

		// 現在のグローバル加算カラーを取得
		[[nodiscard]] ColorF GetColorAdd();

		// 現在のブレンドステートを取得
		[[nodiscard]] BlendState GetBlendState();

		// 現在のラスタライザーステートを取得
		[[nodiscard]] RasterizerState GetRasterizerState();

		// サンプラーステートを設定
		void SetSamplerState(uint32 slot, const SamplerState& samplerState);

		// 現在のサンプラーステートを取得
		[[nodiscard]] SamplerState GetSamplerState(uint32 slot = 0);

		// 現在のカスタムビューポートを取得
		[[nodiscard]] Optional<Rect> GetViewport();

		// 現在のカスタムピクセルシェーダを取得
		[[nodiscard]] Optional<PixelShader> GetCustomPixelShader();

		// 現在のレンダーターゲットを取得
		[[nodiscard]] Optional<RenderTexture> GetRenderTarget();

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

		// マルチテクスチャ用のテクスチャをセット
		void SetTexture(uint32 slot, const Optional<Texture>& texture);

		// 現在までの 2D 描画を実行
		void Flush();

		namespace Internal
		{
			void SetColorMul(const ColorF& color);

			void SetColorAdd(const ColorF& color);

			void SetBlendState(const BlendState& blendState);

			void SetRasterizerState(const RasterizerState& rasterizerState);

			void SetSamplerState(const SamplerState& samplerState);

			void SetViewport(const Optional<Rect>& viewport);

			void SetCustomPixelShader(const Optional<PixelShader>& ps);

			void SetConstantBuffer(ShaderStage stage, uint32 index, const detail::ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		
			void SetRenderTarget(const Optional<RenderTexture>& rt);

			void SetInternalConstantBufferValue(ShaderStage stage, const Float4& value);
		}

		// 定数バッファを設定
		template <class Type>
		inline void SetConstantBuffer(ShaderStage stage, uint32 index, const ConstantBuffer<Type>& buffer)
		{
			Internal::SetConstantBuffer(stage, index, buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(Float4));
		}
	}
}
