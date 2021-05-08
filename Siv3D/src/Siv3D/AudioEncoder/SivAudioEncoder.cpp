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

# include <Siv3D/AudioEncoder.hpp>
# include <Siv3D/Wave.hpp>
# include "IAudioEncoder.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	//namespace detail
	//{
	//	[[nodiscard]]
	//	constexpr StringView ToString(const AudioFormat imageFormat) noexcept
	//	{
	//		switch (imageFormat)
	//		{
	//		case AudioFormat::DDS:
	//			return U"DDS"_sv;
	//		case AudioFormat::PNG:
	//			return U"PNG"_sv;
	//		case AudioFormat::JPEG:
	//			return U"JPEG"_sv;
	//		case AudioFormat::JPEG2000:
	//			return U"JPEG2000"_sv;
	//		case AudioFormat::BMP:
	//			return U"BMP"_sv;
	//		case AudioFormat::WebP:
	//			return U"WebP"_sv;
	//		case AudioFormat::GIF:
	//			return U"GIF"_sv;
	//		case AudioFormat::TIFF:
	//			return U"TIFF"_sv;
	//		case AudioFormat::TGA:
	//			return U"TGA"_sv;
	//		case AudioFormat::PPM:
	//			return U"PPM"_sv;
	//		default:
	//			return U""_sv;
	//		}
	//	}
	//}

	//namespace AudioEncoder
	//{
	//	bool Save(const Audio& image, AudioFormat format, const FilePathView path)
	//	{
	//		if (not image)
	//		{
	//			return false;
	//		}

	//		String encoderName;

	//		if (format == AudioFormat::Unspecified)
	//		{
	//			encoderName = SIV3D_ENGINE(AudioEncoder)->getEncoderNameFromExtension(FileSystem::Extension(path));
	//		}
	//		else
	//		{
	//			encoderName = detail::ToString(format);
	//		}

	//		return Save(image, encoderName, path);
	//	}

	//	bool Save(const Audio& image, const String& encoderName, const FilePathView path)
	//	{
	//		return SIV3D_ENGINE(AudioEncoder)->save(image, encoderName, path);
	//	}

	//	bool Encode(const Audio& image, const AudioFormat format, IWriter& writer)
	//	{
	//		return Encode(image, String(detail::ToString(format)), writer);
	//	}

	//	bool Encode(const Audio& image, const String& encoderName, IWriter& writer)
	//	{
	//		return SIV3D_ENGINE(AudioEncoder)->encode(image, encoderName, writer);
	//	}

	//	Blob Encode(const Audio& image, const AudioFormat format)
	//	{
	//		return Encode(image, String(detail::ToString(format)));
	//	}

	//	Blob Encode(const Audio& image, const String& encoderName)
	//	{
	//		return SIV3D_ENGINE(AudioEncoder)->encode(image, encoderName);
	//	}

	//	bool Add(std::unique_ptr<IAudioEncoder>&& Encoder)
	//	{
	//		return SIV3D_ENGINE(AudioEncoder)->add(std::move(Encoder));
	//	}

	//	void Remove(const StringView name)
	//	{
	//		return SIV3D_ENGINE(AudioEncoder)->remove(name);
	//	}

	//	const Array<std::unique_ptr<IAudioEncoder>>& Enum()
	//	{
	//		return SIV3D_ENGINE(AudioEncoder)->enumEncoder();
	//	}
	//}
}
