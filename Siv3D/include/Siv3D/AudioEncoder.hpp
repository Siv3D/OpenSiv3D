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
# include "Blob.hpp"
# include "AudioFormat.hpp"
# include "IAudioEncoder.hpp"

namespace s3d
{
	namespace AudioEncoder
	{
		/// @brief Wave をエンコードしてファイルに保存します。
		/// @param wave エンコードする Wave
		/// @param format 使用するエンコーダの音声フォーマット。拡張子から判断する場合は `AudioFormat::Unknown`
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool Save(const Wave& wave, AudioFormat format, FilePathView path);

		/// @brief Wave をエンコードしてファイルに保存します。
		/// @param wave エンコードする Wave
		/// @param encoderName 使用するエンコーダの名前
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool Save(const Wave& wave, StringView encoderName, FilePathView path);

		/// @brief Wave をエンコードして書き出します。
		/// @param wave エンコードする Wave
		/// @param format 使用するエンコーダの音声フォーマット
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool Encode(const Wave& wave, const AudioFormat format, IWriter& writer);

		/// @brief Wave をエンコードして書き出します。
		/// @param wave エンコードする Wave
		/// @param encoderName 使用するエンコーダの名前
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool Encode(const Wave& wave, StringView encoderName, IWriter& writer);

		/// @brief Wave をエンコードした結果を Blob で返します。
		/// @param wave エンコードする Wave
		/// @param format 使用するエンコーダの音声フォーマット
		/// @return エンコード結果
		[[nodiscard]]
		Blob Encode(const Wave& wave, const AudioFormat format);

		/// @brief Wave をエンコードした結果を Blob で返します。
		/// @param wave エンコードする Wave
		/// @param encoderName 使用するエンコーダの名前
		/// @return エンコード結果
		[[nodiscard]]
		Blob Encode(const Wave& wave, StringView encoderName);

		/// @brief エンジンに新しいカスタム音声エンコードを追加します。
		/// @param encoder 追加するエンコーダ
		/// @return 追加に成功した場合 true, それ以外の場合は false
		bool Add(std::unique_ptr<IAudioEncoder>&& encoder);

		/// @brief エンジンから音声エンコーダを削除します。
		/// @param name 音声エンコーダの名前
		void Remove(const StringView name);

		/// @brief エンジンに登録されている音声エンコーダの一覧を返します。
		/// @return エンジンに登録されている音声エンコーダの一覧
		[[nodiscard]]
		const Array<std::unique_ptr<IAudioEncoder>>& Enum();
	}
}
