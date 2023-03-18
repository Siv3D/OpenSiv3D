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
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include <Siv3D/HashTable.hpp>
# include "ScriptData.hpp"
# include "IScript.hpp"

namespace s3d
{
	class CScript final : public ISiv3DScript
	{
	public:

		CScript();

		~CScript() override;

		void init() override;

		void shutdown() override;

		Script::IDType createFromCode(StringView code, ScriptCompileOption compileOption) override;

		Script::IDType createFromFile(FilePathView path, ScriptCompileOption compileOption) override;

		void release(Script::IDType handleID) override;

		bool compiled(Script::IDType handleID) override;

		bool reload(Script::IDType handleID, ScriptCompileOption compileOption) override;

		const std::shared_ptr<ScriptModule>& getModule(Script::IDType handleID) override;

		AngelScript::asIScriptFunction* getFunction(Script::IDType handleID, StringView decl) override;

		Array<String> getFunctionDeclarations(Script::IDType handleID, IncludeParamNames includeParamNames) override;

		const FilePath& path(Script::IDType handleID) override;

		Array<String> retrieveMessages_internal() override;

		const Array<FilePath>& getIncludedFiles(Script::IDType handleID) override;

		const Array<String>& getMessages(Script::IDType handleID) override;

		void setSystemUpdateCallback(Script::IDType handleID, const std::function<bool()>& callback) override;
		
		const std::function<bool()>& getSystemUpdateCallback(uint64 scriptID) override;

		AngelScript::asIScriptEngine* getEngine() override;

	private:

		AngelScript::asIScriptEngine* m_engine = nullptr;

		AssetHandleManager<Script::IDType, ScriptData> m_scripts{ U"Script" };

		bool m_initialized = false;

		Array<String> m_messages;
	};
}
