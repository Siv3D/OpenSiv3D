# include <Siv3D.hpp> // OpenSiv3D v0.6

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetFullscreen(true);

	//Print << U"ウィンドウのクライアント領域のサイズ: " << Window::GetState().frameBufferSize;
	//Print << U"シーンのサイズ: " << Scene::Size();

	while (System::Update())
	{
		ClearPrint();
		Print << U"ウィンドウのクライアント領域のサイズ: " << Window::GetState().frameBufferSize;
		Print << U"シーンのサイズ: " << Scene::Size();

		if (KeyF.down())
		{
			Window::SetFullscreen(true);
		}

		if (KeyW.down())
		{
			Window::SetFullscreen(false);
		}

		for (auto p : step({ 40, 40 }))
		{
			if (IsEven(p.x + p.y))
			{
				Rect(p * 100, 100).draw(Palette::Gray);
			}
		}

		PutText(U"{}"_fmt(Cursor::Pos()), Arg::leftCenter = Cursor::PosF().movedBy(20, 0));
	}
}
