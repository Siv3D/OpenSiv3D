# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Optional<int> x = 1, y = none;
	
	Print << x
		.then([](int& a) { a += 5; })
		.map([](int a) { return L"value is " + ToString(a); })
		.map([](const String& s) { return s.length(); }, []() { return -1; });

	// size_t と -1 の common_type を取るため、-1 が size_t にキャストされてしまう
	Print << y
		.then([](int& a) { a += 5; })
		.map([](int a) { return ToString(a); })
		.map([](const String& s) { return s.length(); }, []() { return -1; });

	while (System::Update()) {
	}
}
