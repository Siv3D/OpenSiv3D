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
# include <memory>
# include "Common.hpp"
# include "Texture.hpp"
# include "TextureFilter.hpp"

namespace s3d
{
	/// @brief 9 パッチテクスチャ
	class NinePatch
	{
	public:

		/// @brief 9 パッチのスタイル
		struct Style
		{
			/// @brief 上端と下端のパッチをタイリングするか
			bool tileTopBottom = false;

			/// @brief 左端と右端のパッチをタイリングするか
			bool tileLeftRight = false;

			/// @brief 中央のパッチをタイリングするか
			bool tileCenter = false;

			/// @brief 狭すぎる場合に角を描画しないフォールバックを行うか
			bool fallbackToSimple = true;

			/// @brief デフォルトのスタイル
			/// @return デフォルトのスタイル
			[[nodiscard]]
			static constexpr Style Default() noexcept;

			/// @brief 上端と下端のパッチをタイリングするスタイル
			/// @return 上端と下端のパッチをタイリングするスタイル
			[[nodiscard]]
			static constexpr Style TileTopBottom() noexcept;

			/// @brief 左端と右端のパッチをタイリングするスタイル
			/// @return 左端と右端のパッチをタイリングするスタイル
			[[nodiscard]]
			static constexpr Style TileLeftRight() noexcept;

			/// @brief 中央のパッチをタイリングするスタイル
			/// @return 中央のパッチをタイリングするスタイル
			[[nodiscard]]
			static constexpr Style TileCenter() noexcept;

			/// @brief 上端と下端、左端、右端のパッチをタイリングするスタイル
			/// @return 上端と下端、左端、右端のパッチをタイリングするスタイル
			[[nodiscard]]
			static constexpr Style Tile4() noexcept;

			/// @brief すべてのパッチをタイリングするスタイル
			/// @return すべてのパッチをタイリングするスタイル
			[[nodiscard]]
			static constexpr Style TileAll() noexcept;
		};

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		NinePatch() = default;

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param texture テクスチャ
		/// @param cornerSize 9 パッチテクスチャの四隅のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		explicit NinePatch(const Texture& texture, int32 cornerSize, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param texture テクスチャ
		/// @param cornerWidth 9 パッチテクスチャの左および右のパッチの幅（ピクセル）
		/// @param cornerHeight 9 パッチテクスチャの上および下のパッチの高さ（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		explicit NinePatch(const Texture& texture, int32 cornerWidth, int32 cornerHeight, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param texture テクスチャ
		/// @param leftWidth 9 パッチテクスチャの左のパッチの幅（ピクセル）
		/// @param topHeight 9 パッチテクスチャの上のパッチの高さ（ピクセル）
		/// @param rightWidth 9 パッチテクスチャの右のパッチの幅（ピクセル）
		/// @param bottomHeight 9 パッチテクスチャの下のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		explicit NinePatch(const Texture& texture, int32 leftWidth, int32 topHeight, int32 rightWidth, int32 bottomHeight, const Style& style = Style::Default());

		/// @brief 9 パッチを用いて長方形を描画します。
		/// @param rect 長方形
		/// @param color 乗算する色
		void draw(const RectF& rect, const ColorF& color = Palette::White) const;

		/// @brief 9 パッチを用いて長方形を描画します。
		/// @param rect 長方形
		/// @param textureScale 角のスケール
		/// @param textureFilter テクスチャのフィルタ
		/// @param color 乗算する色
		void draw(const RectF& rect, double textureScale, TextureFilter textureFilter = TextureFilter::Linear, const ColorF& color = Palette::White) const;

		void release();

	private:

		class NinePatchDetail;

		std::shared_ptr<NinePatchDetail> pImpl;
	};
}

# include "detail/NinePatch.ipp"
