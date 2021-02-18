//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

namespace s3d
{
	template <class State, class Data> class SceneManager;

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

			SceneManager<State_t, Data_t>* _m;

			SIV3D_NODISCARD_CXX20
			InitData() = default;

			SIV3D_NODISCARD_CXX20
			InitData(const State_t& _state, const std::shared_ptr<Data_t>& data, SceneManager<State_t, Data_t>* manager);
		};

	public:

		SIV3D_NODISCARD_CXX20
		explicit IScene(const InitData& init);

		virtual ~IScene() = default;

		virtual void updateFadeIn(double) {}

		virtual void update() {}

		virtual void updateFadeOut(double) {}

		virtual void draw() const {}

		virtual void drawFadeIn(double t) const;

		virtual void drawFadeOut(double t) const;

	protected:

		[[nodiscard]]
		const State_t& getState() const;

		[[nodiscard]]
		Data_t& getData() const;

		bool changeScene(const State_t& state, const Duration& transitionTime = Milliseconds{ 1000 }, bool crossFade = false);

		bool changeScene(const State_t& state, int32 transitionTimeMillisec, bool crossFade = false);

		void notifyError();

	private:

		State_t m_state;

		std::shared_ptr<Data_t> m_data;

		SceneManager<State_t, Data_t>* m_manager;
	};

	template <class State, class Data = void>
	class SceneManager
	{
	public:

		using Scene = IScene<State, Data>;

		SIV3D_NODISCARD_CXX20
		SceneManager();

		SIV3D_NODISCARD_CXX20
		explicit SceneManager(const std::shared_ptr<Data>& data);

		template <class Scene>
		SceneManager& add(const State& state);

		bool init(const State& state);

		bool updateScene();

		void drawScene() const;

		bool update();

		[[nodiscard]]
		std::shared_ptr<Data> get() noexcept;

		[[nodiscard]]
		const std::shared_ptr<const Data> get() const noexcept;

		bool changeScene(const State& state, int32 transitionTimeMillisec, bool crossFade);

		SceneManager& setFadeColor(const ColorF& color);

		[[nodiscard]]
		const ColorF& getFadeColor() const noexcept;

		void notifyError() noexcept;

	private:

		using Scene_t = std::shared_ptr<IScene<State, Data>>;

		using FactoryFunction_t = std::function<Scene_t()>;

		HashTable<State, FactoryFunction_t> m_factories;

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

		bool updateSingle();

		bool updateCross();

		[[nodiscard]]
		bool hasError() const noexcept;
	};
}

# include "detail/SceneManager.ipp"
