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

		Script::IDType createFromCode(StringView code, int32 compileOption) override;

		Script::IDType createFromFile(FilePathView path, int32 compileOption) override;

		void release(Script::IDType handleID) override;

		Array<String> retrieveInternalMessages() override;

	private:

		AngelScript::asIScriptEngine* m_engine = nullptr;

		AssetHandleManager<Script::IDType, ScriptData> m_scripts{ U"Script" };

		bool m_shutDown = true;

		Array<String> m_messages;
	};
}
