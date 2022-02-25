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
	namespace Cursor
	{
		inline void SetPos(int32 x, int32 y)
		{
			SetPos(Point{ x, y });
		}

		namespace Internal
		{
			void SetLocalTransform(const Mat3x2& matrix);

			void SetCameraTransform(const Mat3x2& matrix);
		}
	}
}
