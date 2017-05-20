# include <Siv3D.hpp>

void Main()
{
	//FileSystem::Remove(L"out.png");

	//const Image image(L"input.png");

	//TimeProfiler tp;

	//tp.begin(L"a");
	//
	//const Image result = ImageProcessing::GenerateSDF(image, 16);
	//
	//tp.end();

	//result.save(L"sdf.png");

	//Log << Hash::MD5FromFile(L"sdf.png");
	//Log << Hash::MD5FromFile(L"sdf_ref.png");

	const Texture textureS(L"sdf.png", TextureDesc::SDF);
	const Texture textureN(L"sdf.png");

	double s = 4.0;

	while (System::Update())
	{
		s *= (1.0 + Mouse::Wheel() * 0.1);

		if (MouseL.pressed())
		{
			textureS.scale(s).drawAt(Window::Center());
		}
		else
		{
			textureN.scale(s).drawAt(Window::Center());
		}
	}
}
