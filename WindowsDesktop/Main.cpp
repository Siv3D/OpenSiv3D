
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Print << U"(10 <=> 15): " << (10 <=> 15);
	Print << U"(10 <=> 10): " << (10 <=> 10);
	Print << U"(10 <=> 5): " << (10 <=> 5);

	Print << U"(5.5 <=> 7.5): " << (5.5 <=> 7.5);
	Print << U"(5.5 <=> 5.5): " << (5.5 <=> 5.5);
	Print << U"(5.5 <=> 2.5): " << (5.5 <=> 2.5);
	Print << U"(5.5 <=> Inf): " << (5.5 <=> Inf<double>);
	Print << U"(5.5 <=> NaN): " << (5.5 <=> QNaN<double>);

	while (System::Update())
	{

	}
}
