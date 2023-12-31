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
	class JSON;

	namespace OpenAI
	{
		namespace Embedding
		{
			namespace Model
			{
				/// @brief 埋め込みモデル text-embedding-ada-002 | Embedding Model text-embedding-ada-002
				/// @see https://platform.openai.com/docs/models/embeddings
				/// @remark Embeddings API 用のモデルです。 | This is a model for the Embeddings API.
				inline constexpr char32 EmbeddingAda002[] = U"text-embedding-ada-002";
			}

			/// @brief 文章の埋め込みベクトルを返します。 | Returns the embedding vector of the text.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param text 文章 | Text
			/// @param model 使用するモデル | The model to be used (default: Model::EmbeddingAda002)
			/// @return 埋め込みベクトル。取得に失敗した場合空の配列 | Embedding vector. Empty array if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			Array<float> Create(StringView apiKey, StringView text, StringView model = Model::EmbeddingAda002);

			/// @brief 文章の埋め込みベクトルを返します。 | Returns the embedding vector of the text.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param text 文章 | Text
			/// @param error エラーメッセージの格納先。エラーが無い場合は空の文字列になる | Destination for the error message. Will be an empty string if no error occurs.
			/// @param model 使用するモデル | The model to be used (default: Model::EmbeddingAda002)
			/// @return 埋め込みベクトル。取得に失敗した場合空の配列 | Embedding vector. Empty array if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			Array<float> Create(StringView apiKey, StringView text, String& error, StringView model = Model::EmbeddingAda002);

			/// @brief 文章の埋め込みベクトルを含むレスポンス（JSON）を取得する非同期タスクを返します。 | Returns an asynchronous task that retrieves a response (JSON) containing the embedding vector of the text.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param text 文章 | Text
			/// @param model 使用するモデル | The model to be used (default: Model::EmbeddingAda002)
			/// @return 非同期タスク | Asynchronous task
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncHTTPTask CreateAsync(StringView apiKey, StringView text, StringView model = Model::EmbeddingAda002);

			/// @brief レスポンス（JSON）から、文章の埋め込みベクトルを抽出して返します。 | Extracts and returns the embedding vector of the text from the response (JSON).
			/// @param response JSON レスポンス | JSON response
			/// @return 埋め込みベクトル。抽出に失敗した場合は空の文字列 | Embedding vector. Empty array if the extraction fails.
			[[nodiscard]]
			Array<float> GetVector(const JSON& response);

			/// @brief 2 つの埋め込みベクトルのコサイン類似度を返します。 | Returns the cosine similarity of two embedding vectors.
			/// @param a 一方の埋め込みベクトル（正規化済み） | One of the embedding vectors (normalized)
			/// @param b もう一方の埋め込みベクトル（正規化済み） | The other embedding vector (normalized)
			/// @return コサイン類似度 | Cosine similarity
			[[nodiscard]]
			float CosineSimilarity(const Array<float>& a, const Array<float>& b);
		}
	}
}
