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

# pragma once

namespace s3d
{
	template <class Ret, class... Args>
	inline ScriptFunction<Ret(Args...)>::ScriptFunction(const std::shared_ptr<ScriptModule>& module, AngelScript::asIScriptFunction* function)
		: m_module{ module }
		, m_function{ function } {}

	template <class Ret, class... Args>
	inline ScriptFunction<Ret(Args...)>::operator bool() const noexcept
	{
		return static_cast<bool>(m_function);
	}
}
