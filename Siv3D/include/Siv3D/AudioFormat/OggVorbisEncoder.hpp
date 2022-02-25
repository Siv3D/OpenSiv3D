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
# include <Siv3D/IAudioEncoder.hpp>
# include <Siv3D/AudioLoopTiming.hpp>

namespace s3d
{
	/// @brief Ogg Vorbis 形式音声データのエンコーダ
	class OggVorbisEncoder : public IAudioEncoder
	{
	public:

		/// @brief デフォルトのエンコード品質 (60)
		static constexpr int32 DefaultQuality = 60;
		
		/// @brief エンコーダの名前 `U"OggVorbis"` を返します。
		/// @return 文字列 `U"OggVorbis"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief Ogg Vorbis 形式のファイルに想定される拡張子一覧 `{ U"ogg" }` を返します。
		/// @return 配列 `{ U"ogg" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief Wave を Ogg Vorbis 形式でエンコードしてファイルに保存します。
		/// @param wave エンコードする Wave
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Wave& wave, FilePathView path) const override;

		/// @brief Wave を Ogg Vorbis 形式でエンコードしてファイルに保存します。
		/// @param wave エンコードする Wave
		/// @param path 保存するファイルのパス
		/// @param quality エンコード品質 [0, 100], 低いと低音質高圧縮
		/// @param loopTiming タグに埋め込むループ情報。`{}` の場合は埋め込み無し
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Wave& wave, FilePathView path, int32 quality, const AudioLoopTiming& loopTiming = {}) const;

		/// @brief Wave を Ogg Vorbis 形式でエンコードして書き出します。
		/// @param wave エンコードする Wave
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Wave& wave, IWriter& writer) const override;

		/// @brief Wave を Ogg Vorbis 形式でエンコードして書き出します。
		/// @param wave エンコードする Wave
		/// @param writer 書き出し先の IWriter インタフェース
		/// @param quality エンコード品質 [0, 100], 低いと低音質高圧縮
		/// @param loopTiming タグに埋め込むループ情報。`{}` の場合は埋め込み無し
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Wave& wave, IWriter& writer, int32 quality, const AudioLoopTiming& loopTiming = {}) const;

		/// @brief Wave を Ogg Vorbis 形式でエンコードした結果を Blob で返します。
		/// @param wave エンコードする Wave
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Wave& wave) const override;

		/// @brief Wave を Ogg Vorbis 形式でエンコードした結果を Blob で返します。
		/// @param wave エンコードする Wave
		/// @param quality エンコード品質 [0, 100], 低いと低音質高圧縮
		/// @param loopTiming タグに埋め込むループ情報。`{}` の場合は埋め込み無し
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Wave& wave, int32 quality, const AudioLoopTiming& loopTiming = {}) const;
	};
}
