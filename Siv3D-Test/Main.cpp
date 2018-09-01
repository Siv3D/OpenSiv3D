
# include <Siv3D.hpp>

bool HasChanged(const FilePath& target, const Array<std::pair<FilePath, FileAction>>& fileChanges)
{
	for (auto[path, action] : fileChanges)
	{
		if ((path == target)
			&& (action == FileAction::Modified || action == FileAction::Added))
		{
			return true;
		}
	}

	return false;
}

void Main()
{
	Script script(U"example/script.txt");
	script.getMessages().each(Print);
	if (!script)
	{
		return;
	}

	bool requestReload = false;
	auto callback = [&requestReload, path = script.path(), watcher = DirectoryWatcher(FileSystem::ParentPath(script.path()))]()
	{
		requestReload = HasChanged(path, watcher.retrieveChanges());
		return !requestReload;
	};
	script.setSystemUpdateCallback(callback);
	
	auto ScriptMain = script.getFunction<void()>(U"Main");

	while (System::Update())
	{
		if (requestReload || !callback())
		{
			ClearPrint();
			script.reload();
			script.getMessages().each(Print);
			ScriptMain = script.getFunction<void()>(U"Main");
			requestReload = false;
		}

		ScriptMain();
	}
}
