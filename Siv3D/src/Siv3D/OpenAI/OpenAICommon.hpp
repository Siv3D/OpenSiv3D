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
# include <Siv3D/String.hpp>
# include <Siv3D/Duration.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	namespace detail
	{
		// HTTP ヘッダーを作成する
		[[nodiscard]]
		HashTable<String, String> MakeHeaders(StringView apiKey);

		// 非同期タスクのポーリング間隔
		constexpr Milliseconds TaskPollingInterval{ 5 };
	}
}
