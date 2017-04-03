
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	Log << Array<Byte>{Byte(0), Byte(1), Byte(2), Byte(3), Byte(255)};
	
	int n = 255;

	Log << Byte(255);

	Log << ByteArray(&n, sizeof(n));

	Log << ByteArrayView(n);

	while (System::Update())
	{
		if (KeyQ.down() && System::ShowMessageBox(L"アプリを終了します。", MessageBoxButtons::OKCancel)
			== MessageBoxSelection::OK)
		{
			break;
		}
	}
}
