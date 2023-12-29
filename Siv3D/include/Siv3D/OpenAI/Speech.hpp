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
				inline constexpr StringView TTS1{ U"tts-1" };

				/// @brief 音声合成モデル tts-1-hd | Speech Synthesis Model tts-1-hd
				/// @see https://platform.openai.com/docs/models/tts
				/// @remark tts-1 よりも高品質な音声を生成します。 | Generates higher quality audio than tts-1.
				inline constexpr StringView TTS1HD{ U"tts-1-hd" };
			}

			namespace Voice
			{
				inline constexpr StringView Alloy{ U"alloy" };

				inline constexpr StringView Echo{ U"echo" };

				inline constexpr StringView Fable{ U"fable" };

				inline constexpr StringView Onyx{ U"onyx" };

				inline constexpr StringView Nova{ U"nova" };

				inline constexpr StringView Shimmer{ U"shimmer" };
			}

			namespace ResponseFormat
			{
				inline constexpr StringView MP3{ U"mp3" };

				inline constexpr StringView Opus{ U"opus" };

				inline constexpr StringView AAC{ U"aac" };

				inline constexpr StringView FLAC{ U"flac" };
			}

			inline constexpr size_t MaxInputLength = 4096;

			inline constexpr double MinSpeed = 0.25;

			inline constexpr double DefaultSpeed = 1.0;

			inline constexpr double MaxSpeed = 4.0;

			struct Request
			{
				String model{ OpenAI::Speech::Model::TTS1 };

				String input;

				String voice{ OpenAI::Speech::Voice::Alloy };

				String responseFormat{ OpenAI::Speech::ResponseFormat::MP3 };

				double speed = OpenAI::Speech::DefaultSpeed;
			};

			bool Create(StringView apiKey, const Request& request, FilePathView path);

			AsyncTask<bool> CreateAsync(StringView apiKey, const Request& request, FilePathView path);
		}
	}
}
