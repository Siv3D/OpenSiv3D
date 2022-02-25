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
# include "SamplerState.hpp"
# include "ShaderStage.hpp"
# include "VertexShader.hpp"
# include "PixelShader.hpp"
# include "Texture.hpp"
# include "RenderTexture.hpp"
# include "ConstantBuffer.hpp"
# include "Mat3x2.hpp"

namespace s3d
{
	struct TextStyle;

	namespace Graphics2D
	{
		/// @brief 現在適用されている乗算カラーを返します。
		/// @return 現在適用されている乗算カラー
		[[nodiscard]]
		Float4 GetColorMul();

		/// @brief 現在適用されている加算カラーを返します。
		/// @return 現在適用されている加算カラー
		[[nodiscard]]
		Float4 GetColorAdd();

		/// @brief 現在適用されているブレンドステートを返します。
		/// @return 現在適用されているブレンドステート
		[[nodiscard]]
		BlendState GetBlendState();

		/// @brief 現在適用されているラスタライザーステートを返します。
		/// @return 現在適用されているラスタライザーステート
		[[nodiscard]]
		RasterizerState GetRasterizerState();

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

		/// @brief 現在適用されているローカル座標変換を返します。
		/// @return 現在適用されているローカル座標変換
		[[nodiscard]]
		const Mat3x2& GetLocalTransform();

		/// @brief 現在適用されている 2D カメラ座標変換を返します。
		/// @return 現在適用されている 2D カメラ座標変換
		[[nodiscard]]
		const Mat3x2& GetCameraTransform();

		/// @brief 現在適用されている座標変換による縦横の拡大縮小倍率のうち大きいほうを返します。 
		/// @return 現在適用されている座標変換による縦横の拡大縮小倍率のうち大きいほう
		/// @remark 線の太さをこの値で除算すれば、どのような拡大縮小倍率でも一定の太さになる線を描けます。
		[[nodiscard]]
		float GetMaxScaling() noexcept;

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

		/// @brief 現在までの 2D 描画を実行します。
		/// @remark `MSRenderTexture` のリゾルブ前に必要です。
		void Flush();

		/// @brief 頂点情報を設定せずに 2D 三角形を描画します。
		/// @remark 頂点シェーダを使って、各三角形に適切な頂点情報を与える必要があります。
		/// @param count 描画する三角形の個数
		void DrawTriangles(uint32 count);

		/// @brief SDF 描画用のパラメータを設定します。
		/// @param textStyle テキストスタイル
		void SetSDFParameters(const TextStyle& textStyle);

		/// @brief MSDF 描画用のパラメータを設定します。
		/// @param textStyle テキストスタイル
		void SetMSDFParameters(const TextStyle& textStyle);

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

# include "detail/Graphics2D.ipp"
