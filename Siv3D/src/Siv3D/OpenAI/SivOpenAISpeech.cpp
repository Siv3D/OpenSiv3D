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
		constexpr URLView TextToSpeechEndpoint = U"https://api.openai.com/v1/audio/speech";

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

		static bool CreateSpeechImpl(const String apiKey, const OpenAI::Speech::Request request, const FilePath path)
		{
			// API キーが空の文字列である場合は失敗
			if (apiKey.isEmpty())
			{
				return false;
			}

			const auto headers = MakeHeaders(apiKey);

			const std::string data = MakeSpeechRequest(request);

			AsyncHTTPTask task = SimpleHTTP::PostAsync(TextToSpeechEndpoint, headers, data.data(), data.size(), path);

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
