# include <Siv3D.hpp>

void Main()
{
	const Audio audio(U"test.mp3", Arg::loopBegin = 2s, Arg::loopEnd = 8s);

	const Audio sound(U"example/shot.mp3");

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		Print << audio.streamPosSample();

		Print << audio.posSample();

		//Logger << audio.posSample();
		
		Print << audio.samplesPlayed();
		
		if (Key1.down())
		{
			audio.play();
		}
		
		if (Key2.down())
		{
			audio.pause();
		}
		
		if (Key3.down())
		{
			audio.stop();
		}
		
		const double volume = Cursor::Pos().x / 640.0;
		const double speed = 1.0 + (Cursor::Pos().y - 320) / 320.0;
		
		Print << volume;
		Print << speed;
		
		audio.setVolume(volume);

	}
}
