//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Windows.hpp>

namespace s3d
{
	namespace detail
	{
		static BOOL CALLBACK EnumResourceNameCallback(HMODULE, LPCWSTR, LPWSTR lpName, LONG_PTR lParam)
		{
			Array<FilePath>& paths = *(Array<FilePath>*)lParam;

			paths.push_back(Unicode::FromWString(lpName));

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

		return U'/' + path;
	}
}
