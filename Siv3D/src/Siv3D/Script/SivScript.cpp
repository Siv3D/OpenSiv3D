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

# include "../Siv3DEngine.hpp"
# include "IScript.hpp"

namespace s3d
{
	namespace detail
	{
		uint64 scriptStepCounter = 0;
	}

	template <>
	AssetHandle<Script::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetScript())
		{
			p->release(m_id);
		}
	}

	Script::Script()
		: m_handle(std::make_shared<ScriptHandle>())
	{

	}

	Script::Script(const FilePath& path, const int32 compileOption)
		: m_handle(std::make_shared<ScriptHandle>(Siv3DEngine::GetScript()->createFromFile(path, compileOption)))
	{

	}

	Script::Script(Arg::code_<String> code, const int32 compileOption)
		: m_handle(std::make_shared<ScriptHandle>(Siv3DEngine::GetScript()->createFromCode(*code, compileOption)))
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
		return Siv3DEngine::GetScript()->compiled(m_handle->id());
	}

	AngelScript::asIScriptFunction* Script::_getFunction(const String& decl) const
	{
		return Siv3DEngine::GetScript()->getFunction(m_handle->id(), decl);
	}

	std::shared_ptr<ScriptModuleData> Script::_getModuleData() const
	{
		return Siv3DEngine::GetScript()->getModuleData(m_handle->id());
	}

	namespace ScriptManager
	{
		AngelScript::asIScriptEngine* GetEngine()
		{
			return Siv3DEngine::GetScript()->getEngine();
		}
	}
}
