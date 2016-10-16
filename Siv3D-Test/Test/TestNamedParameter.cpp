//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include <gtest/gtest.h>
using namespace s3d;

struct W
{
	int x = 0;

	W() = default;

	explicit W(int _x)
		: x(_x) {}

	W(const String& s)
		: x(int(s.length()) * 25) {}

	W(int _x, int _y)
		: x(_x + _y) {}

	W(const W& w)
		: x(w.x) {}

	W(W&& w)
		: x(w.x) {}
};

void Test0(Arg::r_<int32> n)
{
	n;
}

void Test1(Arg::r_<int32&> n)
{
	++n.value();
}

void Test2(Arg::r_<const int32&> n)
{
	n;
}

void Test3(Arg::r_<W> w)
{
	w;
}

void Test4(Arg::r_<W&> w)
{
	++w->x;
}

void Test5(Arg::r_<const W&> w)
{
	w;
}

TEST(NamedParameter, NamedParameter)
{
	int n = 100;
	const int cn = 100;
	uint8 un = 100;
	double d = 99.9;
	W w(100);
	const W cw(100);

	Test0(Arg::r = 100);
	Test0(Arg::r = n);
	Test0(Arg::r = cn);
	Test0(Arg::r = un);
	Test0(Arg::r = std::ref(n));
	Test0(Arg::r = std::ref(cn));
	Test0(Arg::r = std::ref(un));
	Test0(Arg::r = std::cref(n));
	Test0(Arg::r = std::cref(cn));
	Test0(Arg::r = std::cref(un));

	Test0(Arg::r());
	Test0(Arg::r(100));
	Test0(Arg::r(n));
	Test0(Arg::r(cn));
	Test0(Arg::r(un));
	Test0(Arg::r(std::ref(n)));
	Test0(Arg::r(std::ref(cn)));
	Test0(Arg::r(std::ref(un)));
	Test0(Arg::r(std::cref(n)));
	Test0(Arg::r(std::cref(cn)));
	Test0(Arg::r(std::cref(un)));


	//Test0(Arg::r = 99.9); // warning
	//Test0(Arg::r = d); // warning
	//Test0(Arg::r = std::ref(d)); // warning
	//Test0(Arg::r = std::cref(d)); // warning

	Test0(Arg::r(99.9));
	Test0(Arg::r(d));
	//Test0(Arg::r(std::ref(d))); // warning
	//Test0(Arg::r(std::cref(d))); // warning


	//Test1(Arg::r = 100); //err
	//Test1(Arg::r = n); //err
	//Test1(Arg::r = cn); //err
	//Test1(Arg::r = un); //err
	Test1(Arg::r = std::ref(n)); Log << n;
	//Test1(Arg::r = std::ref(cn)); //err
	//Test1(Arg::r = std::ref(un)); //err
	//Test1(Arg::r = std::cref(n)); //err
	//Test1(Arg::r = std::cref(cn)); //err
	//Test1(Arg::r = std::cref(un)); //err

	//Test1(Arg::r()); //err
	//Test1(Arg::r(100)); //err
	//Test1(Arg::r(n)); //err
	//Test1(Arg::r(cn)); //err
	//Test1(Arg::r(un)); //err
	Test1(Arg::r(std::ref(n))); Log << n;
	//Test1(Arg::r(std::ref(cn))); //err
	//Test1(Arg::r(std::ref(un))); //err
	//Test1(Arg::r(std::cref(n))); //err
	//Test1(Arg::r(std::cref(cn))); //err
	//Test1(Arg::r(std::cref(un))); //err


	//Test1(Arg::r = 99.9); //err
	//Test1(Arg::r = d); //err
	//Test1(Arg::r = std::ref(d)); //err
	//Test1(Arg::r = std::cref(d)); //err

	//Test1(Arg::r(99.9)); //err
	//Test1(Arg::r(d)); //err
	//Test1(Arg::r(std::ref(d))); //err
	//Test1(Arg::r(std::ref(d))); //err


	//Test2(Arg::r = 100); //err
	//Test2(Arg::r = n); //err
	//Test2(Arg::r = cn); //err
	//Test2(Arg::r = un); //err
	//Test2(Arg::r = std::ref(n)); //err
	Test2(Arg::r = std::ref(cn));
	//Test2(Arg::r = std::ref(un)); //err
	Test2(Arg::r = std::cref(n));
	Test2(Arg::r = std::cref(cn));
	//Test2(Arg::r = std::cref(un)); //err

	//Test2(Arg::r()); //err
	//Test2(Arg::r(100)); //err
	//Test2(Arg::r(n)); //err
	//Test2(Arg::r(cn)); //err
	//Test2(Arg::r(un)); //err
	//Test2(Arg::r(std::ref(n))); //err
	Test2(Arg::r(std::ref(cn)));
	//Test2(Arg::r(std::ref(un))); //err
	Test2(Arg::r(std::cref(n)));
	Test2(Arg::r(std::cref(cn)));
	//Test2(Arg::r(std::cref(un))); //err


	//Test2(Arg::r = 99.9); //err
	//Test2(Arg::r = d); //err
	//Test2(Arg::r = std::ref(d)); //err
	//Test2(Arg::r = std::cref(d)); //err

	//Test2(Arg::r(99.9)); //err
	//Test2(Arg::r(d)); //err
	//Test2(Arg::r(std::ref(d))); //err
	//Test2(Arg::r(std::ref(d))); //err


	Test3(Arg::r = w);
	Test3(Arg::r = cw);
	//Test3(Arg::r = 100); //err
	//Test3(Arg::r = 99.9); //err
	Test3(Arg::r = W(100));
	Test3(Arg::r = String(L"abcd"));
	//Test3(Arg::r = L"abcd"); //err
	Test3(Arg::r = std::ref(w));
	Test3(Arg::r = std::ref(cw));
	//Test3(Arg::r = std::ref(n)); //err
	Test3(Arg::r = std::cref(w));
	Test3(Arg::r = std::cref(cw));
	//Test3(Arg::r = std::cref(n)); //err


	Test3(Arg::r());
	Test3(Arg::r(w));
	Test3(Arg::r(cw));
	Test3(Arg::r(100));
	//Test3(Arg::r(99.9)); // warning
	Test3(Arg::r(W(100)));
	Test3(Arg::r(String(L"abcd")));
	//Test3(Arg::r(L"abcd")); //err
	Test3(Arg::r(std::ref(w)));
	Test3(Arg::r(std::ref(cw)));
	//Test3(Arg::r(std::ref(n))); //err
	Test3(Arg::r(std::cref(w)));
	Test3(Arg::r(std::cref(cw)));
	//Test3(Arg::r(std::cref(n))); //err


	//Test4(Arg::r = w); //err
	//Test4(Arg::r = cw); //err
	//Test4(Arg::r = 100); //err
	//Test4(Arg::r = 99.9); //err
	//Test4(Arg::r = W(100)); //err
	//Test4(Arg::r = String(L"abcd")); //err
	//Test4(Arg::r = L"abcd"); //err
	Test4(Arg::r = std::ref(w)); Log << w.x;
	//Test4(Arg::r = std::ref(cw)); //err
	//Test4(Arg::r = std::ref(n)); //err
	//Test4(Arg::r = std::cref(w)); //err
	//Test4(Arg::r = std::cref(cw)); //err
	//Test4(Arg::r = std::cref(n)); //err

	//Test4(Arg::r()); //err
	//Test4(Arg::r(w)); //err
	//Test4(Arg::r(cw)); //err
	//Test4(Arg::r(100)); //err
	//Test4(Arg::r(99.9)); // warning
	//Test4(Arg::r(W(100))); //err
	//Test4(Arg::r(String(L"abcd"))); //err
	//Test4(Arg::r(L"abcd")); //err
	Test4(Arg::r(std::ref(w))); Log << w.x;
	//Test4(Arg::r(std::ref(cw))); //err
	//Test4(Arg::r(std::ref(n))); //err
	//Test4(Arg::r(std::cref(w))); //err
	//Test4(Arg::r(std::cref(cw))); //err
	//Test4(Arg::r(std::cref(n))); //err


	//Test5(Arg::r = w); //err
	//Test5(Arg::r = cw); //err
	//Test5(Arg::r = 100); //err
	//Test5(Arg::r = 99.9); //err
	//Test5(Arg::r = W(100)); //err
	//Test5(Arg::r = String(L"abcd")); //err
	//Test5(Arg::r = L"abcd"); //err
	//Test5(Arg::r = std::ref(w)); //err
	Test5(Arg::r = std::ref(cw));
	//Test5(Arg::r = std::ref(n)); //err
	Test5(Arg::r = std::cref(w));
	Test5(Arg::r = std::cref(cw));
	//Test5(Arg::r = std::cref(n)); //err


	//Test5(Arg::r()); //err
	//Test5(Arg::r(w)); //err
	//Test5(Arg::r(cw)); //err
	//Test5(Arg::r(100)); //err
	//Test5(Arg::r(99.9)); // warning
	//Test5(Arg::r(W(100))); //err
	//Test5(Arg::r(String(L"abcd"))); //err
	//Test5(Arg::r(L"abcd")); //err
	//Test5(Arg::r(std::ref(w))); //err
	Test5(Arg::r(std::ref(cw)));
	//Test5(Arg::r(std::ref(n))); //err
	Test5(Arg::r(std::cref(w)));
	Test5(Arg::r(std::cref(cw)));
	//Test5(Arg::r(std::cref(n))); //err



	// Array<int32>{ 2, 3, 6, 2, 5 }
	const Array<int32> v(5, Arg::generator = RNG(1, 6));

	// Circular(3.5, 20.5)
	constexpr Circular c(Arg::theta = 20.5, Arg::r = 3.5);

	// L"FF"
	ToString(255, Arg::radix = 16, Arg::upperCase = true);

	// Rect(80, 80, 40, 40)
	constexpr Rect rect(Arg::center(100, 100), 40);
}
