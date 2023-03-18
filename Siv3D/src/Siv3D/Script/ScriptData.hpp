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

# pragma once
# include <Siv3D/Script.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include "angelscript/scriptbuilder.h"

namespace s3d
{
	class ScriptData
	{
	public:

		struct Null {};
		struct Code {};
		struct File {};

		ScriptData() = default;

		ScriptData(Null, AngelScript::asIScriptEngine * engine);

		ScriptData(Code, StringView code, AngelScript::asIScriptEngine* engine, ScriptCompileOption compileOption);

		ScriptData(File, FilePathView path, AngelScript::asIScriptEngine* engine, ScriptCompileOption compileOption);

		[[nodiscard]]
		bool isInitialized() const noexcept;

		void setScriptID(uint64 id) noexcept;

		[[nodiscard]]
		bool compileSucceeded() const noexcept;

		[[nodiscard]]
		bool reload(ScriptCompileOption compileOption, uint64 scriptID);

		[[nodiscard]]
		const std::shared_ptr<ScriptModule>& getModule() const;

		[[nodiscard]]
		AngelScript::asIScriptFunction* getFunction(StringView decl);

		[[nodiscard]]
		const FilePath& path() const noexcept;

		[[nodiscard]]
		const Array<FilePath>& getIncludedFiles() const noexcept;

		[[nodiscard]]
		const Array<String>& getMessages() const noexcept;

		[[nodiscard]]
		Array<String> getFunctionDeclarations(IncludeParamNames includeParamNames) const;

		void setSystemUpdateCallback(const std::function<bool()>& callback);

		const std::function<bool()>& getSystemUpdateCallback() const;

	private:

		AngelScript::asIScriptEngine* m_engine = nullptr;

		std::shared_ptr<ScriptModule> m_module;

		std::string m_moduleName;

		HashTable<String, AngelScript::asIScriptFunction*> m_functions;

		std::function<bool()> m_systemUpdateCallback;

		Array<String> m_messages;

		ScriptCompileOption m_compileOption = ScriptCompileOption::Default;

		FilePath m_fullpath;

		Array<FilePath> m_includedFiles;

		bool m_complieSucceeded = false;

		bool m_initialized = false;
	};
}
