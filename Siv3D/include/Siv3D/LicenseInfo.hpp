//-----------------------------------------------
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
# include "Common.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief ライセンス情報
	struct LicenseInfo
	{
		/// @brief 見出し
		String title;

		/// @brief コピーライト表示
		String copyright;

		/// @brief 説明文
		String text;
	};
}
