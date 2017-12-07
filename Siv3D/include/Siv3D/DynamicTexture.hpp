//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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
	private:

	public:

		DynamicTexture() = default;

		DynamicTexture(uint32 width, uint32 height, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		DynamicTexture(uint32 width, uint32 height, const ColorF& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		explicit DynamicTexture(const Size& size, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped)
			: DynamicTexture(size.x, size.y, format, desc) {}

		DynamicTexture(const Size& size, const ColorF& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped)
			: DynamicTexture(size.x, size.y, color, format, desc) {}

		explicit DynamicTexture(const Image& image, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		bool fill(const ColorF& color);

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
	};
}
