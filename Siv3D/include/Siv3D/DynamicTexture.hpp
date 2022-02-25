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
# include "Texture.hpp"

namespace s3d
{
	/// @brief 中身を更新できる、動的テクスチャクラス
	/// @remark テクスチャの中身を更新する場合、新しい Texture を毎回作成する代わりにこのクラスの `fill()` を使うのが効率的です。
	class DynamicTexture : public Texture
	{
	public:

		SIV3D_NODISCARD_CXX20
		DynamicTexture() = default;

		SIV3D_NODISCARD_CXX20
		DynamicTexture(uint32 width, uint32 height, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		DynamicTexture(uint32 width, uint32 height, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		explicit DynamicTexture(const Size& size, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		DynamicTexture(const Size& size, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		SIV3D_NODISCARD_CXX20
		DynamicTexture(const Image& image, TextureDesc desc);

		SIV3D_NODISCARD_CXX20
		explicit DynamicTexture(const Image& image, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, TextureDesc desc = TextureDesc::Unmipped);

		bool fill(const ColorF& color);

		bool fillRegion(const ColorF& color, const Rect& rect);

		/// @brief 動的テクスチャの中身を同じ大きさの画像で更新します。
		/// @remark 動的テクスチャが空の場合は新しい動的テクスチャを画像から作成します。
		/// @param image 画像
		/// @return 動的テクスチャの更新または作成に成功した場合 true, それ以外の場合は false
		bool fill(const Image& image);

		bool fillRegion(const Image& image, const Rect& rect);

		bool fillIfNotBusy(const Image& image);

		bool fillRegionIfNotBusy(const Image& image, const Rect& rect);

		void swap(DynamicTexture& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::DynamicTexture& a, s3d::DynamicTexture& b) noexcept;

# include "detail/DynamicTexture.ipp"
