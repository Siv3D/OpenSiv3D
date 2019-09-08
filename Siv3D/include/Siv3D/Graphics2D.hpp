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
		void SetColorMul(const ColorF& color);

		[[nodiscard]] ColorF GetColorMul();

		void SetColorAdd(const ColorF& color);

		[[nodiscard]] ColorF GetColorAdd();

		/// <summary>
		/// 2D 描画のブレンドステートを設定します。
		/// </summary>
		/// <param name="blendState">
		/// ブレンドステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetBlendState(const BlendState& blendState);

		/// <summary>
		/// 現在の 2D 描画のブレンドステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のブレンドステート
		/// </returns>
		[[nodiscard]] BlendState GetBlendState();

		/// <summary>
		/// 2D 描画のラスタライザーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// ラスタライザーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRasterizerState(const RasterizerState& rasterizerState);

		/// <summary>
		/// 現在の 2D 描画のラスタライザーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のラスタライザーステート
		/// </returns>
		[[nodiscard]] RasterizerState GetRasterizerState();

		void SetSamplerState(uint32 slot, const SamplerState& samplerState);

		/// <summary>
		/// 2D 描画のサンプラーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSamplerState(const SamplerState& samplerState);

		/// <summary>
		/// 現在の 2D 描画のサンプラーステートを取得します。
		/// </summary>
		/// <param name="slot">
		/// スロット
		/// </param>
		/// <returns>
		/// 現在の 2D 描画のサンプラーステート
		/// </returns>
		[[nodiscard]] SamplerState GetSamplerState(uint32 slot = 0);

		void SetScissorRect(const Rect& rect);

		[[nodiscard]] Rect GetScissorRect();

		void SetViewport(const Optional<Rect>& viewport);

		[[nodiscard]] Optional<Rect> GetViewport();

		void SetLocalTransform(const Mat3x2& transform);

		[[nodiscard]] const Mat3x2& GetLocalTransform();

		void SetCameraTransform(const Mat3x2& transform);

		[[nodiscard]] const Mat3x2& GetCameraTransform();

		[[nodiscard]] double GetMaxScaling();

		void SetSDFParameters(const Float4& parameters);

		[[nodiscard]] Float4 GetSDFParameters();

		namespace detail
		{
			void SetCustomPixelShader(const Optional<PixelShader>& ps);

			[[nodiscard]] Optional<PixelShader> GetCustomPixelShader();

			void SetConstantBuffer(ShaderStage stage, uint32 slot, const s3d::detail::ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		
			void SetRenderTarget(const Optional<RenderTexture>& rt);

			[[nodiscard]] Optional<RenderTexture> GetRenderTarget();
		}

		template <class Type>
		inline void SetConstantBuffer(ShaderStage stage, const ConstantBuffer<Type>& buffer)
		{
			detail::SetConstantBuffer(stage, buffer.BindingPoint(), buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(Float4));
		}
	}
}
