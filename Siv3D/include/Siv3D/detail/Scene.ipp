﻿//-----------------------------------------------
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
	namespace Scene
	{
		inline void Resize(const int32 width, const int32 height)
		{
			Resize(s3d::Size{ width, height });
		}

		inline int32 Width() noexcept
		{
			return Size().x;
		}

		inline int32 Height() noexcept
		{
			return Size().x;
		}

		inline Point Center() noexcept
		{
			return (Size() / 2);
		}

		inline Vec2 CenterF() noexcept
		{
			return (Size() * 0.5);
		}

		inline s3d::Rect Rect() noexcept
		{
			return s3d::Rect{ Size() };
		}
	}
}
