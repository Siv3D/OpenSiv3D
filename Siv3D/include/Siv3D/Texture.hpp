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
	};
}
