
# include <Siv3D.hpp>

void Main()
{
	const String text = U"あいうえお";

	for (auto [i, ch] : Indexed(text))
	{

	}

	HashTable<int32, String> m = { { 1, U"Aaaa" },{ 2, U"Bbbb" },{ 3, U"Cccc" } };

	for (const auto[i, p] : Indexed(m))
	{

	}
}
