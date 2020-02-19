# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Print << Math::Lerp(10, 20, 0.6);
	Print << Math::InvLerp(10, 20, 16);

	while (System::Update())
	{

	}
}
