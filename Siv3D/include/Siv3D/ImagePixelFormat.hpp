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
	/// @brief ピクセルフォーマット
	enum class ImagePixelFormat : uint8
	{
		/// @brief 不明
		Unknown,

		R8G8B8,

		R8G8B8X8,

		R8G8B8A8,

		Gray8,

		Gray16,

		Gray8A8,

		Gray16A16,
	};
}
