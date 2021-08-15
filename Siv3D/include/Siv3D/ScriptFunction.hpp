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
# include "Common.hpp"

namespace s3d
{
	template <class Type>
	struct ScriptFunction;

	template <class Ret, class... Args>
	struct ScriptFunction<Ret(Args...)>
	{
	public:

		static constexpr size_t nargs = (sizeof...(Args));

		template <size_t i>
		struct Arg
		{
			using type = typename std::tuple_element_t<i, std::tuple<Args...>>;
		};

		SIV3D_NODISCARD_CXX20
		ScriptFunction() = default;

		SIV3D_NODISCARD_CXX20
		ScriptFunction(const std::shared_ptr<ScriptModule>& module, AngelScript::asIScriptFunction* function);

		[[nodiscard]]
		explicit operator bool() const noexcept;

		Ret operator()(Args... args) const;

		Ret tryCall(Args... args, String& exception) const;

	private:

		std::shared_ptr<ScriptModule> m_module;

		AngelScript::asIScriptFunction* m_function = nullptr;
	};
}

# include "detail/ScriptFunction.ipp"
