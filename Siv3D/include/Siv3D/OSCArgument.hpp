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
# include <variant>
# include "Common.hpp"
# include "OSCTypeTag.hpp"
# include "ColorHSV.hpp"
# include "String.hpp"
# include "Blob.hpp"

namespace s3d
{
	/// @brief OSC 受信メッセージの引数
	struct OSCArgument
	{
		/// @brief OSC 型タグ
		OSCTypeTag tag;

		/// @brief 値
		std::variant<std::monostate, bool, char, int32, int64, float, double, uint32, uint64, Color, String, Blob> value;

		/// @brief bool 型の値を取得します。
		/// @throw std::bad_variant_access bool 型の値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		bool getBool() const;

		/// @brief char 型の値を取得します。
		/// @throw std::bad_variant_access char 型の値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		char getChar() const;

		/// @brief int32 型の値を取得します。
		/// @throw std::bad_variant_access int32 型の値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		int32 getInt32() const;

		/// @brief int64 型の値を取得します。
		/// @throw std::bad_variant_access int64 型の値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		int64 getInt64() const;

		/// @brief float 型の値を取得します。
		/// @throw std::bad_variant_access float 型の値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		float getFloat() const;

		/// @brief double 型の値を取得します。
		/// @throw std::bad_variant_access double 型の値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		double getDouble() const;

		/// @brief MIDI メッセージの値を取得します。
		/// @throw std::bad_variant_access MIDI メッセージの値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		uint32 getMIDIMessage() const;

		/// @brief 時刻タグの値を取得します。
		/// @throw std::bad_variant_access 時刻タグの値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		uint64 getTimeTag() const;

		/// @brief RGBA カラーの値を取得します。
		/// @throw std::bad_variant_access RGBA カラーの値が格納されていない場合
		/// @return 値
		[[nodiscard]]
		Color getColor() const;

		/// @brief 文字列を取得します。
		/// @throw std::bad_variant_access 値に 文字列が格納されていない場合
		/// @return 文字列
		[[nodiscard]]
		const String& getString() const;

		/// @brief blob を取得します。
		/// @throw std::bad_variant_access 値に blob が格納されていない場合
		/// @return blob
		[[nodiscard]]
		const Blob& getBlob() const;
	};
}

# include "detail/OSCArgument.ipp"
