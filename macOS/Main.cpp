
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	const ZIPReader zip(U"example/zip/zip_test.zip");

	if (!zip)
	{
		return;
	}

	for (const auto& path : zip.enumPaths())
	{
		Print << path;
	}

	const Texture texture1(zip.extractToMemory(U"zip_test/image/windmill.png"));
	const Texture texture2(zip.extractToMemory(U"zip_test/image/siv3d-kun.png"));

	Print << U"-----";
	Print << zip.extract(U"zip_test/loremipsum.txt", U"unzipped1/");
	Print << zip.extract(U"zip_test/image/*", U"unzipped2/");
	Print << zip.extractAll(U"unzipped3/");

	while (System::Update())
	{
		texture1.draw();
		texture2.draw();
	}
}
