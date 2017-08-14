# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Audio audio(L"example/test.wav");
	audio.play();

	Window::SetTitle(audio.lengthSec());

	while (System::Update())
	{
		//Print << audio.posSample();
	}
}
