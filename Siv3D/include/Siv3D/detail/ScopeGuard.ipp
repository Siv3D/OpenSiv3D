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
	template <class Callback>
	ScopeGuard<Callback>::ScopeGuard(ScopeGuard&& other) noexcept(std::is_nothrow_constructible_v<Callback, Callback&&>)
		: m_callback{ std::forward<Callback>(other.m_callback) }
		, m_active{ other.m_active }
	{
		other.m_active = false;
	}

	template <class Callback>
	ScopeGuard<Callback>::ScopeGuard(Callback&& callback) noexcept(std::is_nothrow_constructible_v<Callback, Callback&&>)
		: m_callback{ std::forward<Callback>(callback) } {}

	template <class Callback>
	ScopeGuard<Callback>::~ScopeGuard() noexcept(std::is_nothrow_invocable_v<Callback>&& std::is_nothrow_destructible_v<Callback>)
	{
		if (m_active)
		{
			m_callback();
		}
	}

	template <class Callback>
	void ScopeGuard<Callback>::dismiss() noexcept
	{
		m_active = false;
	}
}
