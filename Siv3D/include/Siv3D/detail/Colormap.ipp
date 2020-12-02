//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Color Colormap01(const double x, const ColormapType colormapType)
	{
		const auto c = tinycolormap::GetColor(x, ToEnum<tinycolormap::ColormapType>(FromEnum(colormapType)));
		return{ c.ri(), c.gi(), c.bi() };
	}

	inline ColorF Colormap01F(const double x, const ColormapType colormapType)
	{
		const auto c = tinycolormap::GetColor(x, ToEnum<tinycolormap::ColormapType>(FromEnum(colormapType)));
		return{ c.r(), c.g(), c.b() };
	}
}
