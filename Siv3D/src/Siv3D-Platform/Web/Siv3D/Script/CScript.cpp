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

# include <Siv3D/Script/CScript.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	__attribute__((weak)) CScript::CScript() {}

	__attribute__((weak)) CScript::~CScript()
	{
		LOG_SCOPED_TRACE(U"CScript::~CScript()");

		shutdown();
	}

	__attribute__((weak)) void CScript::init()
	{
		LOG_SCOPED_TRACE(U"CScript::init()");

        m_initialized = true;
	}

	__attribute__((weak)) void CScript::shutdown()
	{
		if (not m_initialized)
		{
			return;
		}

		LOG_SCOPED_TRACE(U"CScript::shutdown()");

		m_initialized = false;
	}

	__attribute__((weak)) Script::IDType CScript::createFromCode(const StringView code, const ScriptCompileOption compileOption)
	{
		return Script::IDType::NullAsset();
	}

	__attribute__((weak)) Script::IDType CScript::createFromFile(const FilePathView path, const ScriptCompileOption compileOption)
	{
		return Script::IDType::NullAsset();
	}

	__attribute__((weak)) void CScript::release(const Script::IDType handleID)
	{
		
	}

	__attribute__((weak)) bool CScript::compiled(const Script::IDType handleID)
	{
		return false;
	}

	__attribute__((weak)) bool CScript::reload(const Script::IDType handleID, const ScriptCompileOption compileOption)
	{
		return false;
	}
	
	__attribute__((weak)) const std::shared_ptr<ScriptModule>& CScript::getModule(const Script::IDType handleID)
	{
		return m_scripts[handleID]->getModule();
	}
	
	__attribute__((weak)) AngelScript::asIScriptFunction* CScript::getFunction(const Script::IDType handleID, const StringView decl)
	{
		return nullptr;
	}

	__attribute__((weak)) Array<String> CScript::getFunctionDeclarations(const Script::IDType handleID, const IncludeParamNames includeParamNames)
	{
		return{};
	}

	__attribute__((weak)) const FilePath& CScript::path(const Script::IDType handleID)
	{
		return{};
	}

	__attribute__((weak)) Array<String> CScript::retrieveMessages_internal()
	{
		return {};
	}

	__attribute__((weak)) const Array<FilePath>& CScript::getIncludedFiles(const Script::IDType handleID)
	{
		return {};
	}

	__attribute__((weak)) const Array<String>& CScript::getMessages(const Script::IDType handleID)
	{
		return m_scripts[handleID]->getMessages();
	}

	__attribute__((weak)) void CScript::setSystemUpdateCallback(const Script::IDType handleID, const std::function<bool()>& callback)
	{
	}

	__attribute__((weak)) const std::function<bool()>& CScript::getSystemUpdateCallback(const uint64 scriptID)
	{
		return m_scripts[Script::IDType(static_cast<Script::IDType>(scriptID))]->getSystemUpdateCallback();
	}

	__attribute__((weak)) AngelScript::asIScriptEngine* CScript::getEngine()
	{
		return nullptr;
	}
}