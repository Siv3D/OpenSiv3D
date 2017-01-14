
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (const auto dragOver = DragDrop::DragOver())
		{
			Window::SetTitle(L"");
		}

		if (DragDrop::HasNewFilePaths())
		{
			const FilePath path = DragDrop::GetDroppedFilePaths().back().path;

			Window::SetTitle(L"{} > [{}]"_fmt(FileSystem::FileName(path), Hash::MD5FromFile(path)));
		}
	}
}
