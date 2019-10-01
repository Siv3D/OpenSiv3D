//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Siv3D/Print.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include "IScript.hpp"

namespace s3d
{
	ScriptModuleData::~ScriptModuleData()
	{
		if (context)
		{
			context->Release();
		}
	}

	namespace detail
	{
		uint64 scriptStepCounter = 0;

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
		void SetArg<bool>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const bool& value)
		{
			moduleData->context->SetArgByte(argIndex, value);
		}

		template <>
		void SetArg<bool&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, bool& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int8>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const int8& value)
		{
			moduleData->context->SetArgByte(argIndex, value);
		}

		template <>
		void SetArg<int8&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, int8& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint8>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const uint8& value)
		{
			moduleData->context->SetArgByte(argIndex, value);
		}

		template <>
		void SetArg<uint8&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, uint8& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int16>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const int16& value)
		{
			moduleData->context->SetArgWord(argIndex, value);
		}

		template <>
		void SetArg<int16&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, int16& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint16>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const uint16& value)
		{
			moduleData->context->SetArgWord(argIndex, value);
		}

		template <>
		void SetArg<uint16&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, uint16& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int32>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const int32& value)
		{
			moduleData->context->SetArgDWord(argIndex, value);
		}

		template <>
		void SetArg<int32&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, int32& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint32>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const uint32& value)
		{
			moduleData->context->SetArgDWord(argIndex, value);
		}

		template <>
		void SetArg<uint32&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, uint32& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<int64>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const int64& value)
		{
			moduleData->context->SetArgQWord(argIndex, value);
		}

		template <>
		void SetArg<int64&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, int64& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<uint64>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const uint64& value)
		{
			moduleData->context->SetArgQWord(argIndex, value);
		}

		template <>
		void SetArg<uint64&>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, uint64& value)
		{
			moduleData->context->SetArgAddress(argIndex, reinterpret_cast<void*>(&value));
		}

		template <>
		void SetArg<float>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const float& value)
		{
			moduleData->context->SetArgFloat(argIndex, value);
		}

		template <>
		void SetArg<double>(const std::shared_ptr<ScriptModuleData>& moduleData, uint32 argIndex, const double& value)
		{
			moduleData->context->SetArgDouble(argIndex, value);
		}


		template <>
		void GetReturnValue<void>(const std::shared_ptr<ScriptModuleData>&)
		{
			return;
		}

		template <>
		bool GetReturnValue<bool>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return !!moduleData->context->GetReturnByte();
		}

		template <>
		int8 GetReturnValue<int8>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnByte();
		}

		template <>
		uint8 GetReturnValue<uint8>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnByte();
		}

		template <>
		int16 GetReturnValue<int16>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnWord();
		}

		template <>
		uint16 GetReturnValue<uint16>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnWord();
		}

		template <>
		int32 GetReturnValue<int32>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnDWord();
		}

		template <>
		uint32 GetReturnValue<uint32>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnDWord();
		}

		template <>
		int64 GetReturnValue<int64>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnQWord();
		}

		template <>
		uint64 GetReturnValue<uint64>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnQWord();
		}

		template <>
		float GetReturnValue<float>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnFloat();
		}

		template <>
		double GetReturnValue<double>(const std::shared_ptr<ScriptModuleData>& moduleData)
		{
			return moduleData->context->GetReturnDouble();
		}
	}

	template <>
	AssetHandle<Script::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Script` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Script::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Script` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Script::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DScript>())
		{
			p->release(m_id);
		}
	}

	Script::Script()
		: m_handle(std::make_shared<ScriptHandle>())
	{

	}

	Script::Script(const FilePath& path, const int32 compileOption)
		: m_handle(std::make_shared<ScriptHandle>(Siv3DEngine::Get<ISiv3DScript>()->createFromFile(path, compileOption)))
	{

	}

	Script::Script(Arg::code_<String> code, const int32 compileOption)
		: m_handle(std::make_shared<ScriptHandle>(Siv3DEngine::Get<ISiv3DScript>()->createFromCode(*code, compileOption)))
	{

	}

	Script::~Script()
	{

	}

	void Script::release()
	{
		m_handle = std::make_shared<ScriptHandle>();
	}

	bool Script::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	ScriptID Script::id() const
	{
		return m_handle->id();
	}

	bool Script::operator ==(const Script& script) const
	{
		return m_handle->id() == script.m_handle->id();
	}

	bool Script::operator !=(const Script& script) const
	{
		return m_handle->id() != script.m_handle->id();
	}

	bool Script::compiled() const
	{
		return Siv3DEngine::Get<ISiv3DScript>()->compiled(m_handle->id());
	}

	void Script::setSystemUpdateCallback(const std::function<bool(void)>& callback)
	{
		Siv3DEngine::Get<ISiv3DScript>()->setSystemUpdateCallback(m_handle->id(), callback);
	}

	void Script::clearSystemUpdateCallback()
	{
		Siv3DEngine::Get<ISiv3DScript>()->setSystemUpdateCallback(m_handle->id(), std::function<bool(void)>());
	}

	bool Script::reload(const int32 compileOption)
	{
		return Siv3DEngine::Get<ISiv3DScript>()->reload(m_handle->id(), compileOption);
	}

	const Array<String>& Script::getMessages() const
	{
		return Siv3DEngine::Get<ISiv3DScript>()->retrieveMessages(m_handle->id());
	}

	const FilePath& Script::path() const
	{
		return Siv3DEngine::Get<ISiv3DScript>()->path(m_handle->id());
	}

	AngelScript::asIScriptFunction* Script::_getFunction(const String& decl) const
	{
		return Siv3DEngine::Get<ISiv3DScript>()->getFunction(m_handle->id(), decl);
	}

	std::shared_ptr<ScriptModuleData> Script::_getModuleData() const
	{
		return Siv3DEngine::Get<ISiv3DScript>()->getModuleData(m_handle->id());
	}

	namespace ScriptManager
	{
		AngelScript::asIScriptEngine* GetEngine()
		{
			return Siv3DEngine::Get<ISiv3DScript>()->getEngine();
		}
	}
}
