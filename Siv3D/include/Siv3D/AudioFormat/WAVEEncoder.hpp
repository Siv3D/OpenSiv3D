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
# include <Siv3D/WAVEFormat.hpp>

namespace s3d
{
	/// @brief WAVE 形式音声データのエンコーダ
	class WAVEEncoder : public IAudioEncoder
	{
	public:

		/// @brief エンコーダの名前 `U"WAVE"` を返します。
		/// @return 文字列 `U"WAVE"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief WAVE 形式のファイルに想定される拡張子一覧 `{ U"wav" }` を返します。
		/// @return 配列 `{ U"wav" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief Wave を WAVE 形式でエンコードしてファイルに保存します。
		/// @param wave エンコードする Wave
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Wave& wave, FilePathView path) const override;

		/// @brief Wave を WAVE 形式でエンコードしてファイルに保存します。
		/// @param wave エンコードする Wave
		/// @param path 保存するファイルのパス
		/// @param format WAVE のフォーマット 
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Wave& wave, FilePathView path, WAVEFormat format) const;

		/// @brief Wave を WAVE 形式でエンコードして書き出します。
		/// @param wave エンコードする Wave
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return  書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Wave& wave, IWriter& writer) const override;

		/// @brief Wave を WAVE 形式でエンコードして書き出します。
		/// @param wave エンコードする Wave
		/// @param writer 書き出し先の IWriter インタフェース
		/// @param format WAVE のフォーマット 
		/// @return  書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Wave& wave, IWriter& writer, WAVEFormat format) const;

		/// @brief Wave を WAVE 形式でエンコードした結果を Blob で返します。
		/// @param wave エンコードする Wave
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Wave& wave) const override;

		/// @brief Wave を WAVE 形式でエンコードした結果を Blob で返します。
		/// @param wave エンコードする Wave
		/// @param format WAVE のフォーマット 
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Wave& wave, WAVEFormat format) const;
	};
}
