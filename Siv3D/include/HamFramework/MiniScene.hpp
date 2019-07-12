//-----------------------------------------------
//
//	This file is part of the Siv3D HamFramework.
//
//	Copyright (C) 2014-2019 HAMSTRO
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	template <class State>
	class MiniScene
	{
	private:

		using SceneFunction = std::function<void()>;

		HashTable<State, SceneFunction> m_scenes;

		Optional<State> m_currentState;

	public:

		~MiniScene()
		{
			if (!m_currentState || m_scenes.empty())
			{
				return;
			}

			while (System::Update())
			{
				auto it = m_scenes.find(*m_currentState);

				if (it != m_scenes.end())
				{
					it->second();
				}
			}
		}

		[[nodiscard]] SceneFunction& operator [](const State& state)
		{
			if (!m_currentState)
			{
				m_currentState = state;
			}

			return m_scenes[state];
		}

		void changeState(const State& state)
		{
			if (m_scenes.find(state) == m_scenes.end())
			{
				return;
			}

			*m_currentState = state;
		}
	};
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	const Font fontTitle(95, Typeface::Heavy);
	constexpr Size blockSize(40, 20);
	constexpr double speed = 500.0;
	Circle ball;
	Vec2 ballSpeed;
	Array<Rect> blocks;
	MiniScene<String> scene;

	scene[U"Title"] = [&]()
	{
		fontTitle(U"Breakout").drawAt(Scene::Width() / 2, 100);

		if (MouseL.down())
		{
			ball.set(320, 400, 8);
			ballSpeed.set(0, -speed);
			blocks = Iota2D(Scene::Width() / blockSize.x, 5).asArray()
				.map([=](Point p) { return Rect(p * blockSize, blockSize).moveBy(0, 60); });

			scene.changeState(U"Game");
		}
	};

	scene[U"Game"] = [&]()
	{
		const Rect paddle(Arg::center(Cursor::Pos().x, 500), 60, 10);
		ball.moveBy(ballSpeed * Scene::DeltaTime());

		for (auto it = blocks.begin(); it != blocks.end(); ++it)
		{
			if (it->intersects(ball))
			{
				(it->bottom().intersects(ball) || it->top().intersects(ball) ? ballSpeed.y : ballSpeed.x) *= -1;
				blocks.erase(it);
				break;
			}
		}

		if (ball.y < 0 && ballSpeed.y < 0)
		{
			ballSpeed.y *= -1;
		}

		if ((ball.x < 0 && ballSpeed.x < 0) || (Scene::Width() < ball.x && ballSpeed.x > 0))
		{
			ballSpeed.x *= -1;
		}

		if (ballSpeed.y > 0 && paddle.intersects(ball))
		{
			ballSpeed = Vec2((ball.x - paddle.center().x) * 10, -ballSpeed.y).setLength(speed);
		}

		blocks.each([](const Rect & b) { b.stretched(-1).draw(HSV(b.y - 40)); });
		ball.draw();
		paddle.draw();

		if (ball.y > (Scene::Height() + 20))
		{
			scene.changeState(U"Title");
		}
	};
}

*/
