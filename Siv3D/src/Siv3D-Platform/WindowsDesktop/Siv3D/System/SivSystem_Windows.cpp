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

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Windows/Windows.hpp>
# define SECURITY_WIN32
# include <Security.h>
# include <lmcons.h>

namespace s3d
{
	namespace
	{
		[[nodiscard]]
		static bool IsRunningInVisualStudio_impl()
		{
			wchar_t* pValue;
			size_t len;
			errno_t err = ::_wdupenv_s(&pValue, &len, L"VisualStudioVersion");

			if (err || (not pValue))
			{
				return false;
			}

			std::free(pValue);

			return true;
		}
	}

	namespace System
	{
		void Sleep(const int32 milliseconds)
		{
			if (milliseconds < 0)
			{
				return;
			}

			// システムクロックの精度を上げる
			::timeBeginPeriod(1);
			{
				::Sleep(milliseconds);
			}
			::timeEndPeriod(1);
		}

		bool LaunchBrowser(const FilePathView _url)
		{
			String url{ _url };
			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");

			if (not isWebPage)
			{
				const String extension = FileSystem::Extension(_url);
				const bool isHTML = (extension == U"html") || (extension == U"htm");

				if (not isHTML)
				{
					return false;
				}

				url = (U"file://" + FileSystem::FullPath(_url));
			}

			return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, L"open", url.toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
		}

		bool ShowInFileManager(const FilePathView path)
		{
			const FilePath fullPath = FileSystem::FullPath(path);

			if (FileSystem::IsFile(fullPath))
			{
				const String param = U"/select," + fullPath.replaced(U'/', U'\\');

				return (reinterpret_cast<int64>(::ShellExecuteW(nullptr, L"open", L"explorer.exe", param.toWstr().c_str(), nullptr, SW_SHOWNORMAL)) > 32);
			}
			else if (FileSystem::IsDirectory(fullPath))
			{
				return (reinterpret_cast<int64>(::ShellExecuteW(nullptr, L"explore", fullPath.toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32);
			}

			return false;
		}

		String ComputerName()
		{
			wchar_t buffer[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD size = static_cast<DWORD>(std::ssize(buffer));

			if (::GetComputerNameExW(ComputerNamePhysicalDnsHostname, buffer, &size))
			{
				return Unicode::FromWstring(buffer);
			}
			else
			{
				return{};
			}
		}

		String UserName()
		{
			wchar_t buffer[UNLEN + 1];
			DWORD size = static_cast<DWORD>(std::ssize(buffer));
			
			if (GetUserNameW(buffer, &size))
			{
				return Unicode::FromWstring(buffer);
			}
			else
			{
				return{};
			}
		}

		String FullUserName()
		{
			wchar_t buffer[UNLEN + 1];
			ULONG size = static_cast<ULONG>(std::ssize(buffer));

			if (::GetUserNameExW(NameDisplay, buffer, &size))
			{
				return Unicode::FromWstring(buffer);
			}
			else
			{
				return{};
			}
		}

		String DefaultLocale()
		{
			wchar_t languageBuffer[LOCALE_NAME_MAX_LENGTH];

			if (const size_t length = ::GetUserDefaultLocaleName(languageBuffer, LOCALE_NAME_MAX_LENGTH))
			{
				return Unicode::FromWstring(std::wstring_view{ languageBuffer, (length - 1) });
			}
			else
			{
				return U"en-US";
			}
		}

		String DefaultLanguage()
		{
			ULONG numLanguages = 0;
			ULONG languageBufferSize = 0;

			if (::GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &numLanguages, nullptr, &languageBufferSize))
			{
				std::wstring languages(languageBufferSize, '\0');

				if (::GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &numLanguages, languages.data(), &languageBufferSize))
				{
					// languages はヌル区切りされた文字列。
					// ヌル区切りされたうち、最初の言語が使用言語
					return Unicode::FromWstring(languages.data());
				}
			}

			return DefaultLocale();
		}

		bool LaunchFile(const FilePathView fileName)
		{
			const Platform::NativeFilePath fullpath = FileSystem::NativePath(fileName);

			const HINSTANCE result = ::ShellExecuteW(nullptr, nullptr, fullpath.c_str(), nullptr, nullptr, SW_SHOW);

			return (32 < static_cast<int32>(reinterpret_cast<size_t>(result)));
		}

		bool LaunchFileWithTextEditor(const FilePathView fileName)
		{
			const Platform::NativeFilePath fullpath = FileSystem::NativePath(fileName);

			SHELLEXECUTEINFO sei{};
			sei.cbSize = sizeof(sei);
			sei.lpVerb = L"open";
			sei.lpFile = L"notepad.exe";
			sei.lpParameters = fullpath.c_str();
			sei.nShow = SW_SHOW;

			return (::ShellExecuteExW(&sei) != 0);
		}

		bool IsRunningInVisualStudio()
		{
			static const bool result = IsRunningInVisualStudio_impl();

			return result;
		}

		bool IsRunningInXcode()
		{
			return false;
		}
	}
}
