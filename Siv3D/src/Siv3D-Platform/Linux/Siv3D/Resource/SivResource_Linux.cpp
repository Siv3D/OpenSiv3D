﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Resource.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail::init
	{
		const Array<FilePath>& GetResourceFilePaths() noexcept;
	}

	const Array<FilePath>& EnumResourceFiles() noexcept
	{
		return detail::init::GetResourceFilePaths();
	}

	FilePath Resource(const FilePathView path)
	{
		const FilePath resourceDirectory = (FileSystem::ParentPath(FileSystem::ModulePath()) + U"resources/");

		return (resourceDirectory + path);
	}
}
