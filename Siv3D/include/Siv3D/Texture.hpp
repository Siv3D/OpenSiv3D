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
# include <memory>
# include "Common.hpp"
# include "Image.hpp"
# include "TextureDesc.hpp"
# include "TextureFormat.hpp"
# include "AssetHandle.hpp"
# include "2DShapesFwd.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	class Texture : public AssetHandle<Texture>
	{
	public:

		Texture();

		explicit Texture(const Image& image, TextureDesc desc = TextureDesc::Unmipped);

		Texture(const Image& image, const Array<Image>& mipmaps, TextureDesc desc = TextureDesc::Mipped);

		explicit Texture(FilePathView path, TextureDesc desc = TextureDesc::Unmipped);

		explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);

		Texture(FilePathView rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		Texture(const Color& rgb, FilePathView alpha, TextureDesc desc = TextureDesc::Unmipped);

		//explicit Texture(const Emoji& emoji, TextureDesc desc = TextureDesc::Mipped);

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

		//RectF drawClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		//RectF drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;
	
		RectF drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		//RectF drawAtClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		//RectF drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;
	};
}
