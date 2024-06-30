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
# include <ThirdParty/nativefiledialog-extended/nfd.hpp>

namespace s3d
{
	static bool g_dialogInitialized = false;

	namespace Dialog
	{
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView)
		{
			if (not g_dialogInitialized)
			{
				NFD_Init();
				g_dialogInitialized = true;
			}

			const Array<std::pair<std::string, std::string>> tmp =
				filters.map([](const FileFilter& f) ->std::pair<std::string, std::string>
					{ return{ f.name.narrow(), f.patterns.join(U",", U"", U"").narrow() }; });

			const Array<nfdfilteritem_t> filterItems = tmp
				.map([](const std::pair<std::string, std::string>& p)
					{ return nfdfilteritem_t{ p.first.c_str(), p.second.c_str() }; });

			const std::string defaultPathUTF8 = defaultPath.narrow();
			const char* defaultPathC = (defaultPathUTF8.empty() ? nullptr : defaultPathUTF8.data());

			NFD::UniquePath outPath;
			const nfdresult_t result = NFD::OpenDialog(outPath, filterItems.data(), static_cast<nfdfiltersize_t>(filterItems.size()), defaultPathC);
	
			if (result == NFD_OKAY)
			{
				return Unicode::Widen(outPath.get());
			}
			else
			{
				return none;
			}
		}

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView)
		{
			if (not g_dialogInitialized)
			{
				NFD_Init();
				g_dialogInitialized = true;
			}

			const Array<std::pair<std::string, std::string>> tmp =
				filters.map([](const FileFilter& f) ->std::pair<std::string, std::string>
					{ return{ f.name.narrow(), f.patterns.join(U",", U"", U"").narrow() }; });

			const Array<nfdfilteritem_t> filterItems = tmp
				.map([](const std::pair<std::string, std::string>& p)
					{ return nfdfilteritem_t{ p.first.c_str(), p.second.c_str() }; });

			const std::string defaultPathUTF8 = defaultPath.narrow();
			const char* defaultPathC = (defaultPathUTF8.empty() ? nullptr : defaultPathUTF8.data());

			NFD::UniquePathSet outPaths;
			const nfdresult_t result = NFD::OpenDialogMultiple(outPaths, filterItems.data(), static_cast<nfdfiltersize_t>(filterItems.size()), defaultPathC);

			if (result == NFD_OKAY)
			{
				nfdpathsetsize_t numPaths;
				NFD::PathSet::Count(outPaths, numPaths);

				Array<FilePath> results(Arg::reserve = numPaths);

				for (nfdfiltersize_t i = 0; i < numPaths; ++i)
				{
					NFD::UniquePathSetPath path;
					NFD::PathSet::GetPath(outPaths, i, path);
					results << Unicode::Widen(path.get());
				}

				return results;
			}
			else
			{
				return{};
			}
		}

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView, const StringView)
		{
			if (not g_dialogInitialized)
			{
				NFD_Init();
				g_dialogInitialized = true;
			}

			const Array<std::pair<std::string, std::string>> tmp =
				filters.map([](const FileFilter& f) ->std::pair<std::string, std::string>
					{ return{ f.name.narrow(), f.patterns.join(U",", U"", U"").narrow() }; });

			const Array<nfdfilteritem_t> filterItems = tmp
				.map([](const std::pair<std::string, std::string>& p)
					{ return nfdfilteritem_t{ p.first.c_str(), p.second.c_str() }; });

			const std::string defaultPathUTF8 = defaultPath.narrow();
			const char* defaultPathC = (defaultPathUTF8.empty() ? nullptr : defaultPathUTF8.data());

			NFD::UniquePath outPath;
			const nfdresult_t result = NFD::SaveDialog(outPath, filterItems.data(), static_cast<nfdfiltersize_t>(filterItems.size()), defaultPathC);

			if (result == NFD_OKAY)
			{
				return Unicode::Widen(outPath.get());
			}
			else
			{
				return none;
			}
		}

		Optional<FilePath> SelectFolder(const FilePathView defaultPath, const StringView)
		{
			if (not g_dialogInitialized)
			{
				NFD_Init();
				g_dialogInitialized = true;
			}

			const std::string defaultPathUTF8 = defaultPath.narrow();
			const char* defaultPathC = (defaultPathUTF8.empty() ? nullptr : defaultPathUTF8.data());

			NFD::UniquePath outPath;
			const nfdresult_t result = NFD::PickFolder(outPath, defaultPathC);

			if (result == NFD_OKAY)
			{
				return FileSystem::FullPath(Unicode::Widen(outPath.get()));
			}
			else
			{
				return none;
			}
		}
	}
}
