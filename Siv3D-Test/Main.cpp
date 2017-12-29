# include <Siv3D.hpp>

void Main()
{
	const Audio audio(U"test.mp3", Arg::loop = false);

	const Audio sound(U"example/shot.mp3");

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		Print << audio.streamPosSample();

		Print << audio.posSample();

		//Logger << audio.posSample();
		
		Print << audio.samplesPlayed();
		
		if (KeyP.down())
		{
			audio.pause();
		}
		
		if (KeyR.down())
		{
			audio.play();
		}
	}
}
