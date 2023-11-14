﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Texture.hpp"

namespace s3d
{
	/// @brief レンダーテクスチャ
	class RenderTexture : public Texture
	{
	public:

		SIV3D_NODISCARD_CXX20
		RenderTexture();

		SIV3D_NODISCARD_CXX20
		RenderTexture(uint32 width, uint32 height, const ColorF& color = ColorF{ 0.0, 1.0 }, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		explicit RenderTexture(const Size& size, const ColorF& color = ColorF{ 0.0, 1.0 }, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(uint32 width, uint32 height, const TextureFormat& format, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(uint32 width, uint32 height, HasDepth hasDepth, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(const Size& size, const TextureFormat& format, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(const Size& size, HasDepth hasDepth, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(const Image& image, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(const Grid<float>& image, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(const Grid<Float2>& image, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		SIV3D_NODISCARD_CXX20
		RenderTexture(const Grid<Float4>& image, HasDepth hasDepth = HasDepth::No, HasMipMap hasMipMap = HasMipMap::No);

		virtual ~RenderTexture();

		/// @brief テクスチャを指定した色で塗りつぶします。デプスを持つ場合、デプスもクリアします。
		/// @param color 塗りつぶしの色
		/// @return *this
		const RenderTexture& clear(const ColorF& color) const;

		/// @brief ミップマップを生成します。
		/// @remark この関数は、テクスチャの作成時に `HasMipMap::Yes` を指定した場合にのみ効果があります。
		void generateMips() const;

		// TextureFormat::R8G8B8A8_Unorm のみサポート
		void readAsImage(Image& image) const;

		// TextureFormat::R32_Float のみサポート
		void read(Grid<float>& image) const;

		// TextureFormat::R32G32_Float のみサポート
		void read(Grid<Float2>& image) const;

		// TextureFormat::R32G32B32A32_Float のみサポート
		void read(Grid<Float4>& image) const;

		void swap(RenderTexture& other) noexcept;

	protected:

		struct MSRender {};

		SIV3D_NODISCARD_CXX20
		RenderTexture(MSRender, const Size& size, const TextureFormat& format, HasDepth hasDepth, HasMipMap hasMipMap);
	};
}

template <>
inline void std::swap(s3d::RenderTexture& a, s3d::RenderTexture& b) noexcept;

# include "detail/RenderTexture.ipp"
