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

namespace s3d
{
	template <class Type>
	inline Type Texture::horizontalAspectRatio() const noexcept
	{
		return size().horizontalAspectRatio();
	}
}

template <>
inline void std::swap(s3d::Texture& a, s3d::Texture& b) noexcept
{
	a.swap(b);
}
