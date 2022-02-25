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
# include "Common.hpp"

namespace s3d
{
	template <class Callback>
	class ScopeGuard final
	{
	public:

		ScopeGuard() = delete;

		ScopeGuard(const ScopeGuard&) = delete;

		SIV3D_NODISCARD_CXX20
		ScopeGuard(ScopeGuard&& other) noexcept(std::is_nothrow_constructible_v<Callback, Callback&&>);

		SIV3D_NODISCARD_CXX20
		ScopeGuard(Callback&& callback) noexcept(std::is_nothrow_constructible_v<Callback, Callback&&>);

		~ScopeGuard() noexcept(std::is_nothrow_invocable_v<Callback> && std::is_nothrow_destructible_v<Callback>);

		ScopeGuard& operator =(const ScopeGuard&) = delete;

		void dismiss() noexcept;

	private:

		Callback m_callback;

		bool m_active = true;
	};

	template <class Callback>
	ScopeGuard(Callback) -> ScopeGuard<Callback>;
}

# include "detail/ScopeGuard.ipp"
