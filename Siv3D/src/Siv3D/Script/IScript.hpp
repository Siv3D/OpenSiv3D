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
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Script.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DScript
	{
	public:

		static ISiv3DScript* Create();

		virtual ~ISiv3DScript() = default;

		virtual void init() = 0;

		virtual void shutdown() = 0;

		virtual Script::IDType createFromCode(StringView code, ScriptCompileOption compileOption) = 0;

		virtual Script::IDType createFromFile(FilePathView path, ScriptCompileOption compileOption) = 0;

		virtual void release(Script::IDType handleID) = 0;

		virtual bool compiled(Script::IDType handleID) = 0;

		virtual bool reload(Script::IDType handleID, ScriptCompileOption compileOption) = 0;

		virtual const std::shared_ptr<ScriptModule>& getModule(Script::IDType handleID) = 0;

		virtual AngelScript::asIScriptFunction* getFunction(Script::IDType handleID, StringView decl) = 0;

		virtual Array<String> getFunctionDeclarations(Script::IDType handleID, IncludeParamNames includeParamNames) = 0;

		virtual const FilePath& path(Script::IDType handleID) = 0;

		virtual Array<String> retrieveMessages_internal() = 0;

		virtual const Array<FilePath>& getIncludedFiles(Script::IDType handleID) = 0;

		virtual const Array<String>& getMessages(Script::IDType handleID) = 0;

		virtual void setSystemUpdateCallback(Script::IDType handleID, const std::function<bool()>& callback) = 0;

		virtual const std::function<bool()>& getSystemUpdateCallback(uint64 scriptID) = 0;

		virtual AngelScript::asIScriptEngine* getEngine() = 0;
	};
}
