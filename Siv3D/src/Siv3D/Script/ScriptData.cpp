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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/UUID.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "IScript.hpp"
# include "ScriptData.hpp"

namespace s3d
{
	ScriptData::ScriptData(Null, AngelScript::asIScriptEngine* const engine)
		: m_engine{ engine }
		, m_module{ std::make_shared<ScriptModule>() }
	{
		m_initialized = true;
	}

	/*
	ScriptData::ScriptData(Code, const String& code, AngelScript::asIScriptEngine* const engine, const int32 compileOption)
		: m_engine(engine)
		, m_moduleData(std::make_shared<ScriptModuleData>())
		, m_compileOption(compileOption)
	{
		m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, !(m_compileOption & ScriptCompileOption::BuildWithLineCues));

		AngelScript::CScriptBuilder builder;

		m_moduleName = detail::GenerateModuleName();

		int32 r = builder.StartNewModule(m_engine, m_moduleName.c_str());

		if (r < 0)
		{
			LOG_FAIL(U"Unrecoverable error while starting a new module.");
			return;
		}

		const std::string codeUTF8 = code.toUTF8();

		r = builder.AddSectionFromMemory("", codeUTF8.c_str(), static_cast<uint32>(codeUTF8.length()), 0);

		if (r < 0)
		{
			m_messages = Siv3DEngine::Get<ISiv3DScript>()->retrieveMessagesInternal();
			return;
		}

		r = builder.BuildModule();

		if (r < 0)
		{
			m_messages = Siv3DEngine::Get<ISiv3DScript>()->retrieveMessagesInternal();
			return;
		}

		m_moduleData->module = m_engine->GetModule(m_moduleName.c_str());
		m_moduleData->context = m_engine->CreateContext();
		m_moduleData->withLineCues = withLineCues();

		m_complieSucceeded = true;

		m_initialized = true;
	}

	*/

	ScriptData::ScriptData(File, const FilePathView path, AngelScript::asIScriptEngine* const engine, const int32 compileOption)
		: m_engine{ engine }
		, m_module{ std::make_shared<ScriptModule>() }
		, m_moduleName{ UUID::Generate().to_string() }
		, m_compileOption{ compileOption }
		, m_fullpath{ FileSystem::FullPath(path) }
	{
		if (not FileSystem::IsFile(path))
		{
			return;
		}

		m_initialized = true;

		const bool withLineCues = static_cast<bool>(m_compileOption & ScriptCompileOption::BuildWithLineCues);
		m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, (not withLineCues));

		AngelScript::CScriptBuilder builder;
		int32 r = 0;
		
		if (builder.StartNewModule(m_engine, m_moduleName.c_str()); 
			(r < 0))
		{
			LOG_FAIL(U"Unrecoverable error while starting a new module.");
			return;
		}

		if (r = builder.AddSectionFromFile(m_fullpath); 
			(r < 0))
		{
			m_messages = SIV3D_ENGINE(Script)->retrieveInternalMessages();
			return;
		}

		if (r = builder.BuildModule(); 
			(r < 0))
		{
			m_messages = SIV3D_ENGINE(Script)->retrieveInternalMessages();
			return;
		}

		m_module->module = m_engine->GetModule(m_moduleName.c_str());
		m_module->context = m_engine->CreateContext();
		m_module->withLineCues = withLineCues;

		m_complieSucceeded = true;
	}

	bool ScriptData::isInitialized() const
	{
		return m_initialized;
	}
}
