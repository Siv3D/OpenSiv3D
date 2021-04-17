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
			FileFilter::MP3(),
			FileFilter::OggVorbis(),
			FileFilter::Opus(),
		};
	}

	namespace Dialog
	{
		Image OpenImage(const FilePathView defaultPath, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultPath, title))
			{
				return Image{ path.value() };
			}
			else
			{
				return{};
			}
		}

		Texture OpenTexture(const FilePathView defaultPath, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultPath, title))
			{
				return Texture{ path.value() };
			}
			else
			{
				return{};
			}
		}

		Texture OpenTexture(const TextureDesc desc, const FilePathView defaultPath, const StringView title)
		{
			if (const auto path = OpenFile(detail::OpenImageFilters, defaultPath, title))
			{
				return Texture{ path.value(), desc };
			}
			else
			{
				return{};
			}
		}

		//Wave OpenWave(const FilePathView defaultPath, const StringView title)
		//{
		//	if (const auto path = OpenFile(detail::OpenAudioFilters, defaultPath, title))
		//	{
		//		return Wave{ path.value() };
		//	}
		//	else
		//	{
		//		return{};
		//	}
		//}

		//Audio OpenAudio(const FilePathView defaultPath, const StringView title)
		//{
		//	if (const auto path = OpenFile(detail::OpenAudioFilters, defaultPath, title))
		//	{
		//		return Audio{ path.value() };
		//	}
		//	else
		//	{
		//		return{};
		//	}
		//}

		//Audio OpenAudio(const Arg::loop_<bool> loop, const FilePathView defaultPath, const StringView title)
		//{
		//	if (const auto path = OpenFile(detail::OpenAudioFilters, defaultPath, title))
		//	{
		//		return Audio{ path.value(), loop };
		//	}
		//	else
		//	{
		//		return{};
		//	}
		//}

		Optional<FilePath> SaveImage(const FilePathView defaultPath, const StringView title)
		{
			return SaveFile(detail::SaveImageFilters, defaultPath, title);
		}

		//Optional<FilePath> SaveWave(const FilePathView defaultPath, const StringView title)
		//{
		//	return SaveFile(detail::SaveWaveFilters, defaultPath, title);
		//}
	}
}
