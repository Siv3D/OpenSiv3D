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
		/// @brief HTTP ヘッダーを作成します。
		/// @param apiKey API キー
		/// @return HTTP ヘッダー
		[[nodiscard]]
		HashTable<String, String> MakeHeaders(StringView apiKey);

		/// @brief 非同期タスクのポーリング間隔
		constexpr Milliseconds TaskPollingInterval{ 5 };

		/// @brief API キーが空の文字列である場合のエラーメッセージ
		inline constexpr StringView Error_APIKeyIsEmpty = U"API key is empty.";

		/// @brief API キーが不正である場合のエラーメッセージ
		inline constexpr StringView Error_InvalidAPIKey = U"Invalid API key. [Status code: 401]";

		/// @brief HTTP レスポンスの取得に失敗した場合のエラーメッセージ
		inline constexpr StringView Error_FailedToRetrieveHTTPResponse = U"Failed to retrieve HTTP response.";
	}
}
