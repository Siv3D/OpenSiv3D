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
# include "../Image.hpp"
# include "../AsyncTask.hpp"

namespace s3d
{
	namespace OpenAI
	{
		namespace Image
		{
			/// @brief 画像の品質 | Image quality
			enum class Quality
			{
				/// @brief 標準 | Standard
				Standard,

				/// @brief 高品質 | High quality
				HD
			};

			/// @brief 画像のスタイル | Image style
			enum class Style
			{
				/// @brief 超現実的・ドラマチック | Hyper-realistic and dramatic
				Vivid,

				/// @brief 自然 | Natural
				Natural
			};

			/// @brief DALLE-2 モデルを使用して画像を生成するためのリクエスト | Request to generate an image using the DALLE-2 model
			struct RequestDALLE2
			{
				/// @brief プロンプトの最大長 | Maximum length of the prompt
				static constexpr size_t MaxPromptLength = 1000;

				/// @brief 画像の最大個数 | Maximum number of images
				static constexpr int32 MaxImageCount = 10;

				/// @brief 256x256 ピクセルの画像サイズ | Image size of 256x256 pixels
				static constexpr Size ImageSize256{ 256, 256 };

				/// @brief 512x512 ピクセルの画像サイズ | Image size of 512x512 pixels
				static constexpr Size ImageSize512{ 512, 512 };

				/// @brief 1024x1024 ピクセルの画像サイズ | Image size of 1024x1024 pixels
				static constexpr Size ImageSize1024{ 1024, 1024 };

				/// @brief 画像を説明するテキスト。英語で 1000 文字以下 | Text describing the image, in English and up to 1000 characters
				String prompt;

				/// @brief 生成する画像のサイズ | Size of the generated image
				/// @remark `ImageSize256`, `ImageSize512`, `ImageSize1024` のいずれか | One of `ImageSize256`, `ImageSize512`, `ImageSize1024`
				Size imageSize = ImageSize256;
			};

			/// @brief DALLE-3 モデルを使用して画像を生成するためのリクエスト | Request to generate an image using the DALLE-3 model
			struct RequestDALLE3
			{
				/// @brief プロンプトの最大長 | Maximum length of the prompt
				static constexpr size_t MaxPromptLength = 4000;

				/// @brief 1024x1024 ピクセルの画像サイズ | Image size of 1024x1024 pixels
				static constexpr Size ImageSize1024{ 1024, 1024 };

				/// @brief 1792x1024 ピクセルの画像サイズ | Image size of 1792x1024 pixels
				static constexpr Size ImageSize1792x1024{ 1792, 1024 };

				/// @brief 1024x1792 ピクセルの画像サイズ | Image size of 1024x1792 pixels
				static constexpr Size ImageSize1024x1792{ 1024, 1792 };

				/// @brief 画像を説明するテキスト。英語で 4000 文字以下 | Text describing the image, in English and up to 4000 characters
				String prompt;

				/// @brief 画像の品質 | Image quality
				Quality quality = Quality::Standard;

				/// @brief 生成する画像のサイズ | Size of the generated image
				/// @remark `ImageSize1024`, `ImageSize1792x1024`, `ImageSize1024x1792` のいずれか | One of `ImageSize1024`, `ImageSize1792x1024`, `ImageSize1024x1792`
				Size imageSize = ImageSize1024;

				/// @brief 画像のスタイル | Image style
				Style style = Style::Vivid;
			};

			/// @brief プロンプトに基づいて DALLE-2 モデルを使用して画像を生成します。 | Generate an image using the DALLE-2 model based on the prompt.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 生成された画像。生成に失敗した場合は空の画像 | Generated image. An empty image if the generation fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			s3d::Image Create(StringView apiKey, const RequestDALLE2& request);

			/// @brief プロンプトに基づいて DALLE-2 モデルを使用して 1 つまたは複数の画像を生成します。 | Generate one or more images using the DALLE-2 model based on the prompt.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @param numImages 生成する画像の個数。1 以上 `OpenAI::RequestDALLE2::MaxImageCount` 以下 | Number of images to generate, between 1 and `OpenAI::RequestDALLE2::MaxImageCount`
			/// @return 生成された画像の配列。生成に失敗した場合は空の配列 | Array of generated images. An empty array if the generation fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			Array<s3d::Image> Create(StringView apiKey, const RequestDALLE2& request, int32 numImages);

			/// @brief プロンプトに基づいて DALLE-3 モデルを使用して画像を生成します。 | Generate an image using the DALLE-3 model based on the prompt.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 生成された画像。生成に失敗した場合は空の画像 | Generated image. An empty image if the generation fails.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			s3d::Image Create(StringView apiKey, const RequestDALLE3& request);

			/// @brief プロンプトに基づいて DALLE-2 モデルを使用して画像を生成する非同期タスクを返します。 | Returns an asynchronous task that generates an image using the DALLE-2 model based on the prompt.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 生成された画像を返す非同期タスク | Asynchronous task that returns the generated image
			/// @remark 戻り値の task が `task.isReady() == true` になれば `task.get()` で結果を取得できます。 | The result can be retrieved if `task.isReady() == true`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncTask<s3d::Image> CreateAsync(StringView apiKey, const RequestDALLE2& request);

			/// @brief プロンプトに基づいて DALLE-2 モデルを使用して 1 つまたは複数の画像を生成する非同期タスクを返します。 | Returns an asynchronous task that generates one or more images using the DALLE-2 model based on the prompt.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @param numImages 生成する画像の個数。1 以上 `OpenAI::RequestDALLE2::MaxImageCount` 以下 | Number of images to generate, between 1 and `OpenAI::RequestDALLE2::MaxImageCount`
			/// @return 生成された画像の配列を返す非同期タスク | Asynchronous task that returns an array of generated images
			/// @remark 戻り値の task が `task.isReady() == true` になれば `task.get()` で結果を取得できます。 | The result can be retrieved if `task.isReady() == true`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncTask<Array<s3d::Image>> CreateAsync(StringView apiKey, const RequestDALLE2& request, int32 numImages);

			/// @brief プロンプトに基づいて DALLE-3 モデルを使用して画像を生成する非同期タスクを返します。 | Returns an asynchronous task that generates an image using the DALLE-3 model based on the prompt.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @return 生成された画像を返す非同期タスク | Asynchronous task that returns the generated image
			/// @remark 戻り値の task が `task.isReady() == true` になれば `task.get()` で結果を取得できます。 | The result can be retrieved if `task.isReady() == true`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			[[nodiscard]]
			AsyncTask<s3d::Image> CreateAsync(StringView apiKey, const RequestDALLE3& request);
		}
	}
}
