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
