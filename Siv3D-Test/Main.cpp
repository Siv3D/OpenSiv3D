
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

void Main()
{
	Log(L"Hello, Siv3D!");

	//Log(Date::Today());

	//Log(Date::Today().isToday());

	//Log(Date::Today() + 5_d);

	//Log(Date::Today() - 366_d);

	/*
	// 0～100 の範囲
	Log(L"# Range(0, 100)");
	Log(Range(0, 100));

	// 0～100 の合計
	Log(L"# Range(0, 100).reduce1(Plus())");
	Log(Range(0, 100).reduce1(Plus()));

	// 1/1 + 1/2 + 1/3 + 1/4 + ... + 1/10000 の合計
	Log(L"# Range(1, 10000).map(Divides(1.0, none)).reduce1(Plus())");
	Log(18_dp, Range(1, 10000).map(Divides(1.0, none)).reduce1(Plus()));
	Log(L"# Iota(10000, 1, -1).map(Divides(1.0, none)).reduce1(Plus())");
	Log(18_dp, Iota(10000, 0, -1).map(Divides(1.0, none)).reduce1(Plus()));
	Log(L"# Actual:");
	Log(L"9.787606036044382264178...");

	// 0～100 のうち 20 未満の個数
	Log(L"# Range(0, 100).count_if(LessThan(20))");
	Log(Range(0, 100).count_if(LessThan(20)));

	// 0～10 の範囲の奇数
	Log(L"# Range(0, 10).filter(Odd())");
	Log(Range(0, 10).filter(Odd()));

	// 100 の階乗
	Log(L"# Range(1, 100).reduce1(Multiplies<BigInt>())");
	Log(Range(1, 100).reduce1(Multiplies<BigInt>()));

	// FizzBuzz
	Log(L"# FizzBuzz");
	Range(1, 20).map([](auto n) { return n % 15 == 0 ? L"FizzBuzz"
									   : n %  3 == 0 ? L"Fizz"
									   : n %  5 == 0 ? L"Buzz"
									   : Format(n); }).each(Log);
	
	// フィボナッチ数列
	Log(L"# Fibbonaci");
	BigInt a = 0, b = 1;
	Log(a, L'\n', b);
	Range(1, 100).map([&a, &b](auto) { a = std::exchange(b, a + b); return b; }).each(Log);
	
	// 0〜9 の数をシャッフル
	Log(L"# Range(0, 9).asArray().shuffle()");
	Log(Range(0, 9).asArray().shuffle());
	
	// Grid
	Log(L"# Grid");
	const Grid<int32> g = {{10, 20, 30, 40}, {11, 22, 33, 44}, {50, 51, 52, 53}};
	Log(g);
	
	// Grid from Range
	Log(L"# Grid from Range");
	Log(Grid<int32>(10, 10, Range(0, 99)));
	
	// Format
	Log(L"# Format");
	Log(2016, L'/', 5, L'/', 7);
	Log(L"{}/{}/{}"_fmt(2016, 5, 17));
	Log(L"{2}/{1}/{0}"_fmt(2016, 5, 17));
	Log(31415.9265358979);
	Log(314.159265358979);
	Log(3.14159265358979);

	// 小数点以下の桁数指定（0 は省略）
	Log(L"# ToString(double)");
	Log(ToString(1.234, 0));
	Log(ToString(1.234, 1));
	Log(ToString(1.234, 2));
	Log(ToString(1.234, 3));
	Log(ToString(1.234, 4));
	Log(ToString(1.234, 5));

	// 小数点以下の桁数指定（0 は省略）
	Log(L"# Format(DecimalPlace, double)");
	Log(0_dp, 1.234);
	Log(1_dp, 1.234);
	Log(2_dp, 1.234);
	Log(3_dp, 1.234);
	Log(4_dp, 1.234);
	Log(5_dp, 1.234);
	
	// 小数点以下の桁数指定（0 も表示）
	Log(L"# ToFixed(double)");
	Log(ToFixed(1.234, 0));
	Log(ToFixed(1.234, 1));
	Log(ToFixed(1.234, 2));
	Log(ToFixed(1.234, 3));
	Log(ToFixed(1.234, 4));
	Log(ToFixed(1.234, 5));
	
	// 小数点以下の桁数指定（0 も表示）
	Log(L"# {:.Nf}_fmt(double)");
	Log(L"{:.0f}"_fmt(1.234));
	Log(L"{:.1f}"_fmt(1.234));
	Log(L"{:.2f}"_fmt(1.234));
	Log(L"{:.3f}"_fmt(1.234));
	Log(L"{:.4f}"_fmt(1.234));
	Log(L"{:.5f}"_fmt(1.234));
	
	// BigInt
	Log(L"# BigInt");
	Log("100000000000000000000000000000000000000000000000000000000000000000000000000000001"_big * 1234567890);
	
	// String
	Log(L"# String");
	const String str(L"Siv3D");
	Log(str);
	Log(str.uppercased());
	Log(str.lowercased());
	Log(str.reversed());
	Log(str.includes(L"3D"));
	Log(str.starts_with(L"Si"));
	Log(str.ends_with(L"v3D"));
	
	// Parse
	Log(L"# Parse");
	const int32 parsed0 = Parse<int32>(L"12345");
	const double parsed1 = Parse<double>(L" 3.1415 ");
	const int32 parsed2 = ParseOr<int32>(L"???", 42);
	const double parsed3 = ParseOr<double>(L"5.55", 42);	
	Log(parsed0);
	Log(parsed1);
	Log(parsed2);
	Log(parsed3);
	Log(ParseOpt<int32>(L"???"));
	Log(ParseOpt<double>(L"7.77"));

	// Time
	Log(L"# Time");
	Log(Time::GetSec());
	Log(Time::GetMillisec());
	Log(Time::GetMicrosec());
	Log(Time::GetNanosec());
	Log(Time::GetSecSinceEpoch());
	Log(Time::GetMillisecSinceEpoch());
	Log(Time::GetMicrosecSinceEpoch());

	// Duration
	Log(L"# Duration");
	Log(1_d + 24h);
	Log(DurationCast<HoursF>(60min + 30min));
	Log(DurationCast<Seconds>(1_d));

	// Stopwatch
	Log(L"# Stopwatch");
	Stopwatch stopwatch(true);
	System::Sleep(1.5s);
	Log(stopwatch);
	Log(stopwatch.format(L"S.xxx'秒'"));

	// Stopwatch
	SpeedStopwatch countDown(3s, -1.0, true);
	for (int32 i = 0; i <= 3; ++i)
	{
		Log(countDown);
		System::Sleep(1s);
	}

	// TimeProfiler
	TimeProfiler tp;
	for (int32 i = 0; i < 50; ++i)
	{
		tp.begin(L"System::Sleep(20)");
		System::Sleep(20);
		tp.end();
	}
	*/
}
