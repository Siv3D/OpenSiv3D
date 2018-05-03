
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const Font font(40, Typeface::Medium);
	String text;
	Audio audio;
	Wave wave;

	while (System::Update())
	{
		font(text).draw(20, 20, Palette::Orange);

		if (KeySpace.down())
		{
			const uint8 inst = Random(0,127);
			const uint8 key = Random(50, 80);
			text = U"Instrument: {}\nKey: {}"_fmt(inst, key);

			wave = Wave(inst, key, 1.0s, 1.0);
			audio = Audio(wave);
			audio.play();
		}

		if (audio.isPlaying())
		{
			LineString lines;

			const size_t pos = audio.posSample();

			for (uint32 i = pos; i < std::min(wave.size() - 1, pos + 2560); ++i)
			{
				const double f = wave[i].left;

				lines.emplace_back((i-pos)*0.5, 360 - f * 360);
			}

			lines.draw(3, ColorF(0.0, 1.0, 1.0));
		}
		else
		{
			Line(0, 360, 1280, 360).draw(3, ColorF(0.0, 1.0, 1.0));
		}
	}
}
