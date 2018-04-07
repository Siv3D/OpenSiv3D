
# include "Test.hpp"


# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

	# include <conio.h>  
	# include <Siv3D/Windows.hpp>

# endif

# define CATCH_CONFIG_RUNNER
# include "Catch/catch.hpp"

void Siv3D_RunTest()
{
	Console.open();

	Catch::Session().run();

# if defined(SIV3D_TARGET_WINDOWS)

	::_getch();

# endif
}

TEST_CASE("Platform", "[normal]")
{
	REQUIRE(Platform::PointerSize == sizeof(void*));
	REQUIRE(SIV3D_PLATFORM_PTR_SIZE == sizeof(void*));
}

TEST_CASE("Types", "[normal]")
{
	REQUIRE(sizeof(int8) == 1);
	REQUIRE(sizeof(uint8) == 1);
	REQUIRE(sizeof(int16) == 2);
	REQUIRE(sizeof(uint16) == 2);
	REQUIRE(sizeof(int32) == 4);
	REQUIRE(sizeof(uint32) == 4);
	REQUIRE(sizeof(int64) == 8);
	REQUIRE(sizeof(uint64) == 8);
	REQUIRE(sizeof(char8) == 1);
	REQUIRE(sizeof(char16) == 2);
	REQUIRE(sizeof(char32) == 4);
}

TEST_CASE("Meta", "[normal]")
{

}

TEST_CASE("Utility", "[normal]")
{

}

TEST_CASE("AlignedMalloc", "[normal]")
{
	struct alignas(16) Data16
	{
		float v[4];
	};

	struct alignas(32) Data32
	{
		float v[8];
	};

	struct alignas(64) Data64
	{
		float v[16];
	};

	SECTION("AlignedMalloc(0)")
	{
		{
			uint8* p = AlignedMalloc<uint8>(0);
			AlignedFree(p);
		}

		{
			uint16* p = AlignedMalloc<uint16>(0);
			AlignedFree(p);
		}

		{
			uint32* p = AlignedMalloc<uint32>(0);
			AlignedFree(p);
		}

		{
			uint64* p = AlignedMalloc<uint64>(0);
			AlignedFree(p);
		}

		{
			float* p = AlignedMalloc<float>(0);
			AlignedFree(p);
		}

		{
			double* p = AlignedMalloc<double>(0);
			AlignedFree(p);
		}

		{
			Data16* p = AlignedMalloc<Data16>(0);
			AlignedFree(p);
		}

		{
			Data32* p = AlignedMalloc<Data32>(0);
			AlignedFree(p);
		}

		{
			Data64* p = AlignedMalloc<Data64>(0);
			AlignedFree(p);
		}
	}

	SECTION("AlignedMalloc()")
	{
		{
			uint8* p = AlignedMalloc<uint8>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 1));
			AlignedFree(p);
		}

		{
			uint16* p = AlignedMalloc<uint16>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 2));
			AlignedFree(p);
		}

		{
			uint32* p = AlignedMalloc<uint32>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 4));
			AlignedFree(p);
		}

		{
			uint64* p = AlignedMalloc<uint64>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 8));
			AlignedFree(p);
		}

		{
			float* p = AlignedMalloc<float>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 4));
			AlignedFree(p);
		}

		{
			double* p = AlignedMalloc<double>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 8));
			AlignedFree(p);
		}

		{
			Data16* p = AlignedMalloc<Data16>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 16));
			AlignedFree(p);
		}

		{
			Data32* p = AlignedMalloc<Data32>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 32));
			AlignedFree(p);
		}

		{
			Data64* p = AlignedMalloc<Data64>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 64));
			AlignedFree(p);
		}
	}
}

TEST_CASE("Functors", "[normal]")
{
	using namespace Lambda;

	SECTION("Equal")
	{
		REQUIRE(Equal()(20, 20));
		REQUIRE(Equal(20)(20));
		REQUIRE(Equal(20, 20));
		REQUIRE(Equal(_, 20)(20));
		REQUIRE(Equal(20, _)(20));
		REQUIRE(Equal(_, _)(20, 20));

		REQUIRE_FALSE(Equal()(20, 21));
		REQUIRE_FALSE(Equal(20)(21));
		REQUIRE_FALSE(Equal(20, 21));
		REQUIRE_FALSE(Equal(_, 20)(21));
		REQUIRE_FALSE(Equal(20, _)(21));
		REQUIRE_FALSE(Equal(_, _)(20, 21));
	}
	
	SECTION("NotEqual")
	{
		REQUIRE_FALSE(NotEqual()(20, 20));
		REQUIRE_FALSE(NotEqual(20)(20));
		REQUIRE_FALSE(NotEqual(20, 20));
		REQUIRE_FALSE(NotEqual(_, 20)(20));
		REQUIRE_FALSE(NotEqual(20, _)(20));
		REQUIRE_FALSE(NotEqual(_, _)(20, 20));

		REQUIRE(NotEqual()(20, 21));
		REQUIRE(NotEqual(20)(21));
		REQUIRE(NotEqual(20, 21));
		REQUIRE(NotEqual(_, 20)(21));
		REQUIRE(NotEqual(20, _)(21));
		REQUIRE(NotEqual(_, _)(20, 21));
	}

	SECTION("LessThan")
	{
		REQUIRE_FALSE(LessThan()(20, 20));
		REQUIRE_FALSE(LessThan(20)(20));
		REQUIRE_FALSE(LessThan(20, 20));
		REQUIRE_FALSE(LessThan(_, 20)(20));
		REQUIRE_FALSE(LessThan(20, _)(20));
		REQUIRE_FALSE(LessThan(_, _)(20, 20));

		REQUIRE(LessThan()(20, 21));
		REQUIRE(LessThan(20)(19));
		REQUIRE(LessThan(20, 21));
		REQUIRE(LessThan(_, 20)(19));
		REQUIRE(LessThan(20, _)(21));
		REQUIRE(LessThan(_, _)(20, 21));
	}

	SECTION("LessThanEqual")
	{
		REQUIRE(LessThanEqual()(20, 20));
		REQUIRE(LessThanEqual(20)(20));
		REQUIRE(LessThanEqual(20, 20));
		REQUIRE(LessThanEqual(_, 20)(20));
		REQUIRE(LessThanEqual(20, _)(20));
		REQUIRE(LessThanEqual(_, _)(20, 20));

		REQUIRE(LessThanEqual()(20, 21));
		REQUIRE(LessThanEqual(20)(19));
		REQUIRE(LessThanEqual(20, 21));
		REQUIRE(LessThanEqual(_, 20)(19));
		REQUIRE(LessThanEqual(20, _)(21));
		REQUIRE(LessThanEqual(_, _)(20, 21));
	}

	SECTION("GreaterThan")
	{
		REQUIRE_FALSE(GreaterThan()(20, 20));
		REQUIRE_FALSE(GreaterThan(20)(20));
		REQUIRE_FALSE(GreaterThan(20, 20));
		REQUIRE_FALSE(GreaterThan(_, 20)(20));
		REQUIRE_FALSE(GreaterThan(20, _)(20));
		REQUIRE_FALSE(GreaterThan(_, _)(20, 20));

		REQUIRE(GreaterThan()(20, 19));
		REQUIRE(GreaterThan(20)(21));
		REQUIRE(GreaterThan(20, 19));
		REQUIRE(GreaterThan(_, 20)(21));
		REQUIRE(GreaterThan(20, _)(19));
		REQUIRE(GreaterThan(_, _)(20, 19));
	}

	SECTION("GreaterThanEqual")
	{
		REQUIRE(GreaterThanEqual()(20, 20));
		REQUIRE(GreaterThanEqual(20)(20));
		REQUIRE(GreaterThanEqual(20, 20));
		REQUIRE(GreaterThanEqual(_, 20)(20));
		REQUIRE(GreaterThanEqual(20, _)(20));
		REQUIRE(GreaterThanEqual(_, _)(20, 20));

		REQUIRE(GreaterThanEqual()(20, 19));
		REQUIRE(GreaterThanEqual(20)(21));
		REQUIRE(GreaterThanEqual(20, 19));
		REQUIRE(GreaterThanEqual(_, 20)(21));
		REQUIRE(GreaterThanEqual(20, _)(19));
		REQUIRE(GreaterThanEqual(_, _)(20, 19));
	}
}

TEST_CASE("Parse", "[normal]")
{
	SECTION("Parse<bool>()")
	{
		REQUIRE(Parse<bool>(U"true") == true);
		REQUIRE(Parse<bool>(U"True") == true);
		REQUIRE(Parse<bool>(U"TRUE") == true);

		REQUIRE(Parse<bool>(U"false") == false);
		REQUIRE(Parse<bool>(U"False") == false);
		REQUIRE(Parse<bool>(U"FALSE") == false);

		REQUIRE(Parse<bool>(U" true") == true);
		REQUIRE(Parse<bool>(U"True ") == true);
		REQUIRE(Parse<bool>(U" TRUE ") == true);

		REQUIRE(Parse<bool>(U" false") == false);
		REQUIRE(Parse<bool>(U"False ") == false);
		REQUIRE(Parse<bool>(U" FALSE ") == false);

		REQUIRE(Parse<bool>(U"") == false);
		REQUIRE(Parse<bool>(U"___") == false);
		REQUIRE(Parse<bool>(U"truetrue") == false);
		REQUIRE(Parse<bool>(U"True false") == false);
	}

	SECTION("Parse<int32>()")
	{
		REQUIRE(Parse<int32>(U"0") == 0);
		REQUIRE(Parse<int32>(U"-0") == 0);
		REQUIRE(Parse<int32>(U"123") == 123);
		REQUIRE(Parse<int32>(U"-123") == -123);
		REQUIRE(Parse<int32>(U"123456789") == 123456789);
		REQUIRE(Parse<int32>(U"-123456789") == -123456789);
		REQUIRE(Parse<int32>(U"123456789012345") == 0);
		REQUIRE(Parse<int32>(U"-123456789012345") == 0);

		REQUIRE(Parse<int32>(U"  123") == 123);
		REQUIRE(Parse<int32>(U"-123   ") == -123);
		REQUIRE(Parse<int32>(U"  123 ") == 123);
		REQUIRE(Parse<int32>(U"  +123 ") == 123);

		REQUIRE(Parse<int32>(U"0.0") == 0);
		REQUIRE(Parse<int32>(U"-0.0") == 0);
		REQUIRE(Parse<int32>(U"0.987") == 0);
		REQUIRE(Parse<int32>(U"-0.987") == 0);
		REQUIRE(Parse<int32>(U"123.4") == 0);
		REQUIRE(Parse<int32>(U"-123.4") == 0);

		REQUIRE(Parse<int32>(U"011") == 9);
		REQUIRE(Parse<int32>(U"0123456") == 42798);
		REQUIRE(Parse<int32>(U"0xFF") == 255);
		REQUIRE(Parse<int32>(U"0x12FA") == 4858);

		REQUIRE(Parse<int32>(U"123 123") == 0);
		REQUIRE(Parse<int32>(U"123_123") == 0);
	}

	SECTION("Parse<double>()")
	{
		REQUIRE(Parse<double>(U"0") == 0.0);
		REQUIRE(Parse<double>(U"-0") == 0.0);
		REQUIRE(Parse<double>(U"123") == 123.0);
		REQUIRE(Parse<double>(U"-123") == -123.0);
		REQUIRE(Parse<double>(U"123456789") == 123456789.0);
		REQUIRE(Parse<double>(U"-123456789") == -123456789.0);
		REQUIRE(Parse<double>(U"123456789012345") == 123456789012345.0);
		REQUIRE(Parse<double>(U"-123456789012345") == -123456789012345.0);

		REQUIRE(Parse<double>(U"  123") == 123.0);
		REQUIRE(Parse<double>(U"-123   ") == -123.0);
		REQUIRE(Parse<double>(U"  123 ") == 123.0);
		REQUIRE(Parse<double>(U"  +123 ") == 123.0);

		REQUIRE(Parse<double>(U"0.0") == 0.0);
		REQUIRE(Parse<double>(U"-0.0") == 0.0);
		REQUIRE(Parse<double>(U"0.987") == 0.987);
		REQUIRE(Parse<double>(U"-0.987") == -0.987);
		REQUIRE(Parse<double>(U"123.4") == 123.4);
		REQUIRE(Parse<double>(U"-123.4") == -123.4);
	}
}

TEST_CASE("Format", "[normal]")
{
	REQUIRE(Format((int8)123) == U"123");
	REQUIRE(Format((uint8)123) == U"123");
	REQUIRE(Format((int16)123) == U"123");
	REQUIRE(Format((uint16)123) == U"123");
	REQUIRE(Format((int32)123) == U"123");
	REQUIRE(Format((uint32)123) == U"123");
	REQUIRE(Format((int64)123) == U"123");
	REQUIRE(Format((uint64)123) == U"123");
	REQUIRE(Format((long)123) == U"123");
	REQUIRE(Format(123.0f) == U"123");
	REQUIRE(Format(123.0) == U"123");

	REQUIRE(Format(U'あ') == U"あ");
	REQUIRE(Format(Byte(0xFF)) == U"ff");

}

# endif
