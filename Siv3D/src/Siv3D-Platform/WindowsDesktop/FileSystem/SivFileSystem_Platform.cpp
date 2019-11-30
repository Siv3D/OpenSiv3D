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

# include <filesystem>
# include <Siv3D/Windows.hpp>
# include <Shlobj.h>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/Distribution.hpp>
# include <Siv3D/HardwareRNG.hpp>

namespace s3d
{
	namespace fs = std::filesystem;

	namespace detail
	{
		inline constexpr bool IsResourcePath(const FilePathView path)
		{
			return path.starts_with(U'/');
		}

		static bool ResourceExists(const FilePathView path)
		{
			const std::wstring pathW = Unicode::ToWString(path);

			return ::FindResourceW(::GetModuleHandleW(nullptr), &pathW[1], L"FILE") != nullptr;
		}

		static fs::path ToPath(const FilePathView path)
		{
			return fs::path(Unicode::ToWString(path));
		}

		inline constexpr std::filesystem::copy_options ToCopyOptions(const CopyOption copyOption)
		{
			switch (copyOption)
			{
			case CopyOption::SkipExisting:
				return std::filesystem::copy_options::skip_existing;
			case CopyOption::OverwriteExisting:
				return std::filesystem::copy_options::overwrite_existing;
			case CopyOption::UpdateExisting:
				return std::filesystem::copy_options::update_existing;
			default:
				return std::filesystem::copy_options::none;
			}
		}

		inline bool StatusRegular(const fs::file_status& status)
		{
			return status.type() == fs::file_type::regular;
		}

		inline bool StatusDirectory(const fs::file_status& status)
		{
			return status.type() == fs::file_type::directory;
		}

		inline bool StatusNotFound(const fs::file_status& status)
		{
			return status.type() == fs::file_type::not_found;
		}

		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			path.replace(U'\\', U'/');

			if (!path.ends_with(U'/')
				&& (skipDirectoryCheck || StatusDirectory(fs::status(detail::ToPath(path)))))
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

		static int64 ResourceSize(const FilePathView path)
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

		static DateTime FiletimeToTime(FILETIME& in)
		{
			SYSTEMTIME systemtime;
			::FileTimeToLocalFileTime(&in, &in);
			::FileTimeToSystemTime(&in, &systemtime);

			return{ systemtime.wYear, systemtime.wMonth, systemtime.wDay,
				systemtime.wHour, systemtime.wMinute, systemtime.wSecond, systemtime.wMilliseconds };
		}

		static void DirectoryContentsRecursive(FilePath directory, Array<FilePath>& paths, const bool recursive)
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

		static bool Remove(const FilePathView path, const bool allowUndo)
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
			const static FilePath g_initialDirectory = FileSystem::CurrentDirectory();

			const static FilePath g_modulePath = []()
			{
				wchar_t result[1024];
				const DWORD length = ::GetModuleFileNameW(nullptr, result, _countof(result));

				if (length == 0 || length >= _countof(result))
				{
					return FilePath();
				}

				return NormalizePath(Unicode::FromWString(std::wstring_view(result, length)));
			}();
		}
	}

	namespace FileSystem
	{
		bool Exists(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return !detail::StatusNotFound(fs::status(detail::ToPath(path)));
		}

		bool IsDirectory(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			return detail::StatusDirectory(fs::status(detail::ToPath(path)));
		}

		bool IsFile(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return detail::StatusRegular(fs::status(detail::ToPath(path)));
		}

		bool IsResource(const FilePathView path)
		{
			return detail::IsResourcePath(path)
				&& detail::ResourceExists(path);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return FilePath(path);
			}

			const std::wstring wpath = Unicode::ToWString(path);

			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(wpath.c_str(), _countof(result), result, &pFilePart);

			if (length == 0)
			{
				return FilePath();
			}
			else if (length > std::size(result))
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);
				
				if ((length2 == 0) || (length2 > length))
				{
					return FilePath();
				}

				const bool isDirectory = (pFilePart == nullptr);
				return detail::NormalizePath(Unicode::FromWString(result2), isDirectory);
			}

			const bool isDirectory = (pFilePart == nullptr);
			return detail::NormalizePath(Unicode::FromWString(std::wstring_view(result, length)), isDirectory);
		}

		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return Platform::NativeFilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return Unicode::ToWString(path);
			}

			const std::wstring wpath = Unicode::ToWString(path);
			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(wpath.c_str(), _countof(result), result, &pFilePart);

			if (length == 0)
			{
				return Platform::NativeFilePath();
			}
			else if (length > std::size(result))
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);

				if ((length2 == 0) || (length2 > length))
				{
					return Platform::NativeFilePath();
				}

				const bool isDirectory = (pFilePart == nullptr);
				return result2;
			}

			const bool isDirectory = (pFilePart == nullptr);
			return std::wstring(result, length);
		}

		FilePath VolumePath(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return FilePath();
			}

			const std::wstring wpath = Unicode::ToWString(path);
			wchar_t result[MAX_PATH];

			if (::GetVolumePathNameW(wpath.c_str(), result, _countof(result)) == 0)
			{
				return FilePath();
			}

			return Unicode::FromWString(result).replace(U'\\', U'/');
		}

		bool IsEmptyDirectory(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			const auto fpath = detail::ToPath(path);

			if (!detail::StatusDirectory(fs::status(fpath)))
			{
				return false;
			}

			return (fs::directory_iterator(fpath) == fs::directory_iterator());
		}

		int64 Size(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceSize(path);
			}

			const auto fpath = detail::ToPath(path);
			const auto status = fs::status(fpath);

			if (detail::StatusRegular(status))
			{
				WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(Unicode::ToWString(path).c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					return 0;
				}

				return (static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow;
			}
			else if (detail::StatusDirectory(status))
			{
				return detail::DirectorySizeRecursive(FullPath(path));
			}
			else
			{
				return 0;
			}
		}

		int64 FileSize(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceSize(path);
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(Unicode::ToWString(path).c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return 0;
			}

			if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return 0;
			}

			return (static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow;
		}

		Optional<DateTime> CreationTime(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(Unicode::ToWString(path).c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftCreationTime);
		}

		Optional<DateTime> WriteTime(const FilePathView path)
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

			if (::GetFileAttributesExW(Unicode::ToWString(path).c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastWriteTime);
		}

		Optional<DateTime> AccessTime(const FilePathView path)
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

			if (::GetFileAttributesExW(Unicode::ToWString(path).c_str(), ::GetFileExInfoStandard, &fad) == 0)
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

			if (detail::StatusRegular(fs::status(detail::ToPath(path))))
			{
				return paths;
			}

			detail::DirectoryContentsRecursive(FullPath(path), paths, recursive);

			return paths;
		}

		const FilePath& InitialDirectory()
		{
			return detail::init::g_initialDirectory;
		}

		const FilePath& ModulePath()
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentDirectory()
		{
			wchar_t result[1024];
			const DWORD length = ::GetCurrentDirectoryW(_countof(result), result);

			if (length == 0)
			{
				return FilePath();
			}
			else if (length > std::size(result))
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetCurrentDirectoryW(length, result2.data());

				if ((length2 == 0) || (length2 > length))
				{
					return FilePath();
				}

				return detail::NormalizePath(Unicode::FromWString(result2), true);
			}

			return detail::NormalizePath(Unicode::FromWString(std::wstring_view(result, length)), true);
		}

		bool ChangeCurrentDirectory(const FilePathView path)
		{
			if (!IsDirectory(path))
			{
				return false;
			}

			return (::SetCurrentDirectoryW(Unicode::ToWString(path).c_str()) != 0);
		}

		FilePath SpecialFolderPath(const SpecialFolder folder)
		{
			static constexpr int ids[] = {
				CSIDL_DESKTOP,
				CSIDL_MYDOCUMENTS,
				CSIDL_LOCAL_APPDATA,
				CSIDL_MYPICTURES,
				CSIDL_MYMUSIC,
				CSIDL_MYVIDEO,
				CSIDL_FONTS,
				CSIDL_FONTS,
				CSIDL_FONTS
			};

			assert(static_cast<size_t>(folder) < std::size(ids));

			wchar_t path[MAX_PATH];

			if (FAILED(::SHGetFolderPathW(nullptr, ids[static_cast<size_t>(folder)], nullptr, 0, path)))
			{
				return FilePath();
			}

			return detail::NormalizePath(Unicode::FromWString(path), true);
		}

		FilePath TemporaryDirectoryPath()
		{
			return FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData) + U"Temp/";
		}

		FilePath UniqueFilePath(const FilePathView directory)
		{
			FilePath directoryPath(directory);

			if (!directoryPath.isEmpty() && !directoryPath.ends_with(U'/'))
			{
				directoryPath.push_back(U'/');
			}

			const uint32 time = static_cast<uint32>(Time::GetSecSinceEpoch());
			const String prefix = directoryPath + Pad(ToHex(time), { 8, U'0' }) + U'-';
			uint32 randomValue = HardwareRNG{}();

			for (;;)
			{
				const FilePath path = prefix + Pad(ToHex(randomValue), { 8, U'0'}) + U".tmp";

				if (detail::StatusNotFound(fs::status(detail::ToPath(path))))
				{
					return path;
				}

				++randomValue;
			}
		}

		FilePath RelativePath(const FilePathView path, const FilePathView start)
		{
			const fs::path relativePath = fs::relative(detail::ToPath(path), detail::ToPath(start));
			return detail::NormalizePath(Unicode::FromWString(relativePath.wstring()));
		}

		bool CreateDirectories(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			try
			{
				fs::create_directories(detail::ToPath(path));
				return true;
			}
			catch (const fs::filesystem_error&)
			{
				return false;
			}
		}

		bool CreateParentDirectories(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			const FilePath parentDirectory = ParentPath(FullPath(path));

			if (!Exists(parentDirectory))
			{
				return CreateDirectories(parentDirectory);
			}

			return true;
		}

		bool Copy(const FilePathView from, const FilePathView to, const CopyOption copyOption)
		{
			if (from.isEmpty() || to.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(from) || detail::IsResourcePath(to))
			{
				return false;
			}

			const auto options = detail::ToCopyOptions(copyOption) | std::filesystem::copy_options::recursive;
			std::error_code error;
			std::filesystem::copy(detail::ToPath(from), detail::ToPath(to), options, error);

			return (error.value() == 0);
		}

		bool Remove(const FilePathView path, const bool allowUndo)
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

		bool RemoveContents(const FilePathView path, const bool allowUndo)
		{
			return Remove(path + U"\\*", allowUndo);
		}

		bool Rename(const FilePathView from, const FilePathView to)
		{
			if (from.isEmpty() || to.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(from) || detail::IsResourcePath(to))
			{
				return false;
			}

			std::error_code error;
			std::filesystem::rename(detail::ToPath(from), detail::ToPath(to), error);

			return (error.value() == 0);
		}

		bool IsSandBoxed()
		{
			return false;
		}
	}
}
