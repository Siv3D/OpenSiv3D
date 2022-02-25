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
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	namespace System
	{
		/// @brief アプリケーションに渡されたコマンドライン引数の一覧を返します。
		/// @return コマンドライン引数の一覧
		[[nodiscard]]
		const Array<String>& GetCommandLineArgs() noexcept;
	}
}
