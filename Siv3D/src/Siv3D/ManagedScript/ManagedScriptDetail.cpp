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

# include "ManagedScriptDetail.hpp"
# include <Siv3D/DirectoryWatcher.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Print.hpp>

namespace s3d
{
	namespace detail
	{
		static bool HasChanged(const FilePath& target, const Array<std::pair<FilePath, FileAction>>& fileChanges)
		{
			for (auto[path, action] : fileChanges)
			{
				if ((path == target)
					&& (action == FileAction::Modified || action == FileAction::Added))
				{
					return true;
				}
			}

			return false;
		}
	}

	ManagedScript::ManagedScriptDetail::ManagedScriptDetail()
	{

	}

	ManagedScript::ManagedScriptDetail::ManagedScriptDetail(const FilePath& path)
		: m_script(path)
	{
		m_script.getMessages().each(Print);

		const bool isRsource = FileSystem::IsResource(path);
		const FilePath fullpath = FileSystem::FullPath(path);

		m_callback = [
			&requestReload = m_requestReload,
			path = fullpath,
			watcher = isRsource ? DirectoryWatcher() : DirectoryWatcher(FileSystem::ParentPath(fullpath))
		]()
		{
			requestReload = detail::HasChanged(path, watcher.retrieveChanges());
			return !requestReload;
		};

		m_script.setSystemUpdateCallback(m_callback);

		m_main = m_script.getFunction<void()>(U"Main");
	}

	ManagedScript::ManagedScriptDetail::~ManagedScriptDetail()
	{

	}

	bool ManagedScript::ManagedScriptDetail::isEmpty() const
	{
		return m_script.isEmpty();
	}

	bool ManagedScript::ManagedScriptDetail::compiled() const
	{
		return !!m_main;
	}

	void ManagedScript::ManagedScriptDetail::run()
	{
		if (m_requestReload || !m_callback())
		{
			ClearPrint();
			m_script.reload();
			m_script.getMessages().each(Print);
			m_main = m_script.getFunction<void()>(U"Main");
			m_requestReload = false;
		}

		m_main();
	}
}
