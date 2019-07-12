
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

static int32 LoadInt()
{
	return 123;
}

static String LoadText()
{
	return String(U"DefaultText");
}

TEST_CASE("Optional<Type>")
{
	SECTION("value_or_eval")
	{
		{
			const Optional<int32> v(100), e;
			REQUIRE(v.value_or_eval(LoadInt) == 100);
			REQUIRE(e.value_or_eval(LoadInt) == 123);
		}

		{
			const Optional<String> v(U"Siv3D"), e;
			REQUIRE(v.value_or_eval(LoadText) == U"Siv3D");
			REQUIRE(e.value_or_eval(LoadText) == U"DefaultText");
		}
	}

	SECTION("then")
	{
		{
			int32 t = 0;
			auto f = [&](int32 n) { t = n; };
			const Optional<int32> v(100), e;
			v.then(f); REQUIRE(t == 100);
			e.then(f); REQUIRE(t == 100);
		}

		{
			String t;
			auto f = [&](const String& s) { t = s; };
			const Optional<String> v(U"Siv3D"), e;
			v.then(f); REQUIRE(t == U"Siv3D");
			e.then(f); REQUIRE(t == U"Siv3D");
		}
	}

	SECTION("map")
	{
		{
			const Optional<int32> v = 100, e;
			REQUIRE(v.map(Plus(10)).value() == 110);
			REQUIRE(e.map(Plus(10)) == none);
		}

		{
			const Optional<String> v(U"Siv3D"), e;
			REQUIRE(v.map([](const String& s) { return s.uppercased(); }).value() == U"SIV3D");
			REQUIRE(e.map([](const String& s) { return s.uppercased(); }) == none);
		}
	}
}


TEST_CASE("Optional<Type&>")
{
	SECTION("value_or_eval")
	{
		{
			int32 x = 100;
			const Optional<int32&> v(x), e;
			REQUIRE(v.value_or_eval(LoadInt) == 100);
			REQUIRE(e.value_or_eval(LoadInt) == 123);
		}

		{
			String x = U"Siv3D";
			const Optional<String&> v(x), e;
			REQUIRE(v.value_or_eval(LoadText) == U"Siv3D");
			REQUIRE(e.value_or_eval(LoadText) == U"DefaultText");
		}
	}

	SECTION("then")
	{
		{
			int32 t = 0;
			auto f = [&](int32 n) { t = n; };
			int32 x = 100;
			const Optional<int32&> v(x), e;
			v.then(f); REQUIRE(t == 100);
			e.then(f); REQUIRE(t == 100);
		}

		{
			String t;
			auto f = [&](const String& s) { t = s; };
			String x = U"Siv3D";
			const Optional<String&> v(x), e;
			v.then(f); REQUIRE(t == U"Siv3D");
			e.then(f); REQUIRE(t == U"Siv3D");
		}
	}

	SECTION("map")
	{
		{
			int32 x = 100;
			const Optional<int32&> v(x), e;
			REQUIRE(v.map(Plus(10)).value() == 110);
			REQUIRE(e.map(Plus(10)) == none);
		}

		{
			String x = U"Siv3D";
			const Optional<String&> v(x), e;
			REQUIRE(v.map([](const String& s) { return s.uppercased(); }).value() == U"SIV3D");
			REQUIRE(e.map([](const String& s) { return s.uppercased(); }) == none);
		}
	}
}

# endif
