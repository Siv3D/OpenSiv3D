
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	int frame = 0;
	
	while (System::Update())
	{
		++frame;
		
		if (Clipboard::HasChanged())
		{
			//Log << frame;
			
			Log << L"HasChanged";

			if (Clipboard::HasText())
			{
				Log << L"HasText";

				Log << Clipboard::GetText();
			}
			
			if (Clipboard::HasImage())
			{
				Log << L"HasImage";

				Log << Clipboard::GetImage().size();
				
				Clipboard::GetImage().save(L"{}.png"_fmt(Time::GetMillisec()));
			}
			
			if (Clipboard::HasFilePaths())
			{
				Log << L"HasFilePaths";
				
				Log << Clipboard::GetFilePaths();
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
		
		if (KeyC.down())
		{
			Clipboard::Clear();
		}

		if (KeyQ.down() && System::ShowMessageBox(L"アプリを終了します。", MessageBoxButtons::OKCancel)
			== MessageBoxSelection::OK)
		{
			break;
		}
	}
}
