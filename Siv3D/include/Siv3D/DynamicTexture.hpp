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
# include "Fwd.hpp"
# include "Texture.hpp"
# include "TextureFormat.hpp"

namespace s3d
{
	/// <summary>
	/// 動的テクスチャ
	/// </summary>
	/// <remarks>
	/// 描画可能な画像です。
	/// Texture と異なり、メモリを再確保することなく内容を更新できます。
	/// </remarks>
	class DynamicTexture : public Texture
	{
	public:

		DynamicTexture() = default;

		DynamicTexture(uint32 width, uint32 height, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		DynamicTexture(uint32 width, uint32 height, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		explicit DynamicTexture(const Size& size, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		DynamicTexture(const Size& size, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		DynamicTexture(const Image& image, TextureDesc desc);

		explicit DynamicTexture(const Image& image, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		bool fill(const ColorF& color);

		bool fillRegion(const ColorF& color, const Rect& rect);

		/// <summary>
		/// 動的テクスチャの中身を同じ大きさの画像で更新します。
		/// 動的テクスチャが空の場合は新しい動的テクスチャを画像から作成します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <returns>
		/// 動的テクスチャの更新か作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool fill(const Image& image);

		bool fillRegion(const Image& image, const Rect& rect);

		bool fillIfNotBusy(const Image& image);

		bool fillRegionIfNotBusy(const Image& image, const Rect& rect);
	};
}
