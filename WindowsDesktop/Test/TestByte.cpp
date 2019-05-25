
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

TEST_CASE("Byte")
{
	constexpr Byte b0{ 0x00 };
	constexpr Byte b1{ 0x01 };
	constexpr Byte b2{ 0x02 };
	constexpr Byte b143{ 0x8F };
	constexpr Byte b255{ 0xFF };

	REQUIRE(AsUint8(b0) == 0);
	REQUIRE(AsUint8(b1) == 1);
	REQUIRE(AsUint8(b2) == 2);
	REQUIRE(AsUint8(b143) == 143);
	REQUIRE(AsUint8(b255) == 255);

	REQUIRE(AsUint8(b0 << 1) == 0);
	REQUIRE(AsUint8(b1 << 1) == 2);
	REQUIRE(AsUint8(b2 << 1) == 4);
	REQUIRE(AsUint8(b143 << 1) == 30);
	REQUIRE(AsUint8(b255 << 1) == 254);

	REQUIRE(AsUint8(b0 >> 1) == 0);
	REQUIRE(AsUint8(b1 >> 1) == 0);
	REQUIRE(AsUint8(b2 >> 1) == 1);
	REQUIRE(AsUint8(b143 >> 1) == 71);
	REQUIRE(AsUint8(b255 >> 1) == 127);

	REQUIRE(AsUint8(b0 | b143) == 143);
	REQUIRE(AsUint8(b1 | b143) == 143);
	REQUIRE(AsUint8(b2 | b143) == 143);
	REQUIRE(AsUint8(b143 | b143) == 143);
	REQUIRE(AsUint8(b255 | b143) == 255);

	REQUIRE(AsUint8(b0 & b143) == 0);
	REQUIRE(AsUint8(b1 & b143) == 1);
	REQUIRE(AsUint8(b2 & b143) == 2);
	REQUIRE(AsUint8(b143 & b143) == 143);
	REQUIRE(AsUint8(b255 & b143) == 143);

	REQUIRE(AsUint8(b0 ^ b143) == 143);
	REQUIRE(AsUint8(b1 ^ b143) == 142);
	REQUIRE(AsUint8(b2 ^ b143) == 141);
	REQUIRE(AsUint8(b143 ^ b143) == 0);
	REQUIRE(AsUint8(b255 ^ b143) == 112);

	REQUIRE(AsUint8(~b0) == 255);
	REQUIRE(AsUint8(~b1) == 254);
	REQUIRE(AsUint8(~b2) == 253);
	REQUIRE(AsUint8(~b143) == 112);
	REQUIRE(AsUint8(~b255) == 0);

	{
		Byte t0{ 0x00 };
		Byte t1{ 0x01 };
		Byte t2{ 0x02 };
		Byte t143{ 0x8F };
		Byte t255{ 0xFF };
		t0 <<= 2; REQUIRE(AsUint8(t0) == 0);
		t1 <<= 2; REQUIRE(AsUint8(t1) == 4);
		t2 <<= 2; REQUIRE(AsUint8(t2) == 8);
		t143 <<= 2; REQUIRE(AsUint8(t143) == 60);
		t255 <<= 2; REQUIRE(AsUint8(t255) == 252);
	}

	{
		Byte t0{ 0x00 };
		Byte t1{ 0x01 };
		Byte t2{ 0x02 };
		Byte t143{ 0x8F };
		Byte t255{ 0xFF };
		t0 >>= 2; REQUIRE(AsUint8(t0) == 0);
		t1 >>= 2; REQUIRE(AsUint8(t1) == 0);
		t2 >>= 2; REQUIRE(AsUint8(t2) == 0);
		t143 >>= 2; REQUIRE(AsUint8(t143) == 35);
		t255 >>= 2; REQUIRE(AsUint8(t255) == 63);
	}

	{
		Byte t0{ 0x00 };
		Byte t1{ 0x01 };
		Byte t2{ 0x02 };
		Byte t143{ 0x8F };
		Byte t255{ 0xFF };
		t0 |= b143; REQUIRE(AsUint8(t0) == 143);
		t1 |= b143; REQUIRE(AsUint8(t1) == 143);
		t2 |= b143; REQUIRE(AsUint8(t2) == 143);
		t143 |= b143; REQUIRE(AsUint8(t143) == 143);
		t255 |= b143; REQUIRE(AsUint8(t255) == 255);
	}

	{
		Byte t0{ 0x00 };
		Byte t1{ 0x01 };
		Byte t2{ 0x02 };
		Byte t143{ 0x8F };
		Byte t255{ 0xFF };
		t0 &= b143; REQUIRE(AsUint8(t0) == 0);
		t1 &= b143; REQUIRE(AsUint8(t1) == 1);
		t2 &= b143; REQUIRE(AsUint8(t2) == 2);
		t143 &= b143; REQUIRE(AsUint8(t143) == 143);
		t255 &= b143; REQUIRE(AsUint8(t255) == 143);
	}

	{
		Byte t0{ 0x00 };
		Byte t1{ 0x01 };
		Byte t2{ 0x02 };
		Byte t143{ 0x8F };
		Byte t255{ 0xFF };
		t0 ^= b143; REQUIRE(AsUint8(t0) == 143);
		t1 ^= b143; REQUIRE(AsUint8(t1) == 142);
		t2 ^= b143; REQUIRE(AsUint8(t2) == 141);
		t143 ^= b143; REQUIRE(AsUint8(t143) == 0);
		t255 ^= b143; REQUIRE(AsUint8(t255) == 112);
	}
}

TEST_CASE("Byte.Format")
{
	constexpr Byte b0{ 0x00 };
	constexpr Byte b1{ 0x01 };
	constexpr Byte b2{ 0x02 };
	constexpr Byte b143{ 0x8F };
	constexpr Byte b255{ 0xFF };

	{
		REQUIRE(Format(b0) == U"00");
		REQUIRE(Format(b1) == U"01");
		REQUIRE(Format(b2) == U"02");
		REQUIRE(Format(b143) == U"8F");
		REQUIRE(Format(b255) == U"FF");
	}

	{
		std::stringstream ss;
		ss << b0; REQUIRE(ss.str() == "00"); ss.str("");
		ss << b1; REQUIRE(ss.str() == "01"); ss.str("");
		ss << b2; REQUIRE(ss.str() == "02"); ss.str("");
		ss << b143; REQUIRE(ss.str() == "8F"); ss.str("");
		ss << b255; REQUIRE(ss.str() == "FF"); ss.str("");
	}

	{
		std::wstringstream ss;
		ss << b0; REQUIRE(ss.str() == L"00"); ss.str(L"");
		ss << b1; REQUIRE(ss.str() == L"01"); ss.str(L"");
		ss << b2; REQUIRE(ss.str() == L"02"); ss.str(L"");
		ss << b143; REQUIRE(ss.str() == L"8F"); ss.str(L"");
		ss << b255; REQUIRE(ss.str() == L"FF"); ss.str(L"");
	}

	{
		Byte b;
		std::stringstream{ "00" } >> b; REQUIRE(AsUint8(b) == 0);
		std::stringstream{ "01" } >> b; REQUIRE(AsUint8(b) == 1);
		std::stringstream{ "02" } >> b; REQUIRE(AsUint8(b) == 2);
		std::stringstream{ "8F" } >> b; REQUIRE(AsUint8(b) == 143);
		std::stringstream{ "FF" } >> b; REQUIRE(AsUint8(b) == 255);
		std::stringstream{ "8f" } >> b; REQUIRE(AsUint8(b) == 143);
		std::stringstream{ "ff" } >> b; REQUIRE(AsUint8(b) == 255);
	}

	{
		Byte b;
		std::wstringstream{ L"00" } >> b; REQUIRE(AsUint8(b) == 0);
		std::wstringstream{ L"01" } >> b; REQUIRE(AsUint8(b) == 1);
		std::wstringstream{ L"02" } >> b; REQUIRE(AsUint8(b) == 2);
		std::wstringstream{ L"8F" } >> b; REQUIRE(AsUint8(b) == 143);
		std::wstringstream{ L"FF" } >> b; REQUIRE(AsUint8(b) == 255);
		std::wstringstream{ L"8f" } >> b; REQUIRE(AsUint8(b) == 143);
		std::wstringstream{ L"ff" } >> b; REQUIRE(AsUint8(b) == 255);
	}
}

# endif
