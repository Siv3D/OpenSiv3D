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
# include "ColorHSV.hpp"

namespace s3d
{
	/// @brief カラーマップの種類
	/// @remark https://github.com/yuki-koyama/tinycolormap
	enum class ColormapType : uint8
	{
		Parula,

		Heat,

		Jet,

		/// @remark https://ai.googleblog.com/2019/08/turbo-improved-rainbow-colormap-for.html
		Turbo,

		Hot,

		Gray,

		Magma,

		Inferno,

		Plasma,

		Viridis,

		Cividis,
	};

	/// @brief 値をカラーマップを使って色 (Color 型) に変換します。
	/// @param x 色に変換する値。[0.0, 1.0] 以外の範囲はクランプされます
	/// @param colormapType 変換に使用するカラーマップの種類
	/// @return 変換された色
	[[nodiscard]]
	Color Colormap01(double x, ColormapType colormapType = ColormapType::Turbo);

	/// @brief 値をカラーマップを使って色 (ColorF 型) に変換します。
	/// @param x 色に変換する値。[0.0, 1.0] 以外の範囲はクランプされます
	/// @param colormapType 変換に使用するカラーマップの種類
	/// @return 変換された色
	[[nodiscard]]
	ColorF Colormap01F(double x, ColormapType colormapType = ColormapType::Turbo);
}
