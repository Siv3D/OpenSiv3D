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

# include <Siv3D/Dialog.hpp>

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
			FileFilter::SVG(),
			FileFilter::WebP(),
			FileFilter::PPM(),
		};

		static const Array<FileFilter> OpenAudioFilters =
		{
			FileFilter::AllAudioFiles(),
			FileFilter::WAVE(),
			FileFilter::MP3(),
			FileFilter::AAC(),
			FileFilter::OggVorbis(),
			FileFilter::Opus(),
			FileFilter::MIDI(),
		# if SIV3D_PLATFORM(WINDOWS)
			FileFilter::WMA(),
			FileFilter::FLAC(),
		# elif SIV3D_PLATFORM(MACOS)
			FileFilter::AIFF(),
			FileFilter::FLAC(),
		# elif SIV3D_PLATFORM(LINUX)

		# elif SIV3D_PLATFORM(WEB)

		# endif
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
			//FileFilter::MP3(),
			FileFilter::OggVorbis(),
			//FileFilter::Opus(),
		};
	}

	namespace Dialog
	{
		Image OpenImage(const FilePathView defaultDirectory, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultDirectory, title))
			{
				return Image{ *path };
			}
			else
			{
				return{};
			}
		}

		Texture OpenTexture(const FilePathView defaultDirectory, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultDirectory, title))
			{
				return Texture{ *path };
			}
			else
			{
				return{};
			}
		}

		Texture OpenTexture(const TextureDesc desc, const FilePathView defaultDirectory, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultDirectory, title))
			{
				return Texture{ *path, desc };
			}
			else
			{
				return{};
			}
		}

		Wave OpenWave(const FilePathView defaultDirectory, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenAudioFilters, defaultDirectory, title))
			{
				return Wave{ *path };
			}
			else
			{
				return{};
			}
		}

		Audio OpenAudio(const FilePathView defaultDirectory, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenAudioFilters, defaultDirectory, title))
			{
				return Audio{ *path };
			}
			else
			{
				return{};
			}
		}

		Audio OpenAudio(Audio::FileStreaming, const FilePathView defaultDirectory, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenAudioFilters, defaultDirectory, title))
			{
				return Audio{ Audio::Stream, *path };
			}
			else
			{
				return{};
			}
		}

		Optional<FilePath> SaveImage(const FilePathView defaultDirectory, const StringView title)
		{
			return SaveFile(detail::SaveImageFilters, defaultDirectory, title);
		}

		Optional<FilePath> SaveWave(const FilePathView defaultDirectory, const StringView title)
		{
			return SaveFile(detail::SaveWaveFilters, defaultDirectory, title);
		}
	}
}
