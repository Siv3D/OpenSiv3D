
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4566)

TEST_CASE("FormatLiteral")
{
	REQUIRE(U""_fmt() == U"");
	REQUIRE(U"a"_fmt() == U"a");
	REQUIRE(U"{}"_fmt(0) == U"0");
	REQUIRE(U"{}"_fmt(1) == U"1");
	REQUIRE(U"{}"_fmt(10) == U"10");
	REQUIRE(U"{}"_fmt(-3.45) == U"-3.45");
	REQUIRE(U"{}"_fmt(123456789) == U"123456789");
	REQUIRE(U"{}"_fmt(U"") == U"");
	REQUIRE(U"{}"_fmt(U'a') == U"a");
	REQUIRE(U"{}"_fmt(U"Siv3D") == U"Siv3D");
	REQUIRE(U"{}"_fmt(U"{}") == U"{}");
	REQUIRE(U"{}"_fmt(U"Siv3D"_sv) == U"Siv3D");
	REQUIRE(U"{}"_fmt(Point(1, 2)) == U"(1, 2)");
	REQUIRE(U"{}"_fmt(Vec2(1.5, 2.5)) == U"(1.5, 2.5)");

	REQUIRE(U"あ{}"_fmt(0) == U"あ0");
	REQUIRE(U"あ{}"_fmt(1) == U"あ1");
	REQUIRE(U"あ{}"_fmt(10) == U"あ10");
	REQUIRE(U"あ{}"_fmt(-3.45) == U"あ-3.45");
	REQUIRE(U"あ{}"_fmt(123456789) == U"あ123456789");
	REQUIRE(U"あ{}"_fmt(U"") == U"あ");
	REQUIRE(U"あ{}"_fmt(U'a') == U"あa");
	REQUIRE(U"あ{}"_fmt(U"Siv3D") == U"あSiv3D");
	REQUIRE(U"あ{}"_fmt(U"{}") == U"あ{}");
	REQUIRE(U"あ{}"_fmt(U"Siv3D"_sv) == U"あSiv3D");
	REQUIRE(U"あ{}"_fmt(Point(1, 2)) == U"あ(1, 2)");
	REQUIRE(U"あ{}"_fmt(Vec2(1.5, 2.5)) == U"あ(1.5, 2.5)");

	REQUIRE(U"あ{}い"_fmt(U"") == U"あい");
	REQUIRE(U"あ{}い"_fmt(U'a') == U"あaい");
	REQUIRE(U"あ{}い"_fmt(U"Siv3D") == U"あSiv3Dい");
	REQUIRE(U"あ{}い"_fmt(U"{}") == U"あ{}い");
	REQUIRE(U"あ{}い"_fmt(U"Siv3D"_sv) == U"あSiv3Dい");
	REQUIRE(U"あ{}い"_fmt(Point(1, 2)) == U"あ(1, 2)い");
	REQUIRE(U"あ{}い"_fmt(Vec2(1.5, 2.5)) == U"あ(1.5, 2.5)い");

	REQUIRE(U"あ{}い"_fmt(U"う") == U"あうい");
	REQUIRE(U"あ{}い"_fmt(U'う') == U"あうい");
	REQUIRE(U"あ{}い"_fmt(U"うSiv3D") == U"あうSiv3Dい");
	REQUIRE(U"あ{}い"_fmt(U"う{}") == U"あう{}い");
	REQUIRE(U"あ{}い"_fmt(U"うSiv3D"_sv) == U"あうSiv3Dい");

	REQUIRE(U"{0}, {1}, {2}"_fmt(U'a', U'b', U'c') == U"a, b, c");
	REQUIRE(U"{}, {}, {}"_fmt(U'a', U'b', U'c') == U"a, b, c");
	REQUIRE(U"{2}, {1}, {0}"_fmt(U'a', U'b', U'c') == U"c, b, a");
	REQUIRE(U"{0}{1}{0}"_fmt(U"aa", U"bb") == U"aabbaa");

	REQUIRE(U"{0}, {1}, {2}"_fmt(U'あ', U'い', U'🎈') == U"あ, い, 🎈");
	REQUIRE(U"{}, {}, {}"_fmt(U'あ', U'い', U'🎈') == U"あ, い, 🎈");
	REQUIRE(U"{2}, {1}, {0}"_fmt(U'あ', U'い', U'🎈') == U"🎈, い, あ");
	REQUIRE(U"{0}{1}{0}"_fmt(U"ああ", U"🎈🎈") == U"ああ🎈🎈ああ");

	REQUIRE(U"{:<10}"_fmt(500) == U"500       ");
	REQUIRE(U"{:^10}"_fmt(500) == U"   500    ");
	REQUIRE(U"{:>10}"_fmt(500) == U"       500");
	REQUIRE(U"{:0>10}"_fmt(500) == U"0000000500");
	REQUIRE(U"{:*^10}"_fmt(500) == U"***500****");

	REQUIRE(U"{:<5}"_fmt(U"🎈") == U"🎈    ");
	REQUIRE(U"{:^5}"_fmt(U"🎈") == U"  🎈  ");
	REQUIRE(U"{:>5}"_fmt(U"🎈") == U"    🎈");
	REQUIRE(U"{:0>5}"_fmt(U"🎈") == U"0000🎈");
	REQUIRE(U"{:🎲^5}"_fmt(U"🎈") == U"🎲🎲🎈🎲🎲");

	REQUIRE(U"{:.0f}"_fmt(Math::Pi) == U"3");
	REQUIRE(U"{:.1f}"_fmt(Math::Pi) == U"3.1");
	REQUIRE(U"{:.2f}"_fmt(Math::Pi) == U"3.14");
	REQUIRE(U"{:.3f}"_fmt(Math::Pi) == U"3.142");

	REQUIRE(U"{:<{}}"_fmt(500, 6) == U"500   ");
	REQUIRE(U"{:<.{}f}"_fmt(3.14, 1) == U"3.1");

	REQUIRE(U"{:+f}; {:+f}"_fmt(3.14, -3.14) == U"+3.140000; -3.140000");
	REQUIRE(U"{: f}; {: f}"_fmt(3.14, -3.14) == U" 3.140000; -3.140000");
	REQUIRE(U"{:-f}; {:-f}"_fmt(3.14, -3.14) == U"3.140000; -3.140000");

	REQUIRE(U"int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}"_fmt(42) == U"int: 42;  hex: 2a;  oct: 52; bin: 101010");
	REQUIRE(U"int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}"_fmt(42) == U"int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010");
	REQUIRE(U"{:#04x}"_fmt(0) == U"0x00");

	REQUIRE(U"🎈{}🎈"_fmt(Array<String>{U"あいう", U"ABC", U"🎲🎲🎈🎲🎲"}) == U"🎈{あいう, ABC, 🎲🎲🎈🎲🎲}🎈");

	REQUIRE(U"{:<5}"_fmt(String(U"🎈")) == U"🎈    ");
	REQUIRE(U"{:.1f}"_fmt(Vec2(1.11, 2.22)) == U"(1.1, 2.2)");
}

SIV3D_DISABLE_MSVC_WARNINGS_POP()

# endif
