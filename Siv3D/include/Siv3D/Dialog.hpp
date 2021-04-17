//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "Texture.hpp"
# include "FileFilter.hpp"

namespace s3d
{
	namespace Dialog
	{
		[[nodiscard]]
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters = {}, FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Array<FilePath> OpenFiles(const Array<FileFilter>& filters = {}, FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Optional<FilePath> SaveFile(const Array<FileFilter>& filters = {}, FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Optional<FilePath> SelectFolder(FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Image OpenImage(FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Texture OpenTexture(FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Texture OpenTexture(TextureDesc desc, FilePathView defaultPath = U"", StringView title = U"");

		//[[nodiscard]]
		//Wave OpenWave(FilePathView defaultPath = U"", StringView title = U"");

		//[[nodiscard]]
		//Audio OpenAudio(FilePathView defaultPath = U"", StringView title = U"");

		//[[nodiscard]]
		//Audio OpenAudio(Arg::loop_<bool> loop, FilePathView defaultPath = U"", StringView title = U"");

		[[nodiscard]]
		Optional<FilePath> SaveImage(FilePathView defaultPath = U"", StringView title = U"");

		//[[nodiscard]]
		//Optional<FilePath> SaveWave(FilePathView defaultPath = U"", StringView title = U"");
	}
}
