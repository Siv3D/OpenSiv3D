
# include <Siv3D.hpp>

template <class State>
class MiniScene
{
private:

	using SceneFunc = std::function<void()>;

	HashMap<State, SceneFunc> m_scenes;

	Optional<State> m_currentScene;

public:

	~MiniScene()
	{
		while (System::Update())
		{
			auto it = m_scenes.find(*m_currentScene);

			if (it != m_scenes.end())
			{
				it->second();
			}
		}
	}

	MiniScene& add(const State& name, SceneFunc f)
	{
		if (!m_currentScene)
		{
			m_currentScene = name;
		}

		m_scenes.emplace(name, f);

		return *this;
	}

	void changeScene(const State& name)
	{
		*m_currentScene = name;
	}
};

void Main()
{
	const double speed = 8.0;
	Circle ball;
	Vec2 ballSpeed;
	Array<Rect> blocks;

	MiniScene<String> scene;

	scene.add(L"Title", [&]()
	{
		Circle(Cursor::Pos(), 100).draw();

		if (MouseL.down())
		{
			const Size blockSize(40, 20);		
			ball.set(320, 400, 8);
			ballSpeed.set(0, -speed);
			blocks = Iota2D(Window::Width() / blockSize.x, 5).asArray()
				.map([=](Point p) { return Rect(p * blockSize, blockSize).moveBy(0, 60); });

			scene.changeScene(L"Game");
		}
	});

	scene.add(L"Game", [&]()
	{
		const Rect bar(Arg::center(Cursor::Pos().x, 420), 60, 10);
		ball.moveBy(ballSpeed);

		for (auto it = blocks.begin(); it != blocks.end(); ++it)
		{
			if (it->intersects(ball))
			{
				(it->bottom().intersects(ball) || it->top().intersects(ball) ? ballSpeed.y : ballSpeed.x) *= -1;
				blocks.erase(it);
				break;
			}
		}

		blocks.each([](const Rect& b) { b.stretched(-1).draw(HSV(b.y - 40)); });

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

		ball.draw();
		bar.draw();

		if (ball.y > 500)
		{
			scene.changeScene(L"Title");
		}
	});
}
