//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Wave.hpp"
# include "IAudioDecoder.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	namespace AudioDecoder
	{
		[[nodiscard]]
		AudioFormat GetAudioFormat(FilePathView path);

		[[nodiscard]]
		AudioFormat GetAudioFormat(IReader& reader);

		/// @brief 音声ファイルをデコードして、Wave を作成します。
		/// @param path 音声ファイルのパス
		/// @param audioFormat 音声のフォーマット。不明の場合は `AudioFormat::Unknown`
		/// @return 作成した Wave
		[[nodiscard]]
		Wave Decode(FilePathView path, AudioFormat audioFormat);

		/// @brief 音声ファイルをデコードして、Wave を作成します。
		/// @param path 音声ファイルのパス
		/// @param decoderName 使用するデコーダの名前
		/// @return 作成した Wave
		[[nodiscard]]
		Wave Decode(FilePathView path, StringView decoderName);

		/// @brief 音声データをデコードして、Wave を作成します。
		/// @param reader 音声データの IReader インタフェース
		/// @param audioFormat 音声のフォーマット。不明の場合は `AudioFormat::Unknown`
		/// @return 作成した Wave
		[[nodiscard]]
		Wave Decode(IReader& reader, AudioFormat audioFormat);

		/// @brief 音声データをデコードして、Wave を作成します。
		/// @param reader 音声データの IReader インタフェース
		/// @param decoderName 使用するデコーダの名前
		/// @return 作成した Wave
		[[nodiscard]]
		Wave Decode(IReader& reader, StringView decoderName);

		/// @brief エンジンに新しいカスタム音声デコーダを追加します。
		/// @param decoder 追加するデコーダ
		/// @return 追加に成功した場合 true, それ以外の場合は false
		bool Add(std::unique_ptr<IAudioDecoder>&& decoder);

		/// @brief エンジンから音声デコーダを削除します。
		/// @param name 音声デコーダの名前
		void Remove(StringView name);

		/// @brief エンジンに登録されている音声デコーダの一覧を返します。
		/// @return エンジンに登録されている音声デコーダの一覧
		[[nodiscard]]
		const Array<std::unique_ptr<IAudioDecoder>>& Enum();
	}

# if SIV3D_PLATFORM(WEB)

 	namespace Platform::Web::AudioDecoder
	{
		void DecodeFromFile(const FilePathView path, std::promise<Wave> p);
		
		AsyncTask<Wave> DecodeFromFile(const FilePathView path);
	}

# endif
}
