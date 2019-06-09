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

# include <Siv3D/FileFilter.hpp>

namespace s3d
{
	FileFilter FileFilter::PNG()
	{
		return{ U"PNG",{ U"png" } };
	}

	FileFilter FileFilter::JPEG()
	{
		return{ U"JPEG",{ U"jpg", U"jpeg" } };
	}

	FileFilter FileFilter::BMP()
	{
		return{ U"BMP",{ U"bmp" } };
	}

	FileFilter FileFilter::GIF()
	{
		return{ U"GIF",{ U"gif" } };
	}

	FileFilter FileFilter::TGA()
	{
		return{ U"TGA",{ U"tga" } };
	}

	FileFilter FileFilter::WebP()
	{
		return{ U"WebP",{ U"webp" } };
	}

	FileFilter FileFilter::PPM()
	{
		return{ U"PPM",{ U"ppm" } };
	}

	FileFilter FileFilter::AllImageFiles()
	{
		return{ U"All Picture Files",{ U"png", U"jpg", U"jpeg", U"bmp", U"gif", U"tga", U"webp", U"ppm" } };
	}

	FileFilter FileFilter::WAVE()
	{
		return{ U"WAVE",{ U"wav" } };
	}

	FileFilter FileFilter::MP3()
	{
		return{ U"MP3",{ U"mp3" } };
	}

	FileFilter FileFilter::AAC()
	{
		return{ U"AAC",{ U"m4a" } };
	}

	FileFilter FileFilter::OggVorbis()
	{
		return{ U"Ogg Vorbis",{ U"ogg" } };
	}

	FileFilter FileFilter::AllAudioFiles()
	{
		return{ U"All Audio Files",{ U"wav", U"mp3", U"m4a", U"ogg" } };
	}

	FileFilter FileFilter::Text()
	{
		return{ U"Text",{ U"txt" } };
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

	FileFilter FileFilter::XML()
	{
		return{ U"XML",{ U"xml" } };
	}

	FileFilter FileFilter::TOML()
	{
		return{ U"TOML",{ U"toml" } };
	}

	FileFilter FileFilter::AllFiles()
	{
		return{ U"All Files", {} };
	}
}
