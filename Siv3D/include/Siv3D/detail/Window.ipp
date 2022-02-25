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
	namespace Window
	{
		SIV3D_CONCEPT_FORMATTABLE_ARGS_
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}

		inline WindowStyle GetStyle() noexcept
		{
			return GetState().style;
		}

		inline void SetPos(const int32 x, const int32 y)
		{
			SetPos(Point{ x, y });
		}

		inline Point GetPos() noexcept
		{
			return GetState().bounds.pos;
		}

		inline bool Resize(const Size size, const s3d::Centering centering)
		{
			return ResizeVirtual(size, centering);
		}

		inline bool Resize(const int32 width, const int32 height, const s3d::Centering centering)
		{
			return ResizeVirtual(Size{ width, height }, centering);
		}

		inline bool ResizeVirtual(const int32 width, const int32 height, const s3d::Centering centering)
		{
			return ResizeVirtual(Size{ width, height }, centering);
		}

		inline bool ResizeActual(const int32 width, const int32 height, const s3d::Centering centering)
		{
			return ResizeActual(Size{ width, height }, centering);
		}
	}
}
