
# include <Siv3D.hpp>

void Main()
{
	Audio audio;
	FFTResult fft;
	bool hasChanged = false;

	while (System::Update())
	{
		//ClearPrint();	
		//Print << audio.posSample();

		const int32 posSec = static_cast<int32>(audio.posSec());
		const int32 lengthSec = static_cast<int32>(audio.lengthSec());
		const String time = U"{}:{:0>2}/{}:{:0>2}"_fmt(
			posSec / 60, posSec % 60, lengthSec / 60, lengthSec % 60);
		double progress = static_cast<double>(audio.posSample()) / audio.samples();

		if (SimpleGUI::Button(U"Play", Vec2(40, 380), 120, audio && !audio.isPlaying()))
		{
			audio.play(0.2s);
		}

		if (SimpleGUI::Button(U"Pause", Vec2(170, 380), 120, audio.isPlaying()))
		{
			audio.pause(0.2s);
		}

		if (SimpleGUI::Button(U"Open", Vec2(300, 380), 120))
		{
			audio.stop(0.5s);
			audio = Dialog::OpenAudio();
			audio.play();
		}

		if (SimpleGUI::Slider(time, progress, Vec2(40, 420), 130, 430, !audio.isEmpty()))
		{
			audio.pause(0.1s);
			audio.setPosSample(static_cast<int64>(audio.samples() * progress));
			hasChanged = true;
		}
		else if (hasChanged && MouseL.up())
		{
			audio.play(0.1s);
			hasChanged = false;
		}

		if (audio.isPlaying())
		{
			FFT::Analyze(fft, audio);

			for (auto i : step(640))
			{
				const double size = Pow(fft.buffer[i], 0.6f) * 800;

				RectF(Arg::bottomLeft(i, 360), 1, size).draw(HSV(240 - i));
			}
		}
	}
}
