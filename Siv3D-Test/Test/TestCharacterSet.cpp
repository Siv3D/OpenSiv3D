//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST)

S3D_DISABLE_MSVC_WARNINGS_PUSH(4566)

using namespace s3d;

TEST(CharacterSet, WidenAscii)
{
	EXPECT_EQ(CharacterSet::WidenAscii(""), L"");
	EXPECT_EQ(CharacterSet::WidenAscii("12345ABCDE"), L"12345ABCDE");
	EXPECT_EQ(CharacterSet::WidenAscii(CStringView()), L"");
	EXPECT_EQ(CharacterSet::WidenAscii(CStringView("12345ABCDE???", 10)), L"12345ABCDE");
}

TEST(CharacterSet, Widen)
{
	EXPECT_EQ(CharacterSet::Widen(""), L"");
	EXPECT_EQ(CharacterSet::Widen("12345ABCDEあいうえお"), L"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::Widen(CStringView()), L"");
# if defined(SIV3D_TARGET_WINDOWS)
	EXPECT_EQ(CharacterSet::Widen(CStringView("12345ABCDEあいうえお???", 20)), L"12345ABCDEあいうえお");
# elif defined(SIV3D_TARGET_MACOS)
	EXPECT_EQ(CharacterSet::Widen(CStringView("12345ABCDEあいうえお???", 25)), L"12345ABCDEあいうえお");
# endif
	EXPECT_EQ(CharacterSet::Widen("噂浬欺榎掛弓"), L"噂浬欺榎掛弓");
}

TEST(CharacterSet, NarrowAscii)
{
	EXPECT_EQ(CharacterSet::NarrowAscii(L""), "");
	EXPECT_EQ(CharacterSet::NarrowAscii(L"12345ABCDE"), "12345ABCDE");
	EXPECT_EQ(CharacterSet::NarrowAscii(StringView()), "");
	EXPECT_EQ(CharacterSet::NarrowAscii(StringView(L"12345ABCDE???", 10)), "12345ABCDE");
}

TEST(CharacterSet, Narrow)
{
	EXPECT_EQ(CharacterSet::Narrow(L""), "");
	EXPECT_EQ(CharacterSet::Narrow(L"12345ABCDEあいうえお"), "12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::Narrow(StringView()), "");
	EXPECT_EQ(CharacterSet::Narrow(StringView(L"12345ABCDEあいうえお???", 15)), "12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::Narrow(L"噂浬欺榎掛弓"), "噂浬欺榎掛弓");
}

TEST(CharacterSet, FromUTF8)
{
	EXPECT_EQ(CharacterSet::FromUTF8(u8""), L"");
	EXPECT_EQ(CharacterSet::FromUTF8(u8"12345ABCDEあいうえお"), L"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::FromUTF8(UTF8StringView()), L"");
	EXPECT_EQ(CharacterSet::FromUTF8(UTF8StringView(u8"12345ABCDEあいうえお???", 25)), L"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::FromUTF8(u8"𩸽😁"), L"𩸽😁");
}

TEST(CharacterSet, FromUTF16)
{
	EXPECT_EQ(CharacterSet::FromUTF16(u""), L"");
	EXPECT_EQ(CharacterSet::FromUTF16(u"12345ABCDEあいうえお"), L"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::FromUTF16(u"𩸽😁"), L"𩸽😁");
}

TEST(CharacterSet, FromUTF32)
{
	EXPECT_EQ(CharacterSet::FromUTF32(U""), L"");
	EXPECT_EQ(CharacterSet::FromUTF32(U"12345ABCDEあいうえお"), L"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::FromUTF32(U"𩸽😁"), L"𩸽😁");
}

TEST(CharacterSet, ToUTF8)
{
	EXPECT_EQ(CharacterSet::ToUTF8(L""), u8"");
	EXPECT_EQ(CharacterSet::ToUTF8(L"12345ABCDEあいうえお"), u8"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::ToUTF8(StringView()), u8"");
	EXPECT_EQ(CharacterSet::ToUTF8(StringView(L"12345ABCDEあいうえお???", 15)), u8"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::ToUTF8(L"𩸽😁"), u8"𩸽😁");
}

TEST(CharacterSet, ToUTF16)
{
	EXPECT_EQ(CharacterSet::ToUTF16(L""), u"");
	EXPECT_EQ(CharacterSet::ToUTF16(L"12345ABCDEあいうえお"), u"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::ToUTF16(StringView()), u"");
	EXPECT_EQ(CharacterSet::ToUTF16(StringView(L"12345ABCDEあいうえお???", 15)), u"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::ToUTF16(L"𩸽😁"), u"𩸽😁");
}

TEST(CharacterSet, ToUTF32)
{
	EXPECT_EQ(CharacterSet::ToUTF32(L""), U"");
	EXPECT_EQ(CharacterSet::ToUTF32(L"12345ABCDEあいうえお"), U"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::ToUTF32(StringView()), U"");
	EXPECT_EQ(CharacterSet::ToUTF32(StringView(L"12345ABCDEあいうえお???", 15)), U"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::ToUTF32(L"𩸽😁"), U"𩸽😁");
}

TEST(CharacterSet, UTF8ToUTF16)
{
	EXPECT_EQ(CharacterSet::UTF8ToUTF16(u8""), u"");
	EXPECT_EQ(CharacterSet::UTF8ToUTF16(u8"12345ABCDEあいうえお"), u"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF8ToUTF16(UTF8StringView()), u"");
	EXPECT_EQ(CharacterSet::UTF8ToUTF16(UTF8StringView(u8"12345ABCDEあいうえお???", 25)), u"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF8ToUTF16(u8"𩸽😁"), u"𩸽😁");
}

TEST(CharacterSet, UTF8ToUTF32)
{
	EXPECT_EQ(CharacterSet::UTF8ToUTF32(u8""), U"");
	EXPECT_EQ(CharacterSet::UTF8ToUTF32(u8"12345ABCDEあいうえお"), U"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF8ToUTF32(UTF8StringView()), U"");
	EXPECT_EQ(CharacterSet::UTF8ToUTF32(UTF8StringView(u8"12345ABCDEあいうえお???", 25)), U"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF8ToUTF32(u8"𩸽😁"), U"𩸽😁");
}

TEST(CharacterSet, UTF16ToUTF8)
{
	EXPECT_EQ(CharacterSet::UTF16ToUTF8(u""), u8"");
	EXPECT_EQ(CharacterSet::UTF16ToUTF8(u"12345ABCDEあいうえお"), u8"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF16ToUTF8(u"𩸽😁"), u8"𩸽😁");
}

TEST(CharacterSet, UTF16ToUTF32)
{
	EXPECT_EQ(CharacterSet::UTF16ToUTF32(u""), U"");
	EXPECT_EQ(CharacterSet::UTF16ToUTF32(u"12345ABCDEあいうえお"), U"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF16ToUTF32(u"𩸽😁"), U"𩸽😁");
}

TEST(CharacterSet, UTF32ToUTF8)
{
	EXPECT_EQ(CharacterSet::UTF32ToUTF8(U""), u8"");
	EXPECT_EQ(CharacterSet::UTF32ToUTF8(U"12345ABCDEあいうえお"), u8"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF32ToUTF8(U"𩸽😁"), u8"𩸽😁");
}

TEST(CharacterSet, UTF32ToUTF16)
{
	EXPECT_EQ(CharacterSet::UTF32ToUTF16(U""), u"");
	EXPECT_EQ(CharacterSet::UTF32ToUTF16(U"12345ABCDEあいうえお"), u"12345ABCDEあいうえお");
	EXPECT_EQ(CharacterSet::UTF32ToUTF16(U"𩸽😁"), u"𩸽😁");
}

TEST(CharacterSet, PercentEncode)
{

}

S3D_DISABLE_MSVC_WARNINGS_POP()

# endif
