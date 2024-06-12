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
# include "../Common.hpp"
# include "../String.hpp"
# include "../Array.hpp"
# include "../AsyncHTTPTask.hpp"

namespace s3d
{
	namespace OpenAI
	{
		namespace Chat
		{
			namespace Model
			{
				/// @brief GPT-3.5 16K
				/// @see https://platform.openai.com/docs/models/gpt-3-5
				inline constexpr char32 GPT3_5_Turbo[] = U"gpt-3.5-turbo";

				/// @brief GPT-4 Turbo 128K
				/// @see https://platform.openai.com/docs/models/gpt-4-and-gpt-4-turbo
				inline constexpr char32 GPT4_Turbo[] =  U"gpt-4-turbo";

				/// @brief GPT-4o 128K
				/// @see https://platform.openai.com/docs/models/gpt-4-and-gpt-4-turbo
				inline constexpr char32 GPT4o[] = U"gpt-4o";
			}

			/// @brief メッセージのロール | Message role
			enum class Role
			{
				/// @brief システム | System
				System,

				/// @brief ユーザー | User
				User,

				/// @brief AI アシスタント | AI Assistant
				Assistant,
			};

			/// @brief レスポンスのフォーマット | Response format
			enum class ResponseFormat
			{
				/// @brief テキスト | Text
				Text,

				/// @brief JSON | JSON
				JSON,
			};

			/// @brief チャット API に送信するリクエスト | Request to send to the Chat API
			struct Request
			{
				/// @brief ランダム・創造性の度合いの最小値 | Minimum value of randomness and creativity
				static constexpr double MinTemperature = 0.0;

				/// @brief ランダム・創造性の度合いの最大値 | Maximum value of randomness and creativity
				static constexpr double MaxTemperature = 2.0;

				/// @brief ランダム・創造性の度合いのデフォルト値 | Default value of randomness and creativity
				static constexpr double DefaultTemperature = 1.0;

				/// @brief メッセージ（ロールとメッセージのペアの配列） | Array of message pairs (role and message)
				Array<std::pair<Role, String>> messages;

				/// @brief モデル | Model
				String model = Model::GPT4o;

				/// @brief レスポンスのフォーマット | Response format
				/// @remark `ResponseFormat::JSON` を指定した場合、メッセージには "JSON" という言葉を含める必要があります。 | If `ResponseFormat::JSON` is specified, the message must contain the word "JSON".
				ResponseFormat responseFormat = ResponseFormat::Text;

				/// @brief ランダム・創造性の度合い | Degree of randomness and creativity
				/// @remark `MinTemperature` 以上 `MaxTemperature` 以下の値 | A value between `MinTemperature` and `MaxTemperature`
				double temperature = DefaultTemperature;
			};

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends a message to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param message メッセージ | Message
			/// @param model 使用するモデル | The model to be used (default: Model::GPT4o)
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, StringView message, StringView model = Model::GPT4o);

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends messages to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, const Request& request);

			/// @brief ChatGPT にメッセージを送り、その返答メッセージを取得します。 | Sends messages to ChatGPT and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @param error エラーメッセージの格納先。エラーが無い場合は空の文字列になる | Destination for the error message. Will be an empty string if no error occurs.
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, const Request& request, String& error);

			/// @brief ChatGPT にメッセージを送り、レスポンス（JSON）を取得する非同期タスクを返します。 | Returns an asynchronous task for sending a message to ChatGPT and retrieving the response (JSON).
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param message メッセージ | Message
			/// @param model 使用するモデル | The model to be used (default: Model::GPT4o)
			/// @return 非同期タスク | Asynchronous task
			/// @remark 戻り値の task が `(task.isReady() == true) && (task.getResponse().isOK() == true)` になれば結果を取得できます。 | The result can be retrieved if `(task.isReady() == true) && (task.getResponse().isOK() == true)`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncHTTPTask CompleteAsync(StringView apiKey, StringView message, StringView model = Model::GPT4o);

			/// @brief ChatGPT にメッセージを送り、レスポンス（JSON）を取得する非同期タスクを返します。 | Returns an asynchronous task for sending messages to ChatGPT and retrieving the response (JSON).
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 非同期タスク | Asynchronous task
			/// @remark 戻り値の task が `(task.isReady() == true) && (task.getResponse().isOK() == true)` になれば結果を取得できます。 | The result can be retrieved if `(task.isReady() == true) && (task.getResponse().isOK() == true)`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncHTTPTask CompleteAsync(StringView apiKey, const Request& request);

			/// @brief ChatGPT のレスポンス（JSON）から、返答メッセージを抽出して返します。 | Extracts the response message from the response (JSON) of ChatGPT and returns it.
			/// @param response JSON レスポンス | JSON response
			/// @return 返答メッセージ。抽出に失敗した場合は空の文字列 | Response message. An empty string if extraction fails.
			/// @remark 通常は `AsyncHTTPTask::getAsJSON()` の戻り値を渡します。 | Typically, pass the return value of `AsyncHTTPTask::getAsJSON()`.
			[[nodiscard]]
			String GetContent(const JSON& response);
		}
	}
}
