# include <Siv3D.hpp> // OpenSiv3D v0.1.6

void Main()
{
	const Audio audio(L"example/test.wav");

	audio.play();

	uint64 max = 0, previous = 0;

	while (System::Update())
	{	
		const uint64 c = audio.posSample();

		if (c < previous)
		{
			max = previous;
		}

		previous = c;

		ClearPrint();
		Print << c;
		Print << max << L"/"  << audio.samples();

		if (Key1.down())
		{
			audio.play(0.1s);
		}

		if (Key2.down())
		{
			audio.pause(1s);
		}

		if (Key3.down())
		{
			audio.stop(1s);
		}

		if (Key4.down())
		{
			audio.setVolume_dB(-12);
		}
	}
}
