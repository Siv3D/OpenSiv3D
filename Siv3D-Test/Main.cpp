
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
	const FilePath scriptFilePath = FileSystem::FullPath(U"example/script.txt");
	const DirectoryWatcher watcher(FileSystem::ParentPath(scriptFilePath));

	//Script script(Arg::code = TextReader(scriptFilePath).readAll());
	Script script(scriptFilePath);
	if (!script)
	{
		return;
	}

	Print << U"----------------";
	Print << U"Compile...[{}]"_fmt(script.compiled() ? U"OK" : U"Failed");
	script.getMessages().each(Print);
	auto GetNumber = script.getFunction<int32()>(U"GetNumber");
	auto GetMessage = script.getFunction<String()>(U"GetMessage");
	auto Draw = script.getFunction<void()>(U"Draw");
	auto Draw2 = script.getFunction<void(const Stopwatch&)>(U"Draw2");
	//Print << GetNumber();
	//Print << GetMessage() << U"@" << GetMessage().size();

	Stopwatch s(true);

	while (System::Update())
	{
		const auto fileChanges = watcher.retrieveChanges();

		if (HasChanged(script.path(), fileChanges))
		{
			Print << U"----------------";
			const bool compileSucceeded = script.reload();
			Print << U"Recompile...[{}]"_fmt(compileSucceeded ? U"OK" : U"Failed");
			script.getMessages().each(Print);

			GetNumber = script.getFunction<int32()>(U"GetNumber");
			GetMessage = script.getFunction<String()>(U"GetMessage");
			Draw = script.getFunction<void()>(U"Draw");
			Draw2 = script.getFunction<void(const Stopwatch&)>(U"Draw2");
			//Print << GetNumber();
			//Print << GetMessage() << U"@" << GetMessage().size();
		}

		if (MouseR.down())
		{
			Draw();
		}

		//Draw2(s);
	}
}
