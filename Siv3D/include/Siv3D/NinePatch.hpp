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
# include "RenderTexture.hpp"
# include "TextureFilter.hpp"
# include "2DShapes.hpp"

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

		/// @brief パッチのサイズ（ピクセル）
		struct PatchSize
		{
			/// @brief 左端のパッチの幅（ピクセル）
			int32 left = 0;

			/// @brief 上端のパッチの幅（ピクセル）
			int32 top = 0;

			/// @brief 右端のパッチの幅（ピクセル）
			int32 right = 0;

			/// @brief 下端のパッチの幅（ピクセル）
			int32 bottom = 0;

			/// @brief テクスチャのサイズ（ピクセル）
			Size textureSize{ 0, 0 };

			/// @brief テクスチャにおける左上のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける左上のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect topLeftRect() const noexcept;

			/// @brief テクスチャにおける上中央のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける上中央のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect topRect() const noexcept;

			/// @brief テクスチャにおける右上のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける右上のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect topRightRect() const noexcept;

			/// @brief テクスチャにおける左中央のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける左中央のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect leftRect() const noexcept;

			/// @brief テクスチャにおける中央のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける中央のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect centerRect() const noexcept;

			/// @brief テクスチャにおける右中央のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける右中央のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect rightRect() const noexcept;

			/// @brief テクスチャにおける左下のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける左下のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect bottomLeftRect() const noexcept;

			/// @brief テクスチャにおける下中央のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける下中央のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect bottomRect() const noexcept;

			/// @brief テクスチャにおける右下のパッチの領域（ピクセル）を返します。
			/// @return テクスチャにおける右下のパッチの領域（ピクセル）
			[[nodiscard]]
			constexpr Rect bottomRightRect() const noexcept;
		};

		/// @brief タイリング用のテクスチャ（タイリングしない場合は空のテクスチャ）
		struct RepeatableTexture
		{
			/// @brief 上部のタイリング用テクスチャ
			RenderTexture top;

			/// @brief 下部のタイリング用テクスチャ
			RenderTexture bottom;

			/// @brief 左部のタイリング用テクスチャ
			RenderTexture left;

			/// @brief 右部のタイリング用テクスチャ
			RenderTexture right;

			/// @brief 中央のタイリング用テクスチャ
			RenderTexture center;
		};

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		NinePatch() = default;

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param image 画像ファイルのパス
		/// @param patchSize 9 パッチテクスチャの四隅のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(FilePathView path, int32 patchSize, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param image 画像ファイルのパス
		/// @param patchWidth 9 パッチテクスチャの左および右のパッチの幅（ピクセル）
		/// @param patchHeight 9 パッチテクスチャの上および下のパッチの高さ（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(FilePathView path, int32 patchWidth, int32 patchHeight, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param image 画像ファイルのパス
		/// @param leftWidth 9 パッチテクスチャの左のパッチの幅（ピクセル）
		/// @param topHeight 9 パッチテクスチャの上のパッチの高さ（ピクセル）
		/// @param rightWidth 9 パッチテクスチャの右のパッチの幅（ピクセル）
		/// @param bottomHeight 9 パッチテクスチャの下のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(FilePathView path, int32 leftWidth, int32 topHeight, int32 rightWidth, int32 bottomHeight, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param image 画像
		/// @param patchSize 9 パッチテクスチャの四隅のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(const Image& image, int32 patchSize, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param image 画像
		/// @param patchWidth 9 パッチテクスチャの左および右のパッチの幅（ピクセル）
		/// @param patchHeight 9 パッチテクスチャの上および下のパッチの高さ（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(const Image& image, int32 patchWidth, int32 patchHeight, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param image 画像
		/// @param leftWidth 9 パッチテクスチャの左のパッチの幅（ピクセル）
		/// @param topHeight 9 パッチテクスチャの上のパッチの高さ（ピクセル）
		/// @param rightWidth 9 パッチテクスチャの右のパッチの幅（ピクセル）
		/// @param bottomHeight 9 パッチテクスチャの下のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(const Image& image, int32 leftWidth, int32 topHeight, int32 rightWidth, int32 bottomHeight, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param texture テクスチャ
		/// @param patchSize 9 パッチテクスチャの四隅のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(const Texture& texture, int32 patchSize, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param texture テクスチャ
		/// @param patchWidth 9 パッチテクスチャの左および右のパッチの幅（ピクセル）
		/// @param patchHeight 9 パッチテクスチャの上および下のパッチの高さ（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(const Texture& texture, int32 patchWidth, int32 patchHeight, const Style& style = Style::Default());

		/// @brief 9 パッチでテクスチャを描画するクラスを作成します。
		/// @param texture テクスチャ
		/// @param leftWidth 9 パッチテクスチャの左のパッチの幅（ピクセル）
		/// @param topHeight 9 パッチテクスチャの上のパッチの高さ（ピクセル）
		/// @param rightWidth 9 パッチテクスチャの右のパッチの幅（ピクセル）
		/// @param bottomHeight 9 パッチテクスチャの下のパッチの幅（ピクセル）
		/// @param style スタイル
		SIV3D_NODISCARD_CXX20
		NinePatch(const Texture& texture, int32 leftWidth, int32 topHeight, int32 rightWidth, int32 bottomHeight, const Style& style = Style::Default());

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

		/// @brief 9 パッチのデータをクリアします。
		void release();

		/// @brief 9 パッチの元テクスチャを返します。
		/// @return 9 パッチの元テクスチャ
		[[nodiscard]]
		const Texture& getTexture() const noexcept;

		/// @brief 9 パッチのタイリング用テクスチャを返します。
		/// @return 9 パッチのタイリング用テクスチャ
		/// @remark タイリングしない場合は空のテクスチャが含まれます。
		[[nodiscard]]
		const RepeatableTexture& getRepeatableTexture() const noexcept;

		/// @brief 9 パッチのサイズ（ピクセル）を返します。
		/// @return 9 パッチのサイズ（ピクセル）
		[[nodiscard]]
		const PatchSize& getPatchSize() const noexcept;

	private:

		class NinePatchDetail;

		std::shared_ptr<NinePatchDetail> pImpl;
	};
}

# include "detail/NinePatch.ipp"
