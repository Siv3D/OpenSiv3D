//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Exif.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <ThirdParty/easyexif/exif.h>

namespace s3d
{
	Optional<Exif> Exif::Read(const FilePathView path)
	{
		return Read(BinaryReader{ path });
	}

	Optional<Exif> Exif::Read(const IReader& reader)
	{
		Array<uint8> data(static_cast<size_t>(reader.size()));

		reader.lookahead(data.data(), data.size());

		easyexif::EXIFInfo info;

		if (info.parseFrom(data.data(), static_cast<uint32>(data.size())) != PARSE_EXIF_SUCCESS)
		{
			return none;
		}

		return Exif{
			.imageDescription	= Unicode::Widen(info.ImageDescription),
			.make				= Unicode::Widen(info.Make),
			.model				= Unicode::Widen(info.Model),
			.orientation		= info.Orientation,
			.bitsPerSample		= info.BitsPerSample,
			.software			= Unicode::Widen(info.Software),
			.dateTime			= Unicode::Widen(info.DateTime),
			.dateTimeOriginal	= Unicode::Widen(info.DateTimeOriginal),
			.dateTimeDigitized	= Unicode::Widen(info.DateTimeDigitized),
			.subSecTimeOriginal	= Unicode::Widen(info.SubSecTimeOriginal),
			.copyright			= Unicode::Widen(info.Copyright),
			.exposureTime		= info.ExposureTime,
			.FNumber			= info.FNumber,
			.exposureProgram	= info.ExposureProgram,
			.ISOSpeedRatings	= info.ISOSpeedRatings,
			.shutterSpeedValue	= info.ShutterSpeedValue,
			.exposureBiasValue	= info.ExposureBiasValue,
			.subjectDistance	= info.SubjectDistance,
			.focalLength		= info.FocalLength,
			.focalLengthIn35mm	= info.FocalLengthIn35mm,
			.flash				= static_cast<bool>(info.Flash),
			.flashReturnedLight	= info.FlashReturnedLight,
			.flashMode			= info.FlashMode,
			.meteringMode		= info.MeteringMode,
			.imageWidth			= info.ImageWidth,
			.imageHeight		= info.ImageHeight,

			.geoLocation =
			{
				.latitude		= info.GeoLocation.Latitude,
				.longitude		= info.GeoLocation.Longitude,
				.altitude		= info.GeoLocation.Altitude,
				.altitudeRef	= info.GeoLocation.AltitudeRef,
				.DOP			= info.GeoLocation.DOP,

				.latComponents =
				{
					.degrees	= info.GeoLocation.LatComponents.degrees,
					.minutes	= info.GeoLocation.LatComponents.minutes,
					.seconds	= info.GeoLocation.LatComponents.seconds,
					.direction	= static_cast<char32>(info.GeoLocation.LatComponents.direction),
				},

				.lonComponents =
				{
					.degrees	= info.GeoLocation.LonComponents.degrees,
					.minutes	= info.GeoLocation.LonComponents.minutes,
					.seconds	= info.GeoLocation.LonComponents.seconds,
					.direction	= static_cast<char32>(info.GeoLocation.LonComponents.direction),
				},
			},

			.lensInfo =
			{
				.FStopMin					= info.LensInfo.FStopMin,
				.FStopMax					= info.LensInfo.FStopMax,
				.focalLengthMin				= info.LensInfo.FocalLengthMin,
				.focalLengthMax				= info.LensInfo.FocalLengthMax,
				.focalPlaneXResolution		= info.LensInfo.FocalPlaneXResolution,
				.focalPlaneYResolution		= info.LensInfo.FocalPlaneYResolution,
				.focalPlaneResolutionUnit	= info.LensInfo.FocalPlaneResolutionUnit,
				.make						= Unicode::Widen(info.LensInfo.Make),
				.model						= Unicode::Widen(info.LensInfo.Model),
			}
		};
	}
}
