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
# include <Siv3D/CPUInfo.hpp>
# include "OpenAICommon.hpp"

namespace s3d
{
	namespace detail
	{
		// OpenAI の Embeddings API の URL
		constexpr URLView EmbeddingsEndpoint = U"https://api.openai.com/v1/embeddings";

		// Embeddings API に送信するリクエストを作成する
		[[nodiscard]]
		static std::string MakeEmbeddingRequest(const StringView input, const StringView model)
		{
			JSON request;
			request[U"input"] = input;
			request[U"model"] = model;
			return request.formatUTF8();
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

				if (const auto response = SimpleHTTP::Post(detail::EmbeddingsEndpoint, headers, data.data(), data.size(), memoryWriter))
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

				return SimpleHTTP::PostAsync(detail::EmbeddingsEndpoint, headers, data.data(), data.size());
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
