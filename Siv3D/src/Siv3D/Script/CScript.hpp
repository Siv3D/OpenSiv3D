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
# include "IScript.hpp"
# include "../AssetHandleManager/AssetHandleManager.hpp"
# include <Siv3D/HashTable.hpp>
# include "ScriptData.hpp"

namespace s3d
{
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
