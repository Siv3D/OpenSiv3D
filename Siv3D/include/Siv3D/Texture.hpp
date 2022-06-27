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
# include "Image.hpp"
# include "TextureDesc.hpp"
# include "TextureFormat.hpp"
# include "AssetHandle.hpp"
# include "2DShapesFwd.hpp"
# include "PredefinedNamedParameter.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct TextureRegion;
	struct TexturedQuad;
	struct TexturedRoundRect;

	/// @brief テクスチャ
	/// @remark 描画できる画像です。
	class Texture : public AssetHandle<Texture>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Texture();

		SIV3D_NODISCARD_CXX20
		explicit Texture(const Image& image, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);

		/// @brief 画像ファイルからテクスチャを作成します。
		/// @param path ファイルパス
		/// @param desc テクスチャの設定
		SIV3D_NODISCARD_CXX20
		explicit Texture(FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		Texture(FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		Texture(const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		/// @brief 絵文字からテクスチャを作成します。
		/// @param emoji 絵文字
		/// @remark テクスチャのサイズは `Emoji::ImageSize` です。
		/// @param desc テクスチャの設定
		SIV3D_NODISCARD_CXX20
		explicit Texture(const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		/// @brief アイコンからテクスチャを作成します。
		/// @param icon アイコン
		/// @param size アイコンのサイズ
		/// @param desc テクスチャの設定
		SIV3D_NODISCARD_CXX20
		explicit Texture(const Icon& icon, int32 size, TextureDesc desc = TextureDesc::Mipped);

		virtual ~Texture();

		/// @brief テクスチャの幅（ピクセル）を返します。
		/// @return  テクスチャの幅（ピクセル）
		[[nodiscard]]
		int32 width() const;

		/// @brief テクスチャの高さ（ピクセル）を返します。
		/// @return  テクスチャの高さ（ピクセル）
		[[nodiscard]]
		int32 height() const;

		/// @brief テクスチャの幅と高さ（ピクセル）を返します。
		/// @return  テクスチャの幅と高さ（ピクセル）
		[[nodiscard]]
		Size size() const;

		template <class Type = double>
		[[nodiscard]]
		Type horizontalAspectRatio() const noexcept;

		/// @brief テクスチャの設定を返します。
		/// @return テクスチャの設定
		[[nodiscard]]
		TextureDesc getDesc() const;

		/// @brief テクスチャのフォーマットを返します。
		/// @return テクスチャのフォーマット
		[[nodiscard]]
		TextureFormat getFormat() const;

		/// @brief ミップマッピングが有効化されているかを返します。
		/// @return ミップマッピングが有効化されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isMipped() const;

		[[nodiscard]]
		bool srgbSampling() const;

		[[nodiscard]]
		bool isSDF() const;

		/// @brief デプスバッファを持っているかを返します。
		/// @return デプスバッファを持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasDepth() const;

		[[nodiscard]]
		Rect region(int32 x, int32 y) const;

		[[nodiscard]]
		Rect region(Point pos = Point{ 0, 0 }) const;

		[[nodiscard]]
		RectF region(double x, double y) const;

		[[nodiscard]]
		RectF region(Vec2 pos) const;

		[[nodiscard]]
		RectF regionAt(double x, double y) const;

		[[nodiscard]]
		RectF regionAt(Vec2 pos) const;

		RectF draw(const ColorF& diffuse = Palette::White) const;

		RectF draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// @brief 左上位置を指定してテクスチャを描画します。
		/// @param x 描画を開始する左上の X 座標
		/// @param y 描画を開始する左上の Y 座標
		/// @param diffuse 描画時に乗算する色
		/// @return テクスチャが描画された領域
		RectF draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF draw(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(double x, double y, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(double x, double y, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

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

		RectF drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF drawClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawAtClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		[[nodiscard]]
		TextureRegion operator ()(double x, double y, double w, double h) const;

		[[nodiscard]]
		TextureRegion operator ()(const Vec2& xy, double w, double h) const;

		[[nodiscard]]
		TextureRegion operator ()(double x, double y, double size) const;

		[[nodiscard]]
		TextureRegion operator ()(double x, double y, const Vec2& size) const;

		[[nodiscard]]
		TextureRegion operator ()(const Vec2& xy, const Vec2& size) const;

		[[nodiscard]]
		TextureRegion operator ()(const RectF& rect) const;

		[[nodiscard]]
		TextureRegion uv(double u, double v, double w, double h) const;

		[[nodiscard]]
		TextureRegion uv(const RectF& rect) const;

		[[nodiscard]]
		TextureRegion mirrored() const;

		[[nodiscard]]
		TextureRegion mirrored(bool doMirror) const;

		[[nodiscard]]
		TextureRegion flipped() const;

		[[nodiscard]]
		TextureRegion flipped(bool doFlip) const;

		[[nodiscard]]
		TextureRegion scaled(double s) const;

		[[nodiscard]]
		TextureRegion scaled(double xs, double ys) const;

		[[nodiscard]]
		TextureRegion scaled(Vec2 s) const;

		/// @brief 長辺が指定したサイズになるようリサイズした TextureRegion を返します。
		/// @param size 長辺のサイズ
		/// @return 長辺が指定したサイズになるようリサイズした TextureRegion
		[[nodiscard]]
		TextureRegion resized(double size) const;

		[[nodiscard]]
		TextureRegion resized(double width, double height) const;

		[[nodiscard]]
		TextureRegion resized(Vec2 size) const;

		[[nodiscard]]
		TextureRegion repeated(double xRepeat, double yRepeat) const;

		[[nodiscard]]
		TextureRegion repeated(Vec2 _repeat) const;

		[[nodiscard]]
		TextureRegion mapped(double width, double height) const;

		[[nodiscard]]
		TextureRegion mapped(Vec2 size) const;

		[[nodiscard]]
		TextureRegion fitted(double width, double height, AllowScaleUp allowScaleUp = AllowScaleUp::Yes) const;

		[[nodiscard]]
		TextureRegion fitted(const Vec2& size, AllowScaleUp allowScaleUp = AllowScaleUp::Yes) const;

		[[nodiscard]]
		TexturedQuad rotated(double angle) const;

		[[nodiscard]]
		TexturedQuad rotatedAt(double x, double y, double angle) const;

		[[nodiscard]]
		TexturedQuad rotatedAt(const Vec2& pos, double angle) const;

		[[nodiscard]]
		TexturedRoundRect rounded(double r) const;

		[[nodiscard]]
		TexturedRoundRect rounded(double x, double y, double w, double h, double r) const;

		void swap(Texture& other) noexcept;

	protected:

		struct Dynamic {};

		struct Render {};

		struct MSRender {};

		SIV3D_NODISCARD_CXX20
		Texture(Dynamic, const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		Texture(Dynamic, const Size& size, const ColorF& color, const TextureFormat& format, TextureDesc desc);
	
		SIV3D_NODISCARD_CXX20
		Texture(Render, const Size& size, const TextureFormat& format, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		Texture(Render, const Image& image, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		Texture(Render, const Grid<float>& image, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		Texture(Render, const Grid<Float2>& image, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		Texture(Render, const Grid<Float4>& image, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		Texture(MSRender, const Size& size, const TextureFormat& format, HasDepth hasDepth);
	};
}

template <>
inline void std::swap(s3d::Texture& a, s3d::Texture& b) noexcept;

# include "detail/Texture.ipp"
