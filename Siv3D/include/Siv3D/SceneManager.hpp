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
// s3d::SceneManager is originally designed by Takuto Takahashi (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Uncopyable.hpp"
# include "Duration.hpp"
# include "ColorHSV.hpp"
# include "Optional.hpp"
# include "HashTable.hpp"
# include "Stopwatch.hpp"
# include "Scene.hpp"
# include "Transformer2D.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	template <class State, class Data> class SceneManager;

	/// @brief シーンのインタフェース
	/// @tparam State シーンを区別するキーの型
	/// @tparam Data シーン間で共有するデータの型
	template <class State, class Data>
	class IScene : Uncopyable
	{
	public:

		using State_t = State;

		using Data_t = Data;

		struct InitData
		{
			State_t state;

			std::shared_ptr<Data_t> _s;

			SceneManager<State_t, Data_t>*& _m;

			SIV3D_NODISCARD_CXX20
			InitData() = default;

			SIV3D_NODISCARD_CXX20
			InitData(const State_t& _state, const std::shared_ptr<Data_t>& data, SceneManager<State_t, Data_t>*& manager);
		};

	public:

		SIV3D_NODISCARD_CXX20
		explicit IScene(const InitData& init);

		virtual ~IScene() = default;

		/// @brief フェードイン時の更新処理です。
		/// @param t フェードインの進度 [0.0, 1.0]
		virtual void updateFadeIn([[maybe_unused]] double t) {}
		
		/// @brief 通常時の更新処理です。
		virtual void update() {}

		/// @brief フェードアウト時の更新処理です。
		/// @param t フェードアウトの進度 [0.0, 1.0]
		virtual void updateFadeOut([[maybe_unused]] double t) {}

		/// @brief 通常時の描画処理です。
		virtual void draw() const {}

		/// @brief フェードイン時の描画処理です。
		/// @param t フェードインの進度 [0.0, 1.0]
		virtual void drawFadeIn(double t) const;

		/// @brief フェードアウト時の描画処理です。
		/// @param t フェードアウトの進度 [0.0, 1.0]
		virtual void drawFadeOut(double t) const;

	protected:

		/// @brief 現在のステートのキーを取得します。
		/// @return 現在のステートのキー
		[[nodiscard]]
		const State_t& getState() const;

		/// @brief 共有データへの参照を取得します。
		/// @return 共有データへの参照
		template <class DataType = Data, std::enable_if_t<not std::disjunction_v<std::is_array<DataType>, std::is_void<DataType>>>* = nullptr>
		[[nodiscard]]
		DataType& getData() const;

		/// @brief シーンの変更をリクエストします。
		/// @param state 次のシーンのキー
		/// @param transitionTime フェードイン・アウトの時間
		/// @param crossFade クロスフェードを有効にするか
		/// @return シーンの変更が開始される場合 true, それ以外の場合は false
		bool changeScene(const State_t& state, const Duration& transitionTime = Duration{ 2.0 }, CrossFade crossFade = CrossFade::No);

		/// @brief シーンの変更をリクエストします。
		/// @param state 次のシーンのキー
		/// @param transitionTimeMillisec フェードイン・アウトの時間（ミリ秒）
		/// @param crossFade クロスフェードを有効にするか
		/// @return シーンの変更が開始される場合 true, それ以外の場合は false
		bool changeScene(const State_t& state, int32 transitionTimeMillisec, CrossFade crossFade = CrossFade::No);

		/// @brief エラーの発生を通知します。
		/// @remark この関数を呼ぶと、以降のこのシーンを管理するクラスの `SceneManager::update()` が false を返します。
		void notifyError();

	private:

		State_t m_state;

		std::shared_ptr<Data_t> m_data;

		SceneManager<State_t, Data_t>*& m_manager;
	};

	/// @brief シーン遷移管理
	/// @tparam State シーンを区別するキーの型
	/// @tparam Data シーン間で共有するデータの型
	template <class State, class Data = void>
	class SceneManager
	{
	public:

		/// @brief シーンのインタフェース型
		using Scene = IScene<State, Data>;

		/// @brief シーン管理を初期化します。
		SIV3D_NODISCARD_CXX20
		SceneManager();

		SIV3D_NODISCARD_CXX20
		SceneManager(const SceneManager&) = delete;

		SIV3D_NODISCARD_CXX20
		SceneManager(SceneManager&& other) noexcept;

		/// @brief シーン管理を初期化します。
		/// @param data 共有データ
		SIV3D_NODISCARD_CXX20
		explicit SceneManager(const std::shared_ptr<Data>& data);

		SceneManager& operator =(const SceneManager&) = delete;

		SceneManager& operator =(SceneManager&& other) noexcept;

		/// @brief シーンを登録します。
		/// @tparam SceneType シーンの型
		/// @param state シーンのキー
		/// @return シーンの登録に成功した場合 true, それ以外の場合は false
		template <class SceneType>
		SceneManager& add(const State& state);

		/// @brief 最初のシーンを初期化します。
		/// @param state 最初のシーン
		/// @return 初期化に成功した場合 true, それ以外の場合は false
		bool init(const State& state);

		/// @brief 現在のシーンの更新処理のみを行います。
		/// @remark 通常はこの関数は使用しません。
		/// @return シーンの更新処理に成功した場合 true, それ以外の場合は false
		bool updateScene();

		/// @brief 現在のシーンの描画処理のみを行います。
		/// @remark 通常はこの関数は使用しません。
		void drawScene() const;

		/// @brief 現在のシーンの更新処理と描画処理を行います。
		/// @return シーンの更新処理に成功した場合 true, それ以外の場合は false
		bool update();

		/// @brief 共有データを取得します。
		/// @return 共有データへのポインタ
		[[nodiscard]]
		std::shared_ptr<Data> get() noexcept;

		/// @brief 共有データを取得します。
		/// @return 共有データへのポインタ
		[[nodiscard]]
		const std::shared_ptr<const Data> get() const noexcept;

		/// @brief シーンを変更します。
		/// @param state 次のシーンのキー
		/// @param transitionTime フェードイン・アウトの時間
		/// @param crossFade ロスフェードを有効にするか
		/// @return シーンの変更が開始される場合 true, それ以外の場合は false
		bool changeScene(const State& state, const Duration& transitionTime = Duration{ 2.0 }, CrossFade crossFade = CrossFade::No);

		/// @brief シーンを変更します。
		/// @param state 次のシーンのキー
		/// @param transitionTimeMillisec フェードイン・アウトの時間（ミリ秒）
		/// @param crossFade クロスフェードを有効にするか
		/// @return シーンの変更が開始される場合 true, それ以外の場合は false
		bool changeScene(const State& state, int32 transitionTimeMillisec, CrossFade crossFade = CrossFade::No);

		/// @brief デフォルトのフェードイン・アウトに使う色を設定します。
		/// @param color デフォルトのフェードイン・アウトに使う色
		/// @return *this
		SceneManager& setFadeColor(const ColorF& color) noexcept;

		/// @brief デフォルトのフェードイン・アウトに使う色を返します。
		/// @return デフォルトのフェードイン・アウトに使う色
		[[nodiscard]]
		const ColorF& getFadeColor() const noexcept;

		/// @brief エラーの発生を通知します。
		/// @return この関数を呼ぶと、以降のこのクラスの `SceneManager::update()` が false を返します。
		void notifyError() noexcept;

	private:

		using Scene_t = std::shared_ptr<IScene<State, Data>>;

		using FactoryFunction_t = std::function<Scene_t()>;

		std::unique_ptr<SceneManager*> m_sceneManagerPtr;

		HashTable<State, FactoryFunction_t> m_factories;

		std::shared_ptr<Data> m_data;

		Scene_t m_current;

		Scene_t m_next;

		State m_currentState;

		State m_nextState;

		Optional<State> m_first;

		enum class TransitionState
		{
			None_,

			FadeIn,

			Active,

			FadeOut,

			FadeInOut,

		} m_transitionState = TransitionState::None_;

		Stopwatch m_stopwatch;

		int32 m_transitionTimeMillisec = 1000;

		ColorF m_fadeColor = Palette::Black;

		CrossFade m_crossFade = CrossFade::No;

		bool m_error = false;

		[[nodiscard]]
		bool updateSingle();

		[[nodiscard]]
		bool updateCross();

		[[nodiscard]]
		bool hasError() const noexcept;
	};
}

# include "detail/SceneManager.ipp"


/*
//
//	SceneManager example
//

# include <Siv3D.hpp>

struct GameData
{
	Font font = Font{ 50 };

	int32 score = 0;
};

using MyApp = SceneManager<String, GameData>;

struct Title : MyApp::Scene
{
	Title(const InitData& init)
		: IScene{ init }
	{
		Print << getState();
	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(U"Game", 2.0s);
		}
	}

	void draw() const override
	{
		getData().font(U"Title")
			.drawAt(Scene::Center());
	}
};

struct Game : MyApp::Scene
{
	Game(const InitData& init)
		: IScene{ init }
	{
		Print << getState();

		getData().score = 0;
	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(U"Result", 2.0s);
		}

		++getData().score;
	}

	void draw() const override
	{
		const Font& font = getData().font;

		font(U"Game")
			.drawAt(Scene::Center());

		font(getData().score)
			.drawAt(Scene::Center().movedBy(0, 60));
	}
};

struct Result : MyApp::Scene
{
	Result(const InitData& init)
		: IScene{ init }
	{
		Print << getState();
	}

	void update() override
	{
		if (MouseL.down())
		{
			changeScene(U"Title", 2.0s);
		}
	}

	void draw() const override
	{
		const Font& font = getData().font;

		font(U"Result")
			.drawAt(Scene::Center());

		font(getData().score)
			.drawAt(Scene::Center().movedBy(0, 60));
	}
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.5, 0.6, 0.7 });

	MyApp manager;
	manager
		.add<Title>(U"Title")
		.add<Game>(U"Game")
		.add<Result>(U"Result")
		.setFadeColor(ColorF{ 1.0 });

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}

*/