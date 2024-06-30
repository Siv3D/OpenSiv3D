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

# include <Siv3D/Dialog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Shobjidl.h>

namespace s3d
{
	namespace detail
	{
		static bool SetFilters(const ComPtr<IFileDialog>& fileDialog, const Array<FileFilter>& filters)
		{
			if (not filters)
			{
				return true;
			}

			const Array<std::pair<std::wstring, std::wstring>> specStr = 
				filters.map([](FileFilter f)
			{
				std::pair<std::wstring, std::wstring> result;
				result.first = f.name.toWstr();

				if (f.patterns)
				{
					for (auto& pattern : f.patterns)
					{
						if (pattern)
						{
							pattern.insert(0, U"*.");
						}
					}
				}
				else
				{
					f.patterns << String(U"*.*");
				}

				result.second = f.patterns.join(U";", U"", U"").toWstr();

				return result;
			});

			const Array<COMDLG_FILTERSPEC> specs =
				specStr.map([](const std::pair<std::wstring, std::wstring>& p)
			{
				return COMDLG_FILTERSPEC{ p.first.data(), p.second.data() };
			});

			fileDialog->SetFileTypes(static_cast<UINT>(specs.size()), specs.data());

			return true;
		}

		static bool SetDefaultPath(const ComPtr<IFileDialog>& fileDialog, const FilePathView defaultPath)
		{
			if (not defaultPath)
			{
				return true;
			}

			const FilePath fullPath = FileSystem::FullPath(defaultPath);
			const std::wstring nativePath = FileSystem::NativePath(fullPath);

			ComPtr<IShellItem> folder;
			HRESULT result = ::SHCreateItemFromParsingName(nativePath.c_str(), nullptr, IID_PPV_ARGS(folder.GetAddressOf()));

			if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)
				|| result == HRESULT_FROM_WIN32(ERROR_INVALID_DRIVE))
			{
				return true;
			}
			else if (FAILED(result))
			{
				return false;
			}

			fileDialog->SetFolder(folder.Get());

			return true;
		}
	}

	namespace Dialog
	{
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			ComPtr<IFileOpenDialog> fileOpenDialog;

			if (FAILED(::CoCreateInstance(CLSID_FileOpenDialog, nullptr,
				CLSCTX_ALL, IID_PPV_ARGS(fileOpenDialog.GetAddressOf()))))
			{
				return none;
			}

			if (not detail::SetFilters(fileOpenDialog, filters))
			{
				return none;
			}

			if (not detail::SetDefaultPath(fileOpenDialog, defaultPath))
			{
				return none;
			}

			if (title)
			{
				fileOpenDialog->SetTitle(title.toWstr().c_str());
			}

			if (HRESULT result = fileOpenDialog->Show(static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle()));
				SUCCEEDED(result))
			{
				ComPtr<IShellItem> shellItem;
			
				if (FAILED(fileOpenDialog->GetResult(shellItem.GetAddressOf())))
				{
					return none;
				}
				
				wchar_t* filePath = nullptr;

				if (FAILED(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath)))
				{
					return none;
				}

				const FilePath path = FileSystem::FullPath(Unicode::FromWstring(filePath));

				::CoTaskMemFree(filePath);

				return path;
			}
			else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
			{
				return none;
			}
			else
			{
				return none;
			}
		}

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			ComPtr<IFileOpenDialog> fileOpenDialog;

			if (FAILED(::CoCreateInstance(CLSID_FileOpenDialog, nullptr,
				CLSCTX_ALL, IID_PPV_ARGS(fileOpenDialog.GetAddressOf()))))
			{
				return{};
			}

			if (not detail::SetFilters(fileOpenDialog, filters))
			{
				return{};
			}

			if (not detail::SetDefaultPath(fileOpenDialog, defaultPath))
			{
				return{};
			}

			if (title)
			{
				fileOpenDialog->SetTitle(title.toWstr().c_str());
			}

			DWORD flags;
		
			if (FAILED(fileOpenDialog->GetOptions(&flags)))
			{
				return{};
			}
		
			if (FAILED(fileOpenDialog->SetOptions(flags | FOS_ALLOWMULTISELECT)))
			{
				return{};
			}

			if (HRESULT result = fileOpenDialog->Show(static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle()));
				SUCCEEDED(result))
			{
				ComPtr<IShellItemArray> shellItemArray;

				if (FAILED(fileOpenDialog->GetResults(shellItemArray.GetAddressOf())))
				{
					return{};
				}

				DWORD num_items;

				if (FAILED(shellItemArray->GetCount(&num_items)))
				{
					return{};
				}

				Array<FilePath> paths;

				for (DWORD i = 0; i < num_items; ++i)
				{
					ComPtr<IShellItem> shellItem;
	
					if (FAILED(shellItemArray->GetItemAt(i, shellItem.GetAddressOf())))
					{
						continue;
					}

					SFGAOF attributes;
					if (FAILED(shellItem->GetAttributes(SFGAO_FILESYSTEM, &attributes)))
					{
						continue;
					}

					if (!(attributes & SFGAO_FILESYSTEM))
					{
						continue;
					}

					wchar_t* filePath = nullptr;

					if (FAILED(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath)))
					{
						continue;
					}

					paths << FileSystem::FullPath(Unicode::FromWstring(filePath));

					::CoTaskMemFree(filePath);
				}

				return paths;
			}
			else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
			{
				return{};
			}
			else
			{
				return{};
			}
		}

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title, const StringView defaultFileName)
		{
			ComPtr<IFileSaveDialog> fileSaveDialog;

			if (FAILED(::CoCreateInstance(CLSID_FileSaveDialog, nullptr,
				CLSCTX_ALL, IID_PPV_ARGS(fileSaveDialog.GetAddressOf()))))
			{
				return none;
			}

			if (not detail::SetFilters(fileSaveDialog, filters))
			{
				return none;
			}

			if (not detail::SetDefaultPath(fileSaveDialog, defaultPath))
			{
				return none;
			}

			if (title)
			{
				fileSaveDialog->SetTitle(title.toWstr().c_str());
			}

			// Append file extension
			fileSaveDialog->SetDefaultExtension(L"");

			if (defaultFileName)
			{
				fileSaveDialog->SetFileName(defaultFileName.toWstr().c_str());
			}

			if (HRESULT result = fileSaveDialog->Show(static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle()));
				SUCCEEDED(result))
			{
				ComPtr<IShellItem> shellItem;

				if (FAILED(fileSaveDialog->GetResult(shellItem.GetAddressOf())))
				{
					return none;
				}

				wchar_t* filePath = nullptr;

				if (FAILED(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath)))
				{
					return none;
				}

				const FilePath path = FileSystem::FullPath(Unicode::FromWstring(filePath));

				::CoTaskMemFree(filePath);

				return path;
			}
			else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
			{
				return none;
			}
			else
			{
				return none;
			}
		}

		Optional<FilePath> SelectFolder(const FilePathView defaultPath, const StringView title)
		{
			ComPtr<IFileDialog> folderDialog;

			if (FAILED(::CoCreateInstance(CLSID_FileOpenDialog, nullptr,
				CLSCTX_ALL, IID_PPV_ARGS(folderDialog.GetAddressOf()))))
			{
				return none;
			}

			if (!detail::SetDefaultPath(folderDialog, defaultPath))
			{
				return none;
			}

			DWORD flags;

			if (FAILED(folderDialog->GetOptions(&flags)))
			{
				return{};
			}

			if (FAILED(folderDialog->SetOptions(flags | FOS_PICKFOLDERS)))
			{
				return{};
			}

			if (title)
			{
				folderDialog->SetTitle(title.toWstr().c_str());
			}

			if (HRESULT result = folderDialog->Show(static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle()));
				SUCCEEDED(result))
			{
				ComPtr<IShellItem> shellItem;

				if (FAILED(folderDialog->GetResult(shellItem.GetAddressOf())))
				{
					return none;
				}

				wchar_t* filePath = nullptr;

				if (FAILED(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath)))
				{
					return none;
				}

				const FilePath path = FileSystem::FullPath(Unicode::FromWstring(filePath));

				::CoTaskMemFree(filePath);

				return path;
			}
			else if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED))
			{
				return none;
			}
			else
			{
				return none;
			}
		}
	}
}
