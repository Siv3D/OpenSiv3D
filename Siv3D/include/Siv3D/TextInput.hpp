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
# include "String.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "UnderlineStyle.hpp"
# include "TextInputMode.hpp"

namespace s3d
{
	namespace TextInput
	{
		/// @brief キーボードからのテキスト入力を生の状態で返します。
		/// @return キーボードからのテキスト入力
		[[nodiscard]]
		String GetRawInput();

		/// @brief キーボードからのテキスト入力を処理します。
		/// @param text 操作するテキストへの参照
		/// @param cursorPos テキストを操作するカーソルの位置（文字列の先頭からの要素数）
		/// @param mode テキスト編集モード
		/// @return 新しいカーソルの位置
		[[nodiscard]]
		size_t UpdateText(String& text, size_t cursorPos, TextInputMode mode = TextInputMode::Default);

		/// @brief キーボードからのテキスト入力を処理します。
		/// @param text 操作するテキストへの参照
		/// @param mode テキスト編集モード
		void UpdateText(String& text, TextInputMode mode = TextInputMode::Default);

		/// @brief 変換待ちのテキストを返します。
		/// @remark 日本語入力等で、変換待ちの状態で確定していない文字列を返します。
		/// @return 変換待ちのテキスト
		[[nodiscard]]
		String GetEditingText();
	}

# if SIV3D_PLATFORM(WINDOWS)

	class Font;

	namespace Platform::Windows::TextInput
	{
		/// @brief IME を無効化します。
		void DisableIME();

		[[nodiscard]]
		/// @brief 入力中のテキストの変換候補一覧を取得します。
		/// @return 入力中のテキストの変換候補一覧
		const Array<String>& GetCandidates();

		/// @brief 変換待ちのテキストの範囲を返します。
		/// @return 変換待ちのテキストの範囲
		[[nodiscard]]
		std::pair<int32, int32> GetCursorIndex();

		/// @brief テキストの変換候補を描画します。
		/// @param font フォント
		/// @param basePos 基準座標
		/// @param boxColor 背景色
		/// @param selectedBackgroundColor 選択されているアイテムの背景色
		/// @param frameColor 枠の色
		/// @param textColor テキストの色
		void DrawCandidateWindow(const Font& font,
			const Vec2& basePos,
			const ColorF& boxColor = ColorF{ 1.0 },
			const ColorF& selectedBackgroundColor = ColorF{ 0.55, 0.85, 1.0 },
			const ColorF& frameColor = ColorF{ 0.75 },
			const ColorF& textColor = ColorF{ 0.0 });
	}

# elif SIV3D_PLATFORM(LINUX)

	namespace Platform::Linux::TextInput
	{
		void EnableIME();

		void DisableIME();

		[[nodiscard]]
		int32 GetCursorIndex();

		[[nodiscard]]
		const Array<UnderlineStyle>& GetEditingTextStyle();
	}

# elif SIV3D_PLATFORM(WEB)

	namespace Platform::Web::TextInput
	{
		void RequestEnableIME();
		
		void RequestDisableIME();
	}

# endif
}
