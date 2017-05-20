# include <Siv3D.hpp>

void Main()
{
	FileSystem::Remove(L"out.png");

	const Image image(L"input.png");

	TimeProfiler tp;

	tp.begin(L"a");
	
	const Image result = ImageProcessing::GenerateSDF(image, 16);
	
	tp.end();

	result.save(L"out.png");

	Log << Hash::MD5FromFile(L"out.png");
	Log << Hash::MD5FromFile(L"outRef.png");

	while (System::Update())
	{

	}
}
