//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Colormap.hpp>
# include <ThirdParty/tinycolormap/tinycolormap.hpp>

namespace s3d
{
	Color Colormap01(const double x, const ColormapType colormapType)
	{
		const auto c = tinycolormap::GetColor(x, ToEnum<tinycolormap::ColormapType>(FromEnum(colormapType)));
		return{ c.ri(), c.gi(), c.bi() };
	}

	ColorF Colormap01F(const double x, const ColormapType colormapType)
	{
		const auto c = tinycolormap::GetColor(x, ToEnum<tinycolormap::ColormapType>(FromEnum(colormapType)));
		return{ c.r(), c.g(), c.b() };
	}
}
