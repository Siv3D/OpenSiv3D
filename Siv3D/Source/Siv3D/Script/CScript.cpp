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

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "CScript.hpp"

# include "Bind/ScriptBind.hpp"
# include "AngelScript/scriptarray.h"
# include "AngelScript/scriptstdstring.h"

namespace s3d
{
	namespace detail
	{
		static void MessageCallback(const AngelScript::asSMessageInfo* msg, void*)
		{
			const char *type = "ERR ";
			if (msg->type == AngelScript::asMSGTYPE_WARNING)
				type = "WARN";
			else if (msg->type == AngelScript::asMSGTYPE_INFORMATION)
				type = "INFO";

			char buf[512];

			sprintf_s(buf, "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);

			String type_s = L"エラー";
			if (msg->type == AngelScript::asMSGTYPE_WARNING)
				type_s = L"注意";
			else if (msg->type == AngelScript::asMSGTYPE_INFORMATION)
				type_s = L"通知";

			//Println(PyFmt, L"{} : ({} 行目) : {}", type_s, msg->row, CharacterSet::Widen(msg->message));

			::OutputDebugStringA(buf);

			//Siv3DEngine::GetLogger()->writeRaw(L"<p class=\"fail\">" + CharacterSet::Widen(buf).xmlEscape() + L"</p>\n");
		}
	}

	ScriptModuleData::~ScriptModuleData()
	{
		if (context)
		{
			context->Release();
		}
	}

	CScript::CScript()
	{

	}

	CScript::~CScript()
	{

	}

	bool CScript::init()
	{
		m_engine = AngelScript::asCreateScriptEngine(ANGELSCRIPT_VERSION);

		if (!m_engine)
		{
			return false;
		}

		if (m_engine->SetMessageCallback(asFUNCTION(detail::MessageCallback), 0, AngelScript::asCALL_CDECL) < 0)
		{
			return false;
		}

		if (m_engine->SetEngineProperty(AngelScript::asEP_STRING_ENCODING, 1) < 0)
		{
			return false;
		}

		if (m_engine->SetEngineProperty(AngelScript::asEP_REQUIRE_ENUM_SCOPE, 1) < 0)
		{
			return false;
		}


		AngelScript::RegisterScriptArray(m_engine);
		RegisterTypes(m_engine);
		RegisterFormat(m_engine);
		AngelScript::RegisterStdString(m_engine);

		//RegisterDate(m_engine);
		//RegisterDateTime(m_engine);
		RegisterColor(m_engine);
		RegisterColorF(m_engine);
		RegisterHSV(m_engine);
		RegisterPoint(m_engine);
		RegisterVec2(m_engine);
		//RegisterVec3(m_engine);
		//RegisterVec4(m_engine);
		RegisterLine(m_engine);
		RegisterRect(m_engine);
		RegisterRectF(m_engine);
		RegisterCircle(m_engine);
		//RegisterEllipse(m_engine);
		RegisterTriangle(m_engine);
		RegisterQuad(m_engine);
		RegisterRoundRect(m_engine);

		RegisterCursor(m_engine);
		RegisterGraphics(m_engine);
		RegisterRandom(m_engine);

		const auto nullScript = std::make_shared<ScriptData>(ScriptData::Null{}, m_engine);

		if (!nullScript->isInitialized())
		{
			return false;
		}

		m_scripts.setNullData(nullScript);

		return true;
	}

	void CScript::shutdown()
	{
		m_scripts.destroy();

		m_engine->ShutDownAndRelease();
	}

	Script::IDType CScript::createFromCode(const String& code, const int32 compileOption)
	{
		if (code.isEmpty())
		{
			return Script::NullHandleID;
		}

		const auto script = std::make_shared<ScriptData>(ScriptData::Code{}, code, m_engine, compileOption);

		if (!script->isInitialized())
		{
			return Script::NullHandleID;
		}

		return m_scripts.add(script);
	}

	Script::IDType CScript::createFromFile(const FilePath& path, const int32 compileOption)
	{
		if (path.isEmpty())
		{
			//LOG_FAIL(L"CScript: スクリプトファイル名が空文字列です。");

			return Script::NullHandleID;
		}

		const auto script = std::make_shared<ScriptData>(ScriptData::File{}, path, m_engine, compileOption);

		if (!script->isInitialized())
		{
			return Script::NullHandleID;
		}

		return m_scripts.add(script);
	}

	void CScript::release(const Script::IDType handleID)
	{
		m_scripts.erase(handleID);
	}

	AngelScript::asIScriptFunction* CScript::getFunction(const Script::IDType handleID, const String& decl)
	{
		return m_scripts[handleID]->getFunction(decl);
	}

	std::shared_ptr<ScriptModuleData> CScript::getModuleData(const Script::IDType handleID)
	{
		return m_scripts[handleID]->getModuleData();
	}

	bool CScript::compiled(const Script::IDType handleID)
	{
		return m_scripts[handleID]->compileSucceeded();
	}

	AngelScript::asIScriptEngine* CScript::getEngine()
	{
		return m_engine;
	}
}
