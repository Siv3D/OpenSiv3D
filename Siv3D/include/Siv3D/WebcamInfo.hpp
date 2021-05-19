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
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief Web カメラの情報
	struct WebcamInfo
	{
		uint32 cameraIndex = 0;

		String name;

		String uniqueName;
	};

	namespace System
	{
		/// @brief 利用可能な Web カメラの一覧を返します。
		/// @return 利用可能な Web カメラの一覧
		[[nodiscard]]
		Array<WebcamInfo> EnumerateWebcams();
	}
}
