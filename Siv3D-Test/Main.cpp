
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;

struct W
{
	int x = 0;

	W() = default;

	~W()
	{
		//Log(L"###D");
	}

	explicit W(int _x)
		: x(_x)
	{
		//Log(L"###C");
	}

	W(const String& s)
		: x(int(s.length()) * 25)
	{
		//Log(L"###CS");
	}

	W(int _x, int _y)
		: x(_x + _y)
	{
		//Log(L"###C2");
	}

	W(const W& w)
		: x(w.x)
	{
		//Log(L"###COPY");
	}

	W(W&& w)
		: x(w.x)
	{
		//Log(L"###MOVE");
	}
};

void Test0(Arg::r_<int32> n)
{
	Log << n.value();
}

void Test1(Arg::r_<int32&> n)
{
	++n.value();
}

void Test2(Arg::r_<const int32&> n)
{
	Log << n.value();
}

void Test3(Arg::r_<W> w)
{
	Log(w->x);
}

void Test4(Arg::r_<W&> w)
{
	++w->x;
	//Log(w->x);
}

void Test5(Arg::r_<const W&> w)
{
	Log(w->x);
}

void Main()
{
	int n = 100;
	const int cn = 100;
	uint8 un = 100;
	double d = 99.9;
	W w(100);
	const W cw(100);

	Log(L"-----Test0");
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

	Log(L"-----Test0 d");

	Test0(Arg::r = 99.9); // warning
	Test0(Arg::r = d);
	Test0(Arg::r = std::ref(d)); // warning
	Test0(Arg::r = std::cref(d));

	Test0(Arg::r(99.9));
	Test0(Arg::r(d));
	Test0(Arg::r(std::ref(d)));
	Test0(Arg::r(std::ref(d)));

	Log(L"-----Test1");

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

	Log(L"-----Test1 d");

	//Test1(Arg::r = 99.9); //err
	//Test1(Arg::r = d); //err
	//Test1(Arg::r = std::ref(d)); //err
	//Test1(Arg::r = std::cref(d)); //err

	//Test1(Arg::r(99.9)); //err
	//Test1(Arg::r(d)); //err
	//Test1(Arg::r(std::ref(d))); //err
	//Test1(Arg::r(std::ref(d))); //err

	Log(L"-----Test2");

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

	Log(L"-----Test2 r");

	//Test2(Arg::r = 99.9); //err
	//Test2(Arg::r = d); //err
	//Test2(Arg::r = std::ref(d)); //err
	//Test2(Arg::r = std::cref(d)); //err

	//Test2(Arg::r(99.9)); //err
	//Test2(Arg::r(d)); //err
	//Test2(Arg::r(std::ref(d))); //err
	//Test2(Arg::r(std::ref(d))); //err

	Log(L"-----Test3=");

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

	Log(L"-----Test3()");

	Test3(Arg::r());
	Test3(Arg::r(w));
	Test3(Arg::r(cw));
	Test3(Arg::r(100));
	Test3(Arg::r(99.9)); // warning
	Test3(Arg::r(W(100)));
	Test3(Arg::r(String(L"abcd")));
	//Test3(Arg::r(L"abcd")); //err
	Test3(Arg::r(std::ref(w)));
	Test3(Arg::r(std::ref(cw)));
	//Test3(Arg::r(std::ref(n))); //err
	Test3(Arg::r(std::cref(w)));
	Test3(Arg::r(std::cref(cw)));
	//Test3(Arg::r(std::cref(n))); //err

	Log(L"-----Test4=");

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

	Log(L"-----Test4()");

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

	Log(L"-----Test5=");

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

	Log(L"-----Test5()");

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
	Log << ToString(255, Arg::radix = 16, Arg::upperCase = true);

	// Rect(80, 80, 40, 40)
	constexpr Rect rect(Arg::center(100, 100), 40);

	RunTest();
}



