
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

namespace TestNamedParameter
{
	namespace TestArg
	{
		SIV3D_NAMED_PARAMETER(month);
		SIV3D_NAMED_PARAMETER(day);
		SIV3D_NAMED_PARAMETER(x);
		SIV3D_NAMED_PARAMETER(y);
		SIV3D_NAMED_PARAMETER(pos);
		SIV3D_NAMED_PARAMETER(color);
	}

	int32 DateTest_impl(int32 month, int32 day)
	{
		return month * 100 + day;
	}

	int32 DateTest(TestArg::month_<int32> m, TestArg::day_<int32> d)
	{
		return DateTest_impl(m.value(), d.value());
	}

	int32 DateTest(TestArg::day_<int32> d, TestArg::month_<int32> m)
	{
		return DateTest_impl(m.value(), d.value());
	}

	int32 Draw_impl(const Point& pos, const Color& color)
	{
		return pos.x * 1'000'000 + pos.y * 1'000 + int(color.asUint32());
	}

	int32 Draw(TestArg::x_<int32> x, TestArg::y_<int32> y, TestArg::color_<Color> color)
	{
		return Draw_impl(Point(x.value(), y.value()), color.value());
	}

	int32 Draw(TestArg::color_<Color> color, TestArg::x_<int32> x, TestArg::y_<int32> y)
	{
		return Draw_impl(Point(x.value(), y.value()), color.value());
	}

	int32 Draw(TestArg::pos_<Point> pos, TestArg::color_<Color> color)
	{
		return Draw_impl(pos.value(), color.value());
	}

	int32 Test1(TestArg::x_<int32> x)
	{
		return x.value();
	}

	int32 Test2(TestArg::x_<int32> x)
	{
		return *x;
	}

	void RefTest1(TestArg::x_<int32&> x)
	{
		++x.value();
	}

	void RefTest2(TestArg::x_<int32&> x)
	{
		++*x;
	}

	int32 CRefTest1(TestArg::x_<const int32&> x)
	{
		return x.value();
	}

	int32 CRefTest2(TestArg::x_<const int32&> x)
	{
		return *x;
	}

	int32 DATest1(TestArg::x_<int32> x = 123)
	{
		return x.value();
	}

	int32 DATest2(TestArg::x_<int32> x = 123)
	{
		return *x;
	}

	std::string Test3(TestArg::x_<std::string> x)
	{
		return x.value();
	}

	std::string Test4(TestArg::x_<std::string> x)
	{
		return *x;
	}

	void RefTest3(TestArg::x_<std::string&> x)
	{
		x.value().push_back('3');
	}

	void RefTest4(TestArg::x_<std::string&> x)
	{
		(*x).push_back('4');
	}

	void RefTest5(TestArg::x_<std::string&> x)
	{
		x->push_back('5');
	}

	std::string CRefTest3(TestArg::x_<const std::string&> x)
	{
		return x.value();
	}

	std::string CRefTest4(TestArg::x_<const std::string&> x)
	{
		return *x;
	}

	std::string DATest3(TestArg::x_<std::string> x = "ABC"s)
	{
		return x.value();
	}

	std::string DATest4(TestArg::x_<std::string> x = "ABC"s)
	{
		return *x;
	}
}

TEST_CASE("NamedParameter.Date")
{
	using namespace TestNamedParameter;
	REQUIRE(DateTest_impl(12, 31) == 1231);
	REQUIRE(DateTest(TestArg::month = 12, TestArg::day = 31) == 1231);
	REQUIRE(DateTest(TestArg::day = 31, TestArg::month = 12) == 1231);
}

TEST_CASE("NamedParameter.Draw")
{
	using namespace TestNamedParameter;
	REQUIRE(Draw_impl(Point(12, 34), Color(11, 22, 33, 44)) == 752399835);
	REQUIRE(Draw(TestArg::x = 12, TestArg::y = 34, TestArg::color(11, 22, 33, 44)) == 752399835);
	REQUIRE(Draw(TestArg::color(11, 22, 33, 44), TestArg::x = 12, TestArg::y = 34) == 752399835);
	REQUIRE(Draw(TestArg::pos = Point(12, 34), TestArg::color(11, 22, 33, 44)) == 752399835);
}

TEST_CASE("NamedParameter.Test1/2")
{
	using namespace TestNamedParameter;
	REQUIRE(Test1(TestArg::x = 100) == 100);
	REQUIRE(Test2(TestArg::x = 100) == 100);
	REQUIRE(Test1(TestArg::x(200)) == 200);
	REQUIRE(Test2(TestArg::x(200)) == 200);
}

TEST_CASE("NamedParameter.RefTest1/2")
{
	using namespace TestNamedParameter;
	int32 a = 100;
	RefTest1(TestArg::x = std::ref(a)); REQUIRE(a == 101);
	RefTest2(TestArg::x = std::ref(a)); REQUIRE(a == 102);
	RefTest1(TestArg::x(std::ref(a))); REQUIRE(a == 103);
	RefTest2(TestArg::x(std::ref(a))); REQUIRE(a == 104);
}

TEST_CASE("NamedParameter.CRefTest1/2")
{
	using namespace TestNamedParameter;
	int32 a = 100;
	REQUIRE(CRefTest1(TestArg::x = std::cref(a)) == 100);
	REQUIRE(CRefTest2(TestArg::x = std::cref(a)) == 100);
	REQUIRE(CRefTest1(TestArg::x(std::cref(a))) == 100);
	REQUIRE(CRefTest2(TestArg::x(std::cref(a))) == 100);
}

TEST_CASE("NamedParameter.DATest1/2")
{
	using namespace TestNamedParameter;
	REQUIRE(DATest1(TestArg::x = 100) == 100);
	REQUIRE(DATest2(TestArg::x = 100) == 100);
	REQUIRE(DATest1(TestArg::x(200)) == 200);
	REQUIRE(DATest2(TestArg::x(200)) == 200);
	REQUIRE(DATest1() == 123);
	REQUIRE(DATest2() == 123);
}

TEST_CASE("NamedParameter.Test3/4")
{
	using namespace TestNamedParameter;
	using namespace std::literals::string_literals;
	REQUIRE(Test3(TestArg::x = std::string("ABC")) == "ABC");
	REQUIRE(Test4(TestArg::x = std::string("ABC")) == "ABC");
	REQUIRE(Test3(TestArg::x(std::string("ABC"))) == "ABC");
	REQUIRE(Test4(TestArg::x(std::string("ABC"))) == "ABC");
	REQUIRE(Test3(TestArg::x = "ABC") == "ABC");
	REQUIRE(Test4(TestArg::x = "ABC") == "ABC");
	REQUIRE(Test3(TestArg::x = "ABC"s) == "ABC");
	REQUIRE(Test4(TestArg::x = "ABC"s) == "ABC");
	REQUIRE(Test3(TestArg::x("ABC"s)) == "ABC");
	REQUIRE(Test4(TestArg::x("ABC"s)) == "ABC");
	REQUIRE(Test3(TestArg::x(3, 'A')) == "AAA");
	REQUIRE(Test4(TestArg::x(3, 'A')) == "AAA");
}

TEST_CASE("NamedParameter.RefTest3/4/5")
{
	using namespace TestNamedParameter;
	std::string a = "ABC";
	RefTest3(TestArg::x = std::ref(a)); REQUIRE(a == "ABC3");
	RefTest4(TestArg::x = std::ref(a)); REQUIRE(a == "ABC34");
	RefTest5(TestArg::x = std::ref(a)); REQUIRE(a == "ABC345");
	RefTest3(TestArg::x(std::ref(a))); REQUIRE(a == "ABC3453");
	RefTest4(TestArg::x(std::ref(a))); REQUIRE(a == "ABC34534");
	RefTest5(TestArg::x(std::ref(a))); REQUIRE(a == "ABC345345");
}

TEST_CASE("NamedParameter.CRefTest3/4")
{
	using namespace TestNamedParameter;
	std::string a = "ABC";
	REQUIRE(CRefTest3(TestArg::x = std::cref(a)) == "ABC");
	REQUIRE(CRefTest4(TestArg::x = std::cref(a)) == "ABC");
	REQUIRE(CRefTest3(TestArg::x(std::cref(a))) == "ABC");
	REQUIRE(CRefTest4(TestArg::x(std::cref(a))) == "ABC");
}

TEST_CASE("NamedParameter.DATest3/4")
{
	using namespace TestNamedParameter;
	REQUIRE(DATest3(TestArg::x = "AAA") == "AAA");
	REQUIRE(DATest4(TestArg::x = "AAA") == "AAA");
	REQUIRE(DATest3(TestArg::x("AAA"s)) == "AAA");
	REQUIRE(DATest4(TestArg::x("AAA"s)) == "AAA");
	REQUIRE(DATest3() == "ABC");
	REQUIRE(DATest4() == "ABC");
}

# endif
