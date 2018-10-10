
# include <Siv3D.hpp>

void Main()
{
	constexpr size_t readLength = 800;
	
	LineString lines(readLength);
	for (auto i : step(readLength))
	{
		lines[i].set(i, 150);
	}

	Microphone mic(unspecified);
	
	if (!mic)
	{
		return;
	}

	if (!mic.start())
	{
		return;
	}

	FFTResult fft;

	while (System::Update())
	{
		if (KeyA.down())
		{
			mic.stop();
		}

		if (KeyB.down())
		{
			mic.start();
		}

		const Array<WaveSampleS16>& buffer = mic.getBuffer();
		mic.fft(fft);
		
		for (size_t samplesLeft = readLength, pos = mic.posSample(); samplesLeft; --samplesLeft)
		{
			if (pos == 0)
			{
				pos = buffer.size();
			}

			const auto sample = buffer[--pos].asWaveSample();
			lines[samplesLeft - 1].y = 300 - (sample.left + sample.right) * 150;
		}

		ClearPrint();
		Print << mic.posSample();
		RectF(0, 50, mic.mean() * 800, 50).draw(ColorF(0.5));
		RectF(0, 150, mic.rootMeanSquare() * 800, 50).draw(ColorF(0.5));
		RectF(0, 250, mic.peak() * 800, 50).draw(ColorF(0.5));

		for (auto i : step(Min(static_cast<int32>(fft.buffer.size()), Window::Width())))
		{
			RectF(Arg::bottomLeft(i, Window::Height()), 1, fft.buffer[i] * Window::Height())
				.draw(HSV(240 - i));
		}

		lines.draw();
	}
}

void Main2()
{
	const size_t recordLength = Wave::DefaultSamplingRate * 5;
	Microphone mic(unspecified, RecordingFormat::Default, recordLength, false);
	
	if (!mic || !mic.start())
	{
		return;
	}

	FFTResult fft;
	
	while (System::Update())
	{
		const size_t pos = mic.posSample();

		if (pos == recordLength)
		{
			mic.saveBuffer(U"save.wav");
			break;
		}

		mic.fft(fft);

		ClearPrint();
		Print << pos;

		for (auto i : step(Min(static_cast<int32>(fft.buffer.size()), Window::Width())))
		{
			RectF(Arg::bottomLeft(i, Window::Height()), 1, fft.buffer[i] * Window::Height())
				.draw(HSV(240 - i));
		}
	}
}
