# include <Siv3D.hpp>

void Main()
{
	const Audio audio(U"example/test.mp3", Arg::loop = true);

	const Audio sound(U"example/sound.mp3");

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		Print << audio.streamPosSample();

		Print << audio.posSample();

		Print << audio.samplesPlayed();

		if (KeySpace.down())
			sound.playOneShot(0.5, Random(0.8,1.2));
	}
}
