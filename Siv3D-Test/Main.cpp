# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	Print << Byte(20);

	Print << Concept::HasPlus_v<int32>;

	Print << Concept::HasPlus_v<Wave>;

	if constexpr (Concept::HasPlus_v<int32, String>)
	{
		Print << L"hi";
	}

	while (System::Update())
	{

	}
}