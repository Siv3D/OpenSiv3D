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
# include <memory>
# include "Common.hpp"
# include "Scene.hpp"
# include "Texture.hpp"
# include "TextureRegion.hpp"
# include "TexturedQuad.hpp"
# include "TexturedRoundRect.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class VideoReader;

	/// @brief 動画を Texture のように扱えるクラス
	class VideoTexture
	{
	public:

		SIV3D_NODISCARD_CXX20
		VideoTexture();

		/// @brief 動画テクスチャを作成します。
		/// @param path 動画ファイルのパス
		/// @param loop ループするか
		SIV3D_NODISCARD_CXX20
		explicit VideoTexture(FilePathView path, Loop loop = Loop::Yes, TextureDesc desc = TextureDesc::Unmipped);

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void release();

		/// @brief 動画の時間を進めます。
		/// @param deltaTimeSec 進める時間（秒）
		/// @remark 1 フレーム先までバッファリングするため、この関数を毎フレーム呼び出すのが最も効率的です。
		void advance(double deltaTimeSec = Scene::DeltaTime()) const;

		/// @brief 動画の再生時間を先頭に戻します。
		void reset() const;

		/// @brief 動画がループするかを返します。
		/// @return 動画がループする場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isLoop() const noexcept;

		[[nodiscard]]
		double posSec() const noexcept;

		/// @brief 動画の長さ（秒）を返します。
		/// @return 動画の長さ（秒）
		[[nodiscard]]
		double lengthSec() const;

		void setPosSec(double posSec) const;

		[[nodiscard]]
		const Texture& getTexture() const noexcept;

		[[nodiscard]]
		operator const Texture& () const noexcept;

		[[nodiscard]]
		const VideoReader& getVideoReader() const noexcept;

		/// @brief 動画の幅（ピクセル）を返します。
		/// @return 動画の幅（ピクセル）
		[[nodiscard]]
		int32 width() const;

		/// @brief 動画の高さ（ピクセル）を返します。
		/// @return 動画の高さ（ピクセル）
		[[nodiscard]]
		int32 height() const;

		/// @brief 動画の幅と高さ（ピクセル）を返します。
		/// @return 動画の幅と高さ（ピクセル）
		[[nodiscard]]
		Size size() const;

		[[nodiscard]]
		TextureDesc getDesc() const;

		[[nodiscard]]
		TextureFormat getFormat() const;

		[[nodiscard]]
		bool isMipped() const;

		[[nodiscard]]
		bool isSDF() const;

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

		void swap(VideoTexture& other) noexcept;

	private:

		class VideoTextureDetail;

		std::shared_ptr<VideoTextureDetail> pImpl;
	};
}

template <>
inline void std::swap(s3d::VideoTexture& a, s3d::VideoTexture& b) noexcept
{
	a.swap(b);
}
