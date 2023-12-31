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

# include <Siv3D/OpenAI/Vision.hpp>
# include <Siv3D/JSON.hpp>
# include <Siv3D/Base64.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/MemoryViewReader.hpp>
# include <Siv3D/SimpleHTTP.hpp>
# include "OpenAICommon.hpp"

namespace s3d
{
	namespace detail
	{
		/// @brief チャット API のエンドポイント | Chat API endpoint
		constexpr URLView ChatCompletionsEndpoint{ U"https://api.openai.com/v1/chat/completions" };

		/// @brief チャット API に送信するリクエスト JSON を作成します。
		/// @param request リクエスト
		/// @return リクエストの JSON 文字列
		[[nodiscard]]
		static std::string MakeChatRequest(const OpenAI::Vision::Request& request)
		{
			JSON json;
			json[U"model"] = request.model;
			json[U"max_tokens"] = request.maxTokens;
			json[U"temperature"] = request.temperature;
			json[U"messages"].push_back({ { U"role", U"user" } });
			json[U"messages"][0][U"content"].push_back({ { U"type", U"text" }, { U"text", request.questions } });

			size_t contentIndex = 1;

			for (const auto& image : request.images)
			{
				if (std::holds_alternative<URL>(image))
				{
					json[U"messages"][0][U"content"].push_back({ { U"type", U"image_url" } });
					json[U"messages"][0][U"content"][contentIndex][U"image_url"] = { { U"url", std::get<URL>(image) } };
				}
				else
				{
					const Blob encoded = std::get<Image>(image).encodeJPEG();

					std::string base64;
					Base64::Encode(encoded.data(), encoded.size(), base64);
					base64.insert(0, "data:image/jpeg;base64,");

					json[U"messages"][0][U"content"].push_back({ { U"type", U"image_url" } });
					json[U"messages"][0][U"content"][contentIndex][U"image_url"] = { { U"url", U"" } };
					json[U"messages"][0][U"content"][contentIndex][U"image_url"][U"url"].assignUTF8String(base64);
				}

				++contentIndex;
			}

			return json.formatUTF8();
		}
	}

	namespace OpenAI
	{
		namespace Vision
		{
			String Complete(const StringView apiKey, const Request& request)
			{
				String unused;
				return Complete(apiKey, request, unused);
			}

			String Complete(const StringView apiKey, const Request& request, String& error)
			{
				// エラーをクリアする
				error.clear();

				// API キーが空の文字列である場合は失敗
				if (not apiKey)
				{
					error = detail::Error_APIKeyIsEmpty;
					return{};
				}

				const auto headers = detail::MakeHeaders(apiKey);
				const std::string json = detail::MakeChatRequest(request);
				MemoryWriter memoryWriter;

				if (const auto response = SimpleHTTP::Post(detail::ChatCompletionsEndpoint, headers, json.data(), json.size(), memoryWriter))
				{
					if (const HTTPStatusCode statusCode = response.getStatusCode();
						statusCode == HTTPStatusCode::OK)
					{
						const Blob blob = memoryWriter.retrieve();
						return GetContent(JSON::Load(MemoryViewReader{ blob.data(), blob.size_bytes() }));
					}
					else if (statusCode == HTTPStatusCode::Unauthorized) // 401 は無効な API キーが原因
					{
						error = detail::Error_InvalidAPIKey;
					}
					else
					{
						error = U"Response was not HTTPStatusCode::OK. [Status code: {}]"_fmt(response.getStatusCodeInt());
					}
				}
				else
				{
					error = detail::Error_FailedToRetrieveHTTPResponse;
				}

				return{};
			}

			AsyncHTTPTask CompleteAsync(const StringView apiKey, const Request& request)
			{
				// API キーが空の文字列である場合は失敗
				if (not apiKey)
				{
					return{};
				}

				const std::string json = detail::MakeChatRequest(request);
				const auto headers = detail::MakeHeaders(apiKey);
				return SimpleHTTP::PostAsync(detail::ChatCompletionsEndpoint, headers, json.data(), json.size());
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
