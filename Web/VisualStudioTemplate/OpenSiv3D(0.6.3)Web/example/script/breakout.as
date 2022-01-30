
void Main()
{
	const Point brickSize(40, 20);
	
	const double speed = 480.0;
	
	Vec2 ballVelocity(0, -speed);
	
	Circle ball(400, 400, 8);

	Array<Rect> bricks;
	for (int32 y = 0; y < 5; ++y)
	{
		for (int32 x = 0; x < (Scene::Width() / brickSize.x); ++x)
		{
			bricks << Rect((x * brickSize.x), (60 + y * brickSize.y), brickSize);
		}	
	}

	while (System::Update())
	{
		const Rect paddle(Arg::center(Cursor::Pos().x, 500), 60, 10);

		ball.moveBy(ballVelocity * Scene::DeltaTime());

		for (size_t i = 0; i < bricks.size(); ++i)
		{
			const Rect brick = bricks[i];

			if (brick.intersects(ball))
			{
				(brick.bottom().intersects(ball) || brick.top().intersects(ball)
					? ballVelocity.y : ballVelocity.x) *= -1;

				bricks.removeAt(i);
				break;
			}
		}

		if (ball.y < 0 && ballVelocity.y < 0)
		{
			ballVelocity.y *= -1;
		}

		if ((ball.x < 0 && ballVelocity.x < 0)
			|| (Scene::Width() < ball.x && 0 < ballVelocity.x))
		{
			ballVelocity.x *= -1;
		}

		if (0 < ballVelocity.y && paddle.intersects(ball))
		{
			ballVelocity = Vec2((ball.x - paddle.center().x) * 10, -ballVelocity.y).setLength(speed);
		}

		for (size_t i = 0; i < bricks.size(); ++i)
		{
			const Rect brick = bricks[i];
			brick.stretched(-1).draw(HSV(brick.y - 40));
		}

		ball.draw();
		paddle.draw();
	}
}
