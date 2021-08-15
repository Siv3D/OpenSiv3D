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

# include <Siv3D/Script.hpp>
# include <Siv3D/Script/IScript.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Script>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Script` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
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

	Script::Script() {}

	Script::Script(const FilePathView path, const ScriptCompileOption compileOption)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Script)->createFromFile(path, compileOption)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Script::Script(const Arg::code_<StringView> code, const ScriptCompileOption compileOption)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Script)->createFromCode(*code, compileOption)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Script::~Script() {}

	bool Script::compiled() const
	{
		return SIV3D_ENGINE(Script)->compiled(m_handle->id());
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
