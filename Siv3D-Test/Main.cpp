
# include <Siv3D.hpp>

void Main()
{
	const XMLReader xml(U"example/test.xml");

	for (auto book = xml.firstChild(); book; book = book.nextSibling())
	{
		const auto id = book.attribute(U"id");

		Print << U"Book[{}]:"_fmt(id.value_or(U"?"));

		for (auto element = book.firstChild(); element; element = element.nextSibling())
		{
			Print << element.name() << U" = " << element.text();
		}
	}

	while (System::Update())
	{

	}
}
