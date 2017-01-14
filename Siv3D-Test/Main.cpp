
# include <Siv3D.hpp>

void Main()
{
	TimeProfiler tp;

	for(auto i :step(100))
	{
		tp.begin(L"XXH");
		Hash::XXHashFromFile(L"example/siv3d-kun.png");
		tp.end();
	}

	for (auto i : step(100))
	{
		tp.begin(L"MD5");
		Hash::MD5FromFile(L"example/siv3d-kun.png");
		tp.end();
	}

	/*
	Log << Hash::XXHashFromFile(L"example/siv3d-kun.png");
	Log << Hash::XXHashFromFile(L"example/siv3d-kun2.png");
	Log << Hash::XXHashFromFile(L"example/siv3d-kun3.png");

	Log << Hash::MD5FromFile(L"example/siv3d-kun.png").asString();
	Log << Hash::MD5FromFile(L"example/siv3d-kun2.png").asString();
	Log << Hash::MD5FromFile(L"example/siv3d-kun3.png").asString();
	*/

	//while (System::Update())
	//{

	//}

	/*
	DragDrop::AcceptText(true);

	while (System::Update())
	{
		if (const auto dragOver = DragDrop::DragOver())
		{
			Log(L"DragOver:") << (int32)dragOver->itemType << dragOver->pos;
		}

		if (DragDrop::HasNewFilePaths())
		{
			Log(L"FilePaths:");

			for (const auto& dropped : DragDrop::GetDroppedFilePaths())
			{
				Log << dropped.path << dropped.pos << dropped.timeMillisec;
			}
		}

		if (DragDrop::HasNewText())
		{
			Log(L"Text:");

			for (const auto& dropped : DragDrop::GetDroppedText())
			{
				Log << dropped.text << dropped.pos << dropped.timeMillisec;
			}
		}
	}
	*/
}
