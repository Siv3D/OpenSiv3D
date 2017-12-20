# include <Siv3D.hpp>

void Main()
{
	const Audio audio(U"example/test.mp3", Arg::loop = true);

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		Print << audio.streamPosSample();

		Print << audio.posSample();

		Print << audio.samplesPlayed();
	}
}
