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
# include <cwctype>
# include <wchar.h>
# include "Common.hpp"

/*
# ASCII Table

Dec Hx Ch                            | Dec Hx Ch    | Dec Hx Ch | Dec Hx Ch
-------------------------------------|--------------|-----------|----------
  0  0 NUL Null                      |  32 20 space |  64 40 @  |  96 60 `
  1  1 SOH Start of Heading          |  33 21 !     |  65 41 A  |  97 61 a
  2  2 STX Start of Text             |  34 22 "     |  66 42 B  |  98 62 b
  3  3 ETX End of Text               |  35 23 #     |  67 43 C  |  99 63 c
  4  4 EOT End of Transmission       |  36 24 $     |  68 44 D  | 100 64 d
  5  5 ENQ Enquiry                   |  37 25 %     |  69 45 E  | 101 65 e
  6  6 ACK Acknowledge               |  38 26 &     |  70 46 F  | 102 66 f
  7  7 BEL Bell                      |  39 27 '     |  71 47 G  | 103 67 g
  8  8 BS  Backspace                 |  40 28 (     |  72 48 H  | 104 68 h
  9  9 HT  Horizontal Tab            |  41 29 )     |  73 49 I  | 105 69 i
 10 0A LF  Line Feed                 |  42 2A *     |  74 4A J  | 106 6A j
 11 0B VT  Vertical Tab              |  43 2B +     |  75 4B K  | 107 6B k
 12 0C FF  Form Feed                 |  44 2C ,     |  76 4C L  | 108 6C l
 13 0D CR  Carriage Return           |  45 2D -     |  77 4D M  | 109 6D m
 14 0E SO  Shift Out                 |  46 2E .     |  78 4E N  | 110 6E n
 15 0F SI  Shift In                  |  47 2F /     |  79 4F O  | 111 6F o
 16 10 DLE Data Link Escape          |  48 30 0     |  80 50 P  | 112 70 p
 17 11 DC1 Device Control 1          |  49 31 1     |  81 51 Q  | 113 71 q
 18 12 DC2 Device Control 2          |  50 32 2     |  82 52 R  | 114 72 r
 19 13 DC3 Device Control 3          |  51 33 3     |  83 53 S  | 115 73 s
 20 14 DC4 Device Control 4          |  52 34 4     |  84 54 T  | 116 74 t
 21 15 NAK Negative Acknowledge      |  53 35 5     |  85 55 U  | 117 75 u
 22 16 SYN Synchronous Idle          |  54 36 6     |  86 56 V  | 118 76 v
 23 17 ETB End of Transmission Block |  55 37 7     |  87 57 W  | 119 77 w
 24 18 CAN Cancel                    |  56 38 8     |  88 58 X  | 120 78 x
 25 19 EM  End of Medium             |  57 39 9     |  89 59 Y  | 121 79 y
 26 1A SUB Substitute                |  58 3A :     |  90 5A Z  | 122 7A z
 27 1B ESC Escape                    |  59 3B ;     |  91 5B [  | 123 7B {
 28 1C FS  File Separator            |  60 3C <     |  92 5C \  | 124 7C |
 29 1D GS  Group Separator           |  61 3D =     |  93 5D ]  | 125 7D }
 30 1E RS  Record Separator          |  62 3E >     |  94 5E ^  | 126 7E ~
 31 1F US  Unit Separator            |  63 3F ?     |  95 5F _  | 127 7F DEL
*/

namespace s3d
{
	/// @brief ASCII 文字であるかを返します。 | Checks whether `ch` is an ASCII character.
	/// @param ch 文字 | Character to be checked
	/// @return ASCII 文字である場合 true, それ以外の場合は false | True if ch is an ASCII character, false otherwise
	[[nodiscard]]
	inline constexpr bool IsASCII(char32 ch) noexcept;

	/// @brief 10 進数の数字であるかを返します。
	/// @param ch 文字
	/// @return 10 進数の数字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsDigit(char32 ch) noexcept;

	/// @brief アルファベットの小文字であるかを返します。
	/// @param ch 文字
	/// @return アルファベットの小文字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsLower(char32 ch) noexcept;

	/// @brief アルファベットの大文字であるかを返します。
	/// @param ch 文字
	/// @return アルファベットの大文字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsUpper(char32 ch) noexcept;

	/// @brief アルファベットの大文字を小文字にします。
	/// @param ch 文字
	/// @return アルファベットの大文字である場合はそれを小文字にした文字、それ以外の場合は同じ文字
	[[nodiscard]]
	inline constexpr char32 ToLower(char32 ch) noexcept;

	/// @brief アルファベットの小文字を大文字にします。
	/// @param ch 文字
	/// @return アルファベットの小文字である場合はそれを大文字にした文字、それ以外の場合は同じ文字
	[[nodiscard]]
	inline constexpr char32 ToUpper(char32 ch) noexcept;

	/// @brief 文字がアルファベットであるかを返します。
	/// @param ch 文字
	/// @return アルファベットである場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsAlpha(char32 ch) noexcept;

	/// @brief 文字がアルファベットもしくは数字であるかを返します。
	/// @param ch 文字
	/// @return アルファベットもしくは数字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsAlnum(char32 ch) noexcept;

	/// @brief 文字が 16 進数の数字であるかを返します。
	/// @param ch 文字
	/// @return 16 進数の数字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsXdigit(char32 ch) noexcept;

	/// @brief 文字が制御文字であるかを返します。
	/// @param ch 文字
	/// @return 制御文字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsControl(char32 ch) noexcept;

	/// @brief 文字が空白文字であるかを返します。
	/// @param ch 文字
	/// @remark ' ', '\t', '　' が該当します。
	/// @return 空白文字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsBlank(char32 ch) noexcept;

	/// @brief 文字が空白類文字であるかを返します。
	/// @param ch 文字
	/// @remark ' ', '\t', '\n', '\v', '\f', '\r', '　' が該当します。
	/// @return 空白類文字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool IsSpace(char32 ch) noexcept;

	/// @brief 文字が印字可能文字であるかを返します。
	/// @param ch 文字
	/// @return 印字可能文字である場合 true, それ以外の場合は false
	[[nodiscard]]
	inline bool IsPrint(char32 ch);

	/// @brief 大文字小文字を区別しない文字の大小比較の結果を返します。
	/// @param a 比較する文字
	/// @param b 比較する文字
	/// @return 文字の大小比較の結果
	[[nodiscard]]
	inline constexpr int32 CaseInsensitiveCompare(char32 a, char32 b) noexcept;

	/// @brief 大文字小文字を区別せず、文字が同じであるかを返します。
	/// @param a 比較する文字
	/// @param b 比較する文字
	/// @return 文字が同じである場合 true, それ以外の場合は false
	[[nodiscard]]
	inline constexpr bool CaseInsensitiveEquals(char32 a, char32 b) noexcept;
}

# include "detail/Char.ipp"
