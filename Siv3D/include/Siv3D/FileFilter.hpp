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
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	struct FileFilter
	{
		String name;

		Array<String> patterns;

		[[nodiscard]]
		static FileFilter BMP();

		[[nodiscard]]
		static FileFilter GIF();

		[[nodiscard]]
		static FileFilter JPEG();

		[[nodiscard]]
		static FileFilter PNG();

		[[nodiscard]]
		static FileFilter PPM();

		[[nodiscard]]
		static FileFilter SVG();

		[[nodiscard]]
		static FileFilter TGA();

		[[nodiscard]]
		static FileFilter WebP();

		[[nodiscard]]
		static FileFilter AllImageFiles();

		[[nodiscard]]
		static FileFilter AVI();

		[[nodiscard]]
		static FileFilter MP4();

		[[nodiscard]]
		static FileFilter WebM();

		[[nodiscard]]
		static FileFilter AllVideoFiles();

		[[nodiscard]]
		static FileFilter AAC();

		[[nodiscard]]
		static FileFilter AIFF();

		[[nodiscard]]
		static FileFilter FLAC();

		[[nodiscard]]
		static FileFilter MP3();

		[[nodiscard]]
		static FileFilter OggVorbis();

		[[nodiscard]]
		static FileFilter Opus();

		[[nodiscard]]
		static FileFilter WAVE();

		[[nodiscard]]
		static FileFilter WMA();

		[[nodiscard]]
		static FileFilter AllAudioFiles();

		[[nodiscard]]
		static FileFilter CSV();

		[[nodiscard]]
		static FileFilter INI();

		[[nodiscard]]
		static FileFilter JSON();

		[[nodiscard]]
		static FileFilter Text();

		[[nodiscard]]
		static FileFilter TOML();

		[[nodiscard]]
		static FileFilter XML();

		[[nodiscard]]
		static FileFilter AllFiles();
	};
}

# include "detail/FileFilter.ipp"
