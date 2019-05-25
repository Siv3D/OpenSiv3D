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

# include <Siv3D/Dialog.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace Dialog
	{
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters, const FilePath& defaultPath, const String&)
		{
			// [Siv3D ToDo]
			return none;
		}
		
		Optional<FilePath> SaveFile(const Array<FileFilter>& filters, const FilePath& defaultPath, const String&)
		{
			// [Siv3D ToDo]
			return none;
		}
		
		Optional<FilePath> SelectFolder(const FilePath& defaultPath, const String&)
		{
			// [Siv3D ToDo]
			return none;
		}
	}
}
