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

# include <Siv3D/Script.hpp>
# include <Siv3D/Script/IScript.hpp>
# include <Siv3D/Troubleshooting/Troubleshooting.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		static void CheckEngine()
		{
			if (not Siv3DEngine::isActive())
			{
				Troubleshooting::Show(Troubleshooting::Error::AssetInitializationBeforeEngineStartup, U"Script");
				std::exit(EXIT_FAILURE);
			}
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Script>>::AssetIDWrapper()
	{
		detail::CheckEngine();
	}

	template <>
	AssetIDWrapper<AssetHandle<Script>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Script))
		{
			p->release(m_id);
		}
	}

	Script::Script()
	{
		SIV3D_ENGINE(Script)->init();
	}

	Script::Script(const FilePathView path, const ScriptCompileOption compileOption)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Script)->createFromFile(path, compileOption))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Script::Script(const Arg::code_<StringView> code, const ScriptCompileOption compileOption)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Script)->createFromCode(*code, compileOption))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Script::~Script() {}

	bool Script::compiled() const
	{
		return SIV3D_ENGINE(Script)->compiled(m_handle->id());
	}

	bool Script::reload(const ScriptCompileOption compileOption)
	{
		return SIV3D_ENGINE(Script)->reload(m_handle->id(), compileOption);
	}

	void Script::setSystemUpdateCallback(const std::function<bool()>& callback)
	{
		SIV3D_ENGINE(Script)->setSystemUpdateCallback(m_handle->id(), callback);
	}

	Array<String> Script::getFunctionDeclarations(const IncludeParamNames includeParamNames) const
	{
		return SIV3D_ENGINE(Script)->getFunctionDeclarations(m_handle->id(), includeParamNames);
	}

	const Array<FilePath>& Script::getIncludedFiles() const noexcept
	{
		return SIV3D_ENGINE(Script)->getIncludedFiles(m_handle->id());
	}

	const Array<String>& Script::getMessages() const
	{
		return SIV3D_ENGINE(Script)->getMessages(m_handle->id());
	}

	const FilePath& Script::path() const
	{
		return SIV3D_ENGINE(Script)->path(m_handle->id());
	}

	void Script::swap(Script& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}

	AngelScript::asIScriptEngine* Script::GetEngine()
	{
		return SIV3D_ENGINE(Script)->getEngine();
	}

	const std::shared_ptr<ScriptModule>& Script::_getModule() const
	{
		return SIV3D_ENGINE(Script)->getModule(m_handle->id());
	}

	AngelScript::asIScriptFunction* Script::_getFunction(const StringView decl) const
	{
		return SIV3D_ENGINE(Script)->getFunction(m_handle->id(), decl);
	}
}
