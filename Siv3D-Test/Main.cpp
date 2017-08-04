# include <Siv3D.hpp>
# include <HamFramework.hpp>

struct GameData
{
	Font font = Font(50);

	int32 score = 0;
};

using MyApp = SceneManager<String, GameData>;

struct Title : MyApp::Scene
{
	Title(const InitData& init)
		: IScene(init)
	{
		Print << getState();
	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(L"Game", 2s);
		}
	}

	void draw() const override
	{
		getData().font(L"Title").drawAt(Window::BaseCenter());
	}
};

struct Game : MyApp::Scene
{
	Game(const InitData& init)
		: IScene(init)
	{
		Print << getState();
		
		getData().score = 0;
	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(L"Result", 2s);
		}

		++getData().score;
	}

	void draw() const override
	{
		getData().font(L"Game").drawAt(Window::BaseCenter());

		getData().font(getData().score).drawAt(Window::BaseCenter().movedBy(0, 60));
	}
};

struct Result : MyApp::Scene
{
	Result(const InitData& init)
		: IScene(init)
	{
		Print << getState();
	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(L"Title", 2000);
		}
	}

	void draw() const override
	{
		getData().font(L"Result").drawAt(Window::BaseCenter());

		getData().font(getData().score).drawAt(Window::BaseCenter().movedBy(0, 60));
	}
};

void Main()
{
	MyApp manager;
	manager
		.add<Title>(L"Title")
		.add<Game>(L"Game")
		.add<Result>(L"Result");

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}