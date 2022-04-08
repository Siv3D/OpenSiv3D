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
# include "RenderTexture.hpp"

namespace s3d
{
	/// @brief マルチサンプル（アンチエイリアス付き）レンダーテクスチャ
	class MSRenderTexture : public RenderTexture
	{
	public:

		SIV3D_NODISCARD_CXX20
		MSRenderTexture();

		SIV3D_NODISCARD_CXX20
		MSRenderTexture(uint32 width, uint32 height, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, HasDepth hasDepth = HasDepth::No);

		SIV3D_NODISCARD_CXX20
		MSRenderTexture(uint32 width, uint32 height, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		explicit MSRenderTexture(const Size& size, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, HasDepth hasDepth = HasDepth::No);

		SIV3D_NODISCARD_CXX20
		explicit MSRenderTexture(const Size& size, HasDepth hasDepth);

		SIV3D_NODISCARD_CXX20
		MSRenderTexture(uint32 width, uint32 height, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, HasDepth hasDepth = HasDepth::No);

		SIV3D_NODISCARD_CXX20
		MSRenderTexture(const Size& size, const ColorF& color, const TextureFormat& format = TextureFormat::R8G8B8A8_Unorm, HasDepth hasDepth = HasDepth::No);

		/// @brief レンダリングされたマルチサンプルテクスチャを通常のテクスチャに resolve し、描画可能な状態にします。
		void resolve() const;

		/// @brief テクスチャを指定した色で塗りつぶします。デプスを持つ場合、デプスもクリアします。
		/// @param color 塗りつぶしの色
		/// @return *this
		const MSRenderTexture& clear(const ColorF& color) const;

		// TextureFormat::R8G8B8A8_Unorm のみサポート
		void readAsImage(Image& image) const;

		void swap(MSRenderTexture& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::MSRenderTexture& a, s3d::MSRenderTexture& b) noexcept;

# include "detail/MSRenderTexture.ipp"
