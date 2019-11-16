
# include <Siv3D.hpp>

void Main()
{
	const FilePath tomlPath = FileSystem::FullPath(U"example/gui/gui.toml");
	const DirectoryWatcher watcher(FileSystem::ParentPath(tomlPath));
	SimpleGUIManager gui(tomlPath);

	while (System::Update())
	{
		for (const auto& change : watcher.retrieveChanges())
		{
			if (change.first == tomlPath && change.second == FileAction::Modified)
			{
				ClearPrint();
				gui.load(tomlPath);
			}
		}

		gui.draw();

		if (gui.button(U"bt-OK"))
		{
			Print << U"OK";
		}
		else if (gui.button(U"bt-Cancel"))
		{
			Print << U"Cancel";
		}

		Scene::SetBackground(gui.colorPicker(U"cp-Color"));
	}

	//gui.save(U"save.toml");
}
