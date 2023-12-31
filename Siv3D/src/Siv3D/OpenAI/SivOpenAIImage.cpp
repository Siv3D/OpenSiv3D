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

# include <Siv3D/OpenAI/Image.hpp>
# include <Siv3D/JSON.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/SimpleHTTP.hpp>
# include <Siv3D/MemoryViewReader.hpp>
# include "OpenAICommon.hpp"

namespace s3d
{
	namespace detail
	{
		/// @brief 画像生成 API のエンドポイント | Image generation API endpoint
		constexpr URLView ImageGenerationsEndpoint = U"https://api.openai.com/v1/images/generations";

		/// @brief DALLE-2 画像生成 API に送信するリクエスト JSON を作成します。
		/// @param request リクエスト
		/// @param n 生成する画像の枚数
		/// @return リクエストの JSON 文字列
		[[nodiscard]]
		static std::string MakeImageRequest(const OpenAI::Image::RequestDALLE2& request, const int32 n)
		{
			JSON json;
			json[U"prompt"] = request.prompt;
			json[U"model"] = U"dall-e-2";
			json[U"n"] = n;
			json[U"size"] = ((request.imageSize == OpenAI::Image::RequestDALLE2::ImageSize1024) ? U"1024x1024"
				: (request.imageSize == OpenAI::Image::RequestDALLE2::ImageSize512) ? U"512x512" : U"256x256");
			return json.formatUTF8Minimum();
		}

		/// @brief DALLE-3 画像生成 API に送信するリクエスト JSON を作成します。
		/// @param request リクエスト
		/// @return リクエストの JSON 文字列
		[[nodiscard]]
		static std::string MakeImageRequest(const OpenAI::Image::RequestDALLE3& request)
		{
			JSON json;
			json[U"prompt"] = request.prompt;
			json[U"model"] = U"dall-e-3";
			json[U"quality"] = ((request.quality == OpenAI::Image::Quality::HD) ? U"hd" : U"standard");
			json[U"size"] = ((request.imageSize == OpenAI::Image::RequestDALLE3::ImageSize1024x1792) ? U"1024x1792"
				: (request.imageSize == OpenAI::Image::RequestDALLE3::ImageSize1792x1024) ? U"1792x1024" : U"1024x1024");
			json[U"style"] = ((request.style == OpenAI::Image::Style::Natural) ? U"natural" : U"vivid");
			return json.formatUTF8Minimum();
		}

		/// @brief DALLE-2 画像生成 API による画像生成を行います。
		/// @param apiKey API キー
		/// @param request リクエスト
		/// @param numImages 生成する画像の枚数
		/// @return 生成された画像の配列。失敗した場合は空の配列
		[[nodiscard]]
		static Array<s3d::Image> CreateDALLE2ImagesImpl(const String apiKey, const OpenAI::Image::RequestDALLE2 request, const int32 numImages)
		{
			// API キーが空の文字列である場合は失敗
			if (not apiKey)
			{
				return{};
			}

			// 有効な画像枚数は 1 以上 RequestDALLE2::MaxImageCount 以下
			if (not InRange(numImages, 1, OpenAI::Image::RequestDALLE2::MaxImageCount))
			{
				return{};
			}

			const auto headers = detail::MakeHeaders(apiKey);
			const std::string json = detail::MakeImageRequest(request, numImages);

			// 画像生成 API に非同期でリクエストを送信する
			AsyncHTTPTask task1 = SimpleHTTP::PostAsync(detail::ImageGenerationsEndpoint, headers, json.data(), json.size());

			// タスクが完了するまでポーリングする
			while (not task1.isReady())
			{
				System::Sleep(TaskPollingInterval);
			}

			if (not task1.getResponse().isOK())
			{
				return{};
			}

			const JSON result = task1.getAsJSON();
			const size_t n = result[U"data"].size();

			Array<AsyncHTTPTask> tasks(Arg::reserve = n);

			// 生成された画像を非同期でダウンロード
			for (size_t i = 0; i < n; ++i)
			{
				tasks << SimpleHTTP::LoadAsync(result[U"data"][i][U"url"].getString());
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

		/// @brief DALLE-2 画像生成 API による画像生成を行います。
		/// @param apiKey API キー
		/// @param request リクエスト
		/// @return 生成された画像。失敗した場合は空の画像
		[[nodiscard]]
		static s3d::Image CreateDALLE2ImageImpl(const String apiKey, const OpenAI::Image::RequestDALLE2 request)
		{
			if (Array<s3d::Image> images = CreateDALLE2ImagesImpl(apiKey, request, 1))
			{
				return std::move(images.front());
			}
			else
			{
				return{};
			}
		}

		/// @brief DALLE-3 画像生成 API による画像生成を行います。
		/// @param apiKey API キー
		/// @param request リクエスト
		/// @return 生成された画像。失敗した場合は空の画像
		[[nodiscard]]
		static s3d::Image CreateDALLE3ImageImpl(const String apiKey, const OpenAI::Image::RequestDALLE3 request)
		{
			// API キーが空の文字列である場合は失敗
			if (not apiKey)
			{
				return{};
			}

			const auto headers = detail::MakeHeaders(apiKey);
			const std::string json = detail::MakeImageRequest(request);

			// 画像生成 API に非同期でリクエストを送信する
			AsyncHTTPTask task1 = SimpleHTTP::PostAsync(detail::ImageGenerationsEndpoint, headers, json.data(), json.size());

			// タスクが完了するまでポーリングする
			while (not task1.isReady())
			{
				System::Sleep(TaskPollingInterval);
			}

			if (not task1.getResponse().isOK())
			{
				return{};
			}

			const JSON result = task1.getAsJSON();
			AsyncHTTPTask task2 = SimpleHTTP::LoadAsync(result[U"data"][0][U"url"].getString());

			// タスクが完了するまでポーリングする
			while (not task2.isReady())
			{
				System::Sleep(TaskPollingInterval);
			}

			Image image;

			if (task2.getResponse().isOK())
			{
				image = Image{ task2.getBlobReader() };
			}

			return image;
		}
	}

	namespace OpenAI
	{
		namespace Image
		{
			s3d::Image Create(const StringView apiKey, const RequestDALLE2& request)
			{
				return detail::CreateDALLE2ImageImpl(String{ apiKey }, request);
			}

			Array<s3d::Image> Create(const StringView apiKey, const RequestDALLE2& request, const int32 numImages)
			{
				return detail::CreateDALLE2ImagesImpl(String{ apiKey }, request, numImages);
			}

			s3d::Image Create(const StringView apiKey, const RequestDALLE3& request)
			{
				return detail::CreateDALLE3ImageImpl(String{ apiKey }, request);
			}

			AsyncTask<s3d::Image> CreateAsync(const StringView apiKey, const RequestDALLE2& request)
			{
				return Async(detail::CreateDALLE2ImageImpl, String{ apiKey }, request);
			}

			AsyncTask<Array<s3d::Image>> CreateAsync(const StringView apiKey, const RequestDALLE2& request, const int32 numImages)
			{
				return Async(detail::CreateDALLE2ImagesImpl, String{ apiKey }, request, numImages);
			}

			AsyncTask<s3d::Image> CreateAsync(const StringView apiKey, const RequestDALLE3& request)
			{
				return Async(detail::CreateDALLE3ImageImpl, String{ apiKey }, request);
			}
		}
	}
}
