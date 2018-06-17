
# include <Siv3D.hpp>

void Main()
{
	const Array<FileFilter> filters =
	{
		{ U"PNG Image", { U"png" } },
		{ U"JPEG Image", { U"jpg", U"jpeg" } },
		{ U"BMP Image", { U"bmp" } },
		//{ U"All Files", {} },
	};
	
	while (System::Update())
	{
		if (KeyA.down())
		{
			Print << Dialog::OpenFile(filters, FileSystem::SpecialFolderPath(SpecialFolder::Desktop), U"");
		}

		if (KeyB.down())
		{
			Print << Dialog::OpenFiles(filters, FileSystem::SpecialFolderPath(SpecialFolder::Desktop), U"");
		}

		if (KeyC.down())
		{
			Print << Dialog::SaveFile(filters, FileSystem::SpecialFolderPath(SpecialFolder::Desktop), U"保存する");
		}

		if (KeyD.down())
		{
			Print << Dialog::SelectFolder(FileSystem::SpecialFolderPath(SpecialFolder::Desktop), U"フォルダ");
		}

		Circle(Cursor::PosF(), 20).draw();
	}
}
