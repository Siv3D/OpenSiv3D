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
# include "IScript.hpp"
# include "../AssetHandleManager/AssetHandleManager.hpp"
# include "AngelScript/scriptbuilder.h"
# include <Siv3D/HashTable.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	class ScriptData
	{
	private:

		AngelScript::asIScriptEngine* m_engine = nullptr;

		std::shared_ptr<ScriptModuleData> m_moduleData;

		HashTable<String, AngelScript::asIScriptFunction*> m_functions;

		std::string m_moduleName;

		FilePath m_fullpath;

		int32 m_compileOption = 0;

		bool m_hasChanged = false;

		bool m_fromFile = false;

		bool m_complieSucceeded = false;

		bool m_initialized = false;

	public:

		struct Null {};

		struct Code {};

		struct File {};

		ScriptData() = default;

		ScriptData(Null, AngelScript::asIScriptEngine* engine)
			: m_engine(engine)
			, m_moduleData(std::make_shared<ScriptModuleData>())
		{
			m_initialized = true;
		}

		ScriptData(Code, const String& code, AngelScript::asIScriptEngine* engine, int32 compileOption)
			: m_engine(engine)
			, m_moduleData(std::make_shared<ScriptModuleData>())
		{
			m_compileOption = compileOption;

			//StopwatchMicrosec stopwatch(true);

			m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, !!(m_compileOption & ScriptCompileOption::BuildWithoutLineCues));

			AngelScript::CScriptBuilder builder;

			m_moduleName = Unicode::NarrowAscii(ToString(Time::GetMicrosec()));

			int r = builder.StartNewModule(m_engine, m_moduleName.c_str());

			if (r < 0)
			{
				//LOG_FAIL(L"Unrecoverable error while starting a new module.");
				return;
			}

			r = builder.AddSectionFromMemory("", code.toUTF8().c_str(), static_cast<uint32>(code.length()), 0);

			if (r < 0)
			{
				//LOG_FAIL(L"Please correct the errors in the script and try again.");
				return;
			}

			r = builder.BuildModule();

			if (r < 0)
			{
				//LOG_FAIL(L"Please correct the errors in the script and try again.");
				return;
			}

			//const auto elapsed = stopwatch.elapsed();

			//LOG_SCRIPT(L"スクリプトコードのビルド完了。 build time : {}"_fmt, elapsed);

			m_moduleData->module = m_engine->GetModule(m_moduleName.c_str());

			m_moduleData->context = m_engine->CreateContext();

			m_moduleData->withoutLineCues = withoutLineCues();

			m_complieSucceeded = true;

			m_initialized = true;
		}

		ScriptData(File, const FilePath& path, AngelScript::asIScriptEngine* engine, int32 compileOption)
			: m_engine(engine)
			, m_moduleData(std::make_shared<ScriptModuleData>())
		{
			if (path.isEmpty())
			{
				return;
			}
			
			if(!FileSystem::IsFile(path))
			{
				return;
			}

			m_compileOption = compileOption;

			m_fromFile = true;

			//StopwatchMicrosec stopwatch(true);

			m_engine->SetEngineProperty(AngelScript::asEP_BUILD_WITHOUT_LINE_CUES, !!(m_compileOption & ScriptCompileOption::BuildWithoutLineCues));

			AngelScript::CScriptBuilder builder;

			m_moduleName = Unicode::NarrowAscii(ToString(Time::GetMicrosec()));

			m_fullpath = FileSystem::FullPath(path);

			//m_monitor.monitor(m_fullpath);

			int r = builder.StartNewModule(m_engine, m_moduleName.c_str());

			if (r < 0)
			{
				LOG_FAIL(U"Unrecoverable error while starting a new module.");
				return;
			}

			r = builder.AddSectionFromFile(path);

			if (r < 0)
			{
				LOG_FAIL(U"Please correct the errors in the script and try again.");
				return;
			}

			r = builder.BuildModule();

			if (r < 0)
			{
				LOG_FAIL(U"Please correct the errors in the script and try again.");
				return;
			}

			//const auto elapsed = stopwatch.elapsed();

			//LOG_SCRIPT(L"\"{}\" のビルド完了。 build time : {}"_fmt, m_fullpath, elapsed);

			m_moduleData->module = m_engine->GetModule(m_moduleName.c_str());

			m_moduleData->context = m_engine->CreateContext();

			m_moduleData->withoutLineCues = withoutLineCues();

			m_complieSucceeded = true;

			m_initialized = true;
		}

		AngelScript::asIScriptFunction* getFunction(const String& decl)
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

		std::shared_ptr<ScriptModuleData> getModuleData() const
		{
			return m_moduleData;
		}

		bool compileSucceeded() const
		{
			return m_complieSucceeded;
		}

		bool withoutLineCues() const
		{
			return !!(m_compileOption & ScriptCompileOption::BuildWithoutLineCues);
		}

		bool isInitialized() const
		{
			return m_initialized;
		}
	};

	class CScript : public ISiv3DScript
	{
	private:

		AngelScript::asIScriptEngine* m_engine = nullptr;

		AssetHandleManager<ScriptID, ScriptData> m_scripts{ U"Script" };

		bool m_shutDown = true;
		
	public:

		CScript();

		~CScript() override;

		bool init() override;

		void shutdown() override;

		ScriptID createFromCode(const String& code, int32 compileOption) override;

		ScriptID createFromFile(const FilePath& path, int32 compileOption) override;

		void release(ScriptID handleID) override;

		AngelScript::asIScriptFunction* getFunction(ScriptID handleID, const String& decl) override;

		std::shared_ptr<ScriptModuleData> getModuleData(ScriptID handleID) override;

		bool compiled(ScriptID handleID) override;

		AngelScript::asIScriptEngine* getEngine() override;
	};
}
