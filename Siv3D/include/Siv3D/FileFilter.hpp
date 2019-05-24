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

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	struct FileFilter
	{
		String name;

		Array<String> patterns;

		static FileFilter PNG();

		static FileFilter JPEG();

		static FileFilter BMP();

		static FileFilter GIF();

		static FileFilter TGA();

		static FileFilter WebP();

		static FileFilter PPM();

		static FileFilter AllImageFiles();

		static FileFilter WAVE();

		static FileFilter MP3();

		static FileFilter AAC();

		static FileFilter AllAudioFiles();

		static FileFilter Text();

		static FileFilter CSV();

		static FileFilter INI();

		static FileFilter JSON();

		static FileFilter XML();

		static FileFilter TOML();

		static FileFilter AllFiles();
	};
}
