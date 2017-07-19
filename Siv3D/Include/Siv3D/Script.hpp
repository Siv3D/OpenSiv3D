//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"
# include "MessageBox.hpp"
# include "AssetHandle.hpp"
# include "NamedParameter.hpp"
# define AS_USE_NAMESPACE
# include "../../Include/ThirdParty/angelscript/angelscript.h"

namespace s3d
{
	struct ScriptModuleData
	{
		AngelScript::asIScriptModule* module = nullptr;

		AngelScript::asIScriptContext* context = nullptr;

		bool withoutLineCues = false;

		ScriptModuleData() = default;

		~ScriptModuleData();
	};

	namespace detail
	{
		extern uint64 scriptStepCounter;
	}

	inline void LineCallback(AngelScript::asIScriptContext* ctx, unsigned long*)
	{
		++detail::scriptStepCounter;

		if (detail::scriptStepCounter > 1'000'000)
		{
			ctx->Suspend();
		}
	}

	template <class Type>
	struct ScriptFunction;

	template <class Ret, class... Args>
	struct ScriptFunction<Ret(Args...)>
	{
	private:

		std::shared_ptr<ScriptModuleData> m_moduleData;

		AngelScript::asIScriptFunction* m_function = nullptr;

		template <class Type, class ... Args>
		void setArgs(uint32 argIndex, const Type& value, const Args& ... args) const
		{
			setArg(argIndex++, value);

			setArgs(argIndex, args...);
		}

		template <class Type>
		void setArgs(uint32 argIndex, const Type& value) const
		{
			setArg(argIndex++, value);
		}

		void setArgs(uint32) const
		{

		}

		template <class Type>
		void setArg(uint32 argIndex, const Type& value) const
		{
			m_moduleData->context->SetArgObject(argIndex, const_cast<Type*>(&value));
		}

		template <>
		void setArg<bool>(uint32 argIndex, const bool& value) const
		{
			m_moduleData->context->SetArgByte(argIndex, value);
		}

		template <>
		void setArg<int8>(uint32 argIndex, const int8& value) const
		{
			m_moduleData->context->SetArgByte(argIndex, value);
		}

		template <>
		void setArg<uint8>(uint32 argIndex, const uint8& value) const
		{
			m_moduleData->context->SetArgByte(argIndex, value);
		}

		template <>
		void setArg<int16>(uint32 argIndex, const int16& value) const
		{
			m_moduleData->context->SetArgWord(argIndex, value);
		}

		template <>
		void setArg<uint16>(uint32 argIndex, const uint16& value) const
		{
			m_moduleData->context->SetArgWord(argIndex, value);
		}

		template <>
		void setArg<int32>(uint32 argIndex, const int32& value) const
		{
			m_moduleData->context->SetArgDWord(argIndex, value);
		}

		template <>
		void setArg<uint32>(uint32 argIndex, const uint32& value) const
		{
			m_moduleData->context->SetArgDWord(argIndex, value);
		}

		template <>
		void setArg<int64>(uint32 argIndex, const int64& value) const
		{
			m_moduleData->context->SetArgQWord(argIndex, value);
		}

		template <>
		void setArg<uint64>(uint32 argIndex, const uint64& value) const
		{
			m_moduleData->context->SetArgQWord(argIndex, value);
		}

		template <>
		void setArg<float>(uint32 argIndex, const float& value) const
		{
			m_moduleData->context->SetArgFloat(argIndex, value);
		}

		template <>
		void setArg<double>(uint32 argIndex, const double& value) const
		{
			m_moduleData->context->SetArgDouble(argIndex, value);
		}

		bool execute() const
		{
			int32 steps = 0;

			if (!m_moduleData->withoutLineCues)
			{
				m_moduleData->context->SetLineCallback(asFUNCTION(LineCallback), &steps, AngelScript::asCALL_CDECL);
			}

			const int r = m_moduleData->context->Execute();

			if (r != AngelScript::asEXECUTION_FINISHED && r == AngelScript::asEXECUTION_EXCEPTION)
			{
				Log(L"[script error]An exception '{}' occurred. Please correct the code and try again."_fmt(
					CharacterSet::Widen(m_moduleData->context->GetExceptionString())));

				return false;
			}
			else if (r != AngelScript::asEXECUTION_FINISHED && r == AngelScript::asEXECUTION_SUSPENDED)
			{
				System::ShowMessageBox(L"現在の設定では 100 万回以上の処理はできません。");
				System::Exit();
			}

			return true;
		}

		template <class Type>
		Type getReturn() const
		{
			return *static_cast<Type*>(m_moduleData->context->GetReturnObject());
		}

		template <>
		void getReturn<void>() const
		{
			return;
		}

		template <>
		bool getReturn<bool>() const
		{
			return !!m_moduleData->context->GetReturnByte();
		}

		template <>
		int8 getReturn<int8>() const
		{
			return m_moduleData->context->GetReturnByte();
		}

		template <>
		uint8 getReturn<uint8>() const
		{
			return m_moduleData->context->GetReturnByte();
		}

		template <>
		int16 getReturn<int16>() const
		{
			return m_moduleData->context->GetReturnWord();
		}

		template <>
		uint16 getReturn<uint16>() const
		{
			return m_moduleData->context->GetReturnWord();
		}

		template <>
		int32 getReturn<int32>() const
		{
			return m_moduleData->context->GetReturnDWord();
		}

		template <>
		uint32 getReturn<uint32>() const
		{
			return m_moduleData->context->GetReturnDWord();
		}

		template <>
		int64 getReturn<int64>() const
		{
			return m_moduleData->context->GetReturnQWord();
		}

		template <>
		uint64 getReturn<uint64>() const
		{
			return m_moduleData->context->GetReturnQWord();
		}

		template <>
		float getReturn<float>() const
		{
			return m_moduleData->context->GetReturnFloat();
		}

		template <>
		double getReturn<double>() const
		{
			return m_moduleData->context->GetReturnDouble();
		}

	public:

		static constexpr size_t nargs = sizeof...(Args);

		template <size_t i>
		struct Arg
		{
			using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
		};

		ScriptFunction(const std::shared_ptr<ScriptModuleData>& moduleData, AngelScript::asIScriptFunction* function)
			: m_moduleData(moduleData)
			, m_function((moduleData && moduleData->module && moduleData->context) ? function : nullptr) {}

		Ret operator()(Args... args) const
		{
			if (!m_function)
			{
				return Ret();
			}

			m_moduleData->context->Prepare(m_function);

			setArgs(0, args...);

			if (!execute())
			{
				return Ret();
			}

			return getReturn<Ret>();
		}
	};

	struct ScriptCompileOption
	{
		enum Option
		{
			BuildWithoutLineCues = 0b00001,
		};
	};

	class Script
	{
	protected:

		class Handle {};

		using ScriptHandle = AssetHandle<Handle>;

		friend ScriptHandle::~AssetHandle();

		std::shared_ptr<ScriptHandle> m_handle;

		AngelScript::asIScriptFunction* _getFunction(const String& decl) const;

		std::shared_ptr<ScriptModuleData> _getModuleData() const;

	public:

		using IDType = ScriptHandle::IDType;

		static constexpr IDType NullHandleID = ScriptHandle::NullID;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Script();

		explicit Script(const FilePath& path, int32 compileOption = 0);

		//explicit Script(Arg::code_<String> code, int32 compileOption = 0);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Script();

		/// <summary>
		/// スクリプトをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じスクリプトが使われていない場合、スクリプトのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// スクリプトが空かどうかを示します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// スクリプトが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// スクリプトが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return !isEmpty();
		}

		/// <summary>
		/// スクリプトハンドルの ID を示します。
		/// </summary>
		IDType id() const;

		/// <summary>
		/// 2 つの Script が同じかどうかを返します。
		/// </summary>
		/// <param name="script">
		/// 比較する Script
		/// </param>
		/// <returns>
		/// 2 つの Script が同じ場合 true, それ以外の場合は false
		/// </returns>
		bool operator ==(const Script& script) const;

		/// <summary>
		/// 2 つの Script が異なるかどうかを返します。
		/// </summary>
		/// <param name="script">
		/// 比較する Script
		/// </param>
		/// <returns>
		/// 2 つの Script が異なる場合 true, それ以外の場合は false
		/// </returns>
		bool operator !=(const Script& script) const;

		template <class Fty>
		auto getFunction(const String& decl) const
		{
			const auto func = isEmpty() ? nullptr : _getFunction(decl);

			return ScriptFunction<Fty>(func ? _getModuleData() : nullptr, func);
		}

		bool compiled() const;
	};

	namespace ScriptManager
	{
		AngelScript::asIScriptEngine* GetEngine();
	}
}
