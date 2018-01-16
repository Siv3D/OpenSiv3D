# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 480);

	const Audio audio(U"example/test.mp3");

	audio.play();

	FFTResult result;

	while (System::Update())
	{
		FFT::Analyze(result, audio);

		for (auto i : step(Min(static_cast<int32>(result.buffer.size()), Window::Width() / 2)))
		{
			RectF(i * 2, Window::Height(), 2, -Pow(result.buffer[i], 0.6) * 1000).draw(HSV(240 - i));
		}
	}
}
