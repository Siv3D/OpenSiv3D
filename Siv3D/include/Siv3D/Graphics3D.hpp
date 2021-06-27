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
# include "Common.hpp"
# include "Optional.hpp"
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "DepthStencilState.hpp"
# include "SamplerState.hpp"
# include "ShaderStage.hpp"
# include "VertexShader.hpp"
# include "PixelShader.hpp"
# include "ConstantBuffer.hpp"
# include "RenderTexture.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	namespace Graphics3D
	{
		/// @brief 現在適用されているブレンドステートを返します。
		/// @return 現在適用されているブレンドステート
		[[nodiscard]]
		BlendState GetBlendState();

		/// @brief 現在適用されているラスタライザーステートを返します。
		/// @return 現在適用されているラスタライザーステート
		[[nodiscard]]
		RasterizerState GetRasterizerState();

		[[nodiscard]]
		DepthStencilState GetDepthStencilState();

		/// @brief 
		/// @param shaderStage 
		/// @param slot 
		/// @return 
		[[nodiscard]]
		SamplerState GetSamplerState(ShaderStage shaderStage = ShaderStage::Pixel, uint32 slot = 0);

		/// @brief シザー矩形を設定します。
		/// @param rect シザー矩形
		/// @remark シザー矩形は RasterizerState で scissorEnable を true にすることで有効になります。
		void SetScissorRect(const Rect& rect);

		[[nodiscard]]
		Rect GetScissorRect();

		[[nodiscard]]
		Optional<Rect> GetViewport();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Optional<VertexShader> GetCustomVertexShader();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Optional<PixelShader> GetCustomPixelShader();

		void SetCameraTransform(const Mat4x4& matrix);

		[[nodiscard]]
		const Mat4x4& GetCameraTransform();

		[[nodiscard]]
		Optional<RenderTexture> GetRenderTarget();
		
		[[nodiscard]]
		Size GetRenderTargetSize();

		/// @brief 2D 描画の頂点シェーダのテクスチャスロットにテクスチャをアタッチします。
		/// @param slot スロット。最大 (SamplerState::MaxSamplerCount - 1)
		/// @param texture アタッチするテクスチャ。none の場合テクスチャのアタッチを解除します。
		void SetVSTexture(uint32 slot, const Optional<Texture>& texture);

		/// @brief 2D 描画のピクセルシェーダのテクスチャスロットにテクスチャをアタッチします。
		/// @param slot スロット。最大 (SamplerState::MaxSamplerCount - 1)
		/// @param texture アタッチするテクスチャ。none の場合テクスチャのアタッチを解除します。
		void SetPSTexture(uint32 slot, const Optional<Texture>& texture);

		/// @brief 現在までの 3D 描画を実行します。
		void Flush();

		template <class Type>
		inline void SetConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer);
	}
}

# include "detail/Graphics3D.ipp"
