//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	/// <summary>
	/// テクスチャの設定
	/// </summary>
	enum class TextureDesc
	{
		/// <summary>
		/// ミップマップなし
		/// </summary>
		Unmipped,

		/// <summary>
		/// ミップマップなし、sRGB
		/// </summary>
		UnmippedSRGB,

		/// <summary>
		/// ミップマップあり
		/// </summary>
		Mipped,

		/// <summary>
		/// ミップマップあり、sRGB
		/// </summary>
		MippedSRGB,

		/// <summary>
		/// Signed Distance Field
		/// </summary>
		SDF,

		/// <summary>
		/// 3D 用のテクスチャのデフォルト [ミップマップあり、sRGB]
		/// </summary>
		For3D = MippedSRGB,
	};
	
	namespace detail
	{
		[[nodiscard]] inline constexpr bool IsMipped(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::Mipped)
				|| (desc == TextureDesc::MippedSRGB);
		}

		[[nodiscard]] inline constexpr bool IsSRGB(const TextureDesc desc) noexcept
		{
			return (desc == TextureDesc::UnmippedSRGB)
				|| (desc == TextureDesc::MippedSRGB);
		}
	}
}
