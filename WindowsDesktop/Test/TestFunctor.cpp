
# include "Test.hpp"

# if defined(SIV3D_DO_TEST)

# include <Siv3D.hpp>
# include <ThirdParty/Catch2/catch.hpp>

namespace TestFunctor
{
	enum class TestEnum
	{
		A,
		B,
		C = 123
	};
}

TEST_CASE("Functors.Operator")
{
	using namespace Arg;

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

		REQUIRE_FALSE(Equal()(20, 20.5));
		REQUIRE_FALSE(Equal(20)(20.5));
		REQUIRE_FALSE(Equal(20, 20.5));
		REQUIRE_FALSE(Equal(_, 20)(20.5));
		REQUIRE_FALSE(Equal(20, _)(20.5));
		REQUIRE_FALSE(Equal(_, _)(20, 20.5));

		REQUIRE((_ == _)(20, 20));
		REQUIRE((_ == 20)(20));
		REQUIRE((20 == _)(20));

		REQUIRE_FALSE((_ == _)(20, 21));
		REQUIRE_FALSE((_ == 20)(21));
		REQUIRE_FALSE((20 == _)(21));
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

		REQUIRE(NotEqual()(20, 20.5));
		REQUIRE(NotEqual(20)(20.5));
		REQUIRE(NotEqual(20, 20.5));
		REQUIRE(NotEqual(_, 20)(20.5));
		REQUIRE(NotEqual(20, _)(20.5));
		REQUIRE(NotEqual(_, _)(20, 20.5));

		REQUIRE_FALSE((_ != _)(20, 20));
		REQUIRE_FALSE((_ != 20)(20));
		REQUIRE_FALSE((20 != _)(20));

		REQUIRE((_ != _)(20, 21));
		REQUIRE((_ != 20)(21));
		REQUIRE((20 != _)(21));
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

		REQUIRE(LessThan()(20.0, 21));
		REQUIRE(LessThan(20.0)(19));
		REQUIRE(LessThan(20.0, 21));
		REQUIRE(LessThan(_, 20.0)(19));
		REQUIRE(LessThan(20.0, _)(21));
		REQUIRE(LessThan(_, _)(20.0, 21));

		REQUIRE_FALSE((_ < _)(20, 20));
		REQUIRE_FALSE((_ < 20)(20));
		REQUIRE_FALSE((20 < _)(20));

		REQUIRE((_ < _)(20, 21));
		REQUIRE((_ < 20)(19));
		REQUIRE((20 < _)(21));
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

		REQUIRE(LessThanEqual()(20.0, 21));
		REQUIRE(LessThanEqual(20.0)(19));
		REQUIRE(LessThanEqual(20.0, 21));
		REQUIRE(LessThanEqual(_, 20.0)(19));
		REQUIRE(LessThanEqual(20.0, _)(21));
		REQUIRE(LessThanEqual(_, _)(20.0, 21));

		REQUIRE((_ <= _)(20, 20));
		REQUIRE((_ <= 20)(20));
		REQUIRE((20 <= _)(20));

		REQUIRE((_ <= _)(20, 21));
		REQUIRE((_ <= 20)(19));
		REQUIRE((20 <= _)(21));
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

		REQUIRE(GreaterThan()(20.0, 19));
		REQUIRE(GreaterThan(20.0)(21));
		REQUIRE(GreaterThan(20.0, 19));
		REQUIRE(GreaterThan(_, 20.0)(21));
		REQUIRE(GreaterThan(20.0, _)(19));
		REQUIRE(GreaterThan(_, _)(20.0, 19));

		REQUIRE_FALSE((_ > _)(20, 20));
		REQUIRE_FALSE((_ > 20)(20));
		REQUIRE_FALSE((20 > _)(20));

		REQUIRE_FALSE((_ > _)(20, 21));
		REQUIRE_FALSE((_ > 20)(19));
		REQUIRE_FALSE((20 > _)(21));
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

		REQUIRE(GreaterThanEqual()(20.0, 19));
		REQUIRE(GreaterThanEqual(20.0)(21));
		REQUIRE(GreaterThanEqual(20.0, 19));
		REQUIRE(GreaterThanEqual(_, 20.0)(21));
		REQUIRE(GreaterThanEqual(20.0, _)(19));
		REQUIRE(GreaterThanEqual(_, _)(20.0, 19));

		REQUIRE((_ >= _)(20, 20));
		REQUIRE((_ >= 20)(20));
		REQUIRE((20 >= _)(20));

		REQUIRE_FALSE((_ > _)(20, 21));
		REQUIRE_FALSE((_ > 20)(19));
		REQUIRE_FALSE((20 > _)(21));
	}

	SECTION("UnaryPlus")
	{
		REQUIRE(UnaryPlus(20) == 20);
		REQUIRE(UnaryPlus(_)(20) == 20);
		REQUIRE((+_)(20) == 20);
	}

	SECTION("Negate")
	{
		REQUIRE(Negate(20) == -20);
		REQUIRE(Negate(_)(20) == -20);
		REQUIRE((-_)(20) == -20);
	}

	SECTION("Plus")
	{
		REQUIRE(Plus()(10, 20) == 30);
		REQUIRE(Plus(10)(20) == 30);
		REQUIRE(Plus(10, 20) == 30);
		REQUIRE(Plus(_, 20)(10) == 30);
		REQUIRE(Plus(10, _)(20) == 30);
		REQUIRE(Plus(_, _)(10, 20) == 30);

		REQUIRE(Plus()(10, 2.5) == 12.5);
		REQUIRE(Plus(10)(2.5) == 12.5);
		REQUIRE(Plus(10, 2.5) == 12.5);
		REQUIRE(Plus(_, 2.5)(10) == 12.5);
		REQUIRE(Plus(10, _)(2.5) == 12.5);
		REQUIRE(Plus(_, _)(10, 2.5) == 12.5);

		REQUIRE((_ + _)(10, 20) == 30);
		REQUIRE((10 + _)(20) == 30);
		REQUIRE((_ + 20)(10) == 30);

		REQUIRE((_ + _)(10, 2.5) == 12.5);
		REQUIRE((10 + _)(2.5) == 12.5);
		REQUIRE((_ + 2.5)(10) == 12.5);

		REQUIRE((_ + _)(String(U"A"), String(U"B")) == U"AB");
		REQUIRE((String(U"A") + _)(String(U"B")) == U"AB");
		REQUIRE((_ + String(U"B"))(String(U"A")) == U"AB");
	}

	SECTION("Minus")
	{
		REQUIRE(Minus()(10, 20) == -10);
		REQUIRE(Minus(10)(20) == -10);
		REQUIRE(Minus(10, 20) == -10);
		REQUIRE(Minus(_, 20)(10) == -10);
		REQUIRE(Minus(10, _)(20) == -10);
		REQUIRE(Minus(_, _)(10, 20) == -10);

		REQUIRE(Minus()(10, 2.5) == 7.5);
		REQUIRE(Minus(10)(2.5) == 7.5);
		REQUIRE(Minus(10, 2.5) == 7.5);
		REQUIRE(Minus(_, 2.5)(10) == 7.5);
		REQUIRE(Minus(10, _)(2.5) == 7.5);
		REQUIRE(Minus(_, _)(10, 2.5) == 7.5);

		REQUIRE((_ - _)(10, 20) == -10);
		REQUIRE((10 - _)(20) == -10);
		REQUIRE((_ - 20)(10) == -10);

		REQUIRE((_ - _)(10, 2.5) == 7.5);
		REQUIRE((10 - _)(2.5) == 7.5);
		REQUIRE((_ - 2.5)(10) == 7.5);
	}

	SECTION("Multiplies")
	{
		REQUIRE(Multiplies()(10, 20) == 200);
		REQUIRE(Multiplies(10)(20) == 200);
		REQUIRE(Multiplies(10, 20) == 200);
		REQUIRE(Multiplies(_, 20)(10) == 200);
		REQUIRE(Multiplies(10, _)(20) == 200);
		REQUIRE(Multiplies(_, _)(10, 20) == 200);

		REQUIRE(Multiplies()(10, 2.5) == 25.0);
		REQUIRE(Multiplies(10)(2.5) == 25.0);
		REQUIRE(Multiplies(10, 2.5) == 25.0);
		REQUIRE(Multiplies(_, 2.5)(10) == 25.0);
		REQUIRE(Multiplies(10, _)(2.5) == 25.0);
		REQUIRE(Multiplies(_, _)(10, 2.5) == 25.0);

		REQUIRE((_ * _)(10, 20) == 200);
		REQUIRE((10 * _)(20) == 200);
		REQUIRE((_ * 20)(10) == 200);

		REQUIRE((_ * _)(10, 2.5) == 25.0);
		REQUIRE((10 * _)(2.5) == 25.0);
		REQUIRE((_ * 2.5)(10) == 25.0);
	}

	SECTION("Divides")
	{
		REQUIRE(Divides()(40, 19) == 2);
		REQUIRE(Divides(40)(19) == 2);
		REQUIRE(Divides(40, 19) == 2);
		REQUIRE(Divides(_, 19)(40) == 2);
		REQUIRE(Divides(40, _)(19) == 2);
		REQUIRE(Divides(_, _)(40, 19) == 2);

		REQUIRE(Divides()(75, 10.0) == 7.5);
		REQUIRE(Divides(75)(10.0) == 7.5);
		REQUIRE(Divides(75, 10.0) == 7.5);
		REQUIRE(Divides(_, 10.0)(75) == 7.5);
		REQUIRE(Divides(75, _)(10.0) == 7.5);
		REQUIRE(Divides(_, _)(75, 10.0) == 7.5);

		REQUIRE((_ / _)(40, 19) == 2);
		REQUIRE((40 / _)(19) == 2);
		REQUIRE((_ / 19)(40) == 2);

		REQUIRE((_ / _)(75, 10.0) == 7.5);
		REQUIRE((75 / _)(10.0) == 7.5);
		REQUIRE((_ / 10.0)(75) == 7.5);
	}

	SECTION("Modulus")
	{
		REQUIRE(Modulus()(40, 19) == 2);
		REQUIRE(Modulus(40)(19) == 2);
		REQUIRE(Modulus(40, 19) == 2);
		REQUIRE(Modulus(_, 19)(40) == 2);
		REQUIRE(Modulus(40, _)(19) == 2);
		REQUIRE(Modulus(_, _)(40, 19) == 2);

		REQUIRE(Modulus()(7.5, 10.0) == 7.5);
		REQUIRE(Modulus(7.5)(10.0) == 7.5);
		REQUIRE(Modulus(7.5, 10.0) == 7.5);
		REQUIRE(Modulus(_, 10.0)(7.5) == 7.5);
		REQUIRE(Modulus(7.5, _)(10.0) == 7.5);
		REQUIRE(Modulus(_, _)(7.5, 10.0) == 7.5);

		REQUIRE((_ % _)(40, 19) == 2);
		REQUIRE((40 % _)(19) == 2);
		REQUIRE((_ % 19)(40) == 2);

		REQUIRE((_ % _)(7.5, 10.0) == 7.5);
		REQUIRE((7.5 % _)(10.0) == 7.5);
		REQUIRE((_ % 10.0)(7.5) == 7.5);
	}

	SECTION("Not")
	{
		REQUIRE(Not(false) == true);
		REQUIRE(Not(_)(false) == true);
		REQUIRE((!_)(false) == true);

		REQUIRE(Not(true) == false);
		REQUIRE(Not(_)(true) == false);
		REQUIRE((!_)(true) == false);

		REQUIRE(Not(20) == false);
		REQUIRE(Not(_)(20) == false);
		REQUIRE((!_)(20) == false);
	}
}

TEST_CASE("Functors.Utility")
{
	using namespace Arg;

	SECTION("IsOdd")
	{
		REQUIRE(IsOdd(10) == false);
		REQUIRE(IsOdd(_)(10) == false);

		REQUIRE(IsOdd(11) == true);
		REQUIRE(IsOdd(_)(11) == true);

		REQUIRE(IsOdd(-10) == false);
		REQUIRE(IsOdd(_)(-10) == false);

		REQUIRE(IsOdd(-11) == true);
		REQUIRE(IsOdd(_)(-11) == true);
	}

	SECTION("IsEven")
	{
		REQUIRE(IsEven(10) == true);
		REQUIRE(IsEven(_)(10) == true);

		REQUIRE(IsEven(11) == false);
		REQUIRE(IsEven(_)(11) == false);

		REQUIRE(IsEven(-10) == true);
		REQUIRE(IsEven(_)(-10) == true);

		REQUIRE(IsEven(-11) == false);
		REQUIRE(IsEven(_)(-11) == false);
	}

	SECTION("Id")
	{
		REQUIRE(Id(123) == 123);
		REQUIRE(Id(_)(123) == 123);

		REQUIRE(Id(true) == true);
		REQUIRE(Id(_)(true) == true);

		REQUIRE(Id(Point(20, 20)) == Point(20, 20));
		REQUIRE(Id(_)(Point(20, 20)) == Point(20, 20));
	}

	SECTION("FromEnum")
	{
		REQUIRE(FromEnum(TestFunctor::TestEnum::A) == 0);
		REQUIRE(FromEnum(TestFunctor::TestEnum::B) == 1);
		REQUIRE(FromEnum(TestFunctor::TestEnum::C) == 123);

		REQUIRE(FromEnum(_)(TestFunctor::TestEnum::A) == 0);
		REQUIRE(FromEnum(_)(TestFunctor::TestEnum::B) == 1);
		REQUIRE(FromEnum(_)(TestFunctor::TestEnum::C) == 123);
	}

	SECTION("ToEnum")
	{
		REQUIRE(ToEnum<TestFunctor::TestEnum>(0) == TestFunctor::TestEnum::A);
		REQUIRE(ToEnum<TestFunctor::TestEnum>(1) == TestFunctor::TestEnum::B);
		REQUIRE(ToEnum<TestFunctor::TestEnum>(123) == TestFunctor::TestEnum::C);

		REQUIRE(ToEnum<TestFunctor::TestEnum>(_)(0) == TestFunctor::TestEnum::A);
		REQUIRE(ToEnum<TestFunctor::TestEnum>(_)(1) == TestFunctor::TestEnum::B);
		REQUIRE(ToEnum<TestFunctor::TestEnum>(_)(123) == TestFunctor::TestEnum::C);
	}

	SECTION("Abs")
	{
		REQUIRE(Abs(10) == 10);
		REQUIRE(Abs(_)(10) == 10);
		REQUIRE(Abs(-10) == 10);
		REQUIRE(Abs(_)(-10) == 10);

		REQUIRE(Abs(0.5) == 0.5);
		REQUIRE(Abs(_)(0.5) == 0.5);
		REQUIRE(Abs(-0.5) == 0.5);
		REQUIRE(Abs(_)(-0.5) == 0.5);
	}
}

# endif
