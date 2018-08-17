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

# include "CScript.hpp"

# include <Siv3D/FileSystem.hpp>
# include "Bind/ScriptBind.hpp"
# include "AngelScript/scriptarray.h"
# include "AngelScript/scriptstdstring.h"

namespace s3d
{
	namespace detail
	{
		static String GetMessageType(const AngelScript::asEMsgType msgType)
		{
			const Array<String> types =
			{
				U"error", U"warning", U"info"
			};

			return types[msgType];
		}

		static void MessageCallback(const AngelScript::asSMessageInfo* msg, void* pMessageArray)
		{
			const String type = GetMessageType(msg->type);
			const String section = Unicode::Widen(msg->section);
			const String message = Unicode::Widen(msg->message);

			const String fullMessage = U"[{}] {}({}): {}"_fmt(type, FileSystem::FileName(section), msg->row, message);
			const String logMessage = U"{}({}): {}: {}"_fmt(section, msg->row, type, message);
			Logger(logMessage);

			Array<String>* messageArray = static_cast<Array<String>*>(pMessageArray);
			messageArray->push_back(fullMessage);
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
		shutdown();
	}

	bool CScript::init()
	{
		m_engine = AngelScript::asCreateScriptEngine(ANGELSCRIPT_VERSION);

		if (!m_engine)
		{
			return false;
		}

		if (m_engine->SetMessageCallback(asFUNCTION(detail::MessageCallback), &m_messageArray, AngelScript::asCALL_CDECL) < 0)
		{
			return false;
		}

		//if (m_engine->SetEngineProperty(AngelScript::asEP_STRING_ENCODING, 1) < 0)
		//{
		//	return false;
		//}

		if (m_engine->SetEngineProperty(AngelScript::asEP_REQUIRE_ENUM_SCOPE, 1) < 0)
		{
			return false;
		}


		AngelScript::RegisterScriptArray(m_engine);
		RegisterTypes(m_engine);
		RegisterFormat(m_engine);
		AngelScript::RegisterStdString(m_engine);

		RegisterDate(m_engine);
		RegisterDateTime(m_engine);
		RegisterStopwatch(m_engine);
		RegisterCustomStopwatch(m_engine);
		RegisterTimer(m_engine);
		//RegisterTimeProfiler(m_engine);

		RegisterMillisecClock(m_engine);
		RegisterMicrosecClock(m_engine);
		RegisterRDTSCClock(m_engine);
		RegisterColor(m_engine);
		RegisterColorF(m_engine);
		RegisterHSV(m_engine);
		RegisterPoint(m_engine);
		RegisterVec2(m_engine);
		//RegisterVec3(m_engine);
		//RegisterVec4(m_engine);
		RegisterCircular(m_engine);
		RegisterLine(m_engine);
		RegisterRect(m_engine);
		RegisterRectF(m_engine);
		RegisterCircle(m_engine);
		RegisterEllipse(m_engine);
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

		m_shutDown = false;

		LOG_INFO(U"ℹ️ Script initialized");
		
		return true;
	}

	void CScript::shutdown()
	{
		if (m_shutDown)
		{
			return;
		}
		
		m_scripts.destroy();

		m_engine->ShutDownAndRelease();
		
		m_shutDown = true;
	}

	ScriptID CScript::createFromCode(const String& code, const int32 compileOption)
	{
		if (code.isEmpty())
		{
			return ScriptID::NullAsset();
		}

		const auto script = std::make_shared<ScriptData>(ScriptData::Code{}, code, m_engine, compileOption);

		if (!script->isInitialized())
		{
			return ScriptID::NullAsset();
		}

		return m_scripts.add(script);
	}

	ScriptID CScript::createFromFile(const FilePath& path, const int32 compileOption)
	{
		if (path.isEmpty())
		{
			//LOG_FAIL(L"CScript: スクリプトファイル名が空文字列です。");

			return ScriptID::NullAsset();
		}

		const auto script = std::make_shared<ScriptData>(ScriptData::File{}, path, m_engine, compileOption);

		if (!script->isInitialized())
		{
			return ScriptID::NullAsset();
		}

		return m_scripts.add(script);
	}

	void CScript::release(const ScriptID handleID)
	{
		m_scripts.erase(handleID);
	}

	AngelScript::asIScriptFunction* CScript::getFunction(const ScriptID handleID, const String& decl)
	{
		return m_scripts[handleID]->getFunction(decl);
	}

	std::shared_ptr<ScriptModuleData> CScript::getModuleData(const ScriptID handleID)
	{
		return m_scripts[handleID]->getModuleData();
	}

	bool CScript::compiled(const ScriptID handleID)
	{
		return m_scripts[handleID]->compileSucceeded();
	}

	bool CScript::reload(const ScriptID handleID, const int32 compileOption)
	{
		return m_scripts[handleID]->reload(compileOption);
	}

	const FilePath& CScript::path(const ScriptID handleID)
	{
		return m_scripts[handleID]->path();
	}

	Array<String> CScript::retrieveMessagesInternal()
	{
		Array<String> results;
		results.swap(m_messageArray);
		return results;
	}

	const Array<String>& CScript::retrieveMessages(ScriptID handleID)
	{
		return m_scripts[handleID]->getMessages();
	}

	AngelScript::asIScriptEngine* CScript::getEngine()
	{
		return m_engine;
	}
}
