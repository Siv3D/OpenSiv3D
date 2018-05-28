
# include <Siv3D.hpp> // OpenSiv3D v0.2.6

void Main()
{
	Window::Resize(1280, 720);
	const Font font(40, Typeface::Bold);
	DynamicTexture texture;
	QRCode qr;
	String text, previous;

	while (System::Update())
	{
		TextInput::UpdateText(text);

		const String current = text + TextInput::GetEditingText();

		if (current != previous)
		{
			if (QR::EncodeText(qr, current))
			{
				texture.fill(qr.image.bordered(4).scaled(500, 500, Interpolation::Nearest));
			}
		}

		previous = current;

		font(current).draw(60, 50);

		if (texture)
		{
			texture.drawAt(640, 400);
		}
	}
}
