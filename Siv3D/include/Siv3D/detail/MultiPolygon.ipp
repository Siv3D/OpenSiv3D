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

namespace s3d
{

}

template <>
void std::swap(s3d::MultiPolygon& a, s3d::MultiPolygon& b) noexcept
{
	a.swap(b);
}
