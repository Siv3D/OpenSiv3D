
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

void Main()
{
	constexpr auto a0 = Plus(none)(2);
	constexpr auto a1 = Plus(5);
	constexpr auto a2 = Plus(5, 10);
	constexpr auto a3 = Plus(none, 10)(22);
	constexpr auto a4 = Plus(5.5, none)(22);
	constexpr auto a5 = Plus(none, none)(22, 3.125);

	constexpr auto b0 = Minus(none)(2);
	constexpr auto b1 = Minus(5);
	constexpr auto b2 = Minus(5, 10);
	constexpr auto b3 = Minus(none, 10)(22);
	constexpr auto b4 = Minus(5.5, none)(22);
	constexpr auto b5 = Minus(none, none)(22, 3.125);

	constexpr auto c0 = Multiplies(5, 10);
	constexpr auto c1 = Multiplies(none, 10)(22);
	constexpr auto c2 = Multiplies(5.5, none)(22);
	constexpr auto c3 = Multiplies(none, none)(22, 3.125);

	constexpr auto d0 = Divides(5, 10);
	constexpr auto d1 = Divides(none, 10)(22);
	constexpr auto d2 = Divides(5.5, none)(22);
	constexpr auto d3 = Divides(none, none)(22, 3.125);

	constexpr auto e1 = Modulus(5, 10);
	constexpr auto e2 = Modulus(none, 10)(22);
	const auto e2f1 = Modulus(none, 10)(22.0);
	const auto e2f2 = Modulus(none, 10.0)(22);
	const auto e2f3 = Modulus(none, 10.0)(22.0);
	constexpr auto e3 = Modulus(10, none)(3);
	const auto e3f1 = Modulus(10, none)(3.3);
	const auto e3f2 = Modulus(10.0, none)(3);
	const auto e3f3 = Modulus(10.0, none)(3.3);

	constexpr auto m0 = LessThan()(10, 20);
	constexpr auto m1 = LessThan(20)(10);
	constexpr auto m2 = LessThan(10, 20);
	constexpr auto m3 = LessThan(none, 10)(5);
	constexpr auto m4 = LessThan(5.5, none)(2);
	constexpr auto m5 = LessThan(none, none)(22, 3.125);

	constexpr auto r0 = Even()(4);

	Range(0, 100).filter(InRange(20, 50)).each(Log);
	Log(Range(0, 100).reduce1(Plus()));

	RunTest();
}
