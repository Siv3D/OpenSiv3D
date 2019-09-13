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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "AssetHandle.hpp"
# include "Rectangle.hpp"
# include "Image.hpp"
# include "TextureDesc.hpp"

namespace s3d
{
	class Texture
	{
	protected:

		struct Tag {};

		using TextureHandle = AssetHandle<Tag>;
		
		std::shared_ptr<TextureHandle> m_handle;

		friend TextureHandle::AssetHandle();
		
		friend TextureHandle::AssetHandle(const IDWrapperType) noexcept;
		
		friend TextureHandle::~AssetHandle();

		struct Dynamic {};

		struct Render {};

		struct MSRender {};

		Texture(Dynamic, uint32 width, uint32 height, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);

		Texture(Dynamic, uint32 width, uint32 height, const ColorF& color, TextureFormat format, TextureDesc desc);

		Texture(Render, uint32 width, uint32 height, TextureFormat format);

		Texture(Render, const Image& image);

		Texture(MSRender, uint32 width, uint32 height, TextureFormat format);

	public:

		using IDType = TextureHandle::IDWrapperType;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Texture();

		/// <summary>
		/// 画像からテクスチャを作成します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像が空の場合、空のテクスチャを作成します。
		/// </remarks>
		explicit Texture(const Image& image, TextureDesc desc = TextureDesc::Unmipped);

		Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);

		/// <summary>
		/// 画像ファイルからテクスチャを作成します。
		/// </summary>
		/// <param name="path">
		/// 画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		explicit Texture(const FilePath& path, TextureDesc desc = TextureDesc::Unmipped);

		explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 2 つの画像ファイルからテクスチャを作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB を読み込む画像ファイルのパス
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Texture(const FilePath& rgb, const FilePath& alpha, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 画像ファイルからアルファ値を作成し、テクスチャを作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB 成分の色
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Texture(const Color& rgb, const FilePath& alpha, TextureDesc desc = TextureDesc::Unmipped);
		
		explicit Texture(const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		explicit Texture(const Icon& icon, TextureDesc desc = TextureDesc::Unmipped);
		
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Texture();

		/// <summary>
		/// テクスチャをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じテクスチャが使われていない場合、テクスチャのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// テクスチャが空かどうかを示します。
		/// </summary>
		[[nodiscard]] bool isEmpty() const;

		/// <summary>
		/// テクスチャが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// テクスチャが空ではない場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const
		{
			return !isEmpty();
		}

		/// <summary>
		/// テクスチャハンドルの ID を示します。
		/// </summary>
		[[nodiscard]] IDType id() const;

		/// <summary>
		/// 2 つの Texture が同じかどうかを返します。
		/// </summary>
		/// <param name="texture">
		/// 比較する Texture
		/// </param>
		/// <returns>
		/// 2 つの Texture が同じ場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator ==(const Texture& texture) const;

		/// <summary>
		/// 2 つの Texture が異なるかどうかを返します。
		/// </summary>
		/// <param name="texture">
		/// 比較する Texture
		/// </param>
		/// <returns>
		/// 2 つの Texture が異なる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator !=(const Texture& texture) const;

		[[nodiscard]] int32 width() const;

		[[nodiscard]] int32 height() const;

		[[nodiscard]] Size size() const;

		[[nodiscard]] TextureDesc getDesc() const;

		[[nodiscard]] TextureFormat getFormat() const;

		[[nodiscard]] bool isMipped() const;

		[[nodiscard]] bool isSDF() const;

		[[nodiscard]] Rect region(int32 x, int32 y) const;

		[[nodiscard]] Rect region(const Point& pos = Point(0, 0)) const;

		[[nodiscard]] RectF region(double x, double y) const;

		[[nodiscard]] RectF region(const Vec2& pos) const;

		[[nodiscard]] RectF regionAt(double x, double y) const;

		[[nodiscard]] RectF regionAt(const Vec2& pos) const;

		/// <summary>
		/// テクスチャを描きます。
		/// </summary>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const ColorF& diffuse = Palette::White) const;

		RectF draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 描画開始位置の X 座標
		/// </param>
		/// <param name="y">
		/// 描画開始位置の Y 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF draw(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(double x, double y, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(double x, double y, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 描画開始位置
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF draw(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(const Vec2& pos, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(const Vec2& pos, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;


		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::center_<Vec2> center, const ColorF& diffuse = Palette::White) const;

		RectF drawClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="y">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 中心位置の座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF drawAtClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		[[nodiscard]] TextureRegion operator ()(double x, double y, double w, double h) const;

		[[nodiscard]] TextureRegion operator ()(const Vec2& xy, double w, double h) const;

		[[nodiscard]] TextureRegion operator ()(double x, double y, double size) const;

		[[nodiscard]] TextureRegion operator ()(double x, double y, const Vec2& size) const;

		[[nodiscard]] TextureRegion operator ()(const Vec2& xy, const Vec2& size) const;

		/// <summary>
		/// テクスチャ内の範囲を表す TextureRegion を返します。
		/// </summary>
		/// <param name="rect">
		/// 範囲（ピクセル）
		/// </param>
		/// <returns>
		/// テクスチャの範囲を表す TextureRegion
		/// </returns>
		[[nodiscard]] TextureRegion operator ()(const RectF& rect) const;

		[[nodiscard]] TextureRegion uv(double u, double v, double w, double h) const;

		[[nodiscard]] TextureRegion uv(const RectF& rect) const;

		[[nodiscard]] TextureRegion mirrored() const;

		[[nodiscard]] TextureRegion mirrored(bool doMirror) const;

		[[nodiscard]] TextureRegion flipped() const;

		[[nodiscard]] TextureRegion flipped(bool doFlip) const;

		[[nodiscard]] TextureRegion scaled(double s) const;

		[[nodiscard]] TextureRegion scaled(double xs, double ys) const;

		[[nodiscard]] TextureRegion scaled(const Vec2& s) const;

		[[nodiscard]] TextureRegion resized(double size) const;

		[[nodiscard]] TextureRegion resized(double width, double height) const;

		[[nodiscard]] TextureRegion resized(const Vec2& size) const;

		[[nodiscard]] TextureRegion repeated(double xRepeat, double yRepeat) const;

		[[nodiscard]] TextureRegion repeated(const Vec2& _repeat) const;

		[[nodiscard]] TextureRegion mapped(double width, double height) const;

		[[nodiscard]] TextureRegion mapped(const Vec2& size) const;

		[[nodiscard]] TextureRegion fitted(double width, double height, bool scaleUp = true) const;

		[[nodiscard]] TextureRegion fitted(const Vec2& size, bool scaleUp = true) const;

		[[nodiscard]] TexturedQuad rotated(double angle) const;

		[[nodiscard]] TexturedQuad rotatedAt(double x, double y, double angle) const;

		[[nodiscard]] TexturedQuad rotatedAt(const Vec2& pos, double angle) const;
	};

	using TextureID = Texture::IDType;
}
