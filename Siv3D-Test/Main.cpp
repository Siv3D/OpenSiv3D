
# include <Siv3D.hpp> // OpenSiv3D v0.2.6

void Main()
{
	Window::Resize(1280, 720);

	const Font font(40, Typeface::Bold);

	QRDecoder decoder;

	DynamicTexture texture;

	Image image;

	Webcam webcam;

	Print << webcam.setResolution(1920, 1080);

	Print << webcam.getResolution();

	webcam.start();

	QRContent qrContent;

	while (System::Update())
	{
		if (webcam.hasNewFrame())
		{
			webcam.getFrame(image);

			texture.tryFill(image);

			decoder.decode(image, qrContent);
		}

		if (texture)
		{
			texture.draw();
		}

		if (qrContent)
		{
			qrContent.quad.drawFrame(2, Palette::Red);

			font(qrContent.text).draw(Arg::topLeft = qrContent.quad.p1, Palette::Red);
		}
	}
}
