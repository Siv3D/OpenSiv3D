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

		/// @brief 現在適用されているデプス・ステンシルステートを返します。
		/// @return 現在適用されているデプス・ステンシルステート
		[[nodiscard]]
		DepthStencilState GetDepthStencilState();

		/// @brief 現在適用されているサンプラーステートを返します。
		/// @param shaderStage シェーダステージ
		/// @param slot テクスチャスロット
		/// @return 現在適用されているサンプラーステート
		[[nodiscard]]
		SamplerState GetSamplerState(ShaderStage shaderStage = ShaderStage::Pixel, uint32 slot = 0);

		/// @brief シザー矩形を設定します。
		/// @param rect シザー矩形
		/// @remark シザー矩形は RasterizerState で scissorEnable を true にすることで有効になります。
		void SetScissorRect(const Rect& rect);

		/// @brief 現在設定されているシザー矩形を返します。
		/// @return 現在設定されているシザー矩形
		[[nodiscard]]
		Rect GetScissorRect();

		/// @brief 現在適用されているビューポートを返します。
		/// @return 現在適用されているビューポート。シーンと一致する場合は none
		[[nodiscard]]
		Optional<Rect> GetViewport();

		/// @brief 現在適用されている頂点シェーダを返します。
		/// @return 現在適用されている頂点シェーダ。デフォルトの場合は none
		[[nodiscard]]
		Optional<VertexShader> GetCustomVertexShader();

		/// @brief 現在適用されているピクセルシェーダを返します。
		/// @return 現在適用されているピクセルシェーダ。デフォルトの場合は none
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

		/// @brief 現在のレンダーターゲットになっているレンダーテクスチャを返します。
		/// @return 現在のレンダーターゲットになっているレンダーテクスチャ。デフォルトのシーンの場合 none
		[[nodiscard]]
		Optional<RenderTexture> GetRenderTarget();

		/// @brief 現在のレンダーターゲットのサイズ（ピクセル）を返します
		/// @return 現在のレンダーターゲットのサイズ（ピクセル）	
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

		/// @brief グローバル環境光の色を設定します。
		/// @param color グローバル環境光の色
		void SetGlobalAmbientColor(const ColorF& color);

		[[nodiscard]]
		ColorF GetGlobalAmbientColor();

		/// @brief メイン平行光源への方向を設定します。
		/// @param direction メイン平行光源への方向
		void SetSunDirection(const Vec3& direction);

		[[nodiscard]]
		Vec3 GetSunDirection();

		/// @brief メイン平行光源の色を設定します。
		/// @param color メイン平行光源の色
		void SetSunColor(const ColorF& color);

		[[nodiscard]]
		ColorF GetSunColor();

		/// @brief 現在までの 3D 描画を実行します。
		/// @remark `MSRenderTexture` のリゾルブ前に必要です。
		void Flush();

		/// @brief 頂点シェーダの定数バッファを設定します。
		/// @tparam Type 定数バッファの構造体
		/// @param slot スロット
		/// @param buffer 定数バッファ
		/// @remark 予約されているスロットは使用できません。詳しくはドキュメントを読んでください。
		template <class Type>
		inline void SetVSConstantBuffer(uint32 slot, const ConstantBuffer<Type>& buffer);

		/// @brief ピクセルシェーダの定数バッファを設定します。
		/// @tparam Type 定数バッファの構造体
		/// @param slot スロット
		/// @param buffer 定数バッファ
		/// @remark 予約されているスロットは使用できません。詳しくはドキュメントを読んでください。
		template <class Type>
		inline void SetPSConstantBuffer(uint32 slot, const ConstantBuffer<Type>& buffer);

		/// @brief 定数バッファを設定します。
		/// @tparam Type 定数バッファの構造体
		/// @param stage シェーダステージ
		/// @param slot スロット
		/// @param buffer 定数バッファ
		/// @remark 予約されているスロットは使用できません。詳しくはドキュメントを読んでください
		template <class Type>
		inline void SetConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer);
	}
}

# include "detail/Graphics3D.ipp"
