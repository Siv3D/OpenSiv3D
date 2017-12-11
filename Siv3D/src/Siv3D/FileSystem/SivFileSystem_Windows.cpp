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

# include <Siv3D/Windows.hpp>
# include <Shlobj.h>
# include <filesystem>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace fs = std::experimental::filesystem;

	namespace detail
	{
		bool IsResourcePath(const FilePath& path)
		{
			return path.starts_with(U'/');
		}

		inline bool IsNotFound(const fs::file_status& status)
		{
			return status.type() == fs::file_type::not_found;
		}

		inline bool IsRegular(const fs::file_status& status)
		{
			return status.type() == fs::file_type::regular;
		}

		inline bool IsDirectory(const fs::file_status& status)
		{
			return status.type() == fs::file_type::directory;
		}

		inline bool ResourceExists(const FilePath& path)
		{
			const std::wstring pathW = path.toWstr();

			return ::FindResourceW(::GetModuleHandleW(nullptr), &pathW[1], L"FILE") != nullptr;
		}

		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			for (auto& ch : path)
			{
				if (ch == U'\\')
				{
					ch = U'/';
				}
			}

			if (!path.ends_with(U'/')
				&& (skipDirectoryCheck || IsDirectory(fs::status(fs::path(path.toWstr())))))
			{
				path.push_back(U'/');
			}

			return path;
		}

		static int64 DirectorySizeRecursive(FilePath directory)
		{
			directory = NormalizePath(directory, true);

			WIN32_FIND_DATAW data;
			HANDLE sh = ::FindFirstFileW((directory + U'*').toWstr().c_str(), &data);

			if (sh == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			int64 result = 0;

			do
			{
				if (!(data.cFileName[0] == L'.' && data.cFileName[1] == L'\0')
					&& !(data.cFileName[0] == L'.' && data.cFileName[1] == L'.' && data.cFileName[2] == L'\0'))
				{
					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						result += DirectorySizeRecursive((directory + Unicode::FromWString(data.cFileName)) + U'/');
					}
					else
					{
						result += (static_cast<uint64>(data.nFileSizeHigh) << 32) + data.nFileSizeLow;
					}
				}

			} while (::FindNextFileW(sh, &data));

			::FindClose(sh);

			return result;
		}

		static DateTime FiletimeToTime(FILETIME& in)
		{
			SYSTEMTIME systemtime;
			::FileTimeToLocalFileTime(&in, &in);
			::FileTimeToSystemTime(&in, &systemtime);

			return{ systemtime.wYear, systemtime.wMonth, systemtime.wDay,
				systemtime.wHour, systemtime.wMinute, systemtime.wSecond, systemtime.wMilliseconds };
		}

		static void DirectoryContentsRecursive(FilePath directory, Array<FilePath>& paths, bool recursive = true)
		{
			directory = NormalizePath(directory, true);

			WIN32_FIND_DATAW data;
			HANDLE sh = ::FindFirstFileW((directory + U'*').toWstr().c_str(), &data);

			if (sh == INVALID_HANDLE_VALUE)
			{
				return;
			}

			do
			{
				if (!(data.cFileName[0] == L'.' && data.cFileName[1] == L'\0')
					&& !(data.cFileName[0] == L'.' && data.cFileName[1] == L'.' && data.cFileName[2] == L'\0'))
				{
					paths.push_back(directory + Unicode::FromWString(data.cFileName));

					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						paths.back().push_back(U'/');

						if (recursive)
						{
							DirectoryContentsRecursive(paths.back(), paths, true);
						}
					}
				}

			} while (::FindNextFileW(sh, &data));

			::FindClose(sh);
		}

		static bool Remove(const FilePath& path, const bool allowUndo)
		{
			const std::wstring from = (path + U'\0').replaced(U'/', U'\\').toWstr();

			SHFILEOPSTRUCTW fileOption{};
			fileOption.wFunc = FO_DELETE;
			fileOption.pFrom = from.c_str();
			fileOption.fFlags = FOF_NOERRORUI | FOF_SILENT | FOF_NOCONFIRMATION
				| (allowUndo ? FOF_ALLOWUNDO : 0);

			return ::SHFileOperationW(&fileOption) == 0 && !fileOption.fAnyOperationsAborted;
		}

		namespace init
		{
			const static FilePath g_initialPath = NormalizePath(Unicode::FromWString(fs::current_path().wstring()));

			static FilePath g_modulePath = FilePath();

			void SetModulePath()
			{
				wchar_t result[1024];
				const DWORD length = ::GetModuleFileNameW(nullptr, result, _countof(result));

				if (length == 0 || length >= _countof(result))
				{
					return;
				}

				g_modulePath.assign(Unicode::FromWString(std::wstring_view(result, length))).replace(U'\\', U'/');
			}
		}
	}

	namespace FileSystem
	{
		bool Exists(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return !detail::IsNotFound(fs::status(fs::path(path.toWstr())));
		}

		bool IsDirectory(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			return detail::IsDirectory(fs::status(fs::path(path.toWstr())));
		}

		bool IsFile(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return detail::IsRegular(fs::status(fs::path(path.toWstr())));
		}

		bool IsResource(const FilePath& path)
		{
			return detail::IsResourcePath(path) && detail::ResourceExists(path);
		}

		FilePath FullPath(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return path;
			}

			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(path.toWstr().c_str(), _countof(result), result, &pFilePart);

			if (length == 0)
			{
				// [Siv3D ToDo]
				return FilePath();
			}
			else if (length > std::size(result))
			{
				// [Siv3D ToDo]
				return FilePath();
			}

			const bool isDirectory = (pFilePart == nullptr);

			return detail::NormalizePath(Unicode::FromWString(std::wstring_view(result, length)), isDirectory);
		}

		FilePath VolumePath(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return FilePath();
			}

			wchar_t result[MAX_PATH];

			if (::GetVolumePathNameW(path.toWstr().c_str(), result, _countof(result)) == 0)
			{
				return FilePath();
			}

			return Unicode::FromWString(result).replaced(U'\\', U'/');
		}

		bool IsEmpty(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				HMODULE module = ::GetModuleHandleW(nullptr);

				if (HRSRC hrs = ::FindResourceW(module, (U'#' + path.substr(1)).toWstr().c_str(), L"FILE"))
				{
					return ::SizeofResource(module, hrs) == 0;
				}
				else
				{
					return false;
				}
			}

			const auto fpath = fs::path(path.toWstr());
			const auto status = fs::status(fpath);

			if (detail::IsNotFound(status))
			{
				// [Siv3D ToDo]
				return false;
			}
			else if (detail::IsRegular(status))
			{
				::WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					// [Siv3D ToDo]
					return false;
				}

				return fad.nFileSizeHigh == 0 && fad.nFileSizeLow == 0;
			}
			else if (detail::IsDirectory(status))
			{
				return fs::directory_iterator(fpath) == fs::directory_iterator();
			}
			else
			{
				// [Siv3D ToDo]
				return false;
			}
		}

		int64 Size(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			if (detail::IsResourcePath(path))
			{
				return FileSize(path);
			}

			const auto fpath = fs::path(path.toWstr());
			const auto status = fs::status(fpath);

			if (detail::IsRegular(status))
			{
				::WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(path.replaced(U'/', U'\\').toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					// [Siv3D ToDo]
					return 0;
				}

				return (static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow;
			}
			else if (detail::IsDirectory(status))
			{
				return detail::DirectorySizeRecursive(FullPath(path));
			}
			else
			{
				// [Siv3D ToDo]
				return 0;
			}
		}

		int64 FileSize(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			if (detail::IsResourcePath(path))
			{
				HMODULE module = ::GetModuleHandleW(nullptr);

				if (HRSRC hrs = ::FindResourceW(module, (U'#' + path.substr(1)).toWstr().c_str(), L"FILE"))
				{
					return ::SizeofResource(module, hrs);
				}
				else
				{
					return 0;
				}
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				// [Siv3D ToDo]
				return 0;
			}

			if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return 0;
			}

			return (static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow;
		}

		Optional<DateTime> CreationTime(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftCreationTime);
		}

		Optional<DateTime> WriteTime(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastWriteTime);
		}

		Optional<DateTime> AccessTime(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastAccessTime);
		}

		Array<FilePath> DirectoryContents(const FilePath& path, const bool recursive)
		{
			Array<FilePath> paths;

			if (path.isEmpty())
			{
				return paths;
			}

			if (detail::IsResourcePath(path))
			{
				return paths;
			}

			if (detail::IsRegular(fs::status(fs::path(path.toWstr()))))
			{
				return paths;
			}

			detail::DirectoryContentsRecursive(FullPath(path), paths, recursive);

			return paths;
		}

		const FilePath& InitialPath()
		{
			return detail::init::g_initialPath;
		}

		const FilePath& ModulePath()
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentPath()
		{
			wchar_t result[1024];
			const DWORD length = ::GetCurrentDirectoryW(_countof(result), result);

			if (length == 0)
			{
				// [Siv3D ToDo]
				return FilePath();
			}
			else if (length > _countof(result))
			{
				// [Siv3D ToDo]
				return FilePath();
			}

			return detail::NormalizePath(Unicode::FromWString(std::wstring_view(result, length)), true);
		}

		FilePath SpecialFolderPath(const SpecialFolder folder)
		{
			constexpr int ids[] = {
				CSIDL_DESKTOP,
				CSIDL_MYDOCUMENTS,
				CSIDL_LOCAL_APPDATA,
				CSIDL_MYPICTURES,
				CSIDL_MYMUSIC,
				CSIDL_MYVIDEO
			};

			assert(static_cast<size_t>(folder) < _countof(ids));

			wchar_t path[MAX_PATH];

			if (FAILED(::SHGetFolderPathW(nullptr, ids[static_cast<size_t>(folder)], nullptr, 0, path)))
			{
				return FilePath();
			}

			return detail::NormalizePath(Unicode::FromWString(path), true);
		}

		FilePath TempDirectoryPath()
		{
			return FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData) + U"Temp/";
		}

		bool Copy(const FilePath& from, const FilePath& to, const CopyOption copyOption)
		{
			if (from.isEmpty() || to.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(from) || detail::IsResourcePath(to))
			{
				return false;
			}

			if (copyOption == CopyOption::Fail_if_Exists && fs::exists(fs::path(to.toWstr())))
			{
				return false;
			}

			const std::wstring fromStr = (from + (is_regular_file(fs::path(from.toWstr())) ? U"" : U"\\*") + U'\0').replace(U'/', U'\\').toWstr();
			const std::wstring toStr = (to + U'\0').replace(U'/', U'\\').toWstr(); // pTo ÇÕê‚ëŒÉpÉXÇ… \\ ÇóvãÅ

			SHFILEOPSTRUCTW fileOption{};
			fileOption.wFunc = FO_COPY;
			fileOption.fFlags = FOF_NOERRORUI | FOF_SILENT | FOF_NOCONFIRMMKDIR
				| ((copyOption == CopyOption::Overwrite_if_Exists) ? FOF_NOCONFIRMATION : 0)
				| ((copyOption == CopyOption::Rename_if_Exists) ? FOF_RENAMEONCOLLISION : 0);
			fileOption.pFrom = fromStr.c_str();
			fileOption.pTo = toStr.c_str();

			return ::SHFileOperationW(&fileOption) == 0 && !fileOption.fAnyOperationsAborted;
		}

		bool Remove(const FilePath& path, const bool allowUndo)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			return detail::Remove(path, allowUndo);
		}
		
		bool IsSandBoxed()
		{
			return false;
		}
	}
}

# endif
