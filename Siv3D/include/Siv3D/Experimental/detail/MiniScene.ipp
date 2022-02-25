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
	template <class State>
	MiniScene<State>::~MiniScene()
	{
		if (not m_currentState
			|| m_scenes.empty())
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

	template <class State>
	typename MiniScene<State>::SceneFunction& MiniScene<State>::operator [](const State& state)
	{
		if (not m_currentState)
		{
			m_currentState = state;
		}

		return m_scenes[state];
	}

	template <class State>
	void MiniScene<State>::changeState(const State& state)
	{
		if (not m_scenes.contains(state))
		{
			return;
		}

		*m_currentState = state;
	}
}
