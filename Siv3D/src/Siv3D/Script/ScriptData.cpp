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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/UUIDValue.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "IScript.hpp"
# include "ScriptData.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Array<FilePath> ConvertIncludedFiles(const std::vector<std::string>& includedFiles)
		{
			Array<FilePath> paths(includedFiles.size());

			for (size_t i = 0; i < includedFiles.size(); ++i)
			{
				paths[i] = Unicode::FromUTF8(includedFiles[i]);
			}

			return paths.stable_uniqued();
		}
	}

	ScriptData::ScriptData(Null, AngelScript::asIScriptEngine* const engine)
		: m_engine{ engine }
		, m_module{ std::make_shared<ScriptModule>() }
	{
		m_initialized = true;
	}

	ScriptData::ScriptData(Code, const StringView code, AngelScript::asIScriptEngine* const engine, const ScriptCompileOption compileOption)
		: m_engine{ engine }
		, m_module{ std::make_shared<ScriptModule>() }
		, m_moduleName{ UUIDValue::Generate().to_string() }
		, m_compileOption{ compileOption }
	{
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

		const std::string codeUTF8 = code.toUTF8();
		std::vector<std::string> includedFiles;

		if (r = builder.AddSectionFromMemory(includedFiles, "", codeUTF8.c_str(), static_cast<uint32>(codeUTF8.length()), 0);
			(r < 0))
		{
			m_includedFiles.clear();
			m_messages = SIV3D_ENGINE(Script)->retrieveMessages_internal();
			return;
		}

		m_includedFiles = detail::ConvertIncludedFiles(includedFiles);

		if (r = builder.BuildModule();
			(r < 0))
		{
			m_messages = SIV3D_ENGINE(Script)->retrieveMessages_internal();
			return;
		}

		m_module->module = m_engine->GetModule(m_moduleName.c_str());
		m_module->context = m_engine->CreateContext();
		m_module->withLineCues = withLineCues;

		m_complieSucceeded = true;
	}

	ScriptData::ScriptData(File, const FilePathView path, AngelScript::asIScriptEngine* const engine, const ScriptCompileOption compileOption)
		: m_engine{ engine }
		, m_module{ std::make_shared<ScriptModule>() }
		, m_moduleName{ UUIDValue::Generate().to_string() }
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

		std::vector<std::string> includedFiles;

		if (r = builder.AddSectionFromFile(m_fullpath, includedFiles);
			(r < 0))
		{
			m_includedFiles.clear();
			m_messages = SIV3D_ENGINE(Script)->retrieveMessages_internal();
			return;
		}

		m_includedFiles = detail::ConvertIncludedFiles(includedFiles);

		if (r = builder.BuildModule(); 
			(r < 0))
		{
			m_messages = SIV3D_ENGINE(Script)->retrieveMessages_internal();
			return;
		}

		m_module->module = m_engine->GetModule(m_moduleName.c_str());
		m_moduleName = UUIDValue::Generate().to_string();
		m_module->context = m_engine->CreateContext();
		m_module->withLineCues = withLineCues;

		m_complieSucceeded = true;
	}

	bool ScriptData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	void ScriptData::setScriptID(const uint64 id) noexcept
	{
		m_module->scriptID = id;
	}

	bool ScriptData::compileSucceeded() const noexcept
	{
		return m_complieSucceeded;
	}

	bool ScriptData::reload(const ScriptCompileOption compileOption, const uint64 scriptID)
	{
		if (not m_fullpath)
		{
			return false;
		}

		m_module = std::make_shared<ScriptModule>();
		m_functions.clear();
		m_moduleName.clear();
		m_messages.clear();
		m_complieSucceeded = false;
		m_compileOption = compileOption;

		const bool withLineCues = static_cast<bool>(m_compileOption & ScriptCompileOption::BuildWithLineCues);
		m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, (not withLineCues));

		AngelScript::CScriptBuilder builder;
		int32 r = 0;

		if (builder.StartNewModule(m_engine, m_moduleName.c_str());
			(r < 0))
		{
			LOG_FAIL(U"Unrecoverable error while starting a new module.");
			return false;
		}

		std::vector<std::string> includedFiles;

		if (r = builder.AddSectionFromFile(m_fullpath, includedFiles);
			(r < 0))
		{
			m_includedFiles.clear();
			m_messages = SIV3D_ENGINE(Script)->retrieveMessages_internal();
			return false;
		}

		m_includedFiles = detail::ConvertIncludedFiles(includedFiles);

		if (r = builder.BuildModule();
			(r < 0))
		{
			m_messages = SIV3D_ENGINE(Script)->retrieveMessages_internal();
			return false;
		}

		m_module->module = m_engine->GetModule(m_moduleName.c_str());
		m_module->context = m_engine->CreateContext();
		m_module->withLineCues = withLineCues;
		m_module->scriptID = scriptID;

		m_complieSucceeded = true;

		return true;
	}

	const std::shared_ptr<ScriptModule>& ScriptData::getModule() const
	{
		return m_module;
	}
	
	AngelScript::asIScriptFunction* ScriptData::getFunction(const StringView decl)
	{
		if (not m_complieSucceeded)
		{
			return nullptr;
		}

		auto it = m_functions.find(decl);

		if (it == m_functions.end())
		{
			const bool byDecl = decl.contains(U' ');
			const std::string declc = decl.narrow();

			AngelScript::asIScriptFunction* func =
				byDecl ? m_module->module->GetFunctionByDecl(declc.c_str())
						: m_module->module->GetFunctionByName(declc.c_str());

			if (func == nullptr)
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

	const FilePath& ScriptData::path() const noexcept
	{
		return m_fullpath;
	}

	const Array<FilePath>& ScriptData::getIncludedFiles() const noexcept
	{
		return m_includedFiles;
	}

	const Array<String>& ScriptData::getMessages() const noexcept
	{
		return m_messages;
	}

	Array<String> ScriptData::getFunctionDeclarations(const IncludeParamNames includeParamNames) const
	{
		if (not m_complieSucceeded)
		{
			return{};
		}

		const uint32 functionCount = m_module->module->GetFunctionCount();
		Array<String> declarations(functionCount);

		for (uint32 i = 0; i < functionCount; ++i)
		{
			const AngelScript::asIScriptFunction* function = m_module->module->GetFunctionByIndex(i);

			declarations[i] = Unicode::Widen(function->GetDeclaration(true, true, includeParamNames.getBool()));;
		}

		return declarations;
	}

	void ScriptData::setSystemUpdateCallback(const std::function<bool()>& callback)
	{
		m_systemUpdateCallback = callback;
	}

	const std::function<bool()>& ScriptData::getSystemUpdateCallback() const
	{
		return m_systemUpdateCallback;
	}
}
