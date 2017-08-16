# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Audio audio(L"example/test.mp3");
	audio.play();

	Window::SetTitle(audio.lengthSec());

	while (System::Update())
	{
		if (KeyP.down())
		{
			audio.play();
		}
		else if (KeyQ.down())
		{
			audio.pause();
		}
		
		//Print << audio.posSample();
		Print << audio.samplesPlayed();
	}
}
