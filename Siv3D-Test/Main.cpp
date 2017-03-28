
# include <Siv3D.hpp>

void Main()
{
	Log << L"Hello, Siv3D!";

	/////////////////////////////////////////////////
	//
	//	Range
	//
	/////////////////////////////////////////////////

	// 0～100 の範囲
	Log << L"# Range(0, 100)";
	Log << Range(0, 100);

	// 0～100 の合計
	Log << L"# Range(0, 100).sum()";
	Log << Range(0, 100).sum();

	// 1/1 + 1/2 + 1/3 + 1/4 + ... + 1/10000 の合計
	Log << L"# Range(1, 10000).map(Divides(1.0, none)).sum())";
	Log << 18_dp << Range(10000, 1, -1).map(Divides(1.0, none)).sum();
	Log << Range(10000, 1, -1).map(Divides<BigFloat>(1.0, none)).sum();
	Log << L"9.78760603604438226417847790485160533485926294557769171838946095668160202494315950680012512729008088259135976018399338...";

	// 0～100 のうち 20 未満の個数
	Log << L"# Range(0, 100).count_if(LessThan(20))";
	Log << Range(0, 100).count_if(LessThan(20));

	// 0～10 の範囲の奇数
	Log << L"# Range(0, 10).filter(IsOdd)";
	Log << Range(0, 10).filter(IsOdd);

	// 100 の階乗
	Log << L"# Range(1, 100).reduce1(Multiplies<BigInt>())";
	Log << Range(1, 100).reduce1(Multiplies<BigInt>());

	// FizzBuzz
	Log << L"#FizzBuzz";
	Log << Range(1, 20).map([](auto n) { return n % 15 == 0 ? L"FizzBuzz" : n % 3 == 0 ? L"Fizz" : n % 5 == 0 ? L"Buzz" : Format(n); });

	// フィボナッチ数列
	BigInt a = 0, b = 1;
	Log << L"# Fibbonaci";
	Log << a << L'\n' << b;
	Range(1, 100).map([&a, &b](auto) { a = std::exchange(b, a + b); return b; }).each(Log);

	/////////////////////////////////////////////////
	//
	//	InfiniteList
	//
	/////////////////////////////////////////////////

	// 無限リスト
	Log << L"# InfiniteList";
	Log << InfiniteList().take(5);
	Log << InfiniteList(0, 0.01).take_while([](auto v) { return v * v < 0.1; });
	InfiniteList<BigInt>(L"1000000000000000000000000000000000000000000000000000000"_big, 100).take(5).each(Log);

	// 111122223333 以上の素数を近い順に 5 つ探す
	Log << InfiniteList(111122223333).filter(IsPrime).take(5);

	/////////////////////////////////////////////////
	//
	//	Array
	//
	/////////////////////////////////////////////////

	// 0〜9 の数をシャッフル
	Log << L"# Range(0, 9).asArray().shuffle()";
	Log << Range(0, 9).asArray().shuffle();

	// 4 人にポーカーの札を配る
	Log << Iota(13 * 4).map([](int32 n) { return Format(L"♦♣♥♠"[n / 13], (n % 13 + 1)); }).asArray().shuffle().take(20).chunk(5);

	/////////////////////////////////////////////////
	//
	//	Grid
	//
	/////////////////////////////////////////////////

	// Grid
	Log << L"# Grid";
	Log << Grid<int32>{ { 10, 20, 30, 40 }, { 11, 22, 33, 44 }, { 50, 51, 52, 53 } };

	// Grid from Range
	Log << L"# Grid from Range";
	Log << Grid<int32>(10, 10, Range(0, 99));

	/////////////////////////////////////////////////
	//
	//	Format
	//
	/////////////////////////////////////////////////

	// Format
	Log << L"# Format";
	Log(2016, L'/', 5, L'/', 7);
	Log << L"{}/{}/{}"_fmt(2016, 5, 17);
	Log << L"{2}/{1}/{0}"_fmt(2016, 5, 17);
	Log << 31415.9265358979;
	Log << 314.159265358979;
	Log << 3.14159265358979;

	// 右寄せと詰め文字
	Log << L"# {:>PN}_fmt(5)";
	Log << L"{:>1}"_fmt(5);
	Log << L"{:>2}"_fmt(5);
	Log << L"{:>3}"_fmt(5);
	Log << L"{:>4}"_fmt(5);
	Log << L"{:>5}"_fmt(5);
	Log << L"{:0>1}"_fmt(5);
	Log << L"{:0>2}"_fmt(5);
	Log << L"{:0>3}"_fmt(5);
	Log << L"{:0>4}"_fmt(5);
	Log << L"{:0>5}"_fmt(5);
	Log << L"{:*>1}"_fmt(5);
	Log << L"{:*>2}"_fmt(5);
	Log << L"{:*>3}"_fmt(5);
	Log << L"{:*>4}"_fmt(5);
	Log << L"{:*>5}"_fmt(5);

	// 左寄せと詰め文字
	Log << L"# {:<PN}_fmt(5)";
	Log << L"{:<1}"_fmt(5);
	Log << L"{:<2}"_fmt(5);
	Log << L"{:<3}"_fmt(5);
	Log << L"{:<4}"_fmt(5);
	Log << L"{:<5}"_fmt(5);
	Log << L"{:0<1}"_fmt(5);
	Log << L"{:0<2}"_fmt(5);
	Log << L"{:0<3}"_fmt(5);
	Log << L"{:0<4}"_fmt(5);
	Log << L"{:0<5}"_fmt(5);
	Log << L"{:*<1}"_fmt(5);
	Log << L"{:*<2}"_fmt(5);
	Log << L"{:*<3}"_fmt(5);
	Log << L"{:*<4}"_fmt(5);
	Log << L"{:*<5}"_fmt(5);

	// 中央寄せと詰め文字
	Log << L"# {:^PN}_fmt(5)";
	Log << L"{:^1}"_fmt(5);
	Log << L"{:^2}"_fmt(5);
	Log << L"{:^3}"_fmt(5);
	Log << L"{:^4}"_fmt(5);
	Log << L"{:^5}"_fmt(5);
	Log << L"{:0^1}"_fmt(5);
	Log << L"{:0^2}"_fmt(5);
	Log << L"{:0^3}"_fmt(5);
	Log << L"{:0^4}"_fmt(5);
	Log << L"{:0^5}"_fmt(5);
	Log << L"{:*^1}"_fmt(5);
	Log << L"{:*^2}"_fmt(5);
	Log << L"{:*^3}"_fmt(5);
	Log << L"{:*^4}"_fmt(5);
	Log << L"{:*^5}"_fmt(5);

	// 二進数、八進数、十六進数
	Log << L"bin: {0:#b}, oct: {0:#o}, hex: {0:#x}"_fmt(255);

	// 小数点以下の桁数指定（0 は省略）
	Log << L"# ToString(double)";
	Log << ToString(1.234, 0);
	Log << ToString(1.234, 1);
	Log << ToString(1.234, 2);
	Log << ToString(1.234, 3);
	Log << ToString(1.234, 4);
	Log << ToString(1.234, 5);

	// 小数点以下の桁数指定（0 は省略）
	Log << L"# DecimalPlace";
	Log << 0_dp << 1.234;
	Log << 1_dp << 1.234;
	Log << 2_dp << 1.234;
	Log << 3_dp << 1.234;
	Log << 4_dp << 1.234;
	Log << 5_dp << 1.234;

	// 小数点以下の桁数指定（0 も表示）
	Log << L"# ToFixed(double)";
	Log << ToFixed(1.234, 0);
	Log << ToFixed(1.234, 1);
	Log << ToFixed(1.234, 2);
	Log << ToFixed(1.234, 3);
	Log << ToFixed(1.234, 4);
	Log << ToFixed(1.234, 5);

	// 小数点以下の桁数指定（0 も表示）
	Log << L"# {:.Nf}_fmt(double)";
	Log << L"{:.0f}"_fmt(1.234);
	Log << L"{:.1f}"_fmt(1.234);
	Log << L"{:.2f}"_fmt(1.234);
	Log << L"{:.3f}"_fmt(1.234);
	Log << L"{:.4f}"_fmt(1.234);
	Log << L"{:.5f}"_fmt(1.234);

	/////////////////////////////////////////////////
	//
	//	FormatUtility
	//
	/////////////////////////////////////////////////

	// 詰め文字
	Log << L"# Pad";
	Log << Pad(123, { 1, L'0' });
	Log << Pad(123, { 2, L'0' });
	Log << Pad(123, { 3, L'0' });
	Log << Pad(123, { 4, L'0' });
	Log << Pad(123, { 5, L'0' });
	Log << Pad(123, { 6, L'0' });
	Log << Pad(L"abc", { 1, L'#' });
	Log << Pad(L"abc", { 2, L'#' });
	Log << Pad(L"abc", { 3, L'#' });
	Log << Pad(L"abc", { 4, L'#' });
	Log << Pad(L"abc", { 5, L'#' });
	Log << Pad(L"abc", { 6, L'#' });

	// 千ごとの桁区切り
	Log << L"# ThousandsSeparate";
	Log << ThousandsSeparate(10000000);
	Log << ThousandsSeparate(10000000, L"'");
	Log << ThousandsSeparate(50000.123456789);
	Log << ThousandsSeparate(50000.123456789, 9);
	Log << ThousandsSeparate(5000.1, 3, true);
	Log << ThousandsSeparate(5000.1, 9, true);
	Log << ThousandsSeparate(5000.1, 3, true, L"'");
	Log << ThousandsSeparate(5000.1, 9, true, L"'");

	/////////////////////////////////////////////////
	//
	//	BigInt
	//
	/////////////////////////////////////////////////

	// BigInt
	Log << L"# BigInt";
	Log << "100000000000000000000000000000000000000000000000000000000000000000000000000000001"_big * 1234567890;

	/////////////////////////////////////////////////
	//
	//	String
	//
	/////////////////////////////////////////////////

	// String
	Log << L"# String";
	const String str = L"Siv3D";
	Log << str;
	Log << str.uppercased();
	Log << str.lowercased();
	Log << str.reversed();
	Log << str.includes(L"3D");
	Log << str.starts_with(L"Si");
	Log << str.ends_with(L"v3D");

	/////////////////////////////////////////////////
	//
	//	Parse
	//
	/////////////////////////////////////////////////

	// Parse
	Log << L"# Parse";
	const int32 parsed0 = Parse<int32>(L"12345");
	const double parsed1 = Parse<double>(L" 3.1415 ");
	const int32 parsed2 = ParseOr<int32>(L"???", 42);
	const double parsed3 = ParseOr<double>(L"5.55", 42);
	Log << parsed0;
	Log << parsed1;
	Log << parsed2;
	Log << parsed3;
	Log << ParseOpt<int32>(L"???");
	Log << ParseOpt<double>(L"7.77");

	/////////////////////////////////////////////////
	//
	//	Regex
	//
	/////////////////////////////////////////////////

	// Regex
	Log << L"# Regex::Split";
	Log << Regex::Split(L"C++03 C++98   C++11 C++14	C++17", L"\\s+");

	/////////////////////////////////////////////////
	//
	//	Duration
	//
	/////////////////////////////////////////////////

	// Duration
	Log << L"# Duration";
	Log << 1_d + 24h;
	Log << DurationCast<HoursF>(60min + 30min);
	Log << DurationCast<Seconds>(1_d);

	/////////////////////////////////////////////////
	//
	//	Date
	//
	/////////////////////////////////////////////////

	// Date
	Log << L"# Date";
	Log << Date::Today();
	Log << Date::Today().format(L"yyyy年MM月dd日(E)");
	Log << Date(2016, 12, 25) + 7_d;

	/////////////////////////////////////////////////
	//
	//	DateTime
	//
	/////////////////////////////////////////////////

	// DateTime
	Log << L"# DateTime";
	Log << DateTime::Now();
	Log << DateTime::Now() + 3min;
	Log << DateTime::NowUTC();

	/////////////////////////////////////////////////
	//
	//	Time
	//
	/////////////////////////////////////////////////

	// Time
	Log << L"# Time";
	Log << Time::GetSec();
	Log << Time::GetMillisec();
	Log << Time::GetMicrosec();
	Log << Time::GetNanosec();
	Log << Time::GetSecSinceEpoch();
	Log << Time::GetMillisecSinceEpoch();
	Log << Time::GetMicrosecSinceEpoch();

	/////////////////////////////////////////////////
	//
	//	Stopwatch
	//
	/////////////////////////////////////////////////

	//// Stopwatch
	//Log << L"# Stopwatch";
	//Stopwatch stopwatch(true);
	//System::Sleep(1.5s);
	//Log << stopwatch;
	//Log << stopwatch.format(L"S.xxx秒");
	//Log << (stopwatch > 1.5s);

	/////////////////////////////////////////////////
	//
	//	SpeedStopwatch
	//
	/////////////////////////////////////////////////

	//// SpeedStopwatch
	//Log << L"# SpeedStopwatch";
	//SpeedStopwatch speedStopwatch(10.0, true);
	//for (int32 i = 0; i <= 3; ++i)
	//{
	//	Log << speedStopwatch;
	//	System::Sleep(1s);
	//}

	/////////////////////////////////////////////////
	//
	//	Timer
	//
	/////////////////////////////////////////////////

	//// Timer
	//Log << L"# Timer";
	//Timer timer(3s, true);
	//for (int32 i = 0; i <= 4; ++i)
	//{
	//	Log << timer << L' ' << timer.reachedZero();
	//	System::Sleep(1s);
	//}

	/////////////////////////////////////////////////
	//
	//	TimeProfiler
	//
	/////////////////////////////////////////////////

	//// TimeProfiler
	//{
	//	TimeProfiler tp;
	//
	//	for (int32 i = 0; i < 20; ++i)
	//	{
	//		tp.begin(L"System::Sleep(20)");
	//		System::Sleep(20);
	//		tp.end();
	//	}
	//}

	/////////////////////////////////////////////////
	//
	//	RDTSCClock
	//
	/////////////////////////////////////////////////

	// CPU サイクルカウンター
	Log << L"# RDTSCClock";

	RDTSCClock rdtsc;
	{
		System::Sleep(100ms);
	}
	rdtsc.log();

	/////////////////////////////////////////////////
	//
	//	FileSystem
	//
	/////////////////////////////////////////////////

	// FileSystem
	Log << L"# FileSystem";
	Log << L"## Exists";
	Log << FileSystem::Exists(L"example/");
	Log << FileSystem::Exists(L"example/siv3d-kun.png");
	Log << FileSystem::Exists(L"example/aaa");
	Log << L"## IsDirectory";
	Log << FileSystem::IsDirectory(L"example/");
	Log << FileSystem::IsDirectory(L"example/siv3d-kun.png");
	Log << FileSystem::IsDirectory(L"example/aaa");

	Log << L"## IsFile";
	Log << FileSystem::IsFile(L"example/");
	Log << FileSystem::IsFile(L"example/siv3d-kun.png");
	Log << FileSystem::IsFile(L"example/aaa");

	Log << L"## FullPath";
	Log << FileSystem::FullPath(L"example/windmill.png");
	Log << FileSystem::FullPath(L"example/");
	Log << FileSystem::FullPath(L"./");
	Log << FileSystem::FullPath(L"./example/../");
	Log << L"## Extension";
	Log << FileSystem::Extension(L"example/windmill.png");

	Log << L"## FileName";
	Log << FileSystem::FileName(L"example/windmill.png");

	Log << L"## BaseName";
	Log << FileSystem::BaseName(L"example/windmill.png");

	Log << L"## ParentPath";
	Log << FileSystem::ParentPath(L"example/windmill.png");
	Log << FileSystem::ParentPath(L"example/windmill.png", 0);
	Log << FileSystem::ParentPath(L"example/windmill.png", 1);
	Log << FileSystem::ParentPath(L"example/windmill.png", 2);
	Log << FileSystem::ParentPath(L"example/windmill.png", 3);

	Log << L"## VolumePath";
	Log << FileSystem::VolumePath(L"example/windmill.png");

	Log << L"## NormalizedPath";
	Log << FileSystem::NormalizedPath(L"example/windmill.png");
	Log << FileSystem::NormalizedPath(L"EXAMPLE/WINDMILL.png");
	Log << FileSystem::NormalizedPath(L"example/../example/windmill.png");
	Log << L"## IsEmpty";
	Log << FileSystem::IsEmpty(L"example/windmill.png");
	Log << FileSystem::IsEmpty(L"example/");
	Log << FileSystem::IsEmpty(L"example/empty/");
	Log << FileSystem::IsEmpty(L"example/empty.bin");
	Log << L"## Size";
	Log << FileSystem::Size(L"./");
	Log << FileSystem::Size(L"example");
	Log << FileSystem::Size(L"example/windmill.png");
	Log << FileSystem::Size(L"example/aaa");
	Log << L"## FileSize";
	Log << FileSystem::FileSize(L"./");
	Log << FileSystem::FileSize(L"example");
	Log << FileSystem::FileSize(L"example/windmill.png");
	Log << FileSystem::FileSize(L"example/aaa");

	Log << L"## CreationTime";
	Log << FileSystem::CreationTime(L"example/windmill.png");
	Log << L"## WriteTime";
	Log << FileSystem::WriteTime(L"example/windmill.png");

	Log << L"## AccessTime";
	Log << FileSystem::AccessTime(L"example/windmill.png");

	Log << L"## DirectoryContents";
	FileSystem::DirectoryContents(L"Example", false).each(Log);

	Log << L"## DirectoryContents (recursive)";
	FileSystem::DirectoryContents(L"Example", true).each(Log);
	Log << L"## InitialPath";
	Log << FileSystem::InitialPath();

	Log << L"## CurrentPath";
	Log << FileSystem::CurrentPath();

	Log << L"## ModulePath";
	Log << FileSystem::ModulePath();
	Log << L"## SpecialFolderPath";
	Log << FileSystem::SpecialFolderPath(SpecialFolder::Desktop);
	Log << FileSystem::SpecialFolderPath(SpecialFolder::Documents);
	Log << FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData);
	Log << FileSystem::SpecialFolderPath(SpecialFolder::Music);
	Log << FileSystem::SpecialFolderPath(SpecialFolder::Pictures);
	Log << FileSystem::SpecialFolderPath(SpecialFolder::Videos);
	Log << L"## TempDirectoryPath";
	Log << FileSystem::TempDirectoryPath();
	Log << L"## RelativePath";
	Log << FileSystem::RelativePath(L"example/windmill.png", L"example/");
	Log << FileSystem::RelativePath(L"../../", L"example/");
	Log << FileSystem::RelativePath(L"./", L"./");

	/////////////////////////////////////////////////
	//
	//	CharacterEncoding
	//
	/////////////////////////////////////////////////

	Log << L"# GetEncoding";
	Log << (int32)CharacterSet::GetEncoding(L"example/test.ini");

	/////////////////////////////////////////////////
	//
	//	TextReader
	//
	/////////////////////////////////////////////////

	Log << L"# TextReader";
	{
		TextReader reader(L"example/test.txt");

		String line;

		while (reader.readLine(line))
		{
			Log << line;
		}
	}

	/////////////////////////////////////////////////
	//
	//	Base64
	//
	/////////////////////////////////////////////////

	Log << L"# Base64";
	{
		const String base64 = Base64::Encode(String(L"Siv3D"));
		ByteArray decoded = Base64::Decode(base64);

		String text;
		text.resize(static_cast<size_t>(decoded.size() / sizeof(wchar)));
		decoded.read(text.data(), decoded.size());

		Log << base64;
		Log << text;
	}

	/////////////////////////////////////////////////
	//
	//	MD5
	//
	/////////////////////////////////////////////////

	Log << L"# MD5";
	Log << Hash::MD5(42);
	Log << Hash::MD5FromFile(L"example/windmill.png");
	Log << Hash::MD5FromString(u8"Hello, world!");

	/////////////////////////////////////////////////
	//
	//	XXHash
	//
	/////////////////////////////////////////////////

	Log << L"# XXHash";
	Log << Hash::XXHash(42);
	Log << Hash::XXHashFromFile(L"example/windmill.png");

	/////////////////////////////////////////////////
	//
	//	INIReader
	//
	/////////////////////////////////////////////////

	const INIReader ini(L"example/test.ini");

	Log << L"# INIReader";

	// すべてのデータを列挙	
	for (const auto& key : ini)
	{
		Log << key.section << L"." << key.name << L"=" << key.value;
	}

	// Section を列挙
	Log << L"## INIReader::sections()";

	for (const auto& section : ini.sections())
	{
		Log << section;
	}

	// 指定した Section のキーを列挙
	Log << L"## INIReader::operator[]";

	for (const auto& key : ini[L"Window"])
	{
		Log << key.name << L"=" << key.value;
	}

	// 指定した Section が存在するか調べる
	Log << L"## INIReader::hasSection()";
	Log << ini.hasSection(L"Window");
	Log << ini.hasSection(L"World");

	// 指定した Section と Name が存在するか調べる
	Log << L"## INIReader::hasKey()";
	Log << ini.hasKey(L"Window.width");
	Log << ini.hasKey(L"Window.visibility");

	Log << L"## INIReader::get()";
	Log << ini.get<int32>(L"Window.width");
	Log << ini.get<Color>(L"Window.backgroundColor");
	Log << ini.get<int32>(L"Window.aaa");

	Log << L"## INIReader::getOr()";
	Log << ini.getOr<int32>(L"Window.width", 1280);
	Log << ini.getOr<Color>(L"Window.backgroundColor", Color(255));
	Log << ini.getOr<int32>(L"Window.aaa", 123);

	Log << L"## INIReader::getOpt()";
	Log << ini.getOpt<int32>(L"Window.width");
	Log << ini.getOpt<Color>(L"Window.backgroundColor");
	Log << ini.getOpt<int32>(L"Window.aaa");

	/////////////////////////////////////////////////
	//
	//	Rectangle
	//
	/////////////////////////////////////////////////

	// Rect
	Log << L"# Rect";
	Log << AreEqual(
		Rect(0, 0, 100),
		Rect(Arg::center(50, 50), 100),
		Rect(Arg::topLeft(0, 0), 100),
		Rect(Arg::topRight(100, 0), 100),
		Rect(Arg::bottomLeft(0, 100), 100),
		Rect(Arg::bottomRight(100, 100), 100));

	/////////////////////////////////////////////////
	//
	//	MathParser
	//
	/////////////////////////////////////////////////

	Log << L"# MathParser";

	Log << L"## Eval";
	Log << Eval(L"2 + 10 * 4");
	Log << Eval(L"2 + 10 * 4 +");

	Log << L"## EvalOpt";
	Log << EvalOpt(L"2 + 10 * 4");
	Log << EvalOpt(L"2 + 10 * 4 +");

	Log << L"## MathParser";
	{
		double x = 14.0, y = -6.0;
		MathParser math(L"x + abs(y) + Pi");
		math.setConstant(L"Pi", Math::Pi);
		math.setVaribale(L"x", &x);
		math.setVaribale(L"y", &y);

		Log << math.getExpression();
		Log << math.eval();
		y = -16.0;
		Log << math.eval();

		math.setFunction(L"f", [](double x) { return 2 * x; });
		math.setExpression(L"f(x + y)");

		Log << math.getExpression();
		Log << math.eval();
	}

	/////////////////////////////////////////////////
	//
	//	Image
	//
	/////////////////////////////////////////////////

	Image(L"example/siv3d-kun.png").save(L"test/output1.png");

	Image(200, 200, Arg::generator0_1 = ([](Vec2 pos)
	{
		pos = pos * 2 - Vec2(1, 1);

		double c = 0.0;

		for (int32 i = 0; i < 20; ++i)
		{
			c += 0.02 / pos.distanceFrom(0.8 * Vec2(cos(Math::Pi * i / 10), sin(Math::Pi * i / 10)));
		}

		return ColorF(c);
	}))
		.save(L"test/output2.png");

	/////////////////////////////////////////////////
	//
	//	Monitor
	//
	/////////////////////////////////////////////////

	Log << L"# Monitor";

	for (const auto& monitor : System::EnumActiveMonitors())
	{
		Log << L"-- " << monitor.name;
		Log << L"Display rect: " << monitor.displayRect;
		Log << L"Work area: " << monitor.workArea;
	}

	/////////////////////////////////////////////////
	//
	//	Full screen resolutions
	//
	/////////////////////////////////////////////////

	Log << L"# Full screen resolutions";

	for (const auto& displayOutput : Graphics::EnumOutputs())
	{
		Log << L"-- " << displayOutput.name;
		Log << displayOutput.displayModes.map([](const auto& displayMode) {
			return Format(displayMode.size, L"@", displayMode.refreshRateHz, L"Hz");
		});
	}

	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2, 1.0 - Cursor::Pos().y * 0.001));

		/////////////////////////////////////////////////
		//
		//	DragDrop
		//
		/////////////////////////////////////////////////

		if (DragDrop::HasNewFilePaths())
		{
			for (const auto& drop : DragDrop::GetDroppedFilePaths())
			{
				Log << drop.path << L", " << drop.pos << L", " << drop.timeMillisec;
			}
		}

		/////////////////////////////////////////////////
		//
		//	Cursor, Mouse
		//
		/////////////////////////////////////////////////

		Window::SetTitle(L"{}, wheel: {}, wheelH: {} "_fmt(Cursor::Pos(), Mouse::Wheel(), Mouse::WheelH()));

		if (MouseL.down())
		{
			Log << MouseL << L": down";
		}

		if (MouseL.pressed())
		{
			Log << MouseL << L": pressed";
		}

		if (MouseL.up())
		{
			Log << MouseL << L": up";
		}

		/////////////////////////////////////////////////
		//
		//	Key
		//
		/////////////////////////////////////////////////

		if (KeySpace.down())
		{
			Log << KeySpace << L": down";
		}

		if (KeyA.down())
		{
			Log << KeyA << L": down";
		}

		if ((MouseR | (KeyControl + KeyC) | (KeyCommand + KeyC)).down())
		{
			Log << (MouseR | (KeyControl + KeyC) | (KeyCommand + KeyC)) << L": down";
		}

		/////////////////////////////////////////////////
		//
		//	Window
		//
		/////////////////////////////////////////////////
		
		if (KeyC.down())
		{
			Window::Centering();
		}

		if (KeyR.down())
		{
			Graphics::SetFullScreen(false, Size(1280, 720));
		}
	}
}
