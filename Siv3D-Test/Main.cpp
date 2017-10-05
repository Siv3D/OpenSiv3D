# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Window::Resize(640, 640);

	const TOMLReader reader(L"test.toml");

	while (System::Update())
	{
		if (!reader)
		{
			Print << L"Failed to load.";
			continue;
		}

		Print << L"\n";
		// key access
		Print << L"table.key = " << reader[L"table"][L"key"].getString();
		// chained key access
		Print << L"table.subtable.key = " << reader[L"table.subtable.key"].getString();

		// each table access and get integer
		for (auto&& p : reader[L"integer"].tableView())
		{
			if (p.value.isNumber())
			{
				Print << L"integer." + p.name + L" = " << p.value.get<int64>();
			}
		}

		// get floating number
		Print << L"float.fractional.key2 = " << reader[L"float.fractional.key2"].get<double>();

		// get boolean
		Print << L"boolean.True = " << reader[L"boolean.True"].get<bool>();

		// get datetime
		Print << L"datetime.key1 = " << reader[L"datetime.key1"].getDateTime();

		// get array (and formatting)
		Print << L"array.key1 = " << reader[L"array.key1"];

		// get table array
		Print << L"products = {";
		for (auto&& t : reader[L"products"].tableArrayView())
		{
			Print << L"\t{";
			for (auto&& e : t.tableView())
			{
				Print << L"\t\t" << e.value << L",";
			}
			Print << L"\t},";
		}
		Print << L"}";
	}
}
