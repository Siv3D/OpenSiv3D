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
# include <Siv3D/Wave.hpp>
# include <Siv3D/Audio.hpp>

namespace s3d
{
	namespace detail
	{
		static const Array<FileFilter> OpenImageFilters =
		{
			FileFilter::AllImageFiles(),
			FileFilter::PNG(),
			FileFilter::JPEG(),
			FileFilter::BMP(),
			FileFilter::GIF(),
			FileFilter::TGA(),
			FileFilter::PPM(),
		};

		static const Array<FileFilter> OpenAudioFilters =
		{
			FileFilter::AllAudioFiles(),
			FileFilter::WAVE(),
			FileFilter::MP3(),
			FileFilter::AAC()
		};

		static const Array<FileFilter> SaveImageFilters =
		{
			FileFilter::PNG(),
			FileFilter::JPEG(),
			FileFilter::BMP(),
			FileFilter::GIF(),
			FileFilter::TGA(),
			FileFilter::WebP(),
			FileFilter::PPM(),
		};

		static const Array<FileFilter> SaveWaveFilters =
		{
			FileFilter::WAVE(),
		};
	}

	namespace Dialog
	{
		Image OpenImage(const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultPath, title))
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
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultPath, title))
			{
				return Texture(path.value());
			}
			else
			{
				return Texture();
			}
		}

		Texture OpenTexture(const TextureDesc desc, const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultPath, title))
			{
				return Texture(path.value(), desc);
			}
			else
			{
				return Texture();
			}
		}

		Wave OpenWave(const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::OpenAudioFilters, defaultPath, title))
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
			if (const auto path = OpenFile(detail::OpenAudioFilters, defaultPath, title))
			{
				return Audio(path.value());
			}
			else
			{
				return Audio();
			}
		}

		Audio OpenAudio(const Arg::loop_<bool> loop, const FilePath& defaultPath, const String& title)
		{
			if (const auto path = OpenFile(detail::OpenAudioFilters, defaultPath, title))
			{
				return Audio(path.value(), loop);
			}
			else
			{
				return Audio();
			}
		}

		Optional<FilePath> SaveImage(const FilePath& defaultPath, const String& title)
		{
			return SaveFile(detail::SaveImageFilters, defaultPath, title);
		}

		Optional<FilePath> SaveWave(const FilePath& defaultPath, const String& title)
		{
			return SaveFile(detail::SaveWaveFilters, defaultPath, title);
		}
	}
}
