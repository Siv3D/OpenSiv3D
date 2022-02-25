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
# include "LanguageCode.hpp"
# include "StringView.hpp"

namespace s3d
{
	namespace TextToSpeech
	{
		/// @brief 指定した言語コードで文章読み上げが可能かを返します。
		/// @param languageCode 言語コード
		/// @return 文章読み上げが可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		bool HasLanguage(LanguageCode languageCode);

		/// @brief 文章読み上げ時の言語を設定します。
		/// @param languageCode 言語コード
		void SetDefaultLanguage(LanguageCode languageCode);

		/// @brief システムのデフォルトの文章読み上げ言語コードを返します。
		/// @return システムのデフォルトの文章読み上げ言語コード
		[[nodiscard]]
		LanguageCode GetDefaultLanguage();

		/// @brief 文章の読み上げを開始します。
		/// @param text 文章
		/// @param languageCode 使用する言語
		/// @remark この関数は文章の読み上げを開始したら即座に制御を返します。
		/// @return 読み上げの開始に成功したら true, それ以外の場合は false
		bool Speak(StringView text, LanguageCode languageCode = LanguageCode::Unspecified);

		/// @brief 文章を読み上げ中であるかを返します。
		/// @return 文章を読み上げ中である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsSpeaking();

		/// @brief 文章の読み上げを一時停止します。
		void Pause();

		/// @brief 一時停止した文章の読み上げを再開します。
		void Resume();

		/// @brief 文章読み上げ時の音量を設定します。
		/// @param volume 音量 [0.0, 1.0]
		void SetVolume(double volume);

		/// @brief 文章読み上げ時の音量の設定を返します。
		/// @return 文章読み上げ時の音量の設定 [0.0, 1.0]
		[[nodiscard]]
		double GetVolume();

		/// @brief 文章読み上げ時のスピードを設定します。
		/// @param speed スピード [0.0, 2.0]
		void SetSpeed(double speed);

		/// @brief 文章読み上げ時のスピードの設定を返します。
		/// @return スピード [0.0, 2.0]
		[[nodiscard]]
		double GetSpeed();
	}
}
