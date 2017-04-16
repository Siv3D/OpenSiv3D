
# include <Siv3D.hpp>

void Main()
{
	const Size blockSize(40, 20);
	const double speed = 8.0;
	Rect bar(60, 10);
	Circle ball(320, 400, 8);
	Vec2 ballSpeed(0, -speed);

	Array<Rect> blocks;
	for (auto p : step({ Window::Width() / blockSize.x , 5 }))
	{
		blocks.emplace_back((p*blockSize).moveBy(0, 60), blockSize);
	}

	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		ball.moveBy(ballSpeed);
		bar.setCenter(Cursor::Pos().x, 420);

		for (auto it = blocks.begin(); it != blocks.end(); ++it)
		{
			if (it->intersects(ball))
			{
				(it->bottom().intersects(ball) || it->top().intersects(ball)
					? ballSpeed.y : ballSpeed.x) *= -1;

				blocks.erase(it);
				break;
			}
		}

		for (auto const& block : blocks)
		{
			block.stretched(-1).draw(HSV(block.y - 40));
		}

		if (ball.y < 0 && ballSpeed.y <  0)
		{
			ballSpeed.y *= -1;
		}

		if ((ball.x < 0 && ballSpeed.x < 0) || (Window::Width() < ball.x && ballSpeed.x > 0))
		{
			ballSpeed.x *= -1;
		}

		if (ballSpeed.y > 0 && bar.intersects(ball))
		{
			ballSpeed = Vec2((ball.x - bar.center().x) / 8, -ballSpeed.y).setLength(speed);
		}

		RectF(Arg::center = ball.center, ball.r * 2).rotated(45_deg).draw();
		bar.draw();
	}
}

/*
void Main()
{
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		if (KeyR.down())
		{
			Window::Resize(1280, 720);
		}
		
		for (auto p : step({10,10}))
		{
			Rect(p*20,18).draw(HSV(10*(p.x+p.y)));
		}

		Rect(100, 50, 80).draw({Palette::Orange, Palette::Orange, Palette::White, Palette::White});

		Rect(200, 50, 80).draw(Arg::left = Palette::Orange, Arg::right = Palette::White);

		Rect(400, 100, 100, 80).shearedX(40).draw(Palette::Yellow);

		Rect(Arg::center(320, 240), 160, 40).rotated(System::FrameCount() * 1_deg).draw(Palette::Seagreen);

		Triangle(Window::Center(), 80).draw(Palette::Orange);
		
		Rect(80, 160, 200).draw(Color(255, 127));

		Rect(300, 300, 200, 100).drawFrame(4);
	}
}
*/
