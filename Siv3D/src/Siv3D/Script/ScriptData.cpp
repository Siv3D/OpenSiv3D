//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/Logger.hpp>
# include "ScriptData.hpp"
# include "../Siv3DEngine.hpp"
# include "IScript.hpp"

namespace s3d
{
	namespace detail
	{
		static std::string GenerateModuleName()
		{
			return Unicode::NarrowAscii(ToString(Time::GetMicrosec()));
		}
	}

	ScriptData::ScriptData(Null, AngelScript::asIScriptEngine* const engine)
		: m_engine(engine)
		, m_moduleData(std::make_shared<ScriptModuleData>())
	{
		m_initialized = true;
	}

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
			m_messages = Siv3DEngine::GetScript()->retrieveMessagesInternal();
			return;
		}

		r = builder.BuildModule();

		if (r < 0)
		{
			m_messages = Siv3DEngine::GetScript()->retrieveMessagesInternal();
			return;
		}

		m_moduleData->module = m_engine->GetModule(m_moduleName.c_str());
		m_moduleData->context = m_engine->CreateContext();
		m_moduleData->withLineCues = withLineCues();

		m_complieSucceeded = true;

		m_initialized = true;
	}

	ScriptData::ScriptData(File, const FilePath& path, AngelScript::asIScriptEngine* const engine, const int32 compileOption)
		: m_engine(engine)
		, m_moduleData(std::make_shared<ScriptModuleData>())
		, m_compileOption(compileOption)
		, m_fromFile(true)
	{
		if (path.isEmpty() || !FileSystem::IsFile(path))
		{
			return;
		}

		m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, !(m_compileOption & ScriptCompileOption::BuildWithLineCues));

		AngelScript::CScriptBuilder builder;

		m_moduleName = detail::GenerateModuleName();

		m_fullpath = FileSystem::FullPath(path);

		m_initialized = true;


		int32 r = builder.StartNewModule(m_engine, m_moduleName.c_str());

		if (r < 0)
		{
			LOG_FAIL(U"Unrecoverable error while starting a new module.");
			return;
		}

		r = builder.AddSectionFromFile(path);

		if (r < 0)
		{
			m_messages = Siv3DEngine::GetScript()->retrieveMessagesInternal();
			return;
		}

		r = builder.BuildModule();

		if (r < 0)
		{
			m_messages = Siv3DEngine::GetScript()->retrieveMessagesInternal();
			return;
		}

		m_moduleData->module = m_engine->GetModule(m_moduleName.c_str());
		m_moduleData->context = m_engine->CreateContext();
		m_moduleData->withLineCues = withLineCues();

		m_complieSucceeded = true;
	}

	AngelScript::asIScriptFunction* ScriptData::getFunction(const String& decl)
	{
		if (!m_complieSucceeded)
		{
			return nullptr;
		}

		auto it = m_functions.find(decl);

		if (it == m_functions.end())
		{
			const bool byDecl = decl.includes(L' ');

			AngelScript::asIScriptFunction* func =
				byDecl ? m_moduleData->module->GetFunctionByDecl(decl.narrow().c_str())
				: m_moduleData->module->GetFunctionByName(decl.narrow().c_str());

			if (func == 0)
			{
				//if (byDecl)
				//{
				//	LOG_FAIL(L"関数 '{}' が見つかりません。"_fmt, decl);
				//}
				//else
				//{
				//	LOG_FAIL(L"関数 '{}' が見つからないか、オーバーロードを解決できません。"_fmt, decl);
				//}

				return nullptr;
			}

			it = m_functions.emplace(decl, func).first;
		}

		return it->second;
	}

	std::shared_ptr<ScriptModuleData> ScriptData::getModuleData() const
	{
		return m_moduleData;
	}

	bool ScriptData::compileSucceeded() const
	{
		return m_complieSucceeded;
	}

	void ScriptData::setSystemUpdateCallback(const std::function<bool(void)>& callback)
	{
		m_systemUpdateCallback = callback;
	}

	const std::function<bool(void)>& ScriptData::getSystemUpdateCallback() const
	{
		return m_systemUpdateCallback;
	}

	const Array<String>& ScriptData::getMessages() const
	{
		return m_messages;
	}

	bool ScriptData::reload(const int32 compileOption, const uint64 scriptID)
	{
		if (!m_fromFile)
		{
			return false;
		}

		m_moduleData = std::make_shared<ScriptModuleData>();
		m_functions.clear();
		m_moduleName.clear();
		m_messages.clear();
		m_complieSucceeded = false;
		m_compileOption = compileOption;

		m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, !(m_compileOption & ScriptCompileOption::BuildWithLineCues));

		AngelScript::CScriptBuilder builder;

		m_moduleName = detail::GenerateModuleName();

		int r = builder.StartNewModule(m_engine, m_moduleName.c_str());

		if (r < 0)
		{
			LOG_FAIL(U"Unrecoverable error while starting a new module.");
			return false;
		}

		r = builder.AddSectionFromFile(m_fullpath);

		if (r < 0)
		{
			m_messages = Siv3DEngine::GetScript()->retrieveMessagesInternal();
			return false;
		}

		r = builder.BuildModule();

		if (r < 0)
		{
			m_messages = Siv3DEngine::GetScript()->retrieveMessagesInternal();
			return false;
		}

		m_moduleData->module = m_engine->GetModule(m_moduleName.c_str());
		m_moduleData->context = m_engine->CreateContext();
		m_moduleData->scriptID = scriptID;
		m_moduleData->withLineCues = withLineCues();

		m_complieSucceeded = true;

		return true;
	}

	const FilePath& ScriptData::path() const
	{
		return m_fullpath;
	}

	bool ScriptData::withLineCues() const
	{
		return !!(m_compileOption & ScriptCompileOption::BuildWithLineCues);
	}

	bool ScriptData::isInitialized() const
	{
		return m_initialized;
	}

	void ScriptData::setScriptID(const uint64 id)
	{
		m_moduleData->scriptID = id;
	}
}
