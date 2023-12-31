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

# include <Siv3D/OpenAI/Speech.hpp>
# include <Siv3D/URLView.hpp>
# include <Siv3D/AsyncHTTPTask.hpp>
# include <Siv3D/JSON.hpp>
# include <Siv3D/System.hpp>
# include "OpenAICommon.hpp"

namespace s3d
{
	namespace detail
	{
		/// @brief 音声合成 API のエンドポイント | Text-to-speech API endpoint
		constexpr URLView TextToSpeechEndpoint = U"https://api.openai.com/v1/audio/speech";

		/// @brief 音声合成 API に送信するリクエスト JSON を作成します。
		/// @param request リクエスト
		/// @return リクエストの JSON 文字列
		[[nodiscard]]
		static std::string MakeSpeechRequest(const OpenAI::Speech::Request& request)
		{
			JSON json;
			json[U"model"] = request.model;
			json[U"input"] = request.input;
			json[U"voice"] = request.voice;
			json[U"response_format"] = request.responseFormat;
			json[U"speed"] = request.speed;
			return json.formatUTF8();
		}

		/// @brief 音声合成 API による音声合成を行います。
		/// @param apiKey API キー
		/// @param request リクエスト
		/// @param path 結果の音声ファイルを保存先するパス
		/// @return 成功した場合 true, それ以外の場合は false
		[[nodiscard]]
		static bool CreateSpeechImpl(const String apiKey, const OpenAI::Speech::Request request, const FilePath path)
		{
			// API キーが空の文字列である場合は失敗
			if (not apiKey)
			{
				return false;
			}

			const auto headers = MakeHeaders(apiKey);
			const std::string json = MakeSpeechRequest(request);

			AsyncHTTPTask task = SimpleHTTP::PostAsync(TextToSpeechEndpoint, headers, json.data(), json.size(), path);

			// タスクが完了するまでポーリングする
			while (not task.isReady())
			{
				System::Sleep(TaskPollingInterval);
			}

			if (not task.getResponse().isOK())
			{
				return false;
			}

			return true;
		}
	}

	namespace OpenAI
	{
		namespace Speech
		{
			bool Create(const StringView apiKey, const Request& request, const FilePathView path)
			{
				return detail::CreateSpeechImpl(String{ apiKey }, request, FilePath{ path });
			}

			AsyncTask<bool> CreateAsync(const StringView apiKey, const Request& request, const FilePathView path)
			{
				return Async(detail::CreateSpeechImpl, String{ apiKey }, request, FilePath{ path });
			}
		}
	}
}
