
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# define SIV3D_CONCURRENT
# include <Siv3D.hpp>
# define CATCH_CONFIG_RUNNER
# include <ThirdParty/Catch2/catch.hpp>

void RunTest()
{
	Console.open();

	Catch::Session().run();
}

# pragma region Platform

TEST_CASE("Platform.Pointer")
{
# if !SIV3D_PLATFORM(WINDOWS) && !SIV3D_PLATFORM(MACOS) && !SIV3D_PLATFORM(LINUX)

	FAIL("Target platform is not defined");

# endif

	REQUIRE(Platform::PointerSize == sizeof(void*));
}

# pragma endregion

# pragma region Version

TEST_CASE("Version")
{
	REQUIRE(sizeof(Siv3DVersion) == sizeof(uint32));
	REQUIRE(200'000'000 <= Siv3DVersion);
	REQUIRE(Siv3DVersion < 300'000'000);
}

# pragma endregion

# pragma region Types

TEST_CASE("Types")
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

# pragma endregion

# pragma region ByteArrayViewAdapter

TEST_CASE("ByteArrayViewAdapter")
{
	{
		const int32 v = 123;
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const Vec2 v(11, 22);
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const int32 v[4] = { 11, 22, 33, 44 };
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const Point v[4] = { Point(1, 2), Point(2, 3), Point(3, 4), Point(4, 5) };
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const std::array<int32, 4> v = { 11, 22, 33, 44 };
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const String v = U"Siv3D";
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == v.size_bytes());
	}

	{
		const std::wstring_view v = L"Siv3D";
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == (sizeof(wchar_t) * v.size()));
	}

	{
		const StringView v = U"Siv3D";
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == v.size_bytes());
	}

	{
		const char32 v[] = U"Siv3D";
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(v));
		REQUIRE(a.size() == (sizeof(char32) * (std::char_traits<char32>::length(v) + 1)));
	}

	{
		const std::vector<Point> v = { Point(1, 2), Point(2, 3), Point(3, 4), Point(4, 5) };
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == (sizeof(Point) * v.size()));
	}

	{
		const Array<Point> v = { Point(1, 2), Point(2, 3), Point(3, 4), Point(4, 5) };
		ByteArrayViewAdapter a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == v.size_bytes());
	}

	{
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, int*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, const int*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, const char*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, const char16*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, const char32*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, FormatData> == false);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, StringView> == true);
		REQUIRE(std::is_constructible_v<ByteArrayViewAdapter, std::wstring_view> == true);
	}

	{
		REQUIRE(ByteArrayViewAdapter().size() == 0);
		REQUIRE(ByteArrayViewAdapter().size_bytes() == 0);
		REQUIRE(ByteArrayViewAdapter().isEmpty() == true);
		REQUIRE(ByteArrayViewAdapter().empty() == true);
		REQUIRE(static_cast<bool>(ByteArrayViewAdapter()) == false);

		const int32 v = 123;
		ByteArrayViewAdapter a(v);
		REQUIRE(a.size() == sizeof(v));
		REQUIRE(a.size_bytes() == sizeof(v));
		REQUIRE(a.isEmpty() == false);
		REQUIRE(a.empty() == false);
		REQUIRE(static_cast<bool>(a) == true);
	}
}

# pragma endregion

# pragma region ByteArrayView

TEST_CASE("ByteArrayView")
{
	{
		const int32 v = 123;
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const Vec2 v(11, 22);
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const int32 v[4] = { 11, 22, 33, 44 };
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const Point v[4] = { Point(1, 2), Point(2, 3), Point(3, 4), Point(4, 5) };
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const std::array<int32, 4> v = { 11, 22, 33, 44 };
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(std::addressof(v)));
		REQUIRE(a.size() == sizeof(v));
	}

	{
		const String v = U"Siv3D";
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == v.size_bytes());
	}

	{
		const std::wstring_view v = L"Siv3D";
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == (sizeof(wchar_t) * v.size()));
	}

	{
		const StringView v = U"Siv3D";
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == v.size_bytes());
	}

	{
		const char32 v[] = U"Siv3D";
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(v));
		REQUIRE(a.size() == (sizeof(char32) * (std::char_traits<char32>::length(v) + 1)));
	}

	{
		const std::vector<Point> v = { Point(1, 2), Point(2, 3), Point(3, 4), Point(4, 5) };
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == (sizeof(Point) * v.size()));
	}

	{
		const Array<Point> v = { Point(1, 2), Point(2, 3), Point(3, 4), Point(4, 5) };
		ByteArrayView a(v);
		REQUIRE(a.data() == static_cast<const void*>(v.data()));
		REQUIRE(a.size() == v.size_bytes());
	}

	{
		REQUIRE(std::is_constructible_v<ByteArrayView, int*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayView, const int*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayView, const char*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayView, const char16*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayView, const char32*> == false);
		REQUIRE(std::is_constructible_v<ByteArrayView, FormatData> == false);
		REQUIRE(std::is_constructible_v<ByteArrayView, StringView> == true);
		REQUIRE(std::is_constructible_v<ByteArrayView, std::wstring_view> == true);
	}

	{
		REQUIRE(ByteArrayView().size() == 0);
		REQUIRE(ByteArrayView().size_bytes() == 0);
		REQUIRE(ByteArrayView().isEmpty() == true);
		REQUIRE(ByteArrayView().empty() == true);
		REQUIRE(static_cast<bool>(ByteArrayView()) == false);

		const int32 v = 123;
		ByteArrayView a(v);
		REQUIRE(a.size() == sizeof(v));
		REQUIRE(a.size_bytes() == sizeof(v));
		REQUIRE(a.isEmpty() == false);
		REQUIRE(a.empty() == false);
		REQUIRE(static_cast<bool>(a) == true);
	}
}

# pragma endregion

# pragma region Threading

TEST_CASE("Threading")
{
	REQUIRE(0 < Threading::GetConcurrency());
}

# pragma endregion

# pragma region ConcurrentTask

TEST_CASE("ConcurrentTask")
{
	auto task = CreateConcurrentTask([](int32 n) { return n * n; }, 5);
	REQUIRE(task.get() == 25);
}

# pragma endregion

# pragma region AlignedMemory

TEST_CASE("AlignedMalloc")
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

	SECTION("AlignedMalloc(0) / AlignedFree")
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

	SECTION("AlignedMalloc / AlignedFree")
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

	SECTION("AlignedNew / AlignedDelete")
	{
		{
			uint8* p = AlignedNew<uint8>(static_cast<uint8>(255));
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, 1));
			REQUIRE(*p == 255);
			AlignedDelete(p);
		}

		{
			Vec4* p = AlignedNew<Vec4>(0.0, 1.0, 2.0 ,3.0);
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, alignof(Vec4)));
			REQUIRE(*p == Vec4(0.0, 1.0, 2.0, 3.0));
			AlignedDelete(p);
		}

		{
			Data64* p = AlignedNew<Data64>();
			REQUIRE(p != nullptr);
			REQUIRE(IsAligned(p, alignof(Data64)));
			AlignedDelete(p);
		}
	}

	SECTION("IsAligned")
	{
		const int32 t = 0;
		const int32* p = &t;
		REQUIRE(IsAligned(p, 4));

		const void* p8 = reinterpret_cast<const void*>(1024 + 8);
		REQUIRE(IsAligned(p8, 8));

		const void* p16 = reinterpret_cast<const void*>(1024 + 16);
		REQUIRE(IsAligned(p16, 16));
	}

	SECTION("IsOverAligned")
	{
		REQUIRE(IsOverAligned<uint8>() == false);
		REQUIRE(IsOverAligned<Byte>() == false);
		REQUIRE(IsOverAligned<int32>() == false);
		REQUIRE(IsOverAligned<float>() == false);
		REQUIRE(IsOverAligned<double>() == false);
		REQUIRE(IsOverAligned<Point>() == false);
		REQUIRE(IsOverAligned<Vec2>() == false);
		REQUIRE(IsOverAligned<String>() == false);
		REQUIRE(IsOverAligned<Data32>() == true);
		REQUIRE(IsOverAligned<Data64>() == true);
	}

	SECTION("MakeUnique")
	{
		{
			auto p = MakeUnique<uint8>(static_cast<uint8>(255));
			REQUIRE(p.get() != nullptr);
			REQUIRE(IsAligned(p.get(), alignof(uint8)));
			REQUIRE(*p == 255);
		}

		{
			auto p = MakeUnique<Vec4>(0.0, 1.0, 2.0, 3.0);
			REQUIRE(p.get() != nullptr);
			REQUIRE(IsAligned(p.get(), alignof(Vec4)));
			REQUIRE(*p == Vec4(0.0, 1.0, 2.0, 3.0));
		}

		{
			auto p = MakeUnique<Data64>();
			REQUIRE(p.get() != nullptr);
			REQUIRE(IsAligned(p.get(), alignof(Data64)));
		}
	}

	SECTION("MakeShared")
	{
		{
			auto p = MakeShared<uint8>(static_cast<uint8>(255));
			REQUIRE(p.get() != nullptr);
			REQUIRE(IsAligned(p.get(), alignof(uint8)));
			REQUIRE(*p == 255);
		}

		{
			auto p = MakeShared<Vec4>(0.0, 1.0, 2.0, 3.0);
			REQUIRE(p.get() != nullptr);
			REQUIRE(IsAligned(p.get(), alignof(Vec4)));
			REQUIRE(*p == Vec4(0.0, 1.0, 2.0, 3.0));
		}

		{
			auto p = MakeShared<Data64>();
			REQUIRE(p.get() != nullptr);
			REQUIRE(IsAligned(p.get(), alignof(Data64)));
		}
	}
}

# pragma endregion

# pragma region AlignedAllocator

TEST_CASE("AlignedAllocator")
{
	{
		AlignedAllocator<float, 16> alc;
		float* p = alc.allocate(4);
		REQUIRE(p != nullptr);
		REQUIRE(IsAligned(p, 16));
		alc.deallocate(p, 4);
	}

	{
		REQUIRE(AlignedAllocator<float, 16>::alignment == 16);
		REQUIRE(AlignedAllocator<float, 32>::alignment == 32);
		REQUIRE(AlignedAllocator<float, 64>::alignment == 64);
	}

	{
		typename DefaultAllocator<int32>::type alc1;
		std::allocator<int32> alc2;
		REQUIRE(alc1 == alc2);
		REQUIRE(!(alc1 != alc2));
	}
}

# pragma endregion

# pragma region Indexed

TEST_CASE("Indexed")
{
	SECTION("IndexedRef")
	{
		{
			Array<int32> v = { 0, 10, 20, 30 };
			size_t count = 0;

			for (auto[i, element] : IndexedRef(v))
			{
				element /= 10;
				REQUIRE(i == static_cast<size_t>(element));
				REQUIRE(i == count++);
			}
		}

		{
			String v = U"ABCDE";
			size_t count = 0;

			for (auto[i, element] : IndexedRef(v))
			{
				element -= U'A';
				REQUIRE(i == static_cast<size_t>(element));
				REQUIRE(i == count++);
			}
		}

		{
			int32 v[] = { 0, 10, 20, 30 };
			size_t count = 0;

			for (auto[i, element] : IndexedRef(v))
			{
				element /= 10;
				REQUIRE(i == static_cast<size_t>(element));
				REQUIRE(i == count++);
			}
		}
	}

	SECTION("Indexed")
	{
		{
			const Array<int32> v = { 0, 10, 20, 30 };
			size_t count = 0;

			for (auto[i, element] : Indexed(v))
			{
				REQUIRE(i == static_cast<size_t>(element / 10));
				REQUIRE(i == count++);
			}
		}

		{
			const String v = U"ABCDE";
			size_t count = 0;

			for (auto[i, element] : IndexedRef(v))
			{
				REQUIRE(i == static_cast<size_t>(element - U'A'));
				REQUIRE(i == count++);
			}
		}

		{
			const int32 v[] = { 0, 10, 20, 30 };
			size_t count = 0;

			for (auto[i, element] : Indexed(v))
			{
				REQUIRE(i == static_cast<size_t>(element / 10));
				REQUIRE(i == count++);
			}
		}
	}

	SECTION("IndexedRefReversed")
	{
		{
			Array<int32> v = { 0, 10, 20, 30 };
			size_t count = v.size();

			for (auto[i, element] : IndexedRefReversed(v))
			{
				element /= 10;
				REQUIRE(i == static_cast<size_t>(element));
				REQUIRE(i == --count);
			}
		}

		{
			String v = U"ABCDE";
			size_t count = v.size();

			for (auto[i, element] : IndexedRefReversed(v))
			{
				element -= U'A';
				REQUIRE(i == static_cast<size_t>(element));
				REQUIRE(i == --count);
			}
		}

		{
			int32 v[] = { 0, 10, 20, 30 };
			size_t count = std::size(v);

			for (auto[i, element] : IndexedRefReversed(v))
			{
				element /= 10;
				REQUIRE(i == static_cast<size_t>(element));
				REQUIRE(i == --count);
			}
		}
	}

	SECTION("IndexedReversed")
	{
		{
			const Array<int32> v = { 0, 10, 20, 30 };
			size_t count = v.size();

			for (auto[i, element] : IndexedReversed(v))
			{
				REQUIRE(i == static_cast<size_t>(element / 10));
				REQUIRE(i == --count);
			}
		}

		{
			const String v = U"ABCDE";
			size_t count = v.size();

			for (auto[i, element] : IndexedReversed(v))
			{
				REQUIRE(i == static_cast<size_t>(element - U'A'));
				REQUIRE(i == --count);
			}
		}

		{
			const int32 v[] = { 0, 10, 20, 30 };
			size_t count = std::size(v);

			for (auto[i, element] : IndexedReversed(v))
			{
				REQUIRE(i == static_cast<size_t>(element / 10));
				REQUIRE(i == --count);
			}
		}
	}
}

# pragma endregion





# pragma region Format

TEST_CASE("Format")
{
	REQUIRE(Format(true) == U"true");
	REQUIRE(Format(false) == U"false");
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
	REQUIRE(Format((void*)0) == U"0000000000000000");
	REQUIRE(Format(nullptr) == U"null");
	REQUIRE(Format(L'あ') == U"あ");
	REQUIRE(Format(U'あ') == U"あ");
	REQUIRE(Format(Byte(0x00)) == U"00");
	REQUIRE(Format(Byte(0xFF)) == U"FF");
	REQUIRE(Format(none) == U"none");
	REQUIRE(Format(unspecified) == U"none");
	REQUIRE(Format(Optional<int32>(123)) == U"Optional 123");
	REQUIRE(Format(Optional<String>(U"ABC")) == U"Optional ABC");
	REQUIRE(Format(Optional<int32>()) == U"none");
	REQUIRE(Format(Optional<String>()) == U"none");
	REQUIRE(Format(Optional<String>(U"")) == U"Optional ");
}

# pragma endregion



# pragma region ParseBool

TEST_CASE("ParseBool")
{
	REQUIRE(ParseBool(U"true") == true);
	REQUIRE(ParseBool(U"True") == true);
	REQUIRE(ParseBool(U"trUE") == true);
	REQUIRE(ParseBool(U"TRUE") == true);

	REQUIRE(ParseBool(U"false") == false);
	REQUIRE(ParseBool(U"False") == false);
	REQUIRE(ParseBool(U"fAlSe") == false);
	REQUIRE(ParseBool(U"FALSE") == false);

	REQUIRE(ParseBool(U"  true") == true);
	REQUIRE(ParseBool(U"true  ") == true);
	REQUIRE(ParseBool(U"  true  ") == true);

	REQUIRE(ParseBool(U"  false") == false);
	REQUIRE(ParseBool(U"false  ") == false);
	REQUIRE(ParseBool(U"  false  ") == false);

	REQUIRE(ParseBool(U"  TRUE") == true);
	REQUIRE(ParseBool(U"TRUE  ") == true);
	REQUIRE(ParseBool(U"  TRUE  ") == true);

	REQUIRE(ParseBool(U"  FALSE") == false);
	REQUIRE(ParseBool(U"FALSE  ") == false);
	REQUIRE(ParseBool(U"  FALSE  ") == false);

	REQUIRE_THROWS_AS(ParseBool(U"YES"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"NO"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"t"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"f"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"truetrue"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"falsefalse"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"true true"), ParseError);
	REQUIRE_THROWS_AS(ParseBool(U"false false"), ParseError);
}

# pragma endregion

# endif


/*
# pragma region Version

TEST_CASE("???")
{

}

# pragma endregion
*/