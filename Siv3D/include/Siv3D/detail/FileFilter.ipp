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

# pragma once

namespace s3d
{
	inline FileFilter FileFilter::BMP()
	{
		return{ U"BMP",{ U"bmp" } };
	}

	inline FileFilter FileFilter::GIF()
	{
		return{ U"GIF",{ U"gif" } };
	}

	inline FileFilter FileFilter::JPEG()
	{
		return{ U"JPEG",{ U"jpg", U"jpeg" } };
	}

	inline FileFilter FileFilter::PNG()
	{
		return{ U"PNG",{ U"png" } };
	}

	inline FileFilter FileFilter::PPM()
	{
		return{ U"PPM",{ U"ppm", U"pgm", U"pbm", U"pnm" } };
	}

	inline FileFilter FileFilter::SVG()
	{
		return{ U"SVG",{ U"svg" } };
	}

	inline FileFilter FileFilter::TGA()
	{
		return{ U"TGA",{ U"tga" } };
	}

	inline FileFilter FileFilter::WebP()
	{
		return{ U"WebP",{ U"webp" } };
	}

	inline FileFilter FileFilter::AllImageFiles()
	{
		return{ U"All Picture Files",{ U"png", U"jpg", U"jpeg", U"bmp", U"gif", U"tga", U"svg", U"webp", U"ppm", U"pgm", U"pbm", U"pnm" } };
	}

	inline FileFilter FileFilter::AVI()
	{
		return{ U"AVI",{ U"avi" } };
	}

	inline FileFilter FileFilter::MP4()
	{
		return{ U"MP4",{ U"mp4" } };
	}

	inline FileFilter FileFilter::WebM()
	{
		return{ U"WebM",{ U"webm" } };
	}

	inline FileFilter FileFilter::AllVideoFiles()
	{
		return{ U"All Video Files",{ U"avi", U"mp4", U"webm" } };
	}

	inline FileFilter FileFilter::AAC()
	{
		return{ U"AAC",{ U"m4a" } };
	}

	inline FileFilter FileFilter::AIFF()
	{
		return{ U"AIFF",{ U"aif", U"aiff", U"aifc" } };
	}

	inline FileFilter FileFilter::FLAC()
	{
		return{ U"FLAC",{ U"flac" } };
	}

	inline FileFilter FileFilter::MIDI()
	{
		return{ U"MIDI",{ U"mid" } };
	}

	inline FileFilter FileFilter::MP3()
	{
		return{ U"MP3",{ U"mp3" } };
	}

	inline FileFilter FileFilter::OggVorbis()
	{
		return{ U"Ogg Vorbis",{ U"ogg" } };
	}

	inline FileFilter FileFilter::Opus()
	{
		return{ U"Opus",{ U"opus" } };
	}

	inline FileFilter FileFilter::WAVE()
	{
		return{ U"WAVE",{ U"wav" } };
	}

	inline FileFilter FileFilter::WMA()
	{
		return{ U"WMA",{ U"wma" } };
	}

	inline FileFilter FileFilter::AllAudioFiles()
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

	inline FileFilter FileFilter::CSV()
	{
		return{ U"CSV",{ U"csv" } };
	}

	inline FileFilter FileFilter::INI()
	{
		return{ U"INI",{ U"ini" } };
	}

	inline FileFilter FileFilter::JSON()
	{
		return{ U"JSON",{ U"json" } };
	}

	inline FileFilter FileFilter::Text()
	{
		return{ U"Text",{ U"txt" } };
	}

	inline FileFilter FileFilter::TOML()
	{
		return{ U"TOML",{ U"toml" } };
	}

	inline FileFilter FileFilter::XML()
	{
		return{ U"XML",{ U"xml" } };
	}

	inline FileFilter FileFilter::AllFiles()
	{
		return{ U"All Files", {} };
	}
}
