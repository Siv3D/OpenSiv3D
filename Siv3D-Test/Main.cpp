# include <Siv3D.hpp>

void Main()
{
	const auto v = Array<int32>::Generate(20, RNG<int32>(1, 6));

	Print << v;


	const auto g = Grid<int32>::Generate(Size(5, 3), RNG<int32>(1, 6));

	Print << g;

	while (System::Update())
	{

	}
}
