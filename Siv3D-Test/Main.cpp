
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();
	
	Log << Range(0, 100).sum();
	
	Log << Range(0_big, 100_big).sum();
	
	Log << step(Vec2(10,10), 5, Vec2(0.5,0.5));
	
	Log << step(Vec2(10,10), 5, Vec2(0.5,0.5)).sum();

	Log << step(String(L""), 5, L'.');

	Log << step(String(L""), 5, L'.').sum();
	
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

	while (System::Update())
	{
		if (KeyQ.down() && System::ShowMessageBox(L"アプリを終了します。", MessageBoxButtons::OKCancel)
			== MessageBoxSelection::OK)
		{
			break;
		}
	}
}
