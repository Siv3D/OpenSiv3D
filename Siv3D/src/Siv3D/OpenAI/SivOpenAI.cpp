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
# include <Siv3D/System.hpp>
# include <Siv3D/CPUInfo.hpp>

namespace s3d
{
	namespace detail
	{
		// OpenAI のチャット API の URL
		constexpr URLView ChatV1URL = U"https://api.openai.com/v1/chat/completions";
	
		// OpenAI の画像生成 API の URL
		constexpr URLView ImageGenerationV1URL = U"https://api.openai.com/v1/images/generations";

		// OpenAI の Embeddings API の URL
		constexpr URLView EmbeddingsV1URL = U"https://api.openai.com/v1/embeddings";

		// 非同期タスクのポーリング間隔
		constexpr Milliseconds TaskPollingInterval{ 5 };

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

		// 画像生成 API に送信するリクエストを作成する
		[[nodiscard]]
		static std::string MakeImageRequest(const StringView prompt, const Size& size, const int32 n)
		{
			JSON request;
			request[U"prompt"] = prompt;
			request[U"n"] = n;
			request[U"size"] = ((size == OpenAI::ImageSize1024) ? U"1024x1024" : (size == OpenAI::ImageSize512) ? U"512x512" : U"256x256");
			return request.formatUTF8();
		}

		// Embeddings API に送信するリクエストを作成する
		[[nodiscard]]
		static std::string MakeEmbeddingRequest(const StringView input, const StringView model)
		{
			JSON request;
			request[U"input"] = input;
			request[U"model"] = model;
			return request.formatUTF8();
		}

		// HTTP ヘッダーを作成する
		[[nodiscard]]
		static HashTable<String, String> MakeHeaders(const StringView apiKey)
		{
			return{
				{ U"Content-Type", U"application/json" },
				{ U"Authorization", (U"Bearer " + apiKey) },
			};
		}

		// 画像を生成する
		[[nodiscard]]
		static Array<s3d::Image> CreateImagesImpl(const String apiKey, const String prompt, const int32 n, const Size size)
		{
			// API キーが空の文字列である場合は失敗
			if (apiKey.isEmpty())
			{
				return{};
			}

			// 有効な画像枚数は 1 以上 OpenAI::MaxImageCount 以下
			if (not InRange(n, 1, OpenAI::MaxImageCount))
			{
				return{};
			}

			const std::string data = detail::MakeImageRequest(prompt, size, n);

			const auto headers = detail::MakeHeaders(apiKey);

			// 画像生成 API に非同期でリクエストを送信する
			AsyncHTTPTask task1 = SimpleHTTP::PostAsync(detail::ImageGenerationV1URL, headers, data.data(), data.size());

			// タスクが完了するまでポーリングする
			while (not task1.isReady())
			{
				System::Sleep(TaskPollingInterval);
			}

			if (not task1.getResponse().isOK())
			{
				return{};
			}

			const JSON json = task1.getAsJSON();

			Array<AsyncHTTPTask> tasks;

			// 生成された画像を非同期でダウンロード
			for (size_t i = 0; i < json[U"data"].size(); ++i)
			{
				tasks << SimpleHTTP::LoadAsync(json[U"data"][i][U"url"].getString());
			}

			Array<s3d::Image> images;

			for (auto& task : tasks)
			{
				// タスクが完了するまでポーリングする
				while (not task.isReady())
				{
					System::Sleep(TaskPollingInterval);
				}

				if (task.getResponse().isOK())
				{
					images.emplace_back(task.getBlobReader());
				}
			}

			return images;
		}

		[[nodiscard]]
		static s3d::Image CreateImageImpl(const String apiKey, const String prompt, const Size size)
		{
			if (Array<s3d::Image> images = CreateImagesImpl(apiKey, prompt, 1, size))
			{
				return std::move(images.front());
			}
			else
			{
				return{};
			}
		}

		[[nodiscard]]
		static float DotProduct_SSE3(const float* a, const float* b, const size_t size) noexcept
		{
			assert((size % 4) == 0);

			const float* aEnd = (a + size);

			__m128 sum = ::_mm_setzero_ps();

			while (a != aEnd)
			{
				const __m128 a4 = ::_mm_loadu_ps(a);
				const __m128 b4 = ::_mm_loadu_ps(b);
				sum = ::_mm_add_ps(sum, ::_mm_mul_ps(a4, b4));
				a += 4;
				b += 4;
			}

			sum = ::_mm_hadd_ps(sum, sum);
			sum = ::_mm_hadd_ps(sum, sum);

			float result;
			::_mm_store_ss(&result, sum);

			return result;
		}

		[[nodiscard]]
		static float DotProduct(const float* a, const float* b, const size_t size) noexcept
		{
		# if SIV3D_INTRINSIC(SSE)
			
			if (((size % 4) == 0) && (GetCPUInfo().features.sse3))
			{
				return DotProduct_SSE3(a, b, size);
			}

		# endif

			const float* aEnd = (a + size);

			float result = 0.0;

			while (a != aEnd)
			{
				result += ((*a++) * (*b++));
			}

			return result;
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

				if (const auto response = SimpleHTTP::Post(detail::ChatV1URL, headers, data.data(), data.size(), memoryWriter))
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

				return SimpleHTTP::PostAsync(detail::ChatV1URL, headers, data.data(), data.size());
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

		namespace Image
		{
			s3d::Image Create(const StringView apiKey, const StringView prompt, const Size& size)
			{
				return detail::CreateImageImpl(String{ apiKey }, String{ prompt }, size);
			}

			Array<s3d::Image> Create(const StringView apiKey, const StringView prompt, const int32 n, const Size& size)
			{
				return detail::CreateImagesImpl(String{ apiKey }, String{ prompt }, n, size);
			}

			AsyncTask<s3d::Image> CreateAsync(const StringView apiKey, const StringView prompt, const Size& size)
			{
				return Async(detail::CreateImageImpl, String{ apiKey }, String{ prompt }, size);
			}

			AsyncTask<Array<s3d::Image>> CreateAsync(const StringView apiKey, const StringView prompt, const int32 n, const Size& size)
			{
				return Async(detail::CreateImagesImpl, String{ apiKey }, String{ prompt }, n, size);
			}
		}

		namespace Embedding
		{
			Array<float> Create(const StringView apiKey, const StringView text, const StringView model)
			{
				String unused;
				return Create(apiKey, text, unused, model);
			}

			Array<float> Create(const StringView apiKey, const StringView text, String& error, const StringView model)
			{
				error.clear();

				// API キーが空の文字列である場合は失敗
				if (apiKey.isEmpty())
				{
					error = U"API key is empty.";
					return{};
				}

				const std::string data = detail::MakeEmbeddingRequest(text, model);

				const auto headers = detail::MakeHeaders(apiKey);

				MemoryWriter memoryWriter;

				if (const auto response = SimpleHTTP::Post(detail::EmbeddingsV1URL, headers, data.data(), data.size(), memoryWriter))
				{
					if (const HTTPStatusCode statusCode = response.getStatusCode();
						statusCode == HTTPStatusCode::OK)
					{
						const Blob blob = memoryWriter.retrieve();

						return GetVector(JSON::Load(MemoryViewReader{ blob.data(), blob.size_bytes() }));
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

			AsyncHTTPTask CreateAsync(const StringView apiKey, const StringView text, const StringView model)
			{
				// API キーが空の文字列である場合は失敗
				if (apiKey.isEmpty())
				{
					return{};
				}

				const std::string data = detail::MakeEmbeddingRequest(text, model);

				const auto headers = detail::MakeHeaders(apiKey);

				return SimpleHTTP::PostAsync(detail::EmbeddingsV1URL, headers, data.data(), data.size());
			}

			Array<float> GetVector(const JSON& response)
			{
				if (not response)
				{
					return{};
				}

				if (not response.hasElement(U"data")
					|| (not response[U"data"].isArray())
					|| (response[U"data"].size() < 1)
					|| (not response[U"data"][0].hasElement(U"embedding"))
					|| (not response[U"data"][0][U"embedding"].isArray()))
				{
					return{};
				}

				const auto& embedding = response[U"data"][0][U"embedding"];

				Array<float> result(Arg::reserve = embedding.size());

				for (const auto& value : embedding.arrayView())
				{
					result.push_back(value.get<float>());
				}

				return result;
			}

			float CosineSimilarity(const Array<float>& a, const Array<float>& b)
			{
				if (a.size() != b.size())
				{
					throw Error{ U"OpenAI::Embedding::CosineSimilarity(): Vectors must have the same size." };
				}

				// OpenAI embeddings are normalized to length 1
				return detail::DotProduct(a.data(), b.data(), a.size());
			}
		}
	}
}
