# include <Siv3D.hpp>

void Main()
{
	const TOMLReader reader(U"example/test.toml");

	if (!reader)
	{
		Logger(U"Failed to load.");
		return;
	}

	// key access
	Logger(U"table.key = ", reader[U"table"][U"key"].getString());

	// chained key access
	Logger(U"table.subtable.key = ", reader[U"table.subtable.key"].getString());

	// each table access and get integer
	for (auto&& p : reader[U"integer"].tableView())
	{
		if (p.value.isNumber())
		{
			Logger(U"integer." + p.name + U" = ", p.value.get<int64>());
		}
	}

	// get floating number
	Logger(U"float.fractional.key2 = ", reader[U"float.fractional.key2"].get<double>());

	// get boolean
	Logger(U"boolean.True = ", reader[U"boolean.True"].get<bool>());

	// get datetime
	Logger(U"datetime.key1 = ", reader[U"datetime.key1"].getDateTime());

	// get array (and format it)
	Logger(U"array.key1 = ", reader[U"array.key1"]);

	// get table array
	Logger(U"products = {");

	for (auto&& t : reader[U"products"].tableArrayView())
	{
		Logger(U"\t{");
		for (auto&& e : t.tableView())
		{
			Logger(U"\t\t", e.value, U",");
		}
		Logger(U"\t},");
	}
	Logger(U"}");

	while (System::Update())
	{

	}
}