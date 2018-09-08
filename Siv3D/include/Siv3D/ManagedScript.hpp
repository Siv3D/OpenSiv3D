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
# include "Fwd.hpp"
# include "Script.hpp"
# include "DirectoryWatcher.hpp"
# include "FileSystem.hpp"
# include "Print.hpp"

namespace s3d
{
	class ManagedScript
	{
	private:

		Script m_script;

		std::function<bool()> m_callback;

		std::function<void()> m_main;

		bool m_requestReload = false;

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

	public:

		ManagedScript() = default;

		explicit ManagedScript(const FilePath& path)
			: m_script(path)
		{
			m_script.getMessages().each(Print);

			const bool isRsource = FileSystem::IsResource(path);
			const FilePath fullpath = FileSystem::FullPath(path);

			m_callback = [
				&requestReload = m_requestReload,
				path = fullpath,
				watcher = isRsource ? DirectoryWatcher() : DirectoryWatcher(FileSystem::ParentPath(m_script.path()))
			]()
				{
					requestReload = HasChanged(path, watcher.retrieveChanges());
					return !requestReload;
				};

				m_script.setSystemUpdateCallback(m_callback);

				m_main = m_script.getFunction<void()>(U"Main");
		}

		void update()
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
	};
}
