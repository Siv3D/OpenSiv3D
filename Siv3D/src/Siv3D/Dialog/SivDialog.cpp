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

# include <Siv3D/Dialog.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Audio.hpp>

namespace s3d
{
	namespace detail
	{
		const Array<FileFilter> ImageFilters =
		{
			FileFilter::AllImageFiles(),
			FileFilter::PNG(),
			FileFilter::JPEG(),
			FileFilter::BMP(),
			FileFilter::GIF(),
			FileFilter::TGA(),
			FileFilter::PPM(),
		};

		const Array<FileFilter> AudioFilters =
		{
			FileFilter::AllAudioFiles(),
			FileFilter::WAVE(),
			FileFilter::MP3(),
			FileFilter::AAC()
		};
	}

	namespace Dialog
	{
		Image OpenImage(const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::ImageFilters, defaultPath, title))
			{
				return Image(path.value());
			}
			else
			{
				return Image();
			}
		}

		Texture OpenTexture(const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::ImageFilters, defaultPath, title))
			{
				return Texture(path.value());
			}
			else
			{
				return Texture();
			}
		}

		Wave OpenWave(const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::AudioFilters, defaultPath, title))
			{
				return Wave(path.value());
			}
			else
			{
				return Wave();
			}
		}

		Audio OpenAudio(const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::AudioFilters, defaultPath, title))
			{
				return Audio(path.value());
			}
			else
			{
				return Audio();
			}
		}
	}
}
