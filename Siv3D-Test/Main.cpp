
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

static constexpr wchar hexTable[16] =
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

void Dump(const void* data, size_t size)
{
	if (data == nullptr || size == 0)
	{
		return;
	}

	const uint8* ptr = static_cast<const uint8*>(data);

	String result(size * 3 - 1, L'0');

	wchar* dst = &result[0];

	bool isFirst = true;

	while (size--)
	{
		if (isFirst == true)
		{
			isFirst = false;
		}
		else
		{
			*dst++ = L' ';
		}

		*dst++ = hexTable[(*ptr) >> 4];
		*dst++ = hexTable[(*ptr) & 0x0F];
		++ptr;
	}

	Log(result);
}

void Main()
{
	RunTest();

	//TimeProfiler tp;

	//for (int32 i = 0; i < 50; ++i)
	//{
	//	tp.begin(L"FromUTF8");
	//	CharacterSet::FromUTF8(u8"あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字");
	//	tp.end();
	//}

	//for (int32 i = 0; i < 50; ++i)
	//{
	//	tp.begin(L"UTF8ToUTF16");
	//	CharacterSet::UTF8ToUTF16(u8"あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字あいうえおabc漢字");
	//	tp.end();
	//}

	//Dump(CharacterSet::FromUTF8(u8"あいうえおabc漢字").c_str(), CharacterSet::FromUTF8(u8"あいうえおabc漢字").length()*2);
	//Dump(CharacterSet::UTF8ToUTF16(u8"あいうえおabc漢字").c_str(), CharacterSet::UTF8ToUTF16(u8"あいうえおabc漢字").length()*2);
	/*
	RunTest();

	// 0～100 の範囲
	Log(L"# Range(0, 100)");
	Log(Range(0, 100));

	// 0～100 の合計
	Log(L"# Range(0, 100).reduce1(Plus())");
	Log(Range(0, 100).reduce1(Plus()));

	// 1/1 + 1/2 + 1/3 + 1/4 + ... + 1/10000 の合計
	Log(L"# Range(1, 10000).map(Divides(1.0, none)).reduce1(Plus())");
	Log(18_dp, Range(10000, 1, -1).map(Divides(1.0, none)).reduce1(Plus()));
	Log(Range(10000, 1, -1).map(Divides<BigFloat>(1.0, none)).reduce1(Plus()));

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
	
	// 無限リスト
	Log(L"# InfiniteList");
	InfiniteList().take(5).each(Log);
	Log(InfiniteList(0, 0.01).take_while([](auto v){ return v * v < 0.1; }));
	InfiniteList<BigInt>(L"1000000000000000000000000000000000000000000000000000000"_big, 100).take(5).each(Log);

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

	// Regex
	Log(L"# Regex::Split");
	Log(Regex::Split(L"C++03 C++98   C++11 C++14	C++17", L"\\s+"));

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
	Log(stopwatch.format(L"S.xxx秒"));
	Log(stopwatch > 1.5s);

	// SpeedStopwatch
	Log(L"# SpeedStopwatch");
	SpeedStopwatch speedStopwatch(10.0, true);
	for (int32 i = 0; i <= 3; ++i)
	{
		Log(speedStopwatch);
		System::Sleep(1s);
	}

	// Timer
	Log(L"# Timer");
	Timer timer(3s, true);
	for (int32 i = 0; i <= 4; ++i)
	{
		Log(timer, L' ', timer.reachedZero());
		System::Sleep(1s);
	}

	// Date
	Log(L"# Date");
	Log(Date::Today());
	Log(Date::Today().format(L"yyyy年MM月dd日(E)"));
	Log(Date(2016, 12, 25) + 7_d);
 
	// DateTime
	Log(L"# DateTime");
	Log(DateTime::Now());
	Log(DateTime::Now() + 3min);
	Log(DateTime::NowUTC());
	
	// FileSystem
	Log(L"# FileSystem");

	Log(L"## Exists");
	Log(FileSystem::Exists(L"example/"));
	Log(FileSystem::Exists(L"example/siv3d-kun.png"));
	Log(FileSystem::Exists(L"example/aaa"));

	Log(L"## IsDirectory");
	Log(FileSystem::IsDirectory(L"example/"));
	Log(FileSystem::IsDirectory(L"example/siv3d-kun.png"));
	Log(FileSystem::IsDirectory(L"example/aaa"));
	
	Log(L"## IsFile");
	Log(FileSystem::IsFile(L"example/"));
	Log(FileSystem::IsFile(L"example/siv3d-kun.png"));
	Log(FileSystem::IsFile(L"example/aaa"));
	
	Log(L"## FullPath");
	Log(FileSystem::FullPath(L"example/windmill.png"));
	Log(FileSystem::FullPath(L"example/"));
	Log(FileSystem::FullPath(L"./"));
	Log(FileSystem::FullPath(L"./example/../"));

	Log(L"## Extension");
	Log(FileSystem::Extension(L"example/windmill.png"));
	
	Log(L"## FileName");
	Log(FileSystem::FileName(L"example/windmill.png"));
	
	Log(L"## BaseName");
	Log(FileSystem::BaseName(L"example/windmill.png"));
	
	Log(L"## ParentPath");
	Log(FileSystem::ParentPath(L"example/windmill.png"));
	Log(FileSystem::ParentPath(L"example/windmill.png", 0));
	Log(FileSystem::ParentPath(L"example/windmill.png", 1));
	Log(FileSystem::ParentPath(L"example/windmill.png", 2));
	Log(FileSystem::ParentPath(L"example/windmill.png", 3));
	
	Log(L"## VolumePath");
	Log(FileSystem::VolumePath(L"example/windmill.png"));
	
	Log(L"## NormalizedPath");
	Log(FileSystem::NormalizedPath(L"example/windmill.png"));
	Log(FileSystem::NormalizedPath(L"EXAMPLE/WINDMILL.png"));
	Log(FileSystem::NormalizedPath(L"example/../example/windmill.png"));

	Log(L"## IsEmpty");
	Log(FileSystem::IsEmpty(L"example/windmill.png"));
	Log(FileSystem::IsEmpty(L"example/"));
	Log(FileSystem::IsEmpty(L"example/empty/"));
	Log(FileSystem::IsEmpty(L"example/empty.bin"));

	Log(L"## Size");
	Log(FileSystem::Size(L"./"));
	Log(FileSystem::Size(L"example"));
	Log(FileSystem::Size(L"example/windmill.png"));
	Log(FileSystem::Size(L"example/aaa"));

	Log(L"## FileSize");
	Log(FileSystem::FileSize(L"./"));
	Log(FileSystem::FileSize(L"example"));
	Log(FileSystem::FileSize(L"example/windmill.png"));
	Log(FileSystem::FileSize(L"example/aaa"));
	
	Log(L"## CreationTime");
	Log(FileSystem::CreationTime(L"example/windmill.png"));

	Log(L"## WriteTime");
	Log(FileSystem::WriteTime(L"example/windmill.png"));
	
	Log(L"## AccessTime");
	Log(FileSystem::AccessTime(L"example/windmill.png"));
	
	Log(L"## DirectoryContents");
	FileSystem::DirectoryContents(L"Example", false).each(Log);
	
	Log(L"## DirectoryContents (recursive)");
	FileSystem::DirectoryContents(L"Example", true).each(Log);

	Log(L"## InitialPath");
	Log(FileSystem::InitialPath());
	
	Log(L"## CurrentPath");
	Log(FileSystem::CurrentPath());
	
	Log(L"## ModulePath");
	Log(FileSystem::ModulePath());

	Log(L"## SpecialFolderPath");
	Log(FileSystem::SpecialFolderPath(SpecialFolder::Desktop));
	Log(FileSystem::SpecialFolderPath(SpecialFolder::Documents));
	Log(FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData));
	Log(FileSystem::SpecialFolderPath(SpecialFolder::Music));
	Log(FileSystem::SpecialFolderPath(SpecialFolder::Pictures));
	Log(FileSystem::SpecialFolderPath(SpecialFolder::Videos));

	Log(L"## TempDirectoryPath");
	Log(FileSystem::TempDirectoryPath());

	Log(L"## RelativePath");
	Log(FileSystem::RelativePath(L"example/windmill.png", L"example/"));
	Log(FileSystem::RelativePath(L"../../", L"example/"));
	Log(FileSystem::RelativePath(L"./", L"./"));
		
	// TimeProfiler
	TimeProfiler tp;
	for (int32 i = 0; i < 50; ++i)
	{
		tp.begin(L"System::Sleep(20)");
		System::Sleep(20);
		tp.end();
	}
	//*/
}
