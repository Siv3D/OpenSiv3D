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
# include <variant>
# include "../Common.hpp"
# include "../String.hpp"
# include "../Array.hpp"
# include "../Image.hpp"
# include "../URL.hpp"
# include "../AsyncHTTPTask.hpp"

namespace s3d
{
	namespace OpenAI
	{
		namespace Vision
		{
			namespace Model
			{
				/// @brief GPT-4 Turbo with vision 128K
				/// @see https://platform.openai.com/docs/models/gpt-4-and-gpt-4-turbo
				inline constexpr char32 GPT4o[] = U"gpt-4o";
			}

			/// @brief 画像データ | Image data
			struct ImageData
			{
				/// @brief 画像ファイルの URL | URL of the image file
				URL url;

				/// @brief 画像のデータ URI | Data URI of the image
				/// @remark `url` が空の場合は `base64` が有効になります。 | `base64` is enabled if `url` is empty.
				/// @remark データ URI は `data:image/???;base64,` から始まります。 | The data URI starts with `data:image/???;base64,`.
				std::string base64;

				/// @brief URL から画像データを作成します。 | Creates image data from URL.
				/// @param url 画像ファイルの URL | URL of the image file
				/// @return 画像の URL | URL of the image
				static ImageData FromURL(URLView url);

				/// @brief 画像ファイルから画像のデータ URI を作成します。 | Creates a data URI of the image from the image file.
				/// @param path 画像ファイルのパス | Path of the image file
				/// @return 画像のデータ URI | Data URI of the image
				static ImageData Base64FromFile(FilePathView path);

				/// @brief 画像から画像のデータ URI を作成します。 | Creates a data URI of the image from the image.
				/// @param image 画像 | Image
				/// @param imageFormat 圧縮形式 | Compression format
				/// @return 画像のデータ URI | Data URI of the image
				static ImageData Base64FromImage(const s3d::Image& image, ImageFormat imageFormat = ImageFormat::JPEG);
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

				/// @brief 質問文 | Questions
				String questions;

				/// @brief 画像 | Images
				Array<ImageData> images;

				/// @brief モデル | Model
				String model = Model::GPT4o;

				/// @brief 最大トークン数 | Maximum number of tokens
				int32 maxTokens = 600;

				/// @brief ランダム・創造性の度合い | Degree of randomness and creativity
				/// @remark `MinTemperature` 以上 `MaxTemperature` 以下の値 | A value between `MinTemperature` and `MaxTemperature`
				double temperature = DefaultTemperature;
			};

			/// @brief ChatGPT with vision にメッセージを送り、その返答メッセージを取得します。 | Sends messages to ChatGPT with vision and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, const Request& request);

			/// @brief ChatGPT with vision にメッセージを送り、その返答メッセージを取得します。 | Sends messages to ChatGPT with vision and retrieves the response message.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @param error エラーメッセージの格納先。エラーが無い場合は空の文字列になる | Destination for the error message. Will be an empty string if no error occurs.
			/// @return 返答メッセージ。取得に失敗した場合は空の文字列 | Response message. An empty string if the retrieval fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			String Complete(StringView apiKey, const Request& request, String& error);

			/// @brief ChatGPT with vision にメッセージを送り、レスポンス（JSON）を取得する非同期タスクを返します。 | Sends messages to ChatGPT with vision and returns an asynchronous task to retrieve the response (JSON).
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 非同期タスク | Asynchronous task
			/// @remark 戻り値の task が `(task.isReady() == true) && (task.getResponse().isOK() == true)` になれば結果を取得できます。 | The result can be retrieved if `(task.isReady() == true) && (task.getResponse().isOK() == true)`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncHTTPTask CompleteAsync(StringView apiKey, const Request& request);

			/// @brief ChatGPT with vision のレスポンス（JSON）から、返答メッセージを抽出して返します。 | Extracts the response message from the response (JSON) of ChatGPT with vision and returns it.
			/// @param response JSON レスポンス | JSON response
			/// @return 返答メッセージ。抽出に失敗した場合は空の文字列 | Response message. An empty string if extraction fails.
			/// @remark 通常は `AsyncHTTPTask::getAsJSON()` の戻り値を渡します。 | Typically, pass the return value of `AsyncHTTPTask::getAsJSON()`.
			/// @remark この関数は、`OpenAI::Chat::GetContent()` と同じです。 | This function is the same as `OpenAI::Chat::GetContent()`.
			[[nodiscard]]
			String GetContent(const JSON& response);
		}
	}
}
