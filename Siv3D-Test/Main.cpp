# include <Siv3D.hpp>

void Main()
{
	//Image image(L"test/image/ppm/grayscale_ascii.pgm");
	//Image image(L"test/image/ppm/color_ascii.ppm");
	//Image image(L"test/image/ppm/bilevel_binary.pbm");
	//Image image(L"test/image/ppm/bilevel_2_binary.pbm");
	//Image image(L"test/image/ppm/grayscale_binary_crlf.pgm");
	//Image image(L"test/image/ppm/color_binary.ppm");
	Image image(L"C:/Users/harkuser/Documents/agehama/ppm/color_ascii.ppm");
	Texture texture(image);
	Window::SetTitle(image.size());

	image.savePPM(L"C:/Users/harkuser/Documents/agehama/ppm/test/output_test1.ppm");

	Graphics2D::SetSamplerState(SamplerState::ClampNearest);
	while (System::Update())
	{
		texture.scale(50).draw();
	}
}
