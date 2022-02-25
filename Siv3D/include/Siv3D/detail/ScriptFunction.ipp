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
	namespace detail
	{
		enum class ScriptUserDataIndex
		{
			ScriptID = 3000,

			StepCounter = 3001,
		};

		[[nodiscard]]
		String GetDeclaration(AngelScript::asIScriptFunction* function, bool includeParamNames);

		[[nodiscard]]
		bool Execute(const std::shared_ptr<ScriptModule>& module);

		[[nodiscard]]
		Optional<String> TryExecute(const std::shared_ptr<ScriptModule>& module);

		void LineCallback(AngelScript::asIScriptContext* context, unsigned long*);

		template <class Type>
		inline void SetArg_(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const Type& value)
		{
			module->context->SetArgObject(argIndex, const_cast<Type*>(&value));
		}

		template <class Type>
		inline void SetArg_(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, Type& value)
		{
			module->context->SetArgObject(argIndex, &value);
		}

		template <class Type>
		inline void SetArg(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const Type& value)
		{
			SetArg_<std::decay_t<Type>>(module, argIndex, value);
		}

		template <class Type>
		inline void SetArg(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, Type& value)
		{
			SetArg_<std::decay_t<Type>&>(module, argIndex, value);
		}

		template <>
		void SetArg<bool>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const bool& value);

		template <>
		void SetArg<bool&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, bool& value);

		template <>
		void SetArg<int8>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const int8& value);

		template <>
		void SetArg<int8&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, int8& value);

		template <>
		void SetArg<uint8>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const uint8& value);

		template <>
		void SetArg<uint8&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, uint8& value);

		template <>
		void SetArg<int16>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const int16& value);

		template <>
		void SetArg<int16&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, int16& value);

		template <>
		void SetArg<uint16>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const uint16& value);

		template <>
		void SetArg<uint16&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, uint16& value);

		template <>
		void SetArg<int32>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const int32& value);

		template <>
		void SetArg<int32&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, int32& value);

		template <>
		void SetArg<uint32>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const uint32& value);

		template <>
		void SetArg<uint32&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, uint32& value);

		template <>
		void SetArg<int64>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const int64& value);

		template <>
		void SetArg<int64&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, int64& value);

		template <>
		void SetArg<uint64>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const uint64& value);

		template <>
		void SetArg<uint64&>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, uint64& value);

		template <>
		void SetArg<float>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const float& value);

		template <>
		void SetArg<double>(const std::shared_ptr<ScriptModule>& module, uint32 argIndex, const double& value);

		template <class Type>
		inline Type GetReturnValue(const std::shared_ptr<ScriptModule>& module)
		{
			return *static_cast<Type*>(module->context->GetReturnObject());
		}

		template <>
		void GetReturnValue<void>(const std::shared_ptr<ScriptModule>&);

		template <>
		bool GetReturnValue<bool>(const std::shared_ptr<ScriptModule>& module);

		template <>
		int8 GetReturnValue<int8>(const std::shared_ptr<ScriptModule>& module);

		template <>
		uint8 GetReturnValue<uint8>(const std::shared_ptr<ScriptModule>& module);

		template <>
		int16 GetReturnValue<int16>(const std::shared_ptr<ScriptModule>& module);

		template <>
		uint16 GetReturnValue<uint16>(const std::shared_ptr<ScriptModule>& module);

		template <>
		int32 GetReturnValue<int32>(const std::shared_ptr<ScriptModule>& module);

		template <>
		uint32 GetReturnValue<uint32>(const std::shared_ptr<ScriptModule>& module);

		template <>
		int64 GetReturnValue<int64>(const std::shared_ptr<ScriptModule>& module);

		template <>
		uint64 GetReturnValue<uint64>(const std::shared_ptr<ScriptModule>& module);

		template <>
		float GetReturnValue<float>(const std::shared_ptr<ScriptModule>& module);

		template <>
		double GetReturnValue<double>(const std::shared_ptr<ScriptModule>& module);
	}

	template <class Ret, class... Args>
	inline ScriptFunction<Ret(Args...)>::ScriptFunction(const std::shared_ptr<ScriptModule>& module, AngelScript::asIScriptFunction* function)
		: m_module{ module }
		, m_function{ function } {}

	template <class Ret, class... Args>
	inline ScriptFunction<Ret(Args...)>::operator bool() const noexcept
	{
		return static_cast<bool>(m_function);
	}

	template <class Ret, class... Args>
	inline Ret ScriptFunction<Ret(Args...)>::operator()(Args... args) const
	{
		if (not m_function)
		{
			return Ret{};
		}

		m_module->context->Prepare(m_function);

		setArgs(0, std::forward<Args>(args)...);

		if (not execute())
		{
			return Ret{};
		}

		return getReturn<Ret>();
	}

	template <class Ret, class... Args>
	inline Ret ScriptFunction<Ret(Args...)>::tryCall(Args... args, String& exception) const
	{
		if (not m_function)
		{
			return Ret();
		}

		m_module->context->Prepare(m_function);

		setArgs(0, std::forward<Args>(args)...);

		if (const auto ex = tryExecute())
		{
			exception = ex.value();

			return Ret();
		}
		else
		{
			exception.clear();
		}

		return getReturn<Ret>();
	}

	template <class Ret, class... Args>
	inline String ScriptFunction<Ret(Args...)>::getDeclaration(const IncludeParamNames includeParamNames) const
	{
		return detail::GetDeclaration(m_function, includeParamNames.getBool());
	}

	template <class Ret, class... Args>
	template <class Type, class ... Args2>
	inline void ScriptFunction<Ret(Args...)>::setArgs(uint32 argIndex, Type&& value, Args2&&... args) const
	{
		setArg(argIndex++, std::forward<Type>(value));

		setArgs(argIndex, std::forward<Args2>(args)...);
	}

	template <class Ret, class... Args>
	template <class Type>
	inline void ScriptFunction<Ret(Args...)>::setArgs(uint32 argIndex, Type&& value) const
	{
		setArg(argIndex++, std::forward<Type>(value));
	}

	template <class Ret, class... Args>
	inline void ScriptFunction<Ret(Args...)>::setArgs(uint32) const {}

	template <class Ret, class... Args>
	template <class Type>
	inline void ScriptFunction<Ret(Args...)>::setArg(const uint32 argIndex, Type&& value) const
	{
		detail::SetArg<Type>(m_module, argIndex, std::forward<Type>(value));
	}

	template <class Ret, class... Args>
	inline bool ScriptFunction<Ret(Args...)>::execute() const
	{
		return detail::Execute(m_module);
	}

	template <class Ret, class... Args>
	inline Optional<String> ScriptFunction<Ret(Args...)>::tryExecute() const
	{
		return detail::TryExecute(m_module);
	}

	template <class Ret, class... Args>
	template <class Type>
	inline Type ScriptFunction<Ret(Args...)>::getReturn() const
	{
		return detail::GetReturnValue<Type>(m_module);
	}
}
