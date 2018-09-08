
# include <Siv3D.hpp>

void Main()
{
	const ManagedScript script(U"example/script.txt");

	while (System::Update())
	{
		script.run();
	}
}
