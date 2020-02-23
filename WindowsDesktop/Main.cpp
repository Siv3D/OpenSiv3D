
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	//{
	//	const ZIPReader zip(U"example.zip");
	//	zip.enumPaths().each(Console);
	//	Print << zip.extract(U"example/bay.jpg", U"arcout/");
	//	Print << zip.extractAll(U"arcout2/");
	//}

	//Console << U"---";

	//{
	//	const ZIPReader zip(Resource(U"arc/example.zip"));
	//	zip.enumPaths().each(Console);
	//	Print << zip.extract(U"example/bay.jpg", U"arcout/");
	//	Print << zip.extractAll(U"arcout2/");
	//}

	//Console << U"---";

	//{
	//	const ZIPReader zip(Resource(U"arc/example2.zip"));
	//	zip.enumPaths().each(Console);
	//	Print << zip.extract(U"LICENSE.txt", U"arcout/");
	//	Print << zip.extractAll(U"arcout2/");
	//}

	const ZIPReader zip(Resource(U"arc/example.zip"));
	const Texture texture1(zip.extractToMemory(U"example/bay.jpg"));
	const Texture texture2(zip.extractToMemory(U"example/siv3d-kun.png"));;

	while (System::Update())
	{
		texture1.draw();
		texture2.draw();
	}
}
