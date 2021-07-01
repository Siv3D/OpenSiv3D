//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "Quaternion.hpp"

namespace s3d
{
	struct OrientedBox
	{
		Vec3 center;

		Vec3 size;

		Quaternion orientation;



	};
}

# include "detail/OrientedBox.ipp"
