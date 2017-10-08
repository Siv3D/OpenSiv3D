# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Optional<int> x = 1, y = none;
	
	Print << x
		.then([](int& a) { a += 5; })
		.map([](int a) { return L"value is " + ToString(a); })
		.map([](const String& s) { return s.length(); }, []() { return -1; });

	// size_t �� -1 �� common_type ����邽�߁A-1 �� size_t �ɃL���X�g����Ă��܂�
	Print << y
		.then([](int& a) { a += 5; })
		.map([](int a) { return ToString(a); })
		.map([](const String& s) { return s.length(); }, []() { return -1; });

	while (System::Update()) {
	}
}
