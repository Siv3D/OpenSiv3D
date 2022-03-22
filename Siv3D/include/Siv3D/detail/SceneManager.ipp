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

namespace s3d
{
	template <class State, class Data>
	inline IScene<State, Data>::InitData::InitData(const State_t& _state, const std::shared_ptr<Data_t>& data, SceneManager<State_t, Data_t>*& manager)
		: state{ _state }
		, _s{ data }
		, _m{ manager } {}

	template <class State, class Data>
	inline IScene<State, Data>::IScene(const InitData& init)
		: m_state{ init.state }
		, m_data{ init._s }
		, m_manager{ init._m } {}

	template <class State, class Data>
	inline void IScene<State, Data>::drawFadeIn(const double t) const
	{
		draw();

		Transformer2D transform{ Mat3x2::Identity(), Transformer2D::Target::SetLocal };

		Scene::Rect().draw(ColorF{ m_manager->getFadeColor(), (1.0 - t) });
	}

	template <class State, class Data>
	inline void IScene<State, Data>::drawFadeOut(const double t) const
	{
		draw();

		Transformer2D transform{ Mat3x2::Identity(), Transformer2D::Target::SetLocal };

		Scene::Rect().draw(ColorF{ m_manager->getFadeColor(), t });
	}

	template <class State, class Data>
	inline const typename IScene<State, Data>::State_t& IScene<State, Data>::getState() const
	{
		return m_state;
	}

	template <class State, class Data>
	template <class DataType, std::enable_if_t<not std::disjunction_v<std::is_array<DataType>, std::is_void<DataType>>>*>
	inline DataType& IScene<State, Data>::getData() const
	{
		return *m_data;
	}

	template <class State, class Data>
	inline bool IScene<State, Data>::changeScene(const State_t& state, const Duration& transitionTime, const CrossFade crossFade)
	{
		return changeScene(state, static_cast<int32>(transitionTime.count() * 1000), crossFade);
	}

	template <class State, class Data>
	inline bool IScene<State, Data>::changeScene(const State_t& state, const int32 transitionTimeMillisec, const CrossFade crossFade)
	{
		return m_manager->changeScene(state, transitionTimeMillisec, crossFade);
	}

	template <class State, class Data>
	inline void IScene<State, Data>::notifyError()
	{
		return m_manager->notifyError();
	}


	template <class State, class Data>
	inline SceneManager<State, Data>::SceneManager()
		: m_sceneManagerPtr{ std::make_unique<SceneManager*>(this) }
	{
		if constexpr (not std::is_void_v<Data>)
		{
			m_data = std::make_shared<Data>();
		}
	}

	template <class State, class Data>
	inline SceneManager<State, Data>::SceneManager(SceneManager&& other) noexcept
		: m_sceneManagerPtr{ std::move(other.m_sceneManagerPtr) }
		, m_factories{ std::move(other.m_factories) }
		, m_data{ std::move(other.m_data) }
		, m_current{ std::move(other.m_current) }
		, m_next{ std::move(other.m_next) }
		, m_currentState{ std::move(other.m_currentState) }
		, m_nextState{ std::move(other.m_nextState) }
		, m_first{ std::move(other.m_first) }
		, m_transitionState{ std::move(other.m_transitionState) }
		, m_stopwatch{ std::move(other.m_stopwatch) }
		, m_transitionTimeMillisec{ std::move(other.m_transitionTimeMillisec) }
		, m_fadeColor{ std::move(other.m_fadeColor) }
		, m_crossFade{ std::move(other.m_crossFade) }
		, m_error{ std::move(other.m_error) }
	{
		*m_sceneManagerPtr = this;
	}

	template <class State, class Data>
	inline SceneManager<State, Data>::SceneManager(const std::shared_ptr<Data>& data)
		: m_sceneManagerPtr{ std::make_unique<SceneManager*>(this) }
		, m_data{ data } {}

	template <class State, class Data>
	inline SceneManager<State, Data>& SceneManager<State, Data>::operator =(SceneManager&& other) noexcept
	{
		m_sceneManagerPtr			= std::move(other.m_sceneManagerPtr);
		m_factories					= std::move(other.m_factories);
		m_data						= std::move(other.m_data);
		m_current					= std::move(other.m_current);
		m_next						= std::move(other.m_next);
		m_currentState				= std::move(other.m_currentState);
		m_nextState					= std::move(other.m_nextState);
		m_first						= std::move(other.m_first);
		m_transitionState			= std::move(other.m_transitionState);
		m_stopwatch					= std::move(other.m_stopwatch);
		m_transitionTimeMillisec	= std::move(other.m_transitionTimeMillisec);
		m_fadeColor					= std::move(other.m_fadeColor);
		m_crossFade					= std::move(other.m_crossFade);
		m_error						= std::move(other.m_error);
		*m_sceneManagerPtr			= this;
		return *this;
	}

	template <class State, class Data>
	template <class SceneType>
	inline SceneManager<State, Data>& SceneManager<State, Data>::add(const State& state)
	{
		typename SceneType::InitData initData{ state, m_data, *m_sceneManagerPtr };

		auto factory = [=]() {
			return std::make_shared<SceneType>(initData);
		};

		auto it = m_factories.find(state);

		if (it != m_factories.end())
		{
			it->second = factory;
		}
		else
		{
			m_factories.emplace(state, factory);

			if (not m_first)
			{
				m_first = state;
			}
		}

		return *this;
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::init(const State& state)
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

	template <class State, class Data>
	inline bool SceneManager<State, Data>::updateScene()
	{
		if (hasError())
		{
			return false;
		}

		if (not m_current)
		{
			if (not m_first)
			{
				return true;
			}
			else if (not init(*m_first))
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

	template <class State, class Data>
	inline void SceneManager<State, Data>::drawScene() const
	{
		if (not m_current)
		{
			return;
		}

		if ((m_transitionState == TransitionState::Active)
			|| (m_transitionTimeMillisec <= 0))
		{
			m_current->draw();
		}

		const double elapsed = m_stopwatch.msF();
		const double t = (m_transitionTimeMillisec ? (elapsed / m_transitionTimeMillisec) : 1.0);

		if (m_transitionState == TransitionState::FadeIn)
		{
			m_current->drawFadeIn(t);
		}
		else if (m_transitionState == TransitionState::FadeOut)
		{
			m_current->drawFadeOut(t);
		}
		else if (m_transitionState == TransitionState::FadeInOut)
		{
			m_current->drawFadeOut(t);

			if (m_next)
			{
				m_next->drawFadeIn(t);
			}
		}
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::update()
	{
		if (not updateScene())
		{
			return false;
		}

		drawScene();

		return true;
	}

	template <class State, class Data>
	inline std::shared_ptr<Data> SceneManager<State, Data>::get() noexcept
	{
		return m_data;
	}

	template <class State, class Data>
	inline const std::shared_ptr<const Data> SceneManager<State, Data>::get() const noexcept
	{
		return m_data;
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::changeScene(const State& state, const Duration& transitionTime, const CrossFade crossFade)
	{
		return changeScene(state, static_cast<int32>(transitionTime.count() * 1000), crossFade);
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::changeScene(const State& state, const int32 transitionTimeMillisec, CrossFade crossFade)
	{
		if (state == m_currentState)
		{
			crossFade = CrossFade::No;
		}

		if (not m_factories.contains(state))
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

	template <class State, class Data>
	inline SceneManager<State, Data>& SceneManager<State, Data>::setFadeColor(const ColorF& color) noexcept
	{
		m_fadeColor = color;

		return *this;
	}

	template <class State, class Data>
	inline const ColorF& SceneManager<State, Data>::getFadeColor() const noexcept
	{
		return m_fadeColor;
	}

	template <class State, class Data>
	inline void SceneManager<State, Data>::notifyError() noexcept
	{
		m_error = true;
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::updateSingle()
	{
		double elapsed = m_stopwatch.msF();

		if ((m_transitionState == TransitionState::FadeOut)
			&& (m_transitionTimeMillisec <= elapsed))
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

		if ((m_transitionState == TransitionState::FadeIn)
			&& (m_transitionTimeMillisec <= elapsed))
		{
			m_stopwatch.reset();

			m_transitionState = TransitionState::Active;
		}

		const double t = (m_transitionTimeMillisec ? (elapsed / m_transitionTimeMillisec) : 1.0);

		switch (m_transitionState)
		{
		case TransitionState::FadeIn:
			m_current->updateFadeIn(t);
			break;
		case TransitionState::Active:
			m_current->update();
			break;
		case TransitionState::FadeOut:
			m_current->updateFadeOut(t);
			break;
		default:
			return false;
		}

		return (not hasError());
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::updateCross()
	{
		const double elapsed = m_stopwatch.msF();

		if ((m_transitionState == TransitionState::FadeInOut)
			&& (m_transitionTimeMillisec <= elapsed))
		{
			m_current = m_next;

			m_next = nullptr;

			m_stopwatch.reset();

			m_transitionState = TransitionState::Active;
		}

		if (m_transitionState == TransitionState::Active)
		{
			m_current->update();
		}
		else
		{
			assert(m_transitionTimeMillisec);

			const double t = (m_transitionTimeMillisec ? (elapsed / m_transitionTimeMillisec) : 1.0);

			m_current->updateFadeOut(t);

			if (hasError())
			{
				return false;
			}

			m_next->updateFadeIn(t);
		}

		return (not hasError());
	}

	template <class State, class Data>
	inline bool SceneManager<State, Data>::hasError() const noexcept
	{
		return m_error;
	}
}
