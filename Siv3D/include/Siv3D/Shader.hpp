//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>
# include "Common.hpp"
# include "StringView.hpp"
# include "ShaderStage.hpp"
# include "RenderTexture.hpp"
# include "Graphics2D.hpp"
# include "2DShapes.hpp"
# include "TextureFilter.hpp"
# include "BoxFilterSize.hpp"

namespace s3d
{
	namespace Shader
	{
		/// @brief テクスチャの内容を、同じサイズの別のレンダーテクスチャに描画します。
		/// @param from 描画する内容
		/// @param to 描画先のレンダーテクスチャ
		/// @remark from と to は同サイズで異なるテクスチャである必要があります。
		void Copy(const TextureRegion& from, const RenderTexture& to);

		/// @brief テクスチャの内容を、別のレンダーテクスチャに描画します。
		/// @param from 描画する内容
		/// @param to 描画先のレンダーテクスチャ
		/// @remark from と to は異なるテクスチャである必要があります。
		void Downsample(const TextureRegion& from, const RenderTexture& to);

		void GaussianBlurH(const TextureRegion& from, const RenderTexture& to, BoxFilterSize boxFilterSize = BoxFilterSize::BoxFilter9x9);

		void GaussianBlurV(const TextureRegion& from, const RenderTexture& to, BoxFilterSize boxFilterSize = BoxFilterSize::BoxFilter9x9);

		void GaussianBlur(const TextureRegion& from, const RenderTexture& to, const Vec2& direction, BoxFilterSize boxFilterSize = BoxFilterSize::BoxFilter9x9);

		/// @brief テクスチャの内容をガウスぼかしして別のレンダーテクスチャに描画します。
		/// @param from 元のテクスチャ
		/// @param internalBuffer 中間状態を格納するレンダーテクスチャ
		/// @param to 描画先のレンダーテクスチャ
		/// @param boxFilterSize ボックスフィルタのサイズ
		/// @remark internalBuffer は from や　to と同サイズで異なるテクスチャである必要があります。
		void GaussianBlur(const TextureRegion& from, const RenderTexture& internalBuffer, const RenderTexture& to, BoxFilterSize boxFilterSize = BoxFilterSize::BoxFilter9x9);

		/// @brief 3D シーンを描画したリニア色空間のレンダーテクスチャを、メインのシーンに転送します。
		/// @param src 転送するテクスチャ
		/// @param textureFilter リサイズする場合のテクスチャフィルタ
		/// @param dst メインのシーンの転送先領域
		void LinearToScreen(const TextureRegion& src, TextureFilter textureFilter, const RectF& dst = RectF{ Graphics2D::GetRenderTargetSize() });

		/// @brief 3D シーンを描画したリニア色空間のレンダーテクスチャを、メインのシーンに転送します。
		/// @param src 転送するテクスチャ
		/// @param pos メインのシーンの転送先の座標
		/// @param textureFilter リサイズする場合のテクスチャフィルタ
		void LinearToScreen(const TextureRegion& src, const Vec2& pos, TextureFilter textureFilter = TextureFilter::Linear);

		/// @brief 3D シーンを描画したリニア色空間のレンダーテクスチャを、メインのシーンに転送します。
		/// @param src 転送するテクスチャ
		/// @param dst メインのシーンの転送先領域
		/// @param textureFilter リサイズする場合のテクスチャフィルタ
		void LinearToScreen(const TextureRegion& src, const RectF& dst = RectF{ Graphics2D::GetRenderTargetSize() }, TextureFilter textureFilter = TextureFilter::Linear);
	
		/// @brief 指定した四角形に射影変換を用いてテクスチャを描画します。
		/// @param quad 四角形
		/// @param texture テクスチャ
		/// @remark 内部で専用の頂点シェーダおよびピクセルシェーダ、頂点シェーダ定数バッファ slot 1, ピクセルシェーダ定数バッファ slot 1 を使用します。
		/// @remark ミップマップを持つテクスチャを使用する場合は、テクスチャのサンプラーステートを Aniso に設定すると、高品質な描画が可能です。
		void QuadWarp(const Quad& quad, const TextureRegion& texture);
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		/// @brief HLSL コンパイルオプション | HLSL compile options
		/// @remark see D3DCOMPILE Constants
		enum class HLSLCompileOption
		{
			Debug				= (1 << 0),
			AvoidFlowControl	= (1 << 9),
			PreferFlowControl	= (1 << 10),
			EnableStrictness	= (1 << 11),
			OptimizationLevel3	= (1 << 15),
			WarningsAreErrors	= (1 << 18),
			Default				= EnableStrictness | OptimizationLevel3 | WarningsAreErrors,
		};
		DEFINE_BITMASK_OPERATORS(HLSLCompileOption);

		/// @brief HLSL コンパイラが利用可能かを返します。
		/// @return HLSL コンパイラが利用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsHLSLCompilerAvailable() noexcept;

		/// @brief HLSL ファイルをコンパイルし、生成したシェーダバイナリをファイルに保存します。
		/// @param hlslFilePath HLSL ファイルのパス
		/// @param toFilePath 保存先のファイルパス
		/// @param stage シェーダステージ
		/// @param entryPoint シェーダプログラムのエントリポイント
		/// @param flags HLSL のコンパイルオプション
		/// @return シェーダバイナリを生成し、ファイルの保存に成功した場合 true, それ以外の場合は false
		bool CompileHLSLToFile(FilePathView hlslFilePath, FilePathView toFilePath, ShaderStage stage, StringView entryPoint, HLSLCompileOption flags = HLSLCompileOption::Default);
	}

# endif
}
