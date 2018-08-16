
# include <Siv3D.hpp>

void Main()
{
	const Array<String> actions = 
	{
		U"Unknown", U"Added", U"Removed", U"Modified",
	};

	const DirectoryWatcher watcher(U"../");

	while (System::Update())
	{
		for (const auto& change : watcher.retrieveChanges())
		{
			Print << U"[{}]\n{}"_fmt(actions[(size_t)change.second], change.first);
		}
	}
}
