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

# include <Siv3D/Resource.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Windows/Windows.hpp>

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
		if (path.starts_with(U'/'))
		{
			return FilePath{ path };
		}

		return (U'/' + path);
	}
}
