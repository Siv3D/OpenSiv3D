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

# pragma once
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Script.hpp>
# include "AngelScript/scriptbuilder.h"

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

		Array<String> m_messages;

		std::function<bool(void)> m_systemUpdateCallback;

		bool m_fromFile = false;

		bool m_complieSucceeded = false;

		bool m_initialized = false;

	public:

		struct Null {};

		struct Code {};

		struct File {};

		ScriptData() = default;

		ScriptData(Null, AngelScript::asIScriptEngine* engine);

		ScriptData(Code, const String& code, AngelScript::asIScriptEngine* engine, int32 compileOption);

		ScriptData(File, const FilePath& path, AngelScript::asIScriptEngine* engine, int32 compileOption);

		AngelScript::asIScriptFunction* getFunction(const String& decl);

		std::shared_ptr<ScriptModuleData> getModuleData() const;

		bool compileSucceeded() const;

		void setSystemUpdateCallback(const std::function<bool(void)>& callback);

		const std::function<bool(void)>& getSystemUpdateCallback() const;

		const Array<String>& getMessages() const;

		bool reload(int32 compileOption, uint64 scriptID);

		const FilePath& path() const;

		bool withoutLineCues() const;

		bool isInitialized() const;

		void setScriptID(uint64 id);
	};
}
