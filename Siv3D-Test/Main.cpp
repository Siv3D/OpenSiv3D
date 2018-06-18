# include <Siv3D.hpp> // OpenSiv3D v0.2.6

void Main()
{
	const Size size(128, 128);

	AnimatedGIFWriter gif(U"emoji.gif", size);

	const Font font(110, Typeface::Black);

	for (auto i : Range(1, 4))
	{
		Image image(size, Palette::White);

		font(i).paintAt(image, size / 2, HSV(i * 90, 0.9, 0.7));

		gif.writeFrame(image, 0.1s);
	}
}