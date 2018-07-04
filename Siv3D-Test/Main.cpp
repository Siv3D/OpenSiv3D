
# include <Siv3D.hpp> // OpenSiv3D v0.2.8

void Main()
{
	LineString a;
	a = a;
	a.assign(a);
	a.assign(a.begin(), a.end());
	a.append(a);

	Wave b;
	b = b;
	b.assign(b);
	b.append(b);

	MultiPolygon c;
	c = c;
	c.assign(c);
	c.append(c);

	QRCode qr;
	QR::EncodeAlnum(qr, U"Siv3D");
	const Texture texture(qr.image.bordered(4).scaled(5, Interpolation::Nearest));

	while (System::Update())
	{
		texture.draw();
	}
}
