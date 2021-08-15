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

# include "CScript.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr StringView GetMessageType(const AngelScript::asEMsgType msgType)
		{
			constexpr std::array<StringView, 3> types =
			{
				U"error"_sv, U"warning"_sv, U"info"_sv
			};

			return types[msgType];
		}

		static void MessageCallback(const AngelScript::asSMessageInfo* msg, void* pMessageArray)
		{
			const StringView type = GetMessageType(msg->type);
			const String section = Unicode::Widen(msg->section);
			const String message = Unicode::Widen(msg->message);

			const String fullMessage = U"[{}] {}({}): {}"_fmt(type, FileSystem::FileName(section), msg->row, message);
			const String logMessage = U"{}({}): {}: {}"_fmt(section, msg->row, type, message);
			Logger(logMessage);

			Array<String>* messageArray = static_cast<Array<String>*>(pMessageArray);
			messageArray->push_back(fullMessage);
		}
	}

	CScript::CScript() {}

	CScript::~CScript()
	{
		LOG_SCOPED_TRACE(U"CScript::~CScript()");

		shutdown();
	}

	void CScript::init()
	{
		LOG_SCOPED_TRACE(U"CScript::init()");

		m_engine = AngelScript::asCreateScriptEngine(ANGELSCRIPT_VERSION);

		if (not m_engine)
		{
			throw EngineError{ U"asCreateScriptEngine() failed" };
		}

		if (m_engine->SetMessageCallback(asFUNCTION(detail::MessageCallback), &m_messages, AngelScript::asCALL_CDECL) < 0)
		{
			throw EngineError{ U"SetMessageCallback() failed" };
		}

		m_engine->SetEngineProperty(AngelScript::asEP_REQUIRE_ENUM_SCOPE, 1);
		m_engine->SetEngineProperty(AngelScript::asEP_DISALLOW_EMPTY_LIST_ELEMENTS, 1);
		m_engine->SetEngineProperty(AngelScript::asEP_ALLOW_UNSAFE_REFERENCES, 1);

		{
			auto nullScript = std::make_unique<ScriptData>(ScriptData::Null{}, m_engine);

			if (not nullScript->isInitialized())
			{
				throw EngineError{ U"Failed to create nullScript" };
			}

			m_scripts.setNullData(std::move(nullScript));
		}

		m_shutDown = false;
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

	Script::IDType CScript::createFromCode(const StringView code, const int32 compileOption)
	{
		return Script::IDType::NullAsset();
	}

	Script::IDType CScript::createFromFile(const FilePathView path, const int32 compileOption)
	{
		return Script::IDType::NullAsset();
	}

	void CScript::release(const Script::IDType handleID)
	{
		m_scripts.erase(handleID);
	}

	Array<String> CScript::retrieveInternalMessages()
	{
		Array<String> messages = std::move(m_messages);
		
		m_messages.clear();
		
		return messages;
	}
}
