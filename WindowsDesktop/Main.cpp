
# include <Siv3D.hpp> // OpenSiv3D v0.4.1 pre

void Main()
{
	//ChildProcess child = Process::Spawn(U"C:/Windows/System32/notepad.exe");
	//ChildProcess child = Process::Spawn(U"C:/Program Files (x86)/Google/Chrome/Application/chrome.exe", U"https://siv3d.github.io/");
	ChildProcess child = Process::Spawn(U"Console.exe", Pipe::StdInOut);

	if (!child)
	{
		return;
	}

	while (System::Update())
	{
		if (KeyT.down())
		{
			child.terminate(); // 強制的に終了
		}

		if (MouseR.down())
		{
			Print << child.isValid();
			Print << child.isRunning();
			Print << child.getExitCode();
		}
	}
}


