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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Script.hpp>

namespace s3d
{
	class ISiv3DScript
	{
	public:

		static ISiv3DScript* Create();

		virtual ~ISiv3DScript() = default;

		virtual bool init() = 0;

		virtual void shutdown() = 0;

		virtual ScriptID createFromCode(const String& code, int32 compileOption) = 0;

		virtual ScriptID createFromFile(const FilePath& path, int32 compileOption) = 0;

		virtual void release(ScriptID handleID) = 0;

		virtual AngelScript::asIScriptFunction* getFunction(ScriptID handleID, const String& decl) = 0;

		virtual std::shared_ptr<ScriptModuleData> getModuleData(ScriptID handleID) = 0;

		virtual bool compiled(ScriptID handleID) = 0;

		virtual bool reload(ScriptID handleID, int32 compileOption) = 0;

		virtual const FilePath& path(ScriptID handleID) = 0;

		virtual Array<String> retrieveMessagesInternal() = 0;

		virtual const Array<String>& retrieveMessages(ScriptID handleID) = 0;

		virtual AngelScript::asIScriptEngine* getEngine() = 0;
	};
}
