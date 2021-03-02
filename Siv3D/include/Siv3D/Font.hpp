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
# include "String.hpp"
# include "AssetHandle.hpp"
# include "FontStyle.hpp"
# include "GlyphInfo.hpp"
# include "GlyphCluster.hpp"
# include "OutlineGlyph.hpp"
# include "BitmapGlyph.hpp"
# include "SDFGlyph.hpp"
# include "MSDFGlyph.hpp"
# include "FontMethod.hpp"
# include "Typeface.hpp"
# include "Glyph.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct DrawableText;

	/// @brief フォント
	class Font : public AssetHandle<Font>
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Font();

		/// @brief フォントを作成します。
		/// @param fontSize フォントのサイズ
		/// @param path ロードするフォントファイルのパス
		/// @param style フォントのスタイル
		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		/// @brief フォントを作成します。
		/// @param fontSize フォントのサイズ
		/// @param path ロードするフォントファイルのパス
		/// @param faceIndex フォントファイルが複数のフォントコレクションを含む場合のインデックス
		/// @param style フォントのスタイル
		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		/// @brief フォントを作成します。
		/// @param fontSize フォントのサイズ
		/// @param typeface フォントの種類
		/// @param style フォントのスタイル
		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);

		/// @brief フォントを作成します。
		/// @param fontMethod フォントのレンダリング方式
		/// @param fontSize フォントのサイズ
		/// @param path ロードするフォントファイルのパス
		/// @param style フォントのスタイル
		SIV3D_NODISCARD_CXX20
		Font(FontMethod fontMethod, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		/// @brief フォントを作成します。
		/// @param fontMethod フォントのレンダリング方式
		/// @param fontSize フォントのサイズ
		/// @param path ロードするフォントファイルのパス
		/// @param faceIndex フォントファイルが複数のフォントコレクションを含む場合のインデックス
		/// @param style フォントのスタイル
		SIV3D_NODISCARD_CXX20
		Font(FontMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		/// @brief フォントを作成します。
		/// @param fontMethod フォントのレンダリング方式
		/// @param fontSize フォントのサイズ
		/// @param typeface フォントの種類
		/// @param style フォントのスタイル
		SIV3D_NODISCARD_CXX20
		Font(FontMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);

		/// @brief デストラクタ
		virtual ~Font();

		/// @brief フォールバッグフォントを追加します。
		/// @param font フォールバックとして追加するフォント
		/// @return 追加に成功した場合 true, それ以外の場合は false
		bool addFallback(const Font& font) const;

		bool addFallback(Font&& font) const = delete;

		/// @brief ロードしたフォントのファミリーネームを返します。
		/// @return ロードしたフォントのファミリーネーム
		[[nodiscard]]
		const String& familyName() const;

		/// @brief ロードしたフォントのスタイルネームを返します。
		/// @return ロードしたフォントのスタイルネーム
		[[nodiscard]]
		const String& styleName() const;

		/// @brief フォントが色情報を持つかを返します。
		/// @return フォントが色情報を持つ場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasColor() const;

		/// @brief フォントのスタイルを返します。
		/// @return フォントのスタイル
		[[nodiscard]]
		FontStyle style() const;

		/// @brief フォントのレンダリング方式を返します。
		/// @return フォントのレンダリング方式
		[[nodiscard]]
		FontMethod method() const;

		/// @brief フォトのサイズを返します。
		/// @return フォントのサイズ
		[[nodiscard]]
		int32 fontSize() const;

		/// @brief フォントのアセンダーの高さ（ピクセル）を返します。
		/// @return フォントのアセンダーの高さ（ピクセル）
		[[nodiscard]]
		int32 ascender() const;

		/// @brief フォントのディセンダーの高さ（ピクセル）を返します。
		/// @return フォントのディセンダーの高さ（ピクセル）
		[[nodiscard]]
		int32 descender() const;

		/// @brief フォントの高さ（ピクセル）を返します。
		/// @remark `ascender() + descender()` と一致します。
		/// @return フォントの高さ（ピクセル）
		[[nodiscard]]
		int32 height() const;

		/// @brief 半角スペースの幅（ピクセル）を返します。
		/// @return 半角スペースの幅（ピクセル）
		[[nodiscard]]
		double spaceWidth() const;

		/// @brief レンダリング方式が SDF, MSDF の場合にキャッシュテクスチャに保存する文字の周囲の余白を設定します。 
		/// @param thickness 
		/// @remark デフォルト値は 2 です。
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		void setBufferThickness(int32 thickness) const;

		/// @brief  レンダリング方式が SDF, MSDF の場合にキャッシュテクスチャに保存する文字の周囲の余白を返します。
		/// @return レンダリング方式が SDF, MSDF の場合にキャッシュテクスチャに保存する文字の周囲の余白
		[[nodiscard]]
		int32 getBufferThickness() const;

		/// @brief 指定した文字のグリフを持つかを返します。
		/// @param ch 文字
		/// @return グリフを持つ場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasGlyph(char32 ch) const;

		/// @brief 指定した文字のグリフを持つかを返します。
		/// @param ch 文字
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @return グリフを持つ場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasGlyph(StringView ch) const;

		/// @brief フォントが持つグリフの数を返します。
		/// @return フォントが持つグリフの数。
		[[nodiscard]]
		uint32 num_glyphs() const;

		/// @brief 指定した文字の、このフォント内でのグリフインデックスを返します。
		/// @param ch 文字
		/// @return このフォント内でのグリフインデックス
		[[nodiscard]]
		GlyphIndex getGlyphIndex(char32 ch) const;

		/// @brief 指定した文字の、このフォント内でのグリフインデックスを返します。
		/// @param ch 文字
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @return このフォント内でのグリフインデックス
		[[nodiscard]]
		GlyphIndex getGlyphIndex(StringView ch) const;

		/// @brief 文字列に対応するグリフクラスターを返します。
		/// @param s 文字列
		/// @param useFallback フォールバックフォントを使用するか
		/// @return 文字列に対応するグリフクラスター
		[[nodiscard]]
		Array<GlyphCluster> getGlyphClusters(StringView s, bool useFallback = true) const;

		/// @brief 指定した文字のグリフ情報を返します。
		/// @param ch 文字
		/// @return 文字のグリフ情報
		[[nodiscard]]
		GlyphInfo getGlyphInfo(char32 ch) const;

		/// @brief 指定した文字のグリフ情報を返します。
		/// @param ch 文字
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @return 文字のグリフ情報
		[[nodiscard]]
		GlyphInfo getGlyphInfo(StringView ch) const;

		/// @brief 指定した文字のグリフ情報を返します。
		/// @param glyphIndex 文字のグリフインデックス
		/// @return 文字のグリフ情報
		[[nodiscard]]
		GlyphInfo getGlyphInfoByGlyphIndex(GlyphIndex glyphIndex) const;

		/// @brief 指定した文字の輪郭グリフを作成して返します。
		/// @param ch 文字
		/// @param closeRing 各輪郭の頂点配列について、末尾の頂点を先頭の頂点と一致させるか
		/// @return 文字の輪郭グリフ
		[[nodiscard]]
		OutlineGlyph renderOutline(char32 ch, CloseRing closeRing = CloseRing::No) const;

		/// @brief 指定した文字の輪郭グリフを作成して返します。
		/// @param ch 文字
		/// @param closeRing 各輪郭の頂点配列について、末尾の頂点を先頭の頂点と一致させるか
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @return 文字の輪郭グリフ
		[[nodiscard]]
		OutlineGlyph renderOutline(StringView ch, CloseRing closeRing = CloseRing::No) const;

		/// @brief 指定した文字の輪郭グリフを作成して返します。
		/// @param glyphIndex 文字のグリフインデックス
		/// @param closeRing 各輪郭の頂点配列について、末尾の頂点を先頭の頂点と一致させるか
		/// @return 文字の輪郭グリフ
		[[nodiscard]]
		OutlineGlyph renderOutlineByGlyphIndex(GlyphIndex glyphIndex, CloseRing closeRing = CloseRing::No) const;

		/// @brief 指定した文字列のすべての文字の輪郭グリフの配列を作成して返します。
		/// @param s 文字列
		/// @param closeRing 各輪郭の頂点配列について、末尾の頂点を先頭の頂点と一致させるか
		/// @return 文字の輪郭グリフの配列
		[[nodiscard]]
		Array<OutlineGlyph> renderOutlines(StringView s, CloseRing closeRing = CloseRing::No) const;

		/// @brief 指定した文字の Bitmap グリフを作成して返します。
		/// @param ch 文字
		/// @remark フォント自身のレンダリング方式に関わらずこの関数を使用できますが、結果を内部にキャッシュすることはしません。
		/// @return 文字の Bitmap グリフ
		[[nodiscard]]
		BitmapGlyph renderBitmap(char32 ch) const;

		/// @brief 指定した文字の Bitmap グリフを作成して返します。
		/// @param ch 文字
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @remark フォント自身のレンダリング方式に関わらずこの関数を使用できますが、結果を内部にキャッシュすることはしません。
		/// @return 文字の Bitmap グリフ
		[[nodiscard]]
		BitmapGlyph renderBitmap(StringView ch) const;

		/// @brief 指定した文字の Bitmap グリフを作成して返します。
		/// @param glyphIndex 文字のグリフインデックス
		/// @remark フォント自身のレンダリング方式に関わらずこの関数を使用できますが、結果を内部にキャッシュすることはしません。
		/// @return 文字の Bitmap グリフ
		[[nodiscard]]
		BitmapGlyph renderBitmapByGlyphIndex(GlyphIndex glyphIndex) const;

		/// @brief 指定した文字の SDF グリフを作成して返します。
		/// @param ch 文字
		/// @param buffer 文字の周囲の余白
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		/// @remark ストローク情報を持たないフォントの場合、作成に失敗して空のグリフを返します。
		/// @return 文字の SDF グリフ
		[[nodiscard]]
		SDFGlyph renderSDF(char32 ch, int32 buffer = 3) const;

		/// @brief 指定した文字の SDF グリフを作成して返します。
		/// @param ch 文字
		/// @param buffer 文字の周囲の余白
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		/// @remark ストローク情報を持たないフォントの場合、作成に失敗して空のグリフを返します。
		/// @return 文字の SDF グリフ
		[[nodiscard]]
		SDFGlyph renderSDF(StringView ch, int32 buffer = 3) const;

		/// @brief 指定した文字の SDF グリフを作成して返します。
		/// @param glyphIndex 文字のグリフインデックス
		/// @param buffer 文字の周囲の余白
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		/// @remark ストローク情報を持たないフォントの場合、作成に失敗して空のグリフを返します。
		/// @return 文字の SDF グリフ
		[[nodiscard]]
		SDFGlyph renderSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer = 3) const;

		/// @brief 指定した文字の MSDF グリフを作成して返します。
		/// @param ch 文字
		/// @param buffer 文字の周囲の余白
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		/// @remark ストローク情報を持たないフォントの場合、作成に失敗して空のグリフを返します。
		/// @return 文字の MSDF グリフ
		[[nodiscard]]
		MSDFGlyph renderMSDF(char32 ch, int32 buffer = 3) const;

		/// @brief 指定した文字の MSDF グリフを作成して返します。
		/// @param ch 文字
		/// @param buffer 文字の周囲の余白
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		/// @remark ストローク情報を持たないフォントの場合、作成に失敗して空のグリフを返します。
		/// @return 文字の MSDF グリフ
		[[nodiscard]]
		MSDFGlyph renderMSDF(StringView ch, int32 buffer = 3) const;

		/// @brief 指定した文字の MSDF グリフを作成して返します。
		/// @param glyphIndex 文字のグリフインデックス
		/// @param buffer 文字の周囲の余白
		/// @remark 小さい余白は省メモリで描画のオーバーヘッドが少ないですが、文字の輪郭の描画の品質が低下する場合があります。
		/// @remark ストローク情報を持たないフォントの場合、作成に失敗して空のグリフを返します。
		/// @return 文字の MSDF グリフ
		[[nodiscard]]
		MSDFGlyph renderMSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer = 3) const;

		/// @brief 指定した文字列のためのグリフを事前生成します。
		/// @param chars 文字列
		/// @remark 新しいグリフをキャッシュするための処理でゲーム中のフレームレートが低下するようなことを防げます。
		/// @return 事前生成に成功した場合 true, それ以外の場合は false
		bool preload(StringView chars) const;

		/// @brief フォントの内部でキャッシュされているテクスチャを返します。
		/// @return フォントの内部でキャッシュされているテクスチャ
		[[nodiscard]]
		const Texture& getTexture() const;

		/// @brief 指定した文字の描画用のグリフを返します。
		/// @param ch 文字
		/// @return 描画用グリフ
		[[nodiscard]]
		Glyph getGlyph(char32 ch) const;

		/// @brief 指定した文字の描画用のグリフを返します。
		/// @param ch 文字
		/// @remark char32 型の要素 1 つでは表現できない文字のための関数です。
		/// @return 描画用グリフ
		[[nodiscard]]
		Glyph getGlyph(StringView ch) const;

		/// @brief 指定した文字列の描画用のグリフ配列を返します。
		/// @param s 文字列
		/// @return 指定した文字列の描画用のグリフ配列
		[[nodiscard]]
		Array<Glyph> getGlyphs(StringView s) const;

		/// @brief フォントを描画するために必要な DrawableText を、文字列から構築します。
		/// @param text 文字列
		/// @return DrawableText
		[[nodiscard]]
		DrawableText operator()(const String& text) const;

		/// @brief フォントを描画するために必要な DrawableText を、文字列から構築します。
		/// @param text 文字列
		/// @return DrawableText
		[[nodiscard]]
		DrawableText operator()(String&& text) const;

		/// @brief フォントを描画するために必要な DrawableText を、一連の引数を文字列に変換することで構築します。
		/// @tparam ...Args 引数の型
		/// @param ...args 文字列に変換する値
		/// @return DrawableText
		template <class ... Args>
		[[nodiscard]]
		DrawableText operator()(const Args& ... args) const;
	};
}
