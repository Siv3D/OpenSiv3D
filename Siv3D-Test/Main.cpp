
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
			for (const auto& drop : DragDrop::GetDroppedFilePaths())
			{
				if (!FileSystem::IsFile(drop.path))
				{
					continue;
				}

				const String output = L"[{}] < {}"_fmt(
					Hash::MD5FromFile(drop.path),
					FileSystem::FileName(drop.path));

				Window::SetTitle(output);

				Console << output;
			}
		}
	}
}
