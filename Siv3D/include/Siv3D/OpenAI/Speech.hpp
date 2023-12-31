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

			namespace Voice
			{
				inline constexpr char32 Alloy[] = U"alloy";

				inline constexpr char32 Echo[] = U"echo";

				inline constexpr char32 Fable[] = U"fable";

				inline constexpr char32 Onyx[] = U"onyx";

				inline constexpr char32 Nova[] = U"nova";

				inline constexpr char32 Shimmer[] = U"shimmer";
			}

			namespace ResponseFormat
			{
				inline constexpr char32 MP3[] = U"mp3";

				inline constexpr char32 Opus[] = U"opus";

				inline constexpr char32 AAC[] = U"aac";

				inline constexpr char32 FLAC[] = U"flac";
			}

			struct Request
			{
				static constexpr size_t MaxInputLength = 4096;

				static constexpr double MinSpeed = 0.25;

				static constexpr double DefaultSpeed = 1.0;

				static constexpr double MaxSpeed = 4.0;

				String input;

				String model = Model::TTS1;

				String voice = Voice::Alloy;

				String responseFormat = ResponseFormat::MP3;

				double speed = DefaultSpeed;
			};

			bool Create(StringView apiKey, const Request& request, FilePathView path);

			AsyncTask<bool> CreateAsync(StringView apiKey, const Request& request, FilePathView path);
		}
	}
}
