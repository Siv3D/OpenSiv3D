# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	Window::Resize(1280, 720);

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, 0 }, 1.0, CameraControl::None_ };

	Circular from(100, 0);

	Circular to = from;

	Circular pos = from;

	Circle c1{ pos, 10 };

	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		// 移動の割合 0.0～1.0
		const double t = Min(stopwatch.sF(), 1.0);

		// from から to へ t の割合で Lerp する
		pos = from.lerp(to, t);

		c1.setCenter(pos);

		// クリックした座標へ移動
		if (MouseL.down())
		{
			from = pos;
			to = Circular{ Cursor::PosF() - Scene::Center() };
			stopwatch.restart();
		}

		// 2D カメラを更新
		camera.update();
		{
			// 2D カメラの設定から Transformer2D を作成する
			const auto t = camera.createTransformer();

			for (int32 i = 0; i < 8; ++i)
			{
				Circle{ 0, 0, (50 + i * 50) }.drawFrame(2);
			}

			c1.draw(Palette::Pink);

		}

		// 2D カメラ操作の UI を表示する
		camera.draw(Palette::Orange);
	}
}
