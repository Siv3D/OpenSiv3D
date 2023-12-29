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
		// OpenAI の画像生成 API の URL
		constexpr URLView ImageGenerationsEndpoint = U"https://api.openai.com/v1/images/generations";

		// 画像生成 API に送信するリクエストを作成する
		[[nodiscard]]
		static std::string MakeImageRequest(const StringView prompt, const Size& size, const int32 n)
		{
			JSON request;
			request[U"prompt"] = prompt;
			request[U"n"] = n;
			request[U"size"] = ((size == OpenAI::Image::ImageSize1024) ? U"1024x1024" : (size == OpenAI::Image::ImageSize512) ? U"512x512" : U"256x256");
			return request.formatUTF8();
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
			if (not InRange(n, 1, OpenAI::Image::MaxImageCount))
			{
				return{};
			}

			const std::string data = detail::MakeImageRequest(prompt, size, n);

			const auto headers = detail::MakeHeaders(apiKey);

			// 画像生成 API に非同期でリクエストを送信する
			AsyncHTTPTask task1 = SimpleHTTP::PostAsync(detail::ImageGenerationsEndpoint, headers, data.data(), data.size());

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
	}

	namespace OpenAI
	{
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
	}
}
