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
# include "Common.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief 環境変数
	namespace EnvironmentVariable
	{
		/// @brief 環境変数の値を返します。
		/// @param name 環境変数の名前
		/// @return 環境変数の値。失敗した場合は空の文字列
		[[nodiscard]]
		String Get(StringView name);
	}
}
