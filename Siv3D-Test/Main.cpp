
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		if (KeyColon.down())
			Log << L"a";

		if (KeySemicolon.down())
			Log << L"b";

		if (KeyComma.down())
			Log << L"c";

		if (KeyMinus.down())
			Log << L"d";

		if (KeyPeriod.down())
			Log << L"e";

		if (KeySlash.down())
			Log << L"f";

		if (KeyGraveAccent.down())
			Log << L"g";

		if (KeyLBracket.down())
			Log << L"h";

		if (KeyYen.down())
			Log << L"i";

		if (KeyRBracket.down())
			Log << L"j";

		if (KeyCaret.down())
			Log << L"k";

		if (KeyBackslash.down())
			Log << L"l";
	}
}
