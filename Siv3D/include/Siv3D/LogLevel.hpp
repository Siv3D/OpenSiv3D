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

namespace s3d
{
	/// @brief 出力されるログの詳細度
	enum class LogLevel : uint8
	{
		/// @brief リリースモード
		Release,

		/// @brief デバッグモード
		Debug,

		/// @brief 最も詳細なモード
		Verbose,
	};
}
