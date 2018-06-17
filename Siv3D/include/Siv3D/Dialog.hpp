//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "Optional.hpp"

namespace s3d
{
	struct FileFilter
	{
		String name;

		Array<String> patterns;
	};

	namespace Dialog
	{
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters = {}, const FilePath& defaultPath = U"", const String& title = U"");

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters = {}, const FilePath& defaultPath = U"", const String& title = U"");

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters = {}, const FilePath& defaultPath = U"", const String& title = U"");

		Optional<FilePath> SelectFolder(const FilePath& defaultPath = U"", const String& title = U"");
	}
}
