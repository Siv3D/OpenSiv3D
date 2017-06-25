# include <Siv3D.hpp> //OpenSiv3D v0.1.5

struct Fish
{
<<<<<<< Updated upstream
	Circle c(320, 240, 20);
=======
	Vec2 pos;
	Vec2 velocity;
	size_t index;
	bool isFished;
};
>>>>>>> Stashed changes

void Main()
{
	Window::SetTitle(L"Fishing");
	Window::Resize(1280, 720);
	Graphics::SetBackground(Palette::Lightskyblue);
	const Array<Texture> fishTextures = {
		Texture(Emoji(L"🐟")),
		Texture(Emoji(L"🐠")),
		Texture(Emoji(L"🐡")),
		Texture(Emoji(L"🐋")),
		Texture(Emoji(L"🐙")),
		Texture(Emoji(L"🦑")),
		Texture(Emoji(L"🦐")),
		Texture(Emoji(L"🦀")),
		Texture(Emoji(L"🦈")),
		Texture(Emoji(L"🐉")), };
	const Texture explode(Emoji(L"🌟"), TextureDesc::Mipped);
	
	const Texture playerTexture(Emoji(L"🚣‍♂"));
	double playerX = Window::Center().x / 2.0;
	double playerSpeed = 10.0;
	
	const Texture hookTexture(Emoji(L"⚓"));
	
	const double seaLevel = 100.0;
	Array<Fish> fishes;
	Array<Vec2> bubbles;
	LineString fishingLine(12);
	double currentFishingLineIndexF = 0;
	
	for (auto i : step(fishingLine.size()))
	{
		fishingLine[i] = Vec2(playerX, seaLevel + i * 50.0);
	}
	
	Stopwatch stopwatch(true);
	RectF sea = RectF(0.0, seaLevel, Window::Width(), Window::Height() - seaLevel);
	Stopwatch explosionTime;
	Vec2 explosionPos;
	size_t explosionFishIndex;
	
	int32 score = 0, highScore = 0;
	const Font font(40, Typeface::Bold);
	
	Timer timer(10s, true);
	
	const Polygon rock{ { Vec2(0, 700), Vec2(Window::Width() * 0.25, 710), Vec2(Window::Width() * 0.5, 690), Vec2(Window::Width() * 0.75, 710), Vec2(Window::Width(), 700),Vec2(Window::Width(), Window::Height()), Vec2(0, Window::Height()) } };
	
	while (System::Update())
	{
<<<<<<< Updated upstream
		Circle(Cursor::PreviousPosF(), 40).draw(Palette::Gray);

		Circle(Cursor::PosF(), 40).draw();

		c.moveBy(Cursor::DeltaF());

		c.draw();
=======
		playerX += Clamp(Cursor::Pos().x - playerX, -playerSpeed, playerSpeed);
		
		currentFishingLineIndexF = Clamp<double>(currentFishingLineIndexF + (MouseL.pressed() - MouseR.pressed()) * 0.1, 0, fishingLine.size() - 1);
		const size_t currentFishingLineIndex = static_cast<size_t>(currentFishingLineIndexF);
		const Circle hookCircle(fishingLine.back() + Vec2::Down() * 5.0, 30.0);
		highScore = Max(highScore, score);
		
		if (timer.reachedZero())
		{
			timer.restart();
			fishes.clear();
			score = 0;
		}
		
		if (stopwatch > 0.5s)
		{
			const double speed = 5.0;
			const Vec2 direction = RandomSelect({ Vec2::Left(), Vec2::Right() });
			const double initialX = Window::Center().x - direction.x * 800;
			const double initialY = Random<double>(seaLevel + 50.0, Window::Height());
			
			const Fish fish{
				Vec2(initialX, initialY),
				speed * direction,
				Random(fishTextures.size() - 1),
				false};
			
			fishes.push_back(fish);
			stopwatch.restart();
		}
		
		for (auto& fish : fishes)
		{
			fish.pos += fish.velocity;
			
			if (RandomBool(0.01))
			{
				bubbles.push_back(fish.pos + Vec2::Up() * 50.0);
			}
			
			if (hookCircle.intersects(Circle(fish.pos, 60.0)))
			{
				fish.isFished = true;
				explosionTime.restart();
				explosionPos = fish.pos;
				explosionFishIndex = fish.index;
				score += fish.index * 10 + 10;
			}
		}
		
		for (auto& bubble : bubbles)
		{
			bubble += Vec2(Random(-3.0, 3.0), -3.0);
		}
		
		for (size_t i = 0; i < fishingLine.size(); ++i)
		{
			size_t tIndex = i - currentFishingLineIndex;
			fishingLine[i].y = seaLevel + tIndex * 50.0;
			
			if (i == currentFishingLineIndex)
			{
				fishingLine[i].x = playerX;
			}
			else
			{
				fishingLine[i].x += (fishingLine[i - 1].x - fishingLine[i].x) * 0.1;
			}
		}
		
		Erase_if(fishes, [](const Fish& fish) {return !Window::ClientRect().stretched(200).intersects(fish.pos) || fish.isFished; });
		Erase_if(bubbles, [=](const Vec2& bubble) {return !sea.stretched(-6.0).intersects(bubble); });
		
		playerTexture.mirror(Cursor::Pos().x > playerX).drawAt(playerX, seaLevel - 20.0);
		
		sea.draw(Arg::top = ColorF(0.3, 0.6, 1.0), Arg::bottom = ColorF(0, 0.3, 0.7));
		
		for (const auto& bubble : bubbles)
		{
			Circle(bubble, 6.0).draw(ColorF(1.0, 0.2));
		}
		
		for (const auto& fish : fishes)
		{
			const bool isRight = fish.velocity.x > 0;
			fishTextures[fish.index].mirror(isRight).drawAt(fish.pos);
		}
		
		LineString(fishingLine.begin() + currentFishingLineIndex, fishingLine.end()).drawCatmullRom(3.0, Palette::White);
		hookTexture.scale(0.3).drawAt(hookCircle.center);
		rock.draw(Palette::Gray);
		
		{
			RenderStateBlock2D blend(BlendState::Subtractive);
			sea.draw(Arg::top = ColorF(1.0, 0.0), Arg::bottom = ColorF(1.0, 0.5));
		}
		
		if (explosionTime.isRunning())
		{
			const double t = explosionTime.sF();
			const double energy = (1.0 - std::exp(-7.0 * t));
			
			explode.scale(energy * 5.0)
			.drawAt(explosionPos, AlphaF(1.0 - t * t));
			
			fishTextures[explosionFishIndex].drawAt(explosionPos.lerp(Vec2(explosionPos.x, seaLevel - 35.0), energy));
			
			if (t > 1.0)
			{
				explosionTime.reset();
			}
		}
		
		font(L"🐡SCORE: ",score, L" TIME: ", timer.format(L"SS.xx")).draw(10, 10);
		font(L"🐟HIGHSCORE: ", highScore).draw(Arg::topRight = Vec2(1270, 10));
>>>>>>> Stashed changes
	}
}
