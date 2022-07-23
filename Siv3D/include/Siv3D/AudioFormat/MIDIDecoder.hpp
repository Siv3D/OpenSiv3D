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
# include <Siv3D/IAudioDecoder.hpp>
# include <Siv3D/MIDINote.hpp>

namespace s3d
{
	/// @brief MIDI 形式音声データのデコーダ
	class MIDIDecoder : public IAudioDecoder
	{
	public:

		/// @brief デコーダの名前 `U"MIDI"` を返します。
		/// @return 文字列 `U"MIDI"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief MIDI 形式の先頭データであるかを返します。
		/// @param bytes データの先頭 48 バイト
		/// @return MIDI 形式と推測される場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[48]) const override;

		/// @brief MIDI 形式のファイルに想定される拡張子一覧 `{ U"mid" }` を返します。
		/// @return 配列 `{ U"mid" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief MIDI 形式を示す AudioFormat を返します。
		/// @return `AudioFormat::MIDI`
		[[nodiscard]]
		AudioFormat audioFormat() const noexcept override;

		/// @brief MIDI 形式の音声ファイルをデコードして Wave を作成します。
		/// @param path 音声ファイルのパス
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(FilePathView path) const override;

		/// @brief MIDI 形式の音声ファイルをデコードして Wave と譜面データを作成します。
		/// @param path 音声ファイルのパス
		/// @param midiScore 譜面データの格納先
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore) const;

		/// @brief MIDI 形式の音声データをデコードして Wave を作成します。
		/// @param reader 音声データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(IReader& reader, FilePathView pathHint = {}) const override;

		/// @brief MIDI 形式の音声データをデコードして Wave と譜面データを作成します。
		/// @param reader 音声データの IReader インタフェース
		/// @param midiScore 譜面データの格納先
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, FilePathView pathHint = {}) const;
	};
}
