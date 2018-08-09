
# include <Siv3D.hpp>

void Main()
{
	const Array<String> options = { U"オプション1", U"オプション2", U"オプション3", U"オプション4" };

	size_t index = 0;

	while (System::Update())
	{
		SimpleGUI::RadioButtons(index, options, Vec2(40, 40));
	}
}

