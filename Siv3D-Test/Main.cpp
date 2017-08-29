# include <Siv3D.hpp> // OpenSiv3D v0.1.7

void Main()
{
	Range(0, 10) >> Square >> Multiplies(0.1) >> Print;

	while (System::Update())
	{

	}
}
