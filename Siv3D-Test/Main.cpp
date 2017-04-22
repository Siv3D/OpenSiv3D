# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.2, 0.6, 1.0));

	int32 count = 0, crash = 0, score = 0, highSore = 0;
	Array<Vec2> shots, bullets, enemies;
	Circle player(320, 400, 16);

	while (System::Update())
	{
		++count;

		if (count % (24 - Min(count / 60, 18)) == 0)
		{
			enemies.emplace_back(Random(40, 600), -40);
		}

		player.moveBy(Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
			.setLength(KeyShift.pressed() ? 4.5 : 9.0));

		player.center.clamp(Window::ClientRect());

		if (KeyZ.pressed() && count % 4 == 0)
		{
			shots.push_back(player.center);
		}

		shots.each([](Vec2& shot) { shot.y -= 8.0; });

		bullets.each([](Vec2& bullet) { bullet.y += 4.0; });

		enemies.each([](Vec2& enemy) { enemy.y += 2.0; });

		if (count % 60 == 0)
		{
			enemies.each([&](Vec2& p) { bullets.push_back(p); });
		}

		if (bullets.any([=](const Vec2& b) { return b.intersects(player); })
			|| enemies.any([=](const Vec2& e) { return e.y > 490.0; }))
		{
			count = score = 0;
			crash = 60;
		}

		shots.remove_if([](const Vec2& s) { return s.y < -10.0; });

		bullets.remove_if([](const Vec2& b) { return b.y > 490.0; });

		enemies.remove_if([&](const Vec2& e)
		{
			if (shots.any([=](const Vec2& s) { return e.distanceFrom(s) < 20.0; }))
			{
				++score;
				return true;
			}
			else return e.y > 490.0;
		});

		shots.each([](const Vec2& s) { Circle(s, 7).draw(Palette::Orange); });

		bullets.each([](const Vec2& b) { Circle(b, 4).draw(Palette::Yellow); });

		enemies.each([](const Vec2& e) { RectF(Arg::center(e), 30).rotated(e.y / 100.0).draw(Palette::Black); });

		player.draw();

		if (crash)
		{
			Window::ClientRect().draw(Alpha(--crash * 3));
		}

		highSore = Max(score, highSore);

		Window::SetTitle(L"[Z]: shot | [Arrow keys]: Move | Hi:{} | {}"_fmt(highSore, score));
	}
}