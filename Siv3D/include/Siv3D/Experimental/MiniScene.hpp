//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	/// @brief 簡易的なシーン管理
	/// @tparam State シーンを区別するキーの型
	template <class State>
	class MiniScene
	{
	public:

		/// @brief シーンの関数オブジェクトの型
		using SceneFunction = std::function<void()>;

		/// @brief デストラクタ
		~MiniScene();

		/// @brief シーンを登録します。
		/// @tparam State 登録するシーンの型
		/// @remark この関数の戻り値にシーンの関数オブジェクトを登録します。
		/// @return シーンの関数オブジェクトへの参照
		[[nodiscard]]
		SceneFunction& operator [](const State& state);

		/// @brief シーンを変更します。
		/// @tparam State 次のシーンのキー
		void changeState(const State& state);

	private:

		HashTable<State, SceneFunction> m_scenes;

		Optional<State> m_currentState;
	};
}

# include "detail/MiniScene.ipp"


/*

// example

# include <Siv3D.hpp>

void Main()
{
	const Font fontTitle{ 95, Typeface::Heavy };
	constexpr Size blockSize{ 40, 20 };
	constexpr double speed = 500.0;
	Circle ball;
	Vec2 ballSpeed;
	Array<Rect> blocks;
	MiniScene<String> scene;

	scene[U"Title"] = [&]()
	{
		fontTitle(U"Breakout").drawAt(Scene::Width() / 2, 120);

		if (MouseL.down())
		{
			ball.set(320, 400, 8);
			ballSpeed.set(0, -speed);
			blocks = Iota2D(Scene::Width() / blockSize.x, 5).asArray()
				.map([=](Point p) { return Rect{ p * blockSize, blockSize }.moveBy(0, 60); });
			scene.changeState(U"Game");
		}
	};

	scene[U"Game"] = [&]()
	{
		const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 60, 10 };
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
			ballSpeed = Vec2{ (ball.x - paddle.center().x) * 10, -ballSpeed.y }.setLength(speed);
		}

		blocks.each([](const Rect& b) { b.stretched(-1).draw(HSV{ b.y - 40 }); });
		ball.draw();
		paddle.draw();

		if (ball.y > (Scene::Height() + 20))
		{
			scene.changeState(U"Title");
		}
	};
}

*/