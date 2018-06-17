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

		static FileFilter PNG()
		{
			return{ U"PNG",{ U"png" } };
		}

		static FileFilter JPEG()
		{
			return{ U"JPEG",{ U"jpg", U"jpeg" } };
		}

		static FileFilter BMP()
		{
			return{ U"BMP",{ U"bmp" } };
		}

		static FileFilter GIF()
		{
			return{ U"GIF",{ U"gif" } };
		}

		static FileFilter TGA()
		{
			return{ U"TGA",{ U"tga" } };
		}

		static FileFilter PPM()
		{
			return{ U"PPM",{ U"ppm" } };
		}

		static FileFilter AllImageFiles()
		{
			return{ U"All Picture Files",{ U"png", U"jpg", U"jpeg", U"bmp", U"gif", U"tga", U"ppm" } };
		}

		static FileFilter WAVE()
		{
			return{ U"WAVE",{ U"wav" } };
		}

		static FileFilter MP3()
		{
			return{ U"MP3",{ U"mp3" } };
		}

		static FileFilter AAC()
		{
			return{ U"AAC",{ U"m4a" } };
		}

		static FileFilter AllAudioFiles()
		{
			return{ U"All Audio Files",{ U"wav", U"mp3", U"m4a" } };
		}

		static FileFilter AllFiles()
		{
			return{ U"All Files", {} };
		}
	};

	namespace Dialog
	{
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters = {}, const FilePath& defaultPath = U"", const String& title = U"");

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters = {}, const FilePath& defaultPath = U"", const String& title = U"");

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters = {}, const FilePath& defaultPath = U"", const String& title = U"");

		Optional<FilePath> SelectFolder(const FilePath& defaultPath = U"", const String& title = U"");


		Image OpenImage(const FilePath& defaultPath = U"", const String& title = U"");

		Texture OpenTexture(const FilePath& defaultPath = U"", const String& title = U"");

		Wave OpenWave(const FilePath& defaultPath = U"", const String& title = U"");

		Audio OpenAudio(const FilePath& defaultPath = U"", const String& title = U"");


		Optional<FilePath> SaveImage(const FilePath& defaultPath = U"", const String& title = U"");

		//Optional<FilePath> SaveWave(const FilePath& defaultPath = U"", const String& title = U"");
	}
}
