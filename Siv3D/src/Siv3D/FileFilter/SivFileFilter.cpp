//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/FileFilter.hpp>

namespace s3d
{
	FileFilter FileFilter::BMP()
	{
		return{ U"BMP",{ U"bmp" } };
	}

	FileFilter FileFilter::GIF()
	{
		return{ U"GIF",{ U"gif" } };
	}

	FileFilter FileFilter::JPEG()
	{
		return{ U"JPEG",{ U"jpg", U"jpeg" } };
	}

	FileFilter FileFilter::PNG()
	{
		return{ U"PNG",{ U"png" } };
	}

	FileFilter FileFilter::PPM()
	{
		return{ U"PPM",{ U"ppm", U"pgm", U"pbm", U"pnm" } };
	}

	FileFilter FileFilter::SVG()
	{
		return{ U"SVG",{ U"svg" } };
	}

	FileFilter FileFilter::TGA()
	{
		return{ U"TGA",{ U"tga" } };
	}

	FileFilter FileFilter::WebP()
	{
		return{ U"WebP",{ U"webp" } };
	}

	FileFilter FileFilter::AllImageFiles()
	{
		return{ U"All Picture Files",{ U"png", U"jpg", U"jpeg", U"bmp", U"gif", U"tga", U"svg", U"webp", U"ppm", U"pgm", U"pbm", U"pnm" } };
	}

	FileFilter FileFilter::AVI()
	{
		return{ U"AVI",{ U"avi" } };
	}

	FileFilter FileFilter::MP4()
	{
		return{ U"MP4",{ U"mp4" } };
	}

	FileFilter FileFilter::WebM()
	{
		return{ U"WebM",{ U"webm" } };
	}

	FileFilter FileFilter::AllVideoFiles()
	{
		return{ U"All Video Files",{ U"avi", U"mp4", U"webm" } };
	}

	FileFilter FileFilter::AAC()
	{
		return{ U"AAC",{ U"m4a" } };
	}

	FileFilter FileFilter::AIFF()
	{
		return{ U"AIFF",{ U"aif", U"aiff", U"aifc" } };
	}

	FileFilter FileFilter::FLAC()
	{
		return{ U"FLAC",{ U"flac" } };
	}

	FileFilter FileFilter::MIDI()
	{
		return{ U"MIDI",{ U"mid" } };
	}

	FileFilter FileFilter::MP3()
	{
		return{ U"MP3",{ U"mp3" } };
	}

	FileFilter FileFilter::OggVorbis()
	{
		return{ U"Ogg Vorbis",{ U"ogg" } };
	}

	FileFilter FileFilter::Opus()
	{
		return{ U"Opus",{ U"opus" } };
	}

	FileFilter FileFilter::WAVE()
	{
		return{ U"WAVE",{ U"wav" } };
	}

	FileFilter FileFilter::WMA()
	{
		return{ U"WMA",{ U"wma" } };
	}

	FileFilter FileFilter::AllAudioFiles()
	{
		return{ U"All Audio Files",{ U"wav", U"mp3", U"m4a", U"ogg", U"opus", U"mid",
		# if SIV3D_PLATFORM(WINDOWS)
				U"wma",
				U"flac"
		# elif SIV3D_PLATFORM(MACOS)
				U"aiff",
				U"flac"
		# elif SIV3D_PLATFORM(LINUX)

		# elif SIV3D_PLATFORM(WEB)

		# endif
		} };
	}

	FileFilter FileFilter::CSV()
	{
		return{ U"CSV",{ U"csv" } };
	}

	FileFilter FileFilter::INI()
	{
		return{ U"INI",{ U"ini" } };
	}

	FileFilter FileFilter::JSON()
	{
		return{ U"JSON",{ U"json" } };
	}

	FileFilter FileFilter::Text()
	{
		return{ U"Text",{ U"txt" } };
	}

	FileFilter FileFilter::TOML()
	{
		return{ U"TOML",{ U"toml" } };
	}

	FileFilter FileFilter::XML()
	{
		return{ U"XML",{ U"xml" } };
	}

	FileFilter FileFilter::AllFiles()
	{
		return{ U"All Files", {} };
	}
}
