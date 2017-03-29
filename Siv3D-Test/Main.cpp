
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Key0.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Default);
		}

		if (Key1.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Info);
		}

		if (Key2.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Warning);
		}

		if (Key3.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Error);
		}

		if (Key4.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Question);
		}

		if (Key5.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxButtons::OKCancel);
		}

		if (Key6.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxButtons::YesNo);
		}

		if (Key7.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Warning, MessageBoxButtons::OKCancel);
		}

		if (Key8.down())
		{
			Log << (int)System::ShowMessageBox(L"Quit?", MessageBoxStyle::Error, MessageBoxButtons::YesNo);
		}

		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));	
	}
}
