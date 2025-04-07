﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

template <>
inline void std::swap(s3d::DynamicTexture& a, s3d::DynamicTexture& b) noexcept
{
	a.swap(b);
}
