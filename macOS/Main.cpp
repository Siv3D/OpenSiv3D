
# include <Siv3D.hpp> // OpenSiv3D v0.4.0

void Main()
{
	//ChildProcess child = Process::Spawn(U"/Applications/Safari.app/Contents/MacOS/Safari",
	//									U"https://siv3d.github.io/ja-jp/", Pipe::StdInOut);
	ChildProcess child = Process::Spawn(U"/Applications/Google Chrome.app/Contents/MacOS/Google Chrome",
										U"https://siv3d.github.io/ja-jp/", Pipe::StdInOut);
	
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
