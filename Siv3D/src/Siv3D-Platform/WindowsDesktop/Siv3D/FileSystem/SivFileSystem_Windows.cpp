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

# include <filesystem>
# include <Siv3D/Common.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Shlobj.h>

namespace s3d
{
	namespace fs = std::filesystem;

	namespace detail
	{
		[[nodiscard]]
		inline static fs::path ToPath(const FilePathView path)
		{
			return fs::path(path.toWstr());
		}

		[[nodiscard]]
		inline static fs::file_status GetStatus(const FilePathView path)
		{
			return fs::status(detail::ToPath(path));
		}

		[[nodiscard]]
		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			path.replace(U'\\', U'/');

			if (!path.ends_with(U'/')
				&& (skipDirectoryCheck || (GetStatus(path).type() == fs::file_type::directory)))
			{
				path.push_back(U'/');
			}

			return path;
		}

		[[nodiscard]]
		static bool ResourceExists(const FilePathView path)
		{
			const std::wstring pathW = path.toWstr();

			return (::FindResourceW(::GetModuleHandleW(nullptr), &pathW[1], L"FILE") != nullptr);
		}

		[[nodiscard]]
		static int64 ResourceSize(const FilePathView path)
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);
			const std::wstring pathW = path.toWstr();

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE"))
			{
				return ::SizeofResource(hModule, hrs);
			}
			else
			{
				return 0;
			}
		}

		[[nodiscard]]
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
						result += DirectorySizeRecursive((directory + Unicode::FromWstring(data.cFileName)) + U'/');
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

		static void DirectoryContentsRecursive(FilePath directory, Array<FilePath>& paths, const Recursive recursive)
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
					paths.push_back(directory + Unicode::FromWstring(data.cFileName));

					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						paths.back().push_back(U'/');

						if (recursive)
						{
							DirectoryContentsRecursive(paths.back(), paths, Recursive::Yes);
						}
					}
				}

			} while (::FindNextFileW(sh, &data));

			::FindClose(sh);
		}

		[[nodiscard]]
		static DateTime FiletimeToTime(FILETIME& in)
		{
			SYSTEMTIME systemtime;
			::FileTimeToLocalFileTime(&in, &in);
			::FileTimeToSystemTime(&in, &systemtime);

			return{ systemtime.wYear, systemtime.wMonth, systemtime.wDay,
				systemtime.wHour, systemtime.wMinute, systemtime.wSecond, systemtime.wMilliseconds };
		}

		[[nodiscard]]
		inline constexpr std::filesystem::copy_options ToCopyOptions(const CopyOption copyOption) noexcept
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

		static BOOL CALLBACK EnumResourceNameCallback(HMODULE, LPCWSTR, LPWSTR lpName, LONG_PTR lParam)
		{
			Array<FilePath>& paths = *reinterpret_cast<Array<FilePath>*>(lParam);

			paths.push_back(U'/' + Unicode::FromWstring(lpName));

			return true;
		}

		namespace init
		{
			const static struct FilePathCache
			{
				FilePath initialDirectory;

				FilePath modulePath;

				std::array<FilePath, 11> specialFolderPaths;

				Array<FilePath> resourceFilePaths;

				FilePathCache()
				{
					initialDirectory = FileSystem::CurrentDirectory();

					modulePath = []() -> FilePath
					{
						wchar_t result[1024];
						const DWORD length = ::GetModuleFileNameW(nullptr, result, _countof(result));

						if ((length == 0) || (length >= _countof(result)))
						{
							return{};
						}

						return NormalizePath(Unicode::FromWstring(std::wstring_view(result, length)));
					}();

					specialFolderPaths = []()
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
							CSIDL_FONTS,
							CSIDL_PROFILE,
							CSIDL_PROGRAM_FILES,
						};

						std::array<FilePath, 11> paths;

						for (size_t i = 0; i < paths.size(); ++i)
						{
							wchar_t path[MAX_PATH];

							if (FAILED(::SHGetFolderPathW(nullptr, ids[i], nullptr, 0, path)))
							{
								continue;
							}

							paths[i] = detail::NormalizePath(Unicode::FromWstring(path), true);
						}

						return paths;
					}();

					resourceFilePaths = []()
					{
						Array<FilePath> paths;

						HMODULE hModule = ::GetModuleHandleW(nullptr);

						::EnumResourceNamesW(hModule, L"FILE", EnumResourceNameCallback, (LONG_PTR)&paths);

						paths.sort();

						return paths;
					}();
				}

			} g_filePathCache;

			const Array<FilePath>& GetResourceFilePaths() noexcept
			{
				return g_filePathCache.resourceFilePaths;
			}
		}
	}

	namespace FileSystem
	{
		bool IsResourcePath(const FilePathView path) noexcept
		{
			return path.starts_with(U'/');
		}

		bool Exists(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return (detail::GetStatus(path).type() != fs::file_type::not_found);
		}

		bool IsDirectory(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return false;
			}

			return (detail::GetStatus(path).type() == fs::file_type::directory);
		}

		bool IsFile(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return (detail::GetStatus(path).type() == fs::file_type::regular);
		}

		bool IsResource(const FilePathView path)
		{
			return IsResourcePath(path)
				&& detail::ResourceExists(path);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return{};
			}

			if (IsResourcePath(path)) [[unlikely]]
			{
				return FilePath(path);
			}

			const std::wstring wpath = path.toWstr();
			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(wpath.c_str(), _countof(result), result, &pFilePart);

			if (length == 0) [[unlikely]]
			{
				return{};
			}
			else if (length > std::size(result)) [[unlikely]]
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);

				if ((length2 == 0)
					|| (length < (length2 + 1)))
				{
					return{};
				}

				if (length2 < result2.size())
				{
					result2.resize(length2);
				}

				const bool isDirectory = (pFilePart == nullptr);
				return detail::NormalizePath(Unicode::FromWstring(result2), isDirectory);
			}

			const bool isDirectory = (pFilePart == nullptr);
			return detail::NormalizePath(Unicode::FromWstring(std::wstring_view(result, length)), isDirectory);
		}

		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return{};
			}

			if (IsResourcePath(path)) [[unlikely]]
			{
				return{};
			}

			const std::wstring wpath = path.toWstr();
			wchar_t result[1024];
			wchar_t* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(wpath.c_str(), _countof(result), result, &pFilePart);

			if (length == 0) [[unlikely]]
			{
				return{};
			}
			else if (length > std::size(result)) [[unlikely]]
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetFullPathNameW(wpath.c_str(), length, result2.data(), &pFilePart);

				if ((length2 == 0)
					|| (length < (length2 + 1)))
				{
					return{};
				}

				if (length2  < result2.size())
				{
					result2.resize(length2);
				}

				return result2;
			}

			return std::wstring(result, length);
		}

		FilePath VolumePath(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return{};
			}

			if (IsResourcePath(path))
			{
				return{};
			}

			const std::wstring wpath = path.toWstr();
			wchar_t result[MAX_PATH];

			if (::GetVolumePathNameW(wpath.c_str(), result, _countof(result)) == 0)
			{
				return{};
			}

			return Unicode::FromWstring(result).replace(U'\\', U'/');
		}

		FilePath PathAppend(const FilePathView lhs, const FilePathView rhs)
		{
			return FilePath{ (detail::ToPath(lhs) / detail::ToPath(rhs)).u32string() }.replace(U'\\', U'/');
		}

		bool IsEmptyDirectory(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return false;
			}

			const auto fpath = detail::ToPath(path);

			if (detail::GetStatus(path).type() != fs::file_type::directory)
			{
				return false;
			}

			return (fs::directory_iterator(fpath) == fs::directory_iterator());
		}

		int64 Size(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceSize(path);
			}

			const auto fpath = detail::ToPath(path);
			const auto type = fs::status(fpath).type();

			if (type == fs::file_type::regular)
			{
				WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					return 0;
				}

				return ((static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow);
			}
			else if (type == fs::file_type::directory)
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
			if (not path) [[unlikely]]
			{
				return 0;
			}

			if (IsResourcePath(path))
			{
				return detail::ResourceSize(path);
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0) [[unlikely]]
			{
				return 0;
			}

			// ディレクトリの場合は 0
			if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return 0;
			}

			return ((static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow);
		}

		Optional<DateTime> CreationTime(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return none;
			}

			if (IsResourcePath(path))
			{
				return CreationTime(ModulePath());
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftCreationTime);
		}

		Optional<DateTime> WriteTime(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return none;
			}

			if (IsResourcePath(path))
			{
				return WriteTime(ModulePath());
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastWriteTime);
		}

		Optional<DateTime> AccessTime(const FilePathView path)
		{
			if (not path) [[unlikely]]
			{
				return none;
			}

			if (IsResourcePath(path))
			{
				return AccessTime(ModulePath());
			}

			WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.toWstr().c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastAccessTime);
		}

		Array<FilePath> DirectoryContents(const FilePathView path, const Recursive recursive)
		{
			Array<FilePath> paths;

			if (not path) [[unlikely]]
			{
				return paths;
			}

			if (IsResourcePath(path))
			{
				return paths;
			}

			if (detail::GetStatus(path).type() != fs::file_type::directory)
			{
				return paths;
			}

			detail::DirectoryContentsRecursive(FullPath(path), paths, recursive);

			return paths;
		}

		const FilePath& InitialDirectory() noexcept
		{
			return detail::init::g_filePathCache.initialDirectory;
		}

		const FilePath& ModulePath() noexcept
		{
			return detail::init::g_filePathCache.modulePath;
		}

		FilePath CurrentDirectory()
		{
			wchar_t result[1024];
			const DWORD length = ::GetCurrentDirectoryW(_countof(result), result);

			if (length == 0)
			{
				return{};
			}
			else if (length > std::size(result))
			{
				std::wstring result2(length - 1, L'\0');
				const DWORD length2 = ::GetCurrentDirectoryW(length, result2.data());

				if ((length2 == 0)
					|| (length < (length2 + 1)))
				{
					return{};
				}

				if (length2 < result2.size())
				{
					result2.resize(length2);
				}

				return detail::NormalizePath(Unicode::FromWstring(result2), true);
			}

			return detail::NormalizePath(Unicode::FromWstring(std::wstring_view(result, length)), true);
		}

		bool ChangeCurrentDirectory(const FilePathView path)
		{
			if (not IsDirectory(path))
			{
				return false;
			}

			return (::SetCurrentDirectoryW(path.toWstr().c_str()) != 0);
		}

		const FilePath& GetFolderPath(const SpecialFolder folder)
		{
			assert(FromEnum(folder) < std::ssize(detail::init::g_filePathCache.specialFolderPaths));

			return detail::init::g_filePathCache.specialFolderPaths[FromEnum(folder)];
		}

		FilePath TemporaryDirectoryPath()
		{
			return GetFolderPath(SpecialFolder::LocalAppData) + U"Temp/";
		}

		FilePath RelativePath(const FilePathView path, const FilePathView start)
		{
			const fs::path relativePath = fs::relative(detail::ToPath(path), detail::ToPath(start));
			
			return detail::NormalizePath(Unicode::FromWstring(relativePath.wstring()));
		}

		bool CreateDirectories(const FilePathView path)
		{
			if (not path)
			{
				return true;
			}

			if (IsResourcePath(path))
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
			if (not path)
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return false;
			}

			const FilePath parentDirectory = ParentPath(FullPath(path));

			if (not Exists(parentDirectory))
			{
				return CreateDirectories(parentDirectory);
			}

			return true;
		}

		bool Copy(const FilePathView from, const FilePathView to, const CopyOption copyOption)
		{
			if ((not from) || (not to))
			{
				return false;
			}

			if (IsResourcePath(from) || IsResourcePath(to))
			{
				return false;
			}

			CreateParentDirectories(to);

			const auto options = detail::ToCopyOptions(copyOption) | std::filesystem::copy_options::recursive;
			std::error_code error;
			std::filesystem::copy(detail::ToPath(from), detail::ToPath(to), options, error);

			return (error.value() == 0);
		}

		bool Remove(const FilePathView path, const AllowUndo allowUndo)
		{
			if (not path)
			{
				return false;
			}

			if (IsResourcePath(path))
			{
				return false;
			}

			const std::wstring from = (path + U'\0').replaced(U'/', U'\\').toWstr();

			SHFILEOPSTRUCTW fileOption =
			{
				.wFunc = FO_DELETE,
				.pFrom = from.c_str(),
				.fFlags = FILEOP_FLAGS(FOF_NOERRORUI | FOF_SILENT | FOF_NOCONFIRMATION | (allowUndo ? FOF_ALLOWUNDO : 0)),
			};

			return (::SHFileOperationW(&fileOption) == 0)
				&& (not fileOption.fAnyOperationsAborted);
		}

		bool RemoveContents(const FilePathView path, const AllowUndo allowUndo)
		{
			if (not IsDirectory(path))
			{
				return false;
			}

			return Remove(path + U"\\*", allowUndo);
		}

		bool Rename(const FilePathView from, const FilePathView to)
		{
			if ((not from) || (not to))
			{
				return false;
			}

			if (IsResourcePath(from) || IsResourcePath(to))
			{
				return false;
			}

			std::error_code error;
			std::filesystem::rename(detail::ToPath(from), detail::ToPath(to), error);

			return (error.value() == 0);
		}
	}
}
