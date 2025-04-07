﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/IAudioDecoder.hpp>

namespace s3d
{
	/// @brief AAC 形式音声データのデコーダ
	class AACDecoder : public IAudioDecoder
	{
	public:

		/// @brief デコーダの名前 `U"AAC"` を返します。
		/// @return 文字列 `U"AAC"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief AAC 形式の先頭データであるかを返します。
		/// @param bytes データの先頭 48 バイト
		/// @return AAC 形式と推測される場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[48]) const override;

		/// @brief AAC 形式のファイルに想定される拡張子一覧 `{ U"aac" }` を返します。
		/// @return 配列 `{ U"aac" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief AAC 形式を示す AudioFormat を返します。
		/// @return `AudioFormat::AAC`
		[[nodiscard]]
		AudioFormat audioFormat() const noexcept override;

		/// @brief AAC 形式の音声ファイルをデコードして Wave を作成します。
		/// @param path 音声ファイルのパス
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(FilePathView path) const override;

		/// @brief AAC 形式の音声データをデコードして Wave を作成します。
		/// @param reader 音声データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(IReader& reader, FilePathView pathHint = {}) const override;
	};
}
