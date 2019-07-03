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

namespace s3d
{
	namespace detail
	{
		static Array<FilePath> GetResourceFilePaths()
		{
			const FilePath resourcePath = FileSystem::ModulePath() + U"/resources/";
			
			Array<FilePath> paths = FileSystem::DirectoryContents(resourcePath, true);
			
			paths.remove(resourcePath + U"icon.icns");
			
			paths.remove_if(FileSystem::IsDirectory);
			
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
		
		const FilePath resourcePath = FileSystem::ModulePath() + U"/resources/";
		
		return resourcePath + path;
	}
}
