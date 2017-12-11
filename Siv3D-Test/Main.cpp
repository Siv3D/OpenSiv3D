# include <Siv3D.hpp>

void Main()
{
	const TOMLReader reader(U"ÉeÉXÉg(É≥É÷É≥).toml");
	TextWriter writer(U"test.txt");

	if (!reader)
	{
		writer.writeln(U"Failed to load.");
		return;
	}

	// key access
	writer.writeln(U"table.key = ", reader[U"table"][U"key"].getString());
	// chained key access
	writer.writeln(U"table.subtable.key = ", reader[U"table.subtable.key"].getString());

	// each table access and get integer
	for (auto&& p : reader[U"integer"].tableView())
	{
		if (p.value.isNumber())
		{
			writer.writeln(U"integer." + p.name + U" = ", p.value.get<int64>());
		}
	}

	// get floating number
	writer.writeln(U"float.fractional.key2 = ", reader[U"float.fractional.key2"].get<double>());

	// get boolean
	writer.writeln(U"boolean.True = ", reader[U"boolean.True"].get<bool>());

	// get datetime
	writer.writeln(U"datetime.key1 = ", reader[U"datetime.key1"].getDateTime());

	// get array (and format it)
	writer.writeln(U"array.key1 = ", reader[U"array.key1"]);

	// get table array
	writer.writeln(U"products = {");
	for (auto&& t : reader[U"products"].tableArrayView())
	{
		writer.writeln(U"\t{");
		for (auto&& e : t.tableView())
		{
			writer.writeln(U"\t\t", e.value, U",");
		}
		writer.writeln(U"\t},");
	}
	writer.writeln(U"}");

	while (System::Update())
	{
	}
}