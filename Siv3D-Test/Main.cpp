
# include <Siv3D.hpp> // OpenSiv3D v0.2.3

void Main()
{
	const String def(U"abc");

	Optional<String> s;

	Print << s.value_or(def);

	INIData ini(U"example/test.ini");

	Print << ini.getOr<String>(U"Window.Title", def);

	CSVData csv(U"example/test.csv");

	Print << csv.getOr<String>(0, 0, def);

	while (System::Update())
	{
		
	}
}
