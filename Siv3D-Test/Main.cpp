
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	while (System::Update())
	{
		if (Clipboard::HasChanged())
		{
			Log << L"HasChanged";

			if (Clipboard::HasText())
			{
				Log << L"HasText";

				Log << Clipboard::GetText();
			}
			else if (Clipboard::HasImage())
			{
				Log << L"HasImage";

				Clipboard::GetImage().save(L"{}.png"_fmt(Time::GetMillisec()));
			}
		}

		if (KeyT.down())
		{
			Clipboard::SetText(L"Siv3D あいうえお 𩸽だよ");
		}

		if (KeyS.down())
		{
			Clipboard::SetImage(Image(L"example/siv3d-kun.png"));
		}

		if (KeyW.down())
		{
			Clipboard::SetImage(Image(L"example/windmill.png"));
		}

		if (KeyQ.down() && System::ShowMessageBox(L"アプリを終了します。", MessageBoxButtons::OKCancel)
			== MessageBoxSelection::OK)
		{
			break;
		}
	}
}
