
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

TEST_CASE("Utility")
{
	using Arg::_;

	SECTION("Max")
	{
		REQUIRE(Max(10, 20) == 20);
		REQUIRE(Max(_, 20)(10) == 20);
		REQUIRE(Max(10, _)(20) == 20);
		REQUIRE(Max(_, _)(10, 20) == 20);

		REQUIRE(Max(30, 20) == 30);
		REQUIRE(Max(_, 20)(30) == 30);
		REQUIRE(Max(30, _)(20) == 30);
		REQUIRE(Max(_, _)(30, 20) == 30);

		REQUIRE(Max({ 10, 20, 30, 40, 50 }) == 50);
		REQUIRE(Max({ 10, 50, 20, 40, 30 }) == 50);
		REQUIRE(Max({ 50, 40, 30, 20, 10 }) == 50);
	}

	SECTION("Min")
	{
		REQUIRE(Min(10, 20) == 10);
		REQUIRE(Min(_, 20)(10) == 10);
		REQUIRE(Min(10, _)(20) == 10);
		REQUIRE(Min(_, _)(10, 20) == 10);

		REQUIRE(Min(30, 20) == 20);
		REQUIRE(Min(_, 20)(30) == 20);
		REQUIRE(Min(30, _)(20) == 20);
		REQUIRE(Min(_, _)(30, 20) == 20);

		REQUIRE(Min({ 10, 20, 30, 40, 50 }) == 10);
		REQUIRE(Min({ 10, 50, 20, 40, 30 }) == 10);
		REQUIRE(Min({ 50, 40, 30, 20, 10 }) == 10);
	}

	SECTION("Clamp")
	{
		REQUIRE(Clamp(-50, 0, 100) == 0);
		REQUIRE(Clamp(0, 0, 100) == 0);
		REQUIRE(Clamp(50, 0, 100) == 50);
		REQUIRE(Clamp(100, 0, 100) == 100);
		REQUIRE(Clamp(150, 0, 100) == 100);

		REQUIRE(Clamp(_, 0, 100)(-50) == 0);
		REQUIRE(Clamp(_, 0, 100)(0) == 0);
		REQUIRE(Clamp(_, 0, 100)(50) == 50);
		REQUIRE(Clamp(_, 0, 100)(100) == 100);
		REQUIRE(Clamp(_, 0, 100)(150) == 100);
	}

	SECTION("InRange")
	{
		REQUIRE(InRange(-50, 0, 100) == false);
		REQUIRE(InRange(0, 0, 100) == true);
		REQUIRE(InRange(50, 0, 100) == true);
		REQUIRE(InRange(100, 0, 100) == true);
		REQUIRE(InRange(150, 0, 100) == false);

		REQUIRE(InRange(_, 0, 100)(-50) == false);
		REQUIRE(InRange(_, 0, 100)(0) == true);
		REQUIRE(InRange(_, 0, 100)(50) == true);
		REQUIRE(InRange(_, 0, 100)(100) == true);
		REQUIRE(InRange(_, 0, 100)(150) == false);
	}
}

# endif
