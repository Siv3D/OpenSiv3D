
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

TEST_CASE("FormatInt")
{
	SECTION("ToString(char)")
	{
		REQUIRE(ToString(char(-128)) == U"-128");
		REQUIRE(ToString(char(-127)) == U"-127");
		REQUIRE(ToString(char(-1)) == U"-1");
		REQUIRE(ToString(char(0)) == U"0");
		REQUIRE(ToString(char(1)) == U"1");
		REQUIRE(ToString(char(126)) == U"126");
		REQUIRE(ToString(char(127)) == U"127");

		REQUIRE(ToString(char(123)) == U"123");
	}

	SECTION("ToString(int8)")
	{
		REQUIRE(ToString(int8(-128)) == U"-128");
		REQUIRE(ToString(int8(-127)) == U"-127");
		REQUIRE(ToString(int8(-1)) == U"-1");
		REQUIRE(ToString(int8(0)) == U"0");
		REQUIRE(ToString(int8(1)) == U"1");
		REQUIRE(ToString(int8(126)) == U"126");
		REQUIRE(ToString(int8(127)) == U"127");

		REQUIRE(ToString(int8(123)) == U"123");
		REQUIRE(ToString(int8(-123)) == U"-123");
	}

	SECTION("ToString(uint8)")
	{
		REQUIRE(ToString(uint8(0)) == U"0");
		REQUIRE(ToString(uint8(1)) == U"1");
		REQUIRE(ToString(uint8(126)) == U"126");
		REQUIRE(ToString(uint8(127)) == U"127");
		REQUIRE(ToString(uint8(128)) == U"128");
		REQUIRE(ToString(uint8(254)) == U"254");
		REQUIRE(ToString(uint8(255)) == U"255");

		REQUIRE(ToString(uint8(123)) == U"123");
	}

	SECTION("ToString(int16)")
	{
		REQUIRE(ToString(int16(-32768)) == U"-32768");
		REQUIRE(ToString(int16(-32767)) == U"-32767");
		REQUIRE(ToString(int16(-1)) == U"-1");
		REQUIRE(ToString(int16(0)) == U"0");
		REQUIRE(ToString(int16(1)) == U"1");
		REQUIRE(ToString(int16(32766)) == U"32766");
		REQUIRE(ToString(int16(32767)) == U"32767");

		REQUIRE(ToString(int16(123)) == U"123");
		REQUIRE(ToString(int16(-123)) == U"-123");
	}

	SECTION("ToString(uint16)")
	{
		REQUIRE(ToString(uint16(0)) == U"0");
		REQUIRE(ToString(uint16(1)) == U"1");
		REQUIRE(ToString(uint16(32766)) == U"32766");
		REQUIRE(ToString(uint16(32767)) == U"32767");
		REQUIRE(ToString(uint16(32768)) == U"32768");
		REQUIRE(ToString(uint16(65534)) == U"65534");
		REQUIRE(ToString(uint16(65535)) == U"65535");

		REQUIRE(ToString(uint16(123)) == U"123");
	}

	SECTION("ToString(int32)")
	{
		REQUIRE(ToString(int32(-2147483647 - 1)) == U"-2147483648");
		REQUIRE(ToString(int32(-2147483647)) == U"-2147483647");
		REQUIRE(ToString(int32(-1)) == U"-1");
		REQUIRE(ToString(int32(0)) == U"0");
		REQUIRE(ToString(int32(1)) == U"1");
		REQUIRE(ToString(int32(2147483646)) == U"2147483646");
		REQUIRE(ToString(int32(2147483647)) == U"2147483647");

		REQUIRE(ToString(int32(123)) == U"123");
		REQUIRE(ToString(int32(123456)) == U"123456");
		REQUIRE(ToString(int32(123456789)) == U"123456789");
		REQUIRE(ToString(int32(-123)) == U"-123");
		REQUIRE(ToString(int32(-123456)) == U"-123456");
		REQUIRE(ToString(int32(-123456789)) == U"-123456789");
	}

	SECTION("ToString(uint32)")
	{
		REQUIRE(ToString(uint32(0)) == U"0");
		REQUIRE(ToString(uint32(1)) == U"1");
		REQUIRE(ToString(uint32(2147483646)) == U"2147483646");
		REQUIRE(ToString(uint32(2147483647)) == U"2147483647");
		REQUIRE(ToString(uint32(2147483648)) == U"2147483648");
		REQUIRE(ToString(uint32(4294967294)) == U"4294967294");
		REQUIRE(ToString(uint32(4294967295)) == U"4294967295");

		REQUIRE(ToString(uint32(123)) == U"123");
		REQUIRE(ToString(uint32(123456)) == U"123456");
		REQUIRE(ToString(uint32(123456789)) == U"123456789");
	}

	SECTION("ToString(long)")
	{
		REQUIRE(ToString(long(LONG_MIN)).narrow() == std::to_string(long(LONG_MIN)));
		REQUIRE(ToString(long(LONG_MIN + 1)).narrow() == std::to_string(long(LONG_MIN + 1)));
		REQUIRE(ToString(long(-1)) == U"-1");
		REQUIRE(ToString(long(0)) == U"0");
		REQUIRE(ToString(long(1)) == U"1");
		REQUIRE(ToString(long(LONG_MAX - 1)).narrow() == std::to_string(long(LONG_MAX - 1)));
		REQUIRE(ToString(long(LONG_MAX)).narrow() == std::to_string(long(LONG_MAX)));

		REQUIRE(ToString(long(123)) == U"123");
		REQUIRE(ToString(long(123456)) == U"123456");
		REQUIRE(ToString(long(123456789)) == U"123456789");
		REQUIRE(ToString(long(-123)) == U"-123");
		REQUIRE(ToString(long(-123456)) == U"-123456");
		REQUIRE(ToString(long(-123456789)) == U"-123456789");
	}

	SECTION("ToString(unsigned long)")
	{
		REQUIRE(ToString(unsigned long(0)) == U"0");
		REQUIRE(ToString(unsigned long(1)) == U"1");
		REQUIRE(ToString(unsigned long(ULONG_MAX / 2 - 1)).narrow() == std::to_string(unsigned long(ULONG_MAX / 2 - 1)));
		REQUIRE(ToString(unsigned long(ULONG_MAX / 2)).narrow() == std::to_string(unsigned long(ULONG_MAX / 2)));
		REQUIRE(ToString(unsigned long(ULONG_MAX / 2 + 1)).narrow() == std::to_string(unsigned long(ULONG_MAX / 2 + 1)));
		REQUIRE(ToString(unsigned long(ULONG_MAX - 1)).narrow() == std::to_string(unsigned long(ULONG_MAX - 1)));
		REQUIRE(ToString(unsigned long(ULONG_MAX)).narrow() == std::to_string(unsigned long(ULONG_MAX)));

		REQUIRE(ToString(unsigned long(123)) == U"123");
		REQUIRE(ToString(unsigned long(123456)) == U"123456");
		REQUIRE(ToString(unsigned long(123456789)) == U"123456789");
	}

	SECTION("ToString(long long)")
	{
		REQUIRE(ToString(long long(-9223372036854775807i64 - 1)) == U"-9223372036854775808");
		REQUIRE(ToString(long long(-9223372036854775807i64)) == U"-9223372036854775807");
		REQUIRE(ToString(long long(-1)) == U"-1");
		REQUIRE(ToString(long long(0)) == U"0");
		REQUIRE(ToString(long long(1)) == U"1");
		REQUIRE(ToString(long long(9223372036854775806i64)) == U"9223372036854775806");
		REQUIRE(ToString(long long(9223372036854775807i64)) == U"9223372036854775807");

		REQUIRE(ToString(long long(123i64)) == U"123");
		REQUIRE(ToString(long long(123456i64)) == U"123456");
		REQUIRE(ToString(long long(123456789i64)) == U"123456789");
		REQUIRE(ToString(long long(123456789012i64)) == U"123456789012");
		REQUIRE(ToString(long long(-123i64)) == U"-123");
		REQUIRE(ToString(long long(-123456i64)) == U"-123456");
		REQUIRE(ToString(long long(-123456789i64)) == U"-123456789");
		REQUIRE(ToString(long long(-123456789012i64)) == U"-123456789012");
	}

	SECTION("ToString(unsigned long long)")
	{
		REQUIRE(ToString(unsigned long long(0)) == U"0");
		REQUIRE(ToString(unsigned long long(1)) == U"1");
		REQUIRE(ToString(unsigned long long(9223372036854775806Ui64)) == U"9223372036854775806");
		REQUIRE(ToString(unsigned long long(9223372036854775807Ui64)) == U"9223372036854775807");
		REQUIRE(ToString(unsigned long long(9223372036854775808Ui64)) == U"9223372036854775808");
		REQUIRE(ToString(unsigned long long(18446744073709551614Ui64)) == U"18446744073709551614");
		REQUIRE(ToString(unsigned long long(18446744073709551615Ui64)) == U"18446744073709551615");

		REQUIRE(ToString(unsigned long long(123i64)) == U"123");
		REQUIRE(ToString(unsigned long long(123456i64)) == U"123456");
		REQUIRE(ToString(unsigned long long(123456789i64)) == U"123456789");
		REQUIRE(ToString(unsigned long long(123456789012i64)) == U"123456789012");
	}

	SECTION("ToString(char, radix, LetterCase)")
	{
		REQUIRE(ToString(char(-128), Arg::radix = 10) == U"-128");
		REQUIRE(ToString(char(-127), Arg::radix = 10) == U"-127");
		REQUIRE(ToString(char(-1), Arg::radix = 10) == U"-1");
		REQUIRE(ToString(char(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(char(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(char(126), Arg::radix = 10) == U"126");
		REQUIRE(ToString(char(127), Arg::radix = 10) == U"127");

		REQUIRE(ToString(char(-128), Arg::radix = 2) == U"10000000");
		REQUIRE(ToString(char(-127), Arg::radix = 2) == U"10000001");
		REQUIRE(ToString(char(-1), Arg::radix = 2) == U"11111111");
		REQUIRE(ToString(char(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(char(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(char(126), Arg::radix = 2) == U"1111110");
		REQUIRE(ToString(char(127), Arg::radix = 2) == U"1111111");

		REQUIRE(ToString(char(-128), Arg::radix = 8) == U"200");
		REQUIRE(ToString(char(-127), Arg::radix = 8) == U"201");
		REQUIRE(ToString(char(-1), Arg::radix = 8) == U"377");
		REQUIRE(ToString(char(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(char(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(char(126), Arg::radix = 8) == U"176");
		REQUIRE(ToString(char(127), Arg::radix = 8) == U"177");

		REQUIRE(ToString(char(-128), Arg::radix = 16) == U"80");
		REQUIRE(ToString(char(-127), Arg::radix = 16) == U"81");
		REQUIRE(ToString(char(-1), Arg::radix = 16) == U"FF");
		REQUIRE(ToString(char(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(char(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(char(126), Arg::radix = 16) == U"7E");
		REQUIRE(ToString(char(127), Arg::radix = 16) == U"7F");

		REQUIRE(ToString(char(-128), Arg::radix = 16, LetterCase::Lower) == U"80");
		REQUIRE(ToString(char(-127), Arg::radix = 16, LetterCase::Lower) == U"81");
		REQUIRE(ToString(char(-1), Arg::radix = 16, LetterCase::Lower) == U"ff");
		REQUIRE(ToString(char(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(char(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(char(126), Arg::radix = 16, LetterCase::Lower) == U"7e");
		REQUIRE(ToString(char(127), Arg::radix = 16, LetterCase::Lower) == U"7f");

		REQUIRE(ToString(char(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(char(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(char(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(char(123), Arg::radix = 36) == U"3F");
	}

	SECTION("ToString(int8, radix, LetterCase)")
	{
		REQUIRE(ToString(int8(-128), Arg::radix = 10) == U"-128");
		REQUIRE(ToString(int8(-127), Arg::radix = 10) == U"-127");
		REQUIRE(ToString(int8(-1), Arg::radix = 10) == U"-1");
		REQUIRE(ToString(int8(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(int8(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(int8(126), Arg::radix = 10) == U"126");
		REQUIRE(ToString(int8(127), Arg::radix = 10) == U"127");

		REQUIRE(ToString(int8(-128), Arg::radix = 2) == U"10000000");
		REQUIRE(ToString(int8(-127), Arg::radix = 2) == U"10000001");
		REQUIRE(ToString(int8(-1), Arg::radix = 2) == U"11111111");
		REQUIRE(ToString(int8(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(int8(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(int8(126), Arg::radix = 2) == U"1111110");
		REQUIRE(ToString(int8(127), Arg::radix = 2) == U"1111111");

		REQUIRE(ToString(int8(-128), Arg::radix = 8) == U"200");
		REQUIRE(ToString(int8(-127), Arg::radix = 8) == U"201");
		REQUIRE(ToString(int8(-1), Arg::radix = 8) == U"377");
		REQUIRE(ToString(int8(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(int8(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(int8(126), Arg::radix = 8) == U"176");
		REQUIRE(ToString(int8(127), Arg::radix = 8) == U"177");

		REQUIRE(ToString(int8(-128), Arg::radix = 16) == U"80");
		REQUIRE(ToString(int8(-127), Arg::radix = 16) == U"81");
		REQUIRE(ToString(int8(-1), Arg::radix = 16) == U"FF");
		REQUIRE(ToString(int8(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(int8(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(int8(126), Arg::radix = 16) == U"7E");
		REQUIRE(ToString(int8(127), Arg::radix = 16) == U"7F");

		REQUIRE(ToString(int8(-128), Arg::radix = 16, LetterCase::Lower) == U"80");
		REQUIRE(ToString(int8(-127), Arg::radix = 16, LetterCase::Lower) == U"81");
		REQUIRE(ToString(int8(-1), Arg::radix = 16, LetterCase::Lower) == U"ff");
		REQUIRE(ToString(int8(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(int8(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(int8(126), Arg::radix = 16, LetterCase::Lower) == U"7e");
		REQUIRE(ToString(int8(127), Arg::radix = 16, LetterCase::Lower) == U"7f");

		REQUIRE(ToString(int8(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(int8(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(int8(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(int8(123), Arg::radix = 36) == U"3F");
	}

	SECTION("ToString(uint8, radix, LetterCase)")
	{
		REQUIRE(ToString(uint8(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(uint8(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(uint8(126), Arg::radix = 10) == U"126");
		REQUIRE(ToString(uint8(127), Arg::radix = 10) == U"127");
		REQUIRE(ToString(uint8(128), Arg::radix = 10) == U"128");
		REQUIRE(ToString(uint8(254), Arg::radix = 10) == U"254");
		REQUIRE(ToString(uint8(255), Arg::radix = 10) == U"255");

		REQUIRE(ToString(uint8(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(uint8(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(uint8(126), Arg::radix = 2) == U"1111110");
		REQUIRE(ToString(uint8(127), Arg::radix = 2) == U"1111111");
		REQUIRE(ToString(uint8(128), Arg::radix = 2) == U"10000000");
		REQUIRE(ToString(uint8(254), Arg::radix = 2) == U"11111110");
		REQUIRE(ToString(uint8(255), Arg::radix = 2) == U"11111111");

		REQUIRE(ToString(uint8(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(uint8(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(uint8(126), Arg::radix = 8) == U"176");
		REQUIRE(ToString(uint8(127), Arg::radix = 8) == U"177");
		REQUIRE(ToString(uint8(128), Arg::radix = 8) == U"200");
		REQUIRE(ToString(uint8(254), Arg::radix = 8) == U"376");
		REQUIRE(ToString(uint8(255), Arg::radix = 8) == U"377");

		REQUIRE(ToString(uint8(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(uint8(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(uint8(126), Arg::radix = 16) == U"7E");
		REQUIRE(ToString(uint8(127), Arg::radix = 16) == U"7F");
		REQUIRE(ToString(uint8(128), Arg::radix = 16) == U"80");
		REQUIRE(ToString(uint8(254), Arg::radix = 16) == U"FE");
		REQUIRE(ToString(uint8(255), Arg::radix = 16) == U"FF");

		REQUIRE(ToString(uint8(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(uint8(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(uint8(126), Arg::radix = 16, LetterCase::Lower) == U"7e");
		REQUIRE(ToString(uint8(127), Arg::radix = 16, LetterCase::Lower) == U"7f");
		REQUIRE(ToString(uint8(128), Arg::radix = 16, LetterCase::Lower) == U"80");
		REQUIRE(ToString(uint8(254), Arg::radix = 16, LetterCase::Lower) == U"fe");
		REQUIRE(ToString(uint8(255), Arg::radix = 16, LetterCase::Lower) == U"ff");

		REQUIRE(ToString(uint8(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(uint8(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(uint8(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(uint8(123), Arg::radix = 36) == U"3F");
	}

	SECTION("ToString(int16, radix, LetterCase)")
	{
		REQUIRE(ToString(int16(-32768), Arg::radix = 10) == U"-32768");
		REQUIRE(ToString(int16(-32767), Arg::radix = 10) == U"-32767");
		REQUIRE(ToString(int16(-1), Arg::radix = 10) == U"-1");
		REQUIRE(ToString(int16(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(int16(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(int16(32766), Arg::radix = 10) == U"32766");
		REQUIRE(ToString(int16(32767), Arg::radix = 10) == U"32767");

		REQUIRE(ToString(int16(-32768), Arg::radix = 2) == U"1000000000000000");
		REQUIRE(ToString(int16(-32767), Arg::radix = 2) == U"1000000000000001");
		REQUIRE(ToString(int16(-1), Arg::radix = 2) == U"1111111111111111");
		REQUIRE(ToString(int16(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(int16(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(int16(32766), Arg::radix = 2) == U"111111111111110");
		REQUIRE(ToString(int16(32767), Arg::radix = 2) == U"111111111111111");

		REQUIRE(ToString(int16(-32768), Arg::radix = 8) == U"100000");
		REQUIRE(ToString(int16(-32767), Arg::radix = 8) == U"100001");
		REQUIRE(ToString(int16(-1), Arg::radix = 8) == U"177777");
		REQUIRE(ToString(int16(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(int16(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(int16(32766), Arg::radix = 8) == U"77776");
		REQUIRE(ToString(int16(32767), Arg::radix = 8) == U"77777");

		REQUIRE(ToString(int16(-32768), Arg::radix = 16) == U"8000");
		REQUIRE(ToString(int16(-32767), Arg::radix = 16) == U"8001");
		REQUIRE(ToString(int16(-1), Arg::radix = 16) == U"FFFF");
		REQUIRE(ToString(int16(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(int16(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(int16(32766), Arg::radix = 16) == U"7FFE");
		REQUIRE(ToString(int16(32767), Arg::radix = 16) == U"7FFF");

		REQUIRE(ToString(int16(-32768), Arg::radix = 16, LetterCase::Lower) == U"8000");
		REQUIRE(ToString(int16(-32767), Arg::radix = 16, LetterCase::Lower) == U"8001");
		REQUIRE(ToString(int16(-1), Arg::radix = 16, LetterCase::Lower) == U"ffff");
		REQUIRE(ToString(int16(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(int16(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(int16(32766), Arg::radix = 16, LetterCase::Lower) == U"7ffe");
		REQUIRE(ToString(int16(32767), Arg::radix = 16, LetterCase::Lower) == U"7fff");

		REQUIRE(ToString(int16(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(int16(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(int16(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(int16(123), Arg::radix = 36) == U"3F");
	}

	SECTION("ToString(uint16, radix, LetterCase)")
	{
		REQUIRE(ToString(uint16(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(uint16(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(uint16(32766), Arg::radix = 10) == U"32766");
		REQUIRE(ToString(uint16(32767), Arg::radix = 10) == U"32767");
		REQUIRE(ToString(uint16(32768), Arg::radix = 10) == U"32768");
		REQUIRE(ToString(uint16(65534), Arg::radix = 10) == U"65534");
		REQUIRE(ToString(uint16(65535), Arg::radix = 10) == U"65535");

		REQUIRE(ToString(uint16(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(uint16(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(uint16(32766), Arg::radix = 2) == U"111111111111110");
		REQUIRE(ToString(uint16(32767), Arg::radix = 2) == U"111111111111111");
		REQUIRE(ToString(uint16(32768), Arg::radix = 2) == U"1000000000000000");
		REQUIRE(ToString(uint16(65534), Arg::radix = 2) == U"1111111111111110");
		REQUIRE(ToString(uint16(65535), Arg::radix = 2) == U"1111111111111111");

		REQUIRE(ToString(uint16(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(uint16(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(uint16(32766), Arg::radix = 8) == U"77776");
		REQUIRE(ToString(uint16(32767), Arg::radix = 8) == U"77777");
		REQUIRE(ToString(uint16(32768), Arg::radix = 8) == U"100000");
		REQUIRE(ToString(uint16(65534), Arg::radix = 8) == U"177776");
		REQUIRE(ToString(uint16(65535), Arg::radix = 8) == U"177777");

		REQUIRE(ToString(uint16(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(uint16(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(uint16(32766), Arg::radix = 16) == U"7FFE");
		REQUIRE(ToString(uint16(32767), Arg::radix = 16) == U"7FFF");
		REQUIRE(ToString(uint16(32768), Arg::radix = 16) == U"8000");
		REQUIRE(ToString(uint16(65534), Arg::radix = 16) == U"FFFE");
		REQUIRE(ToString(uint16(65535), Arg::radix = 16) == U"FFFF");

		REQUIRE(ToString(uint16(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(uint16(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(uint16(32766), Arg::radix = 16, LetterCase::Lower) == U"7ffe");
		REQUIRE(ToString(uint16(32767), Arg::radix = 16, LetterCase::Lower) == U"7fff");
		REQUIRE(ToString(uint16(32768), Arg::radix = 16, LetterCase::Lower) == U"8000");
		REQUIRE(ToString(uint16(65534), Arg::radix = 16, LetterCase::Lower) == U"fffe");
		REQUIRE(ToString(uint16(65535), Arg::radix = 16, LetterCase::Lower) == U"ffff");

		REQUIRE(ToString(uint16(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(uint16(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(uint16(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(uint16(123), Arg::radix = 36) == U"3F");
	}

	SECTION("ToString(int32, radix, LetterCase)")
	{
		REQUIRE(ToString(int32(-2147483647 - 1), Arg::radix = 10) == U"-2147483648");
		REQUIRE(ToString(int32(-2147483647), Arg::radix = 10) == U"-2147483647");
		REQUIRE(ToString(int32(-1), Arg::radix = 10) == U"-1");
		REQUIRE(ToString(int32(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(int32(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(int32(2147483646), Arg::radix = 10) == U"2147483646");
		REQUIRE(ToString(int32(2147483647), Arg::radix = 10) == U"2147483647");

		REQUIRE(ToString(int32(-2147483647 - 1), Arg::radix = 2) == U"10000000000000000000000000000000");
		REQUIRE(ToString(int32(-2147483647), Arg::radix = 2) == U"10000000000000000000000000000001");
		REQUIRE(ToString(int32(-1), Arg::radix = 2) == U"11111111111111111111111111111111");
		REQUIRE(ToString(int32(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(int32(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(int32(2147483646), Arg::radix = 2) == U"1111111111111111111111111111110");
		REQUIRE(ToString(int32(2147483647), Arg::radix = 2) == U"1111111111111111111111111111111");

		REQUIRE(ToString(int32(-2147483647 - 1), Arg::radix = 8) == U"20000000000");
		REQUIRE(ToString(int32(-2147483647), Arg::radix = 8) == U"20000000001");
		REQUIRE(ToString(int32(-1), Arg::radix = 8) == U"37777777777");
		REQUIRE(ToString(int32(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(int32(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(int32(2147483646), Arg::radix = 8) == U"17777777776");
		REQUIRE(ToString(int32(2147483647), Arg::radix = 8) == U"17777777777");

		REQUIRE(ToString(int32(-2147483647 - 1), Arg::radix = 16) == U"80000000");
		REQUIRE(ToString(int32(-2147483647), Arg::radix = 16) == U"80000001");
		REQUIRE(ToString(int32(-1), Arg::radix = 16) == U"FFFFFFFF");
		REQUIRE(ToString(int32(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(int32(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(int32(2147483646), Arg::radix = 16) == U"7FFFFFFE");
		REQUIRE(ToString(int32(2147483647), Arg::radix = 16) == U"7FFFFFFF");

		REQUIRE(ToString(int32(-2147483647 - 1), Arg::radix = 16, LetterCase::Lower) == U"80000000");
		REQUIRE(ToString(int32(-2147483647), Arg::radix = 16, LetterCase::Lower) == U"80000001");
		REQUIRE(ToString(int32(-1), Arg::radix = 16, LetterCase::Lower) == U"ffffffff");
		REQUIRE(ToString(int32(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(int32(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(int32(2147483646), Arg::radix = 16, LetterCase::Lower) == U"7ffffffe");
		REQUIRE(ToString(int32(2147483647), Arg::radix = 16, LetterCase::Lower) == U"7fffffff");

		REQUIRE(ToString(int32(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(int32(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(int32(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(int32(123), Arg::radix = 36) == U"3F");

		REQUIRE(ToString(int32(123456789), Arg::radix = 2) == U"111010110111100110100010101");
		REQUIRE(ToString(int32(123456789), Arg::radix = 8) == U"726746425");
		REQUIRE(ToString(int32(123456789), Arg::radix = 16) == U"75BCD15");
		REQUIRE(ToString(int32(123456789), Arg::radix = 36) == U"21I3V9");
	}

	SECTION("ToString(uint32, radix, LetterCase)")
	{
		REQUIRE(ToString(uint32(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(uint32(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(uint32(2147483646), Arg::radix = 10) == U"2147483646");
		REQUIRE(ToString(uint32(2147483647), Arg::radix = 10) == U"2147483647");
		REQUIRE(ToString(uint32(2147483648), Arg::radix = 10) == U"2147483648");
		REQUIRE(ToString(uint32(4294967294), Arg::radix = 10) == U"4294967294");
		REQUIRE(ToString(uint32(4294967295), Arg::radix = 10) == U"4294967295");

		REQUIRE(ToString(uint32(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(uint32(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(uint32(2147483646), Arg::radix = 2) == U"1111111111111111111111111111110");
		REQUIRE(ToString(uint32(2147483647), Arg::radix = 2) == U"1111111111111111111111111111111");
		REQUIRE(ToString(uint32(2147483648), Arg::radix = 2) == U"10000000000000000000000000000000");
		REQUIRE(ToString(uint32(4294967294), Arg::radix = 2) == U"11111111111111111111111111111110");
		REQUIRE(ToString(uint32(4294967295), Arg::radix = 2) == U"11111111111111111111111111111111");

		REQUIRE(ToString(uint32(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(uint32(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(uint32(2147483646), Arg::radix = 8) == U"17777777776");
		REQUIRE(ToString(uint32(2147483647), Arg::radix = 8) == U"17777777777");
		REQUIRE(ToString(uint32(2147483648), Arg::radix = 8) == U"20000000000");
		REQUIRE(ToString(uint32(4294967294), Arg::radix = 8) == U"37777777776");
		REQUIRE(ToString(uint32(4294967295), Arg::radix = 8) == U"37777777777");

		REQUIRE(ToString(uint32(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(uint32(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(uint32(2147483646), Arg::radix = 16) == U"7FFFFFFE");
		REQUIRE(ToString(uint32(2147483647), Arg::radix = 16) == U"7FFFFFFF");
		REQUIRE(ToString(uint32(2147483648), Arg::radix = 16) == U"80000000");
		REQUIRE(ToString(uint32(4294967294), Arg::radix = 16) == U"FFFFFFFE");
		REQUIRE(ToString(uint32(4294967295), Arg::radix = 16) == U"FFFFFFFF");

		REQUIRE(ToString(uint32(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(uint32(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(uint32(2147483646), Arg::radix = 16, LetterCase::Lower) == U"7ffffffe");
		REQUIRE(ToString(uint32(2147483647), Arg::radix = 16, LetterCase::Lower) == U"7fffffff");
		REQUIRE(ToString(uint32(2147483648), Arg::radix = 16, LetterCase::Lower) == U"80000000");
		REQUIRE(ToString(uint32(4294967294), Arg::radix = 16, LetterCase::Lower) == U"fffffffe");
		REQUIRE(ToString(uint32(4294967295), Arg::radix = 16, LetterCase::Lower) == U"ffffffff");

		REQUIRE(ToString(uint32(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(uint32(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(uint32(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(uint32(123), Arg::radix = 36) == U"3F");

		REQUIRE(ToString(uint32(123456789), Arg::radix = 2) == U"111010110111100110100010101");
		REQUIRE(ToString(uint32(123456789), Arg::radix = 8) == U"726746425");
		REQUIRE(ToString(uint32(123456789), Arg::radix = 16) == U"75BCD15");
		REQUIRE(ToString(uint32(123456789), Arg::radix = 36) == U"21I3V9");
	}

	SECTION("ToString(long, radix, LetterCase)")
	{
		REQUIRE(ToString(long(-2147483647 - 1), Arg::radix = 10) == U"-2147483648");
		REQUIRE(ToString(long(-2147483647), Arg::radix = 10) == U"-2147483647");
		REQUIRE(ToString(long(-1), Arg::radix = 10) == U"-1");
		REQUIRE(ToString(long(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(long(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(long(2147483646), Arg::radix = 10) == U"2147483646");
		REQUIRE(ToString(long(2147483647), Arg::radix = 10) == U"2147483647");

		REQUIRE(ToString(long(-2147483647 - 1), Arg::radix = 2) == U"10000000000000000000000000000000");
		REQUIRE(ToString(long(-2147483647), Arg::radix = 2) == U"10000000000000000000000000000001");
		REQUIRE(ToString(long(-1), Arg::radix = 2) == U"11111111111111111111111111111111");
		REQUIRE(ToString(long(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(long(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(long(2147483646), Arg::radix = 2) == U"1111111111111111111111111111110");
		REQUIRE(ToString(long(2147483647), Arg::radix = 2) == U"1111111111111111111111111111111");

		REQUIRE(ToString(long(-2147483647 - 1), Arg::radix = 8) == U"20000000000");
		REQUIRE(ToString(long(-2147483647), Arg::radix = 8) == U"20000000001");
		REQUIRE(ToString(long(-1), Arg::radix = 8) == U"37777777777");
		REQUIRE(ToString(long(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(long(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(long(2147483646), Arg::radix = 8) == U"17777777776");
		REQUIRE(ToString(long(2147483647), Arg::radix = 8) == U"17777777777");

		REQUIRE(ToString(long(-2147483647 - 1), Arg::radix = 16) == U"80000000");
		REQUIRE(ToString(long(-2147483647), Arg::radix = 16) == U"80000001");
		REQUIRE(ToString(long(-1), Arg::radix = 16) == U"FFFFFFFF");
		REQUIRE(ToString(long(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(long(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(long(2147483646), Arg::radix = 16) == U"7FFFFFFE");
		REQUIRE(ToString(long(2147483647), Arg::radix = 16) == U"7FFFFFFF");

		REQUIRE(ToString(long(-2147483647 - 1), Arg::radix = 16, LetterCase::Lower) == U"80000000");
		REQUIRE(ToString(long(-2147483647), Arg::radix = 16, LetterCase::Lower) == U"80000001");
		REQUIRE(ToString(long(-1), Arg::radix = 16, LetterCase::Lower) == U"ffffffff");
		REQUIRE(ToString(long(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(long(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(long(2147483646), Arg::radix = 16, LetterCase::Lower) == U"7ffffffe");
		REQUIRE(ToString(long(2147483647), Arg::radix = 16, LetterCase::Lower) == U"7fffffff");

		REQUIRE(ToString(long(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(long(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(long(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(long(123), Arg::radix = 36) == U"3F");

		REQUIRE(ToString(long(123456789), Arg::radix = 2) == U"111010110111100110100010101");
		REQUIRE(ToString(long(123456789), Arg::radix = 8) == U"726746425");
		REQUIRE(ToString(long(123456789), Arg::radix = 16) == U"75BCD15");
		REQUIRE(ToString(long(123456789), Arg::radix = 36) == U"21I3V9");
	}

	SECTION("ToString(unsigned long, radix, LetterCase)")
	{
		REQUIRE(ToString(unsigned long(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(unsigned long(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(unsigned long(2147483646), Arg::radix = 10) == U"2147483646");
		REQUIRE(ToString(unsigned long(2147483647), Arg::radix = 10) == U"2147483647");
		REQUIRE(ToString(unsigned long(2147483648), Arg::radix = 10) == U"2147483648");
		REQUIRE(ToString(unsigned long(4294967294), Arg::radix = 10) == U"4294967294");
		REQUIRE(ToString(unsigned long(4294967295), Arg::radix = 10) == U"4294967295");

		REQUIRE(ToString(unsigned long(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(unsigned long(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(unsigned long(2147483646), Arg::radix = 2) == U"1111111111111111111111111111110");
		REQUIRE(ToString(unsigned long(2147483647), Arg::radix = 2) == U"1111111111111111111111111111111");
		REQUIRE(ToString(unsigned long(2147483648), Arg::radix = 2) == U"10000000000000000000000000000000");
		REQUIRE(ToString(unsigned long(4294967294), Arg::radix = 2) == U"11111111111111111111111111111110");
		REQUIRE(ToString(unsigned long(4294967295), Arg::radix = 2) == U"11111111111111111111111111111111");

		REQUIRE(ToString(unsigned long(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(unsigned long(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(unsigned long(2147483646), Arg::radix = 8) == U"17777777776");
		REQUIRE(ToString(unsigned long(2147483647), Arg::radix = 8) == U"17777777777");
		REQUIRE(ToString(unsigned long(2147483648), Arg::radix = 8) == U"20000000000");
		REQUIRE(ToString(unsigned long(4294967294), Arg::radix = 8) == U"37777777776");
		REQUIRE(ToString(unsigned long(4294967295), Arg::radix = 8) == U"37777777777");

		REQUIRE(ToString(unsigned long(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(unsigned long(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(unsigned long(2147483646), Arg::radix = 16) == U"7FFFFFFE");
		REQUIRE(ToString(unsigned long(2147483647), Arg::radix = 16) == U"7FFFFFFF");
		REQUIRE(ToString(unsigned long(2147483648), Arg::radix = 16) == U"80000000");
		REQUIRE(ToString(unsigned long(4294967294), Arg::radix = 16) == U"FFFFFFFE");
		REQUIRE(ToString(unsigned long(4294967295), Arg::radix = 16) == U"FFFFFFFF");

		REQUIRE(ToString(unsigned long(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(unsigned long(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(unsigned long(2147483646), Arg::radix = 16, LetterCase::Lower) == U"7ffffffe");
		REQUIRE(ToString(unsigned long(2147483647), Arg::radix = 16, LetterCase::Lower) == U"7fffffff");
		REQUIRE(ToString(unsigned long(2147483648), Arg::radix = 16, LetterCase::Lower) == U"80000000");
		REQUIRE(ToString(unsigned long(4294967294), Arg::radix = 16, LetterCase::Lower) == U"fffffffe");
		REQUIRE(ToString(unsigned long(4294967295), Arg::radix = 16, LetterCase::Lower) == U"ffffffff");

		REQUIRE(ToString(unsigned long(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(unsigned long(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(unsigned long(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(unsigned long(123), Arg::radix = 36) == U"3F");

		REQUIRE(ToString(unsigned long(123456789), Arg::radix = 2) == U"111010110111100110100010101");
		REQUIRE(ToString(unsigned long(123456789), Arg::radix = 8) == U"726746425");
		REQUIRE(ToString(unsigned long(123456789), Arg::radix = 16) == U"75BCD15");
		REQUIRE(ToString(unsigned long(123456789), Arg::radix = 36) == U"21I3V9");
	}

	SECTION("ToString(long long, radix, LetterCase)")
	{
		REQUIRE(ToString(long long(-9223372036854775807i64 - 1), Arg::radix = 10) == U"-9223372036854775808");
		REQUIRE(ToString(long long(-9223372036854775807i64), Arg::radix = 10) == U"-9223372036854775807");
		REQUIRE(ToString(long long(-1), Arg::radix = 10) == U"-1");
		REQUIRE(ToString(long long(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(long long(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(long long(9223372036854775806i64), Arg::radix = 10) == U"9223372036854775806");
		REQUIRE(ToString(long long(9223372036854775807i64), Arg::radix = 10) == U"9223372036854775807");
		
		REQUIRE(ToString(long long(-9223372036854775807i64 - 1), Arg::radix = 2) == U"1000000000000000000000000000000000000000000000000000000000000000");
		REQUIRE(ToString(long long(-9223372036854775807i64), Arg::radix = 2) == U"1000000000000000000000000000000000000000000000000000000000000001");
		REQUIRE(ToString(long long(-1), Arg::radix = 2) == U"1111111111111111111111111111111111111111111111111111111111111111");
		REQUIRE(ToString(long long(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(long long(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(long long(9223372036854775806i64), Arg::radix = 2) == U"111111111111111111111111111111111111111111111111111111111111110");
		REQUIRE(ToString(long long(9223372036854775807i64), Arg::radix = 2) == U"111111111111111111111111111111111111111111111111111111111111111");

		REQUIRE(ToString(long long(-9223372036854775807i64 - 1), Arg::radix = 8) == U"1000000000000000000000");
		REQUIRE(ToString(long long(-9223372036854775807i64), Arg::radix = 8) == U"1000000000000000000001");
		REQUIRE(ToString(long long(-1), Arg::radix = 8) == U"1777777777777777777777");
		REQUIRE(ToString(long long(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(long long(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(long long(9223372036854775806i64), Arg::radix = 8) == U"777777777777777777776");
		REQUIRE(ToString(long long(9223372036854775807i64), Arg::radix = 8) == U"777777777777777777777");

		REQUIRE(ToString(long long(-9223372036854775807i64 - 1), Arg::radix = 16) == U"8000000000000000");
		REQUIRE(ToString(long long(-9223372036854775807i64), Arg::radix = 16) == U"8000000000000001");
		REQUIRE(ToString(long long(-1), Arg::radix = 16) == U"FFFFFFFFFFFFFFFF");
		REQUIRE(ToString(long long(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(long long(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(long long(9223372036854775806i64), Arg::radix = 16) == U"7FFFFFFFFFFFFFFE");
		REQUIRE(ToString(long long(9223372036854775807i64), Arg::radix = 16) == U"7FFFFFFFFFFFFFFF");

		REQUIRE(ToString(long long(-9223372036854775807i64 - 1), Arg::radix = 16, LetterCase::Lower) == U"8000000000000000");
		REQUIRE(ToString(long long(-9223372036854775807i64), Arg::radix = 16, LetterCase::Lower) == U"8000000000000001");
		REQUIRE(ToString(long long(-1), Arg::radix = 16, LetterCase::Lower) == U"ffffffffffffffff");
		REQUIRE(ToString(long long(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(long long(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(long long(9223372036854775806i64), Arg::radix = 16, LetterCase::Lower) == U"7ffffffffffffffe");
		REQUIRE(ToString(long long(9223372036854775807i64), Arg::radix = 16, LetterCase::Lower) == U"7fffffffffffffff");

		REQUIRE(ToString(long long(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(long long(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(long long(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(long long(123), Arg::radix = 36) == U"3F");

		REQUIRE(ToString(long long(123456789), Arg::radix = 2) == U"111010110111100110100010101");
		REQUIRE(ToString(long long(123456789), Arg::radix = 8) == U"726746425");
		REQUIRE(ToString(long long(123456789), Arg::radix = 16) == U"75BCD15");
		REQUIRE(ToString(long long(123456789), Arg::radix = 36) == U"21I3V9");
	}

	SECTION("ToString(unsigned long long, radix, LetterCase)")
	{
		REQUIRE(ToString(unsigned long long(0), Arg::radix = 10) == U"0");
		REQUIRE(ToString(unsigned long long(1), Arg::radix = 10) == U"1");
		REQUIRE(ToString(unsigned long long(9223372036854775806i64), Arg::radix = 10) == U"9223372036854775806");
		REQUIRE(ToString(unsigned long long(9223372036854775807i64), Arg::radix = 10) == U"9223372036854775807");
		REQUIRE(ToString(unsigned long long(9223372036854775808i64), Arg::radix = 10) == U"9223372036854775808");
		REQUIRE(ToString(unsigned long long(18446744073709551614Ui64), Arg::radix = 10) == U"18446744073709551614");
		REQUIRE(ToString(unsigned long long(18446744073709551615Ui64), Arg::radix = 10) == U"18446744073709551615");

		REQUIRE(ToString(unsigned long long(0), Arg::radix = 2) == U"0");
		REQUIRE(ToString(unsigned long long(1), Arg::radix = 2) == U"1");
		REQUIRE(ToString(unsigned long long(9223372036854775806i64), Arg::radix = 2) == U"111111111111111111111111111111111111111111111111111111111111110");
		REQUIRE(ToString(unsigned long long(9223372036854775807i64), Arg::radix = 2) == U"111111111111111111111111111111111111111111111111111111111111111");
		REQUIRE(ToString(unsigned long long(9223372036854775808i64), Arg::radix = 2) == U"1000000000000000000000000000000000000000000000000000000000000000");
		REQUIRE(ToString(unsigned long long(18446744073709551614Ui64), Arg::radix = 2) == U"1111111111111111111111111111111111111111111111111111111111111110");
		REQUIRE(ToString(unsigned long long(18446744073709551615Ui64), Arg::radix = 2) == U"1111111111111111111111111111111111111111111111111111111111111111");

		REQUIRE(ToString(unsigned long long(0), Arg::radix = 8) == U"0");
		REQUIRE(ToString(unsigned long long(1), Arg::radix = 8) == U"1");
		REQUIRE(ToString(unsigned long long(9223372036854775806i64), Arg::radix = 8) == U"777777777777777777776");
		REQUIRE(ToString(unsigned long long(9223372036854775807i64), Arg::radix = 8) == U"777777777777777777777");
		REQUIRE(ToString(unsigned long long(9223372036854775808i64), Arg::radix = 8) == U"1000000000000000000000");
		REQUIRE(ToString(unsigned long long(18446744073709551614Ui64), Arg::radix = 8) == U"1777777777777777777776");
		REQUIRE(ToString(unsigned long long(18446744073709551615Ui64), Arg::radix = 8) == U"1777777777777777777777");

		REQUIRE(ToString(unsigned long long(0), Arg::radix = 16) == U"0");
		REQUIRE(ToString(unsigned long long(1), Arg::radix = 16) == U"1");
		REQUIRE(ToString(unsigned long long(9223372036854775806i64), Arg::radix = 16) == U"7FFFFFFFFFFFFFFE");
		REQUIRE(ToString(unsigned long long(9223372036854775807i64), Arg::radix = 16) == U"7FFFFFFFFFFFFFFF");
		REQUIRE(ToString(unsigned long long(9223372036854775808i64), Arg::radix = 16) == U"8000000000000000");
		REQUIRE(ToString(unsigned long long(18446744073709551614Ui64), Arg::radix = 16) == U"FFFFFFFFFFFFFFFE");
		REQUIRE(ToString(unsigned long long(18446744073709551615Ui64), Arg::radix = 16) == U"FFFFFFFFFFFFFFFF");

		REQUIRE(ToString(unsigned long long(0), Arg::radix = 16, LetterCase::Lower) == U"0");
		REQUIRE(ToString(unsigned long long(1), Arg::radix = 16, LetterCase::Lower) == U"1");
		REQUIRE(ToString(unsigned long long(9223372036854775806i64), Arg::radix = 16, LetterCase::Lower) == U"7ffffffffffffffe");
		REQUIRE(ToString(unsigned long long(9223372036854775807i64), Arg::radix = 16, LetterCase::Lower) == U"7fffffffffffffff");
		REQUIRE(ToString(unsigned long long(9223372036854775808i64), Arg::radix = 16, LetterCase::Lower) == U"8000000000000000");
		REQUIRE(ToString(unsigned long long(18446744073709551614Ui64), Arg::radix = 16, LetterCase::Lower) == U"fffffffffffffffe");
		REQUIRE(ToString(unsigned long long(18446744073709551615Ui64), Arg::radix = 16, LetterCase::Lower) == U"ffffffffffffffff");

		REQUIRE(ToString(unsigned long long(123), Arg::radix = 2) == U"1111011");
		REQUIRE(ToString(unsigned long long(123), Arg::radix = 8) == U"173");
		REQUIRE(ToString(unsigned long long(123), Arg::radix = 16) == U"7B");
		REQUIRE(ToString(unsigned long long(123), Arg::radix = 36) == U"3F");

		REQUIRE(ToString(unsigned long long(123456789), Arg::radix = 2) == U"111010110111100110100010101");
		REQUIRE(ToString(unsigned long long(123456789), Arg::radix = 8) == U"726746425");
		REQUIRE(ToString(unsigned long long(123456789), Arg::radix = 16) == U"75BCD15");
		REQUIRE(ToString(unsigned long long(123456789), Arg::radix = 36) == U"21I3V9");
	}

	// ToBinary

	// ToOctal

	// ToHex
}

# endif
