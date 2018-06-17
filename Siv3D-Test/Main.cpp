
# include <Siv3D.hpp>

void Main()
{
	const Array<FileFilter> filters =
	{
		{ U"PNG", { U"png" } },
		{ U"JPEG", { U"jpg", U"jpeg" } },
		{ U"BMP", { U"bmp" } },
		//{ U"All Files", {} },
	};
	
	while (System::Update())
	{
		if (KeyA.down())
		{
			Print << Dialog::OpenFile(filters);
		}

		if (KeyB.down())
		{
			Print << Dialog::OpenFiles(filters);
		}

		if (KeyC.down())
		{
			Print << Dialog::SaveFile(filters);
		}

		if (KeyD.down())
		{
			Print << Dialog::SelectFolder();
		}
	}
}



