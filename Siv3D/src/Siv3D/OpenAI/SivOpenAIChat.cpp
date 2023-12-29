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

# include <Siv3D/OpenAI.hpp>
# include <Siv3D/JSON.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/MemoryViewReader.hpp>
# include <Siv3D/SimpleHTTP.hpp>
# include "OpenAICommon.hpp"

namespace s3d
{
	namespace detail
	{
		// OpenAI のチャット API の URL
		constexpr URLView ChatCompletionsEndpoint = U"https://api.openai.com/v1/chat/completions";

		// チャット API に送信するリクエストを作成する
		[[nodiscard]]
		static std::string MakeChatRequest(const Array<std::pair<String, String>>& messages, const StringView model)
		{
			JSON request;
			request[U"model"] = model;

			for (auto&& [role, content] : messages)
			{
				request[U"messages"].push_back({ { U"role", role }, { U"content", content } });
			}

			return request.formatUTF8();
		}
	}

	namespace OpenAI
	{
		namespace Chat
		{
			String Complete(const StringView apiKey, const StringView message, const StringView model)
			{
				String unused;
				return Complete(apiKey, { { U"user", String{ message } } }, unused, model);
			}

			String Complete(const StringView apiKey, const StringView message, String& error, const StringView model)
			{
				return Complete(apiKey, { { U"user", String{ message } } }, error, model);
			}

			String Complete(StringView apiKey, const Array<std::pair<String, String>>& messages, const StringView model)
			{
				String unused;
				return Complete(apiKey, messages, unused, model);
			}

			String Complete(StringView apiKey, const Array<std::pair<String, String>>& messages, String& error, const StringView model)
			{
				error.clear();

				// API キーが空の文字列である場合は失敗
				if (apiKey.isEmpty())
				{
					error = U"API key is empty.";
					return{};
				}

				const std::string data = detail::MakeChatRequest(messages, model);

				const auto headers = detail::MakeHeaders(apiKey);

				MemoryWriter memoryWriter;

				if (const auto response = SimpleHTTP::Post(detail::ChatCompletionsEndpoint, headers, data.data(), data.size(), memoryWriter))
				{
					if (const HTTPStatusCode statusCode = response.getStatusCode();
						statusCode == HTTPStatusCode::OK)
					{
						const Blob blob = memoryWriter.retrieve();

						return GetContent(JSON::Load(MemoryViewReader{ blob.data(), blob.size_bytes() }));
					}
					else if (statusCode == HTTPStatusCode::Unauthorized) // 401 は無効な API キーが原因
					{
						error = U"Invalid API key. [Status code: 401]";
					}
					else
					{
						error = U"Response was not HTTPStatusCode::OK. [Status code: {}]"_fmt(response.getStatusCodeInt());
					}
				}
				else
				{
					error = U"Failed to retrieve HTTP response.";
				}

				return{};
			}

			AsyncHTTPTask CompleteAsync(const StringView apiKey, const StringView message, const StringView model)
			{
				return CompleteAsync(apiKey, { { U"user", String{ message } } }, model);
			}

			AsyncHTTPTask CompleteAsync(const StringView apiKey, const Array<std::pair<String, String>>& messages, const StringView model)
			{
				// API キーが空の文字列である場合は失敗
				if (apiKey.isEmpty())
				{
					return{};
				}

				const std::string data = detail::MakeChatRequest(messages, model);

				const auto headers = detail::MakeHeaders(apiKey);

				return SimpleHTTP::PostAsync(detail::ChatCompletionsEndpoint, headers, data.data(), data.size());
			}

			String GetContent(const JSON& response)
			{
				if (not response)
				{
					return{};
				}

				if (not response.hasElement(U"choices"))
				{
					return{};
				}

				return response[U"choices"][0][U"message"][U"content"].getString().trimmed();
			}
		}
	}
}
