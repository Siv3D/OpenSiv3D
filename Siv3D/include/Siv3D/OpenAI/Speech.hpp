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
# include "../AsyncTask.hpp"

namespace s3d
{
	namespace OpenAI
	{
		namespace Speech
		{
			namespace Model
			{
				/// @brief 音声合成モデル tts-1 | Speech Synthesis Model tts-1
				/// @see https://platform.openai.com/docs/models/tts
				inline constexpr char32 TTS1[] = U"tts-1";

				/// @brief 音声合成モデル tts-1-hd | Speech Synthesis Model tts-1-hd
				/// @see https://platform.openai.com/docs/models/tts
				/// @remark tts-1 よりも高品質な音声を生成します。 | Generates higher quality audio than tts-1.
				inline constexpr char32 TTS1HD[] = U"tts-1-hd";
			}

			/// @brief 音声合成モデルの声 | Voice of the speech synthesis model
			/// @see https://platform.openai.com/docs/guides/text-to-speech/voice-options
			namespace Voice
			{
				/// @brief Alloy
				inline constexpr char32 Alloy[] = U"alloy";

				/// @brief Echo
				inline constexpr char32 Echo[] = U"echo";

				/// @brief Fable
				inline constexpr char32 Fable[] = U"fable";

				/// @brief Onyx
				inline constexpr char32 Onyx[] = U"onyx";

				/// @brief Nova
				inline constexpr char32 Nova[] = U"nova";

				/// @brief Shimmer
				inline constexpr char32 Shimmer[] = U"shimmer";
			}

			/// @brief 音声合成 API の出力フォーマット | Output format of the speech synthesis API
			namespace ResponseFormat
			{
				/// @brief MP3
				inline constexpr char32 MP3[] = U"mp3";

				/// @brief Opus
				inline constexpr char32 Opus[] = U"opus";

				/// @brief AAC
				inline constexpr char32 AAC[] = U"aac";
				
				/// @brief FLAC
				inline constexpr char32 FLAC[] = U"flac";
			}

			/// @brief 音声合成 API に送信するリクエスト | Request to send to the speech synthesis API
			struct Request
			{
				/// @brief 入力テキストの最大長 | Maximum length of input text
				static constexpr size_t MaxInputLength = 4096;

				/// @brief 速度の最小値 | Minimum value of speed
				static constexpr double MinSpeed = 0.25;

				/// @brief 速度の最大値 | Maximum value of speed
				static constexpr double MaxSpeed = 4.0;

				/// @brief 速度のデフォルト値 | Default value of speed
				static constexpr double DefaultSpeed = 1.0;

				/// @brief 入力テキスト | Input text
				String input;

				/// @brief モデル | Model
				String model = Model::TTS1;

				/// @brief 声 | Voice
				String voice = Voice::Alloy;

				/// @brief 出力フォーマット | Output format
				String responseFormat = ResponseFormat::MP3;

				/// @brief 速度 | Speed
				double speed = DefaultSpeed;
			};

			/// @brief テキストから音声を合成します。 | Synthesizes speech from text.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @param path 結果の音声ファイルを保存先するパス | Path to save the resulting audio file
			/// @return 成功した場合 true, それ以外の場合は false | Returns true on success, false otherwise
			bool Create(StringView apiKey, const Request& request, FilePathView path);

			/// @brief テキストから音声を合成する非同期タスクを返します。 | Returns an asynchronous task that synthesizes speech from text.
			/// @param apiKey OpenAI API キー | OpenAI API key
			/// @param request リクエスト | Request
			/// @param path 結果の音声ファイルを保存先するパス | Path to save the resulting audio file
			/// @return 非同期タスク | Asynchronous task
			/// @remark 戻り値の task が `task.isReady() == true` になれば `task.get()` で結果を取得できます。 | The result can be retrieved if `task.isReady() == true`.
			/// @remark インターネットアクセスが必要です。 | Internet access is required.
			AsyncTask<bool> CreateAsync(StringView apiKey, const Request& request, FilePathView path);
		}
	}
}
