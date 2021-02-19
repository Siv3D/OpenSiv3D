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

	class Texture : public AssetHandle<Texture>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Texture();

		SIV3D_NODISCARD_CXX20
		explicit Texture(const Image& image, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);

		SIV3D_NODISCARD_CXX20
		explicit Texture(FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		Texture(FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		Texture(const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		//SIV3D_NODISCARD_CXX20
		//explicit Texture(const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

		//SIV3D_NODISCARD_CXX20
		//explicit Texture(const Icon& icon, TextureDesc desc = TextureDesc::Unmipped);

		virtual ~Texture();

		[[nodiscard]]
		int32 width() const;

		[[nodiscard]]
		int32 height() const;

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

	protected:

		struct Dynamic {};

		struct Render {};

		struct MSRender {};

		Texture(Dynamic, const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc);

		Texture(Dynamic, const Size& size, const ColorF& color, const TextureFormat& format, TextureDesc desc);
	};
}
