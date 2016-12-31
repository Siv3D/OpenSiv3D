
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::literals;

void Main()
{
	const Vec2 s = Console.readLine<Vec2>();

	Log << s;

	/*
	DragDrop::AcceptText(true);

	while (System::Update())
	{
		if (const auto dragOver = DragDrop::DragOver())
		{
			Log(L"DragOver:") << (int)dragOver->itemType << dragOver->pos;
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

			for (const auto& dropped : DragDrop::GetDroppedTexts())
			{
				Log << dropped.text << dropped.pos << dropped.timeMillisec;
			}
		}
	}
	*/
}
