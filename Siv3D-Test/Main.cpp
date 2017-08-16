# include <Siv3D.hpp>

void Main()
{
	//Image image(L"C:/Users/harkuser/Documents/agehama/ppm/bilevel_ascii.pbm");
	//Image image(L"C:/Users/harkuser/Documents/agehama/ppm/grayscale_ascii.pgm");
	Image image(L"C:/Users/harkuser/Documents/agehama/ppm/color_ascii.ppm");
	//Image image(L"C:/Users/harkuser/Documents/agehama/ppm/bilevel_binary.pbm");
	//Image image(L"C:/Users/harkuser/Documents/agehama/ppm/bilevel_2_binary.pbm");
	//Image image(L"C:/Users/harkuser/Documents/agehama/ppm/grayscale_binary_crlf.pgm");
	//Image image(L"C:/Users/harkuser/Documents/agehama/ppm/color_binary.ppm");
	Texture texture(image);
	Window::SetTitle(image.size());

	image.savePPM(L"C:/Users/harkuser/Documents/agehama/ppm/test/color_binary.ppm", PPM::BinaryPixmap);

	Graphics2D::SetSamplerState(SamplerState::ClampNearest);
	while (System::Update())
	{
		texture.scale(50).draw();
	}
}
