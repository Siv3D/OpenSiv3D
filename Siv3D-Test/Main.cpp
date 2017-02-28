
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		if (KeyColon_JP.down())
			Console << L"a-j";

		if (KeySemicolon_US.down())
			Console << L"a-u";

		if (KeySemicolon_JP.down())
			Console << L"b-j";

		if (KeyEqual_US.down())
			Console << L"b-u";

		if (KeyComma.down())
			Console << L"c";

		if (KeyMinus.down())
			Console << L"d";

		if (KeyPeriod.down())
			Console << L"e";

		if (KeySlash.down())
			Console << L"f";

		if (KeyGraveAccent.down())
			Console << L"g";

		if (KeyLBracket.down())
			Console << L"h";

		if (KeyYen_JP.down())
			Console << L"i-j";

		if (KeyBackslash_US.down())
			Console << L"i-u";

		if (KeyRBracket.down())
			Console << L"j";

		if (KeyCaret_JP.down())
			Console << L"k-j";

		if (KeyApostrophe_US.down())
			Console << L"k-u";

		if (KeyBackslash_JP.down())
			Console << L"l-j";
	}
}
