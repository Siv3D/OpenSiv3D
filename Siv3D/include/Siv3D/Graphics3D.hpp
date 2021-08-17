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
	class BasicCamera3D;

	namespace Graphics3D
	{
		inline constexpr ColorF DefaultGlobalAmbientColor{ 0.5 };

		inline constexpr ColorF DefaultSunColor{ 1.0 };

		inline constexpr Vec3 DefaultSunDirection{ 0.4082482904638631, 0.4082482904638631, -0.8164965809277261 }; // Vec3{ 1, 1, -2 }.normalized()
	}

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

		void SetCameraTransform(const Mat4x4& matrix, const Float3& eyePosition);

		void SetCameraTransform(const BasicCamera3D& camera3D);

		[[nodiscard]]
		const Mat4x4& GetCameraTransform();

		[[nodiscard]]
		Float3 GetEyePosition();

		[[nodiscard]]
		const Mat4x4& GetLocalTransform();

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

		void SetGlobalAmbientColor(const ColorF& color);

		[[nodiscard]]
		ColorF GetGlobalAmbientColor();

		void SetSunDirection(const Vec3& direction);

		[[nodiscard]]
		Vec3 GetSunDirection();

		void SetSunColor(const ColorF& color);

		[[nodiscard]]
		ColorF GetSunColor();

		/// @brief 現在までの 3D 描画を実行します。
		void Flush();

		template <class Type>
		inline void SetVSConstantBuffer(uint32 slot, const ConstantBuffer<Type>& buffer);

		template <class Type>
		inline void SetPSConstantBuffer(uint32 slot, const ConstantBuffer<Type>& buffer);

		template <class Type>
		inline void SetConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer);
	}
}

# include "detail/Graphics3D.ipp"
