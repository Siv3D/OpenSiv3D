
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	//Log << Math::Lerp(Vec2(1.0, 1.5), Vec2(11.0, 3.0), 0.2);

	constexpr double a = EaseInOut(Easing::Quad, 0.1);

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
