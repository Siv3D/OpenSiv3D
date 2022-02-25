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
inline void std::swap(s3d::MSRenderTexture& a, s3d::MSRenderTexture& b) noexcept
{
	a.swap(b);
}
