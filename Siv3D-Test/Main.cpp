# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Duration d = 35ms;

	Print << 10s;

	Print << d;

	for(auto i : step(10))
		Print << Random(0.4s, 1.6s);

	while (System::Update())
	{

	}
}
