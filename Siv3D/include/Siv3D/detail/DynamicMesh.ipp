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

template <>
inline void std::swap(s3d::DynamicMesh& a, s3d::DynamicMesh& b) noexcept
{
	a.swap(b);
}
