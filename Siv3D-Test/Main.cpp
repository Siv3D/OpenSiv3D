
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Key0.down())
		{
			System::ShowMessageBox(L"Quit?");
		}

		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));	
	}
}
