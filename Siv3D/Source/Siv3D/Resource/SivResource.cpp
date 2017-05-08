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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail
	{
		static BOOL CALLBACK EnumResourceNameCallback(HMODULE, LPCWSTR, LPWSTR lpName, LONG_PTR lParam)
		{
			Array<FilePath>& paths = *(Array<FilePath>*)lParam;

			paths.push_back(lpName);

			return true;
		}

		static Array<FilePath> GetResourceFilePaths()
		{
			Array<FilePath> paths;

			HMODULE hModule = ::GetModuleHandleW(nullptr);

			::EnumResourceNamesW(hModule, L"FILE", detail::EnumResourceNameCallback, (LONG_PTR)&paths);

			paths.sort();

			return paths;
		}
	}

	const Array<FilePath>& EnumResourceFiles()
	{
		const static Array<FilePath> paths = detail::GetResourceFilePaths();

		return paths;
	}

	FilePath Resource(const FilePath& path)
	{
		if (FileSystem::IsResource(path))
		{
			return path;
		}

		return L'/' + path;
	}
}

# elif defined(SIV3D_TARGET_MACOS)

# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

#include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static Array<FilePath> GetResourceFilePaths()
		{
			const FilePath resourcePath = FileSystem::ModulePath() + L"/Contents/Resources/";
			
			Array<FilePath> paths = FileSystem::DirectoryContents(resourcePath, true);
		
			paths.remove(resourcePath + L"icon.icns");

			paths.remove_if([](const FilePath& path){ return FileSystem::IsDirectory(path); });
			
			paths.sort();
			
			return paths;
		}
	}

	const Array<FilePath>& EnumResourceFiles()
	{
		const static Array<FilePath> paths = detail::GetResourceFilePaths();

		return paths;
	}

	FilePath Resource(const FilePath& path)
	{
		if (FileSystem::IsResource(path))
		{
			return path;
		}

		const FilePath resourcePath = FileSystem::ModulePath() + L"/Contents/Resources/";

		return resourcePath + path;
	}
}

# elif defined (SIV3D_TARGET_LINUX)

# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	const Array<FilePath>& EnumResourceFiles()
	{
		// [Siv3D ToDo]

		static Array<FilePath> paths;

		return paths;
	}

	FilePath Resource(const FilePath& path)
	{
		// [Siv3D ToDo]

		if (FileSystem::IsResource(path))
		{
			return path;
		}

		return path;
	}
}

# endif
