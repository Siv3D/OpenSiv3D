
# include <Siv3D.hpp>

void Main()
{
	Log << (Iota(13 * 4).map([](int32 n) { return Format(L"♦♣♥♠"[n / 13], n % 13 + 1); }).asArray() << L"Joker").shuffle().in_groups(5);
}

