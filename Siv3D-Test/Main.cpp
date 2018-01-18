
# include <Siv3D.hpp>

void Main()
{
	const Audio audio(U"example/test.mp3");
	
	audio.play();
	
	while (System::Update())
	{
		if (Key1.down())
		{
			audio.setSpeed(0.5);
		}
		else if (Key2.down())
		{
			audio.setSpeed(1.0);
		}
		else if (Key3.down())
		{
			audio.setSpeed(1.2);
		}
	}
}
