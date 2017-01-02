
# include <Siv3D.hpp>

void Main()
{
	MathParser parser(L"x^2 + sin(pi/2)");
	parser.setConstant(L"pi", Math::Pi);
	
	double x = 0;
	parser.setVaribale(L"x", &x);

	Log << parser.eval();

	x = 10.0;
	Log << parser.eval();

	while (System::Update())
	{

	}

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
