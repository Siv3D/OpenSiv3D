
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	ManagedScript script(U"example/script/paint.txt");

	while (System::Update())
	{
		script.run();
	}
}
