//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		String GetDeclaration(AngelScript::asIScriptFunction* function, const bool includeParamNames)
		{
			if (not function)
			{
				return{};
			}

			return Unicode::Widen(function->GetDeclaration(true, true, includeParamNames));
		}

		bool Execute(const std::shared_ptr<ScriptModule>& module)
		{
			int32 steps = 0;

			if (module->withLineCues)
			{
				module->context->SetLineCallback(asFUNCTION(detail::LineCallback), &steps, AngelScript::asCALL_CDECL);
			}

			uint64 scriptID = module->scriptID;
			uint64 scriptStepCounter = 0;
			module->context->SetUserData(&scriptID, FromEnum(detail::ScriptUserDataIndex::ScriptID));
			module->context->SetUserData(&scriptStepCounter, FromEnum(detail::ScriptUserDataIndex::StepCounter));

			const int32 r = module->context->Execute();

			if (r == AngelScript::asEXECUTION_EXCEPTION)
			{
				LOG_ERROR(U"[script exception]" + Unicode::Widen(module->context->GetExceptionString()));
				return false;
			}
			else if (r == AngelScript::asEXECUTION_SUSPENDED)
			{
				System::Exit();
			}

			return true;
		}

		Optional<String> TryExecute(const std::shared_ptr<ScriptModule>& module)
		{
			int32 steps = 0;

			if (module->withLineCues)
			{
				module->context->SetLineCallback(asFUNCTION(detail::LineCallback), &steps, AngelScript::asCALL_CDECL);
			}

			uint64 scriptID = module->scriptID;
			uint64 scriptStepCounter = 0;
			module->context->SetUserData(&scriptID, FromEnum(detail::ScriptUserDataIndex::ScriptID));
			module->context->SetUserData(&scriptStepCounter, FromEnum(detail::ScriptUserDataIndex::StepCounter));

			const int32 r = module->context->Execute();

			if (r == AngelScript::asEXECUTION_EXCEPTION)
			{
				return Unicode::Widen(module->context->GetExceptionString());
			}
			else if (r == AngelScript::asEXECUTION_SUSPENDED)
			{
				System::Exit();
			}

			return none;
		}

		void LineCallback(AngelScript::asIScriptContext* ctx, unsigned long*)
		{
			uint64* stepCounter = static_cast<uint64*>(ctx->GetUserData(AngelScript::asPWORD(static_cast<uint32>(ScriptUserDataIndex::StepCounter))));

			++(*stepCounter);

			if ((*stepCounter) > 1'000'000)
			{
				ctx->Suspend();
			}
		}

		template <>
		void SetArg<bool>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const bool& value)
		{
			module->context->SetArgByte(argIndex, value);
		}

		template <>
		void SetArg<bool&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, bool& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int8>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const int8& value)
		{
			module->context->SetArgByte(argIndex, value);
		}

		template <>
		void SetArg<int8&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, int8& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint8>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const uint8& value)
		{
			module->context->SetArgByte(argIndex, value);
		}

		template <>
		void SetArg<uint8&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, uint8& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int16>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const int16& value)
		{
			module->context->SetArgWord(argIndex, value);
		}

		template <>
		void SetArg<int16&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, int16& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint16>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const uint16& value)
		{
			module->context->SetArgWord(argIndex, value);
		}

		template <>
		void SetArg<uint16&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, uint16& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int32>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const int32& value)
		{
			module->context->SetArgDWord(argIndex, value);
		}

		template <>
		void SetArg<int32&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, int32& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint32>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const uint32& value)
		{
			module->context->SetArgDWord(argIndex, value);
		}

		template <>
		void SetArg<uint32&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, uint32& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int64>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const int64& value)
		{
			module->context->SetArgQWord(argIndex, value);
		}

		template <>
		void SetArg<int64&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, int64& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint64>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const uint64& value)
		{
			module->context->SetArgQWord(argIndex, value);
		}

		template <>
		void SetArg<uint64&>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, uint64& value)
		{
			module->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<float>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const float& value)
		{
			module->context->SetArgFloat(argIndex, value);
		}

		template <>
		void SetArg<double>(const std::shared_ptr<ScriptModule>& module, const uint32 argIndex, const double& value)
		{
			module->context->SetArgDouble(argIndex, value);
		}


		template <>
		void GetReturnValue<void>(const std::shared_ptr<ScriptModule>&)
		{
			return;
		}

		template <>
		bool GetReturnValue<bool>(const std::shared_ptr<ScriptModule>& module)
		{
			return !!module->context->GetReturnByte();
		}

		template <>
		int8 GetReturnValue<int8>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnByte();
		}

		template <>
		uint8 GetReturnValue<uint8>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnByte();
		}

		template <>
		int16 GetReturnValue<int16>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnWord();
		}

		template <>
		uint16 GetReturnValue<uint16>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnWord();
		}

		template <>
		int32 GetReturnValue<int32>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnDWord();
		}

		template <>
		uint32 GetReturnValue<uint32>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnDWord();
		}

		template <>
		int64 GetReturnValue<int64>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnQWord();
		}

		template <>
		uint64 GetReturnValue<uint64>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnQWord();
		}

		template <>
		float GetReturnValue<float>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnFloat();
		}

		template <>
		double GetReturnValue<double>(const std::shared_ptr<ScriptModule>& module)
		{
			return module->context->GetReturnDouble();
		}
	}
}
