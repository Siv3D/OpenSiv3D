
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

# endif
