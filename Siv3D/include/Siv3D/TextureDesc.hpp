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
		bool IsMipped(TextureDesc desc) noexcept;

		bool IsSRGB(TextureDesc desc) noexcept;
	}
}
