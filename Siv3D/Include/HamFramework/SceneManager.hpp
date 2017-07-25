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
	/// シーケンス管理
	/// </summary>
	/// <remarks>
	/// State にはシーンを区別するキーの型、Data にはシーン間で共有するデータの型を指定します。
	/// </remarks>
	template <class State, class Data> class SceneManager;

	/// <summary>
	/// シーン・インタフェース
	/// </summary>
	template <class State, class Data>
	class SceneBase : Uncopyable
	{
	public:

		using Manager_t = SceneManager<State, Data>;

		using State_t = State;

		using Data_t = Data;

		virtual ~SceneBase() = default;

		void setData(Manager_t* pManager, const std::shared_ptr<Data>& data)
		{
			m_manager = pManager;

			m_data = data;
		}

		/// <summary>
		/// クラスの初期化時に一度だけ呼ばれます。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		virtual void init() {}

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

			Transformer2D transform(Graphics2D::GetTransform().inverse());

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

			Transformer2D transform(Graphics2D::GetTransform().inverse());

			Window::ClientRect().draw(m_manager->getFadeColor().setA(t));
		}

	protected:

		/// <summary>
		/// 共有データへのポインタ
		/// </summary>
		std::shared_ptr<Data> m_data;

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
		bool changeScene(const State& state, int32 transitionTimeMillisec = 1000, bool crossFade = false)
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

	private:

		Manager_t* m_manager = nullptr;
	};

	/// <summary>
	/// シーン管理のオプション
	/// </summary>
	enum class SceneManagerOption
	{
		/// <summary>
		/// なし
		/// </summary>
		None,

		/// <summary>
		/// シーン名をデバッグ表示
		/// </summary>
		ShowSceneName,
	};

	/// <summary>
	/// シーケンス管理
	/// </summary>
	/// <remarks>
	/// State にはシーンを区別するキーの型、Data にはシーン間で共有するデータの型を指定します。
	/// </remarks>
	template <class State, class Data = void>
	class SceneManager
	{
	private:

		using Scene_t = std::shared_ptr<SceneBase<State, Data>>;

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

		SceneManagerOption m_option = SceneManagerOption::None;

		bool m_crossFade = false;

		bool m_error = false;

		bool updateSingle()
		{
			int32 elapsed = m_stopwatch.ms();

			if (m_transitionState == TransitionState::FadeOut && elapsed >= m_transitionTimeMillisec)
			{
				m_current = nullptr;

				m_current = m_factories[m_nextState]();

				m_current->init();

				if (hasError())
				{
					return false;
				}

				m_currentState = m_nextState;

				m_transitionState = TransitionState::FadeIn;

				m_stopwatch.restart();

				elapsed = 0;
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
				m_current->updateFadeIn(static_cast<double>(elapsed) / m_transitionTimeMillisec);
				return !hasError();
			case TransitionState::Active:
				m_current->update();
				return !hasError();
			case TransitionState::FadeOut:
				assert(m_transitionTimeMillisec);
				m_current->updateFadeOut(static_cast<double>(elapsed) / m_transitionTimeMillisec);
				return !hasError();
			default:
				return false;
			}
		}

		bool updateCross()
		{
			const int32 elapsed = m_stopwatch.ms();

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

				const double t = static_cast<double>(elapsed) / m_transitionTimeMillisec;

				m_current->updateFadeOut(t);

				if (hasError())
				{
					return false;
				}

				m_next->updateFadeIn(t);

				return !hasError();
			}
		}

		template <class Type>
		String getSceneName() const
		{
			return Format(L'[', static_cast<int32>(m_currentState), L']');
		}

		template <>
		String getSceneName<String>() const
		{
			return Format(L'[', m_currentState, L']');
		}

		void drawSceneName() const
		{
			//PutText(getSceneName<State>()).at(Window::Center());
		}

		bool hasError() const
		{
			return m_error;
		}

		template <class Type>
		std::shared_ptr<Type> MakeShared() const
		{
			return std::make_shared<Data>();
		}

		template <>
		std::shared_ptr<void> MakeShared() const
		{
			return std::shared_ptr<void>(nullptr);
		}

	public:

		/// <summary>
		/// シーンのインタフェース
		/// </summary>
		using Scene = SceneBase<State, Data>;

		/// <summary>
		/// シーン管理を初期化します。
		/// </summary>
		/// <param name="option">
		/// シーン管理のオプション
		/// </param>
		explicit SceneManager(SceneManagerOption option = SceneManagerOption::None)
			: m_data(MakeShared<Data>())
			, m_option(option) {}

		/// <summary>
		/// シーン管理を初期化します。
		/// </summary>
		/// <param name="data">
		/// 共有データ
		/// </param>
		/// <param name="option">
		/// シーン管理のオプション
		/// </param>
		explicit SceneManager(const std::shared_ptr<Data>& data, SceneManagerOption option = SceneManagerOption::None)
			: m_data(data)
			, m_option(option) {}

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
		bool add(const State& state)
		{
			if (m_factories.find(state) != m_factories.end())
			{
				return false;
			}

			m_factories.emplace(state, [&]()
			{
				auto m = std::make_shared<Scene>();

				m->setData(this, m_data);

				return m;
			});

			if (!m_first)
			{
				m_first = state;
			}

			return true;
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

			m_current->init();

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
		bool update()
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
		void draw() const
		{
			if (!m_current)
			{
				return;
			}

			if (m_transitionState == TransitionState::Active || !m_transitionTimeMillisec)
			{
				m_current->draw();

				if (m_option == SceneManagerOption::ShowSceneName)
				{
					drawSceneName();
				}
			}

			const int32 elapsed = m_stopwatch.ms();

			if (m_transitionState == TransitionState::FadeIn)
			{
				m_current->drawFadeIn(static_cast<double>(elapsed) / m_transitionTimeMillisec);
			}
			else if (m_transitionState == TransitionState::FadeOut)
			{
				m_current->drawFadeOut(static_cast<double>(elapsed) / m_transitionTimeMillisec);
			}
			else if (m_transitionState == TransitionState::FadeInOut)
			{
				m_current->drawFadeOut(static_cast<double>(elapsed) / m_transitionTimeMillisec);

				if (m_next)
				{
					m_next->drawFadeIn(static_cast<double>(elapsed) / m_transitionTimeMillisec);
				}
			}
		}

		/// <summary>
		/// シーンの更新と描画を行います。
		/// </summary>
		/// <returns>
		/// シーンの更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool updateAndDraw()
		{
			if (!update())
			{
				return false;
			}

			draw();

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

				m_next->init();

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


*/
