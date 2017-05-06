//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2017 HAMSTRO
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

		HashMap<State, SceneFunction> m_scenes;

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

		SceneFunction& operator [](const State& state)
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
	const double speed = 8.0;
	Circle ball;
	Vec2 ballSpeed;
	Array<Rect> blocks;

	MiniScene<String> scene;

	scene[L"Title"] = [&]()
	{
		Circle(Cursor::Pos(), 100).draw();

		if (MouseL.down())
		{
			const Size blockSize(40, 20);
			ball.set(320, 400, 8);
			ballSpeed.set(0, -speed);
			blocks = Iota2D(Window::Width() / blockSize.x, 5).asArray()
				.map([=](Point p) { return Rect(p * blockSize, blockSize).moveBy(0, 60); });

			scene.changeState(L"Game");
		}
	};

	scene[L"Game"] = [&]()
	{
		const Rect bar(Arg::center(Cursor::Pos().x, 420), 60, 10);
		ball.moveBy(ballSpeed * (System::DeltaTime() / 0.01667));

		for (auto it = blocks.begin(); it != blocks.end(); ++it)
		{
			if (it->intersects(ball))
			{
				(it->bottom().intersects(ball) || it->top().intersects(ball) ? ballSpeed.y : ballSpeed.x) *= -1;
				blocks.erase(it);
				break;
			}
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

		blocks.each([](const Rect& b) { b.stretched(-1).draw(HSV(b.y - 40)); });
		ball.draw();
		bar.draw();

		if (ball.y > 500)
		{
			scene.changeState(L"Title");
		}
	};
}
*/
