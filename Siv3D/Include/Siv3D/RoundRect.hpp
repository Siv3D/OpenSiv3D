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
# include "PointVector.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	struct RoundRect
	{
		S3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				RectF rect;
			};
			
			struct
			{
				double x, y, w, h;
			};
		};

		double r;

		S3D_DISABLE_MSVC_WARNINGS_POP()

		RoundRect() = default;

		constexpr RoundRect(double _x, double _y, double _w, double _h, double _r) noexcept
			: rect(_x, _y, _w, _h)
			, r(_r) {}
	};
}
