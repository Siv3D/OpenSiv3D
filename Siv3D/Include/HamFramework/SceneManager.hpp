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
	/// <summary>
	/// シーン管理
	/// </summary>
	/// <remarks>
	/// State にはシーンを区別するキーの型、Data にはシーン間で共有するデータの型を指定します。
	/// </remarks>
	template <class State, class Data> class SceneManager;
	
	namespace detail
	{
		template <class Type>
		inline std::shared_ptr<Type> MakeSharedData()
		{
			return MakeShared<Type>();
		}
		
		template <>
		inline std::shared_ptr<void> MakeSharedData()
		{
			return std::shared_ptr<void>(nullptr);
		}
	}

	/// <summary>
	/// シーン・インタフェース
	/// </summary>
	template <class State, class Data>
	class IScene : Uncopyable
	{
	public:

		using State_t = State;

		using Data_t = Data;

		using InitData = struct
		{
			State_t state;

			std::shared_ptr<Data_t> _s;

			SceneManager<State_t, Data_t>* _m;
		};

	private:

		State_t m_state;

		std::shared_ptr<Data_t> m_data;

		SceneManager<State_t, Data_t>* m_manager;

	public:

		IScene(const InitData& init)
			: m_state(init.state)
			, m_data(init._s)
			, m_manager(init._m) {}

		virtual ~IScene() = default;

		/// <summary>
		/// フェードイン時の更新
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		virtual void updateFadeIn(double) {}

		/// <summary>
		/// 通常時の更新
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		virtual void update() {}

		/// <summary>
		/// フェードアウト時の更新
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		virtual void updateFadeOut(double) {}

		/// <summary>
		/// 通常時の描画
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		virtual void draw() const {}

		/// <summary>
		/// フェードイン時の描画
		/// </summary>
		/// <param name="t">
		/// フェードインの経過 (0.0 → 1.0)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		virtual void drawFadeIn(double t) const
		{
			draw();

			Transformer2D transform(Mat3x2::Identity(), Transformer2D::Target::SetLocal);

			Window::ClientRect().draw(m_manager->getFadeColor().setA(1.0 - t));
		}

		/// <summary>
		/// フェードイアウト時の描画
		/// </summary>
		/// <param name="t">
		/// フェードアウトの経過 (0.0 → 1.0)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		virtual void drawFadeOut(double t) const
		{
			draw();

			Transformer2D transform(Mat3x2::Identity(), Transformer2D::Target::SetLocal);

			Window::ClientRect().draw(m_manager->getFadeColor().setA(t));
		}

	protected:

		const State_t& getState() const
		{
			return m_state;
		}

		/// <summary>
		/// 共有データへの参照を取得します。
		/// </summary>
		/// </param>
		/// <returns>
		/// 共有データへの参照
		/// </returns>
		Data_t& getData() const
		{
			return *m_data;
		}

		/// <summary>
		/// シーンの変更を通知します。
		/// </summary>
		/// <param name="state">
		/// 次のシーンのキー
		/// </param>
		/// <param name="transitionTime">
		/// フェードイン・アウトの時間
		/// </param>
		/// <param name="crossFade">
		/// クロスフェードを有効にするか
		/// </param>
		/// <returns>
		/// シーンの変更が可能でフェードイン・アウトが開始される場合 true, それ以外の場合は false
		/// </returns>
		bool changeScene(const State_t& state, const MillisecondsF& transitionTime = 1000ms, bool crossFade = false)
		{
			return changeScene(state, static_cast<int32>(transitionTime.count()), crossFade);
		}

		/// <summary>
		/// シーンの変更を通知します。
		/// </summary>
		/// <param name="state">
		/// 次のシーンのキー
		/// </param>
		/// <param name="transitionTimeMillisec">
		/// フェードイン・アウトの時間（ミリ秒）
		/// </param>
		/// <param name="crossFade">
		/// クロスフェードを有効にするか
		/// </param>
		/// <returns>
		/// シーンの変更が可能でフェードイン・アウトが開始される場合 true, それ以外の場合は false
		/// </returns>
		bool changeScene(const State_t& state, int32 transitionTimeMillisec, bool crossFade = false)
		{
			return m_manager->changeScene(state, transitionTimeMillisec, crossFade);
		}

		/// <summary>
		/// エラーの発生を通知します。
		/// </summary>
		/// <remarks>
		/// この関数を呼ぶと、以降の SceneManager::update() / updateAndDraw() が false を返します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void notifyError()
		{
			return m_manager->notifyError();
		}
	};

	/// <summary>
	/// シーン管理
	/// </summary>
	/// <remarks>
	/// State にはシーンを区別するキーの型、Data にはシーン間で共有するデータの型を指定します。
	/// </remarks>
	template <class State, class Data = void>
	class SceneManager
	{
	private:

		using Scene_t = std::shared_ptr<IScene<State, Data>>;

		using FactoryFunction_t = std::function<Scene_t()>;

		HashMap<State, FactoryFunction_t> m_factories;

		std::shared_ptr<Data> m_data;

		Scene_t m_current;

		Scene_t m_next;

		State m_currentState;

		State m_nextState;

		Optional<State> m_first;

		enum class TransitionState
		{
			None,

			FadeIn,

			Active,

			FadeOut,

			FadeInOut,

		} m_transitionState = TransitionState::None;

		Stopwatch m_stopwatch;

		int32 m_transitionTimeMillisec = 1000;

		ColorF m_fadeColor = Palette::Black;

		bool m_crossFade = false;

		bool m_error = false;

		bool updateSingle()
		{
			double elapsed = m_stopwatch.msF();

			if (m_transitionState == TransitionState::FadeOut && elapsed >= m_transitionTimeMillisec)
			{
				m_current = nullptr;

				m_current = m_factories[m_nextState]();

				if (hasError())
				{
					return false;
				}

				m_currentState = m_nextState;

				m_transitionState = TransitionState::FadeIn;

				m_stopwatch.restart();

				elapsed = 0.0;
			}

			if (m_transitionState == TransitionState::FadeIn && elapsed >= m_transitionTimeMillisec)
			{
				m_stopwatch.reset();

				m_transitionState = TransitionState::Active;
			}

			switch (m_transitionState)
			{
			case TransitionState::FadeIn:
				assert(m_transitionTimeMillisec);
				m_current->updateFadeIn(elapsed / m_transitionTimeMillisec);
				return !hasError();
			case TransitionState::Active:
				m_current->update();
				return !hasError();
			case TransitionState::FadeOut:
				assert(m_transitionTimeMillisec);
				m_current->updateFadeOut(elapsed / m_transitionTimeMillisec);
				return !hasError();
			default:
				return false;
			}
		}

		bool updateCross()
		{
			const double elapsed = m_stopwatch.msF();

			if (m_transitionState == TransitionState::FadeInOut)
			{
				if (elapsed >= m_transitionTimeMillisec)
				{
					m_current = m_next;

					m_next = nullptr;

					m_stopwatch.reset();

					m_transitionState = TransitionState::Active;
				}
			}

			if (m_transitionState == TransitionState::Active)
			{
				m_current->update();

				return !hasError();
			}
			else
			{
				assert(m_transitionTimeMillisec);

				const double t = elapsed / m_transitionTimeMillisec;

				m_current->updateFadeOut(t);

				if (hasError())
				{
					return false;
				}

				m_next->updateFadeIn(t);

				return !hasError();
			}
		}

		bool hasError() const noexcept
		{
			return m_error;
		}

	public:

		/// <summary>
		/// シーンのインタフェース
		/// </summary>
		using Scene = IScene<State, Data>;

		/// <summary>
		/// シーン管理を初期化します。
		/// </summary>
		/// <param name="option">
		/// シーン管理のオプション
		/// </param>
		SceneManager()
			: m_data(detail::MakeSharedData<Data>()) {}

		/// <summary>
		/// シーン管理を初期化します。
		/// </summary>
		/// <param name="data">
		/// 共有データ
		/// </param>
		/// <param name="option">
		/// シーン管理のオプション
		/// </param>
		explicit SceneManager(const std::shared_ptr<Data>& data)
			: m_data(data) {}

		/// <summary>
		/// シーンを追加します。
		/// </summary>
		/// <param name="state">
		/// シーンのキー
		/// </param>
		/// <returns>
		/// 追加に成功した場合 true, それ以外の場合は false
		/// </returns>
		template <class Scene>
		SceneManager& add(const State& state)
		{
			typename Scene::InitData initData{ state, m_data, this };
			
			auto factory = [=](){
				return MakeShared<Scene>(initData);
			};
		
			auto it = m_factories.find(state);
			
			if (it != m_factories.end())
			{
				it.value() = factory;
			}
			else
			{
				m_factories.emplace(state, factory);

				if (!m_first)
				{
					m_first = state;
				}
			}

			return *this;
		}

		/// <summary>
		/// 最初のシーンを初期化します。
		/// </summary>
		/// <param name="state">
		/// 最初のシーン
		/// </param>
		/// <returns>
		/// 初期化に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool init(const State& state)
		{
			if (m_current)
			{
				return false;
			}

			auto it = m_factories.find(state);

			if (it == m_factories.end())
			{
				return false;
			}

			m_currentState = state;

			m_current = it->second();

			if (hasError())
			{
				return false;
			}

			m_transitionState = TransitionState::FadeIn;

			m_stopwatch.restart();

			return true;
		}

		/// <summary>
		/// シーンを更新します。
		/// </summary>
		/// <returns>
		/// シーンの更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool updateScene()
		{
			if (hasError())
			{
				return false;
			}

			if (!m_current)
			{
				if (!m_first)
				{
					return true;
				}
				else if (!init(m_first.value()))
				{
					return false;
				}
			}

			if (m_crossFade)
			{
				return updateCross();
			}
			else
			{
				return updateSingle();
			}
		}

		/// <summary>
		/// シーンを描画します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void drawScene() const
		{
			if (!m_current)
			{
				return;
			}

			if (m_transitionState == TransitionState::Active || !m_transitionTimeMillisec)
			{
				m_current->draw();
			}

			const double elapsed = m_stopwatch.msF();

			if (m_transitionState == TransitionState::FadeIn)
			{
				m_current->drawFadeIn(elapsed / m_transitionTimeMillisec);
			}
			else if (m_transitionState == TransitionState::FadeOut)
			{
				m_current->drawFadeOut(elapsed / m_transitionTimeMillisec);
			}
			else if (m_transitionState == TransitionState::FadeInOut)
			{
				m_current->drawFadeOut(elapsed / m_transitionTimeMillisec);

				if (m_next)
				{
					m_next->drawFadeIn(elapsed / m_transitionTimeMillisec);
				}
			}
		}

		/// <summary>
		/// シーンの更新と描画を行います。
		/// </summary>
		/// <returns>
		/// シーンの更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool update()
		{
			if (!updateScene())
			{
				return false;
			}

			drawScene();

			return true;
		}

		/// <summary>
		/// 共有データを取得します。
		/// </summary>
		/// <returns>
		/// 共有データへのポインタ
		/// </returns>
		std::shared_ptr<Data> get()
		{
			return m_data;
		}

		/// <summary>
		/// 共有データを取得します。
		/// </summary>
		/// <returns>
		/// 共有データへのポインタ
		/// </returns>
		const std::shared_ptr<const Data> get() const
		{
			return m_data;
		}

		/// <summary>
		/// シーンを変更します。
		/// </summary>
		/// <param name="state">
		/// 次のシーンのキー
		/// </param>
		/// <param name="transitionTimeMillisec">
		/// フェードイン・アウトの時間（ミリ秒）
		/// </param>
		/// <param name="crossFade">
		/// クロスフェードを有効にするか
		/// </param>
		/// <returns>
		/// シーンの変更が可能でフェードイン・アウトが開始される場合 true, それ以外の場合は false
		/// </returns>
		bool changeScene(const State& state, int32 transitionTimeMillisec, bool crossFade)
		{
			if (state == m_currentState)
			{
				crossFade = false;
			}

			if (m_factories.find(state) == m_factories.end())
			{
				return false;
			}

			m_nextState = state;

			m_crossFade = crossFade;

			if (crossFade)
			{
				m_transitionTimeMillisec = transitionTimeMillisec;

				m_transitionState = TransitionState::FadeInOut;

				m_next = m_factories[m_nextState]();

				if (hasError())
				{
					return false;
				}

				m_currentState = m_nextState;

				m_stopwatch.restart();
			}
			else
			{
				m_transitionTimeMillisec = (transitionTimeMillisec / 2);

				m_transitionState = TransitionState::FadeOut;

				m_stopwatch.restart();
			}

			return true;
		}

		/// <summary>
		/// フェードイン・アウトのデフォルトの色を設定します。
		/// </summary>
		/// <param name="color">
		/// フェードイン・アウトのデフォルトの色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setFadeColor(const ColorF& color)
		{
			m_fadeColor = color;
		}

		/// <summary>
		/// フェードイン・アウトのデフォルトの色を取得します。
		/// </summary>
		/// <returns>
		/// フェードイン・アウトのデフォルトの色
		/// </returns>
		ColorF getFadeColor() const
		{
			return m_fadeColor;
		}

		/// <summary>
		/// エラーの発生を通知します。
		/// </summary>
		/// <remarks>
		/// この関数を呼ぶと、以降の SceneManager::update() / updateAndDraw() が false を返します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void notifyError()
		{
			m_error = true;
		}
	};
}

/* example

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

*/
