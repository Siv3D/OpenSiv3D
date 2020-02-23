
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Reseed(123);

	SFMT19937_64 smft;
	smft.deserialize(GetDefaultRNG().serialize());

	for (auto i : step(10))
	{
		Print << (Random() == smft.generateReal());
	}

	while (System::Update())
	{

	}
}
