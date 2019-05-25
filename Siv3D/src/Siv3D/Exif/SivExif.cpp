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

# include <easyexif/exif.h>
# include <Siv3D/Exif.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	Optional<Exif> Exif::Read(const FilePath& path)
	{
		return Read(BinaryReader(path));
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

		Exif result;
		result.imageDescription = Unicode::Widen(info.ImageDescription);
		result.make = Unicode::Widen(info.Make);
		result.model = Unicode::Widen(info.Model);
		result.orientation = info.Orientation;
		result.bitsPerSample = info.BitsPerSample;
		result.software = Unicode::Widen(info.Software);
		result.dateTime = Unicode::Widen(info.DateTime);
		result.dateTimeOriginal = Unicode::Widen(info.DateTimeOriginal);
		result.dateTimeDigitized = Unicode::Widen(info.DateTimeDigitized);
		result.subSecTimeOriginal = Unicode::Widen(info.SubSecTimeOriginal);
		result.copyright = Unicode::Widen(info.Copyright);
		result.exposureTime = info.ExposureTime;
		result.FNumber = info.FNumber;
		result.exposureProgram = info.ExposureProgram;
		result.ISOSpeedRatings = info.ISOSpeedRatings;
		result.shutterSpeedValue = info.ShutterSpeedValue;
		result.exposureBiasValue = info.ExposureBiasValue;
		result.subjectDistance = info.SubjectDistance;
		result.focalLength = info.FocalLength;
		result.focalLengthIn35mm = info.FocalLengthIn35mm;
		result.flash = info.Flash;
		result.flashReturnedLight = info.FlashReturnedLight;
		result.flashMode = info.FlashMode;
		result.meteringMode = info.MeteringMode;
		result.imageWidth = info.ImageWidth;
		result.imageHeight = info.ImageHeight;

		result.geoLocation.latitude = info.GeoLocation.Latitude;
		result.geoLocation.longitude = info.GeoLocation.Longitude;
		result.geoLocation.altitude = info.GeoLocation.Altitude;
		result.geoLocation.altitudeRef = info.GeoLocation.AltitudeRef;
		result.geoLocation.DOP = info.GeoLocation.DOP;

		result.geoLocation.latComponents.degrees = info.GeoLocation.LatComponents.degrees;
		result.geoLocation.latComponents.minutes = info.GeoLocation.LatComponents.minutes;
		result.geoLocation.latComponents.seconds = info.GeoLocation.LatComponents.seconds;
		result.geoLocation.latComponents.direction = info.GeoLocation.LatComponents.direction;

		result.geoLocation.lonComponents.degrees = info.GeoLocation.LonComponents.degrees;
		result.geoLocation.lonComponents.minutes = info.GeoLocation.LonComponents.minutes;
		result.geoLocation.lonComponents.seconds = info.GeoLocation.LonComponents.seconds;
		result.geoLocation.lonComponents.direction = info.GeoLocation.LonComponents.direction;

		result.lensInfo.FStopMin = info.LensInfo.FStopMin;
		result.lensInfo.FStopMax = info.LensInfo.FStopMax;
		result.lensInfo.focalLengthMin = info.LensInfo.FocalLengthMin;
		result.lensInfo.focalLengthMax = info.LensInfo.FocalLengthMax;
		result.lensInfo.focalPlaneXResolution = info.LensInfo.FocalPlaneXResolution;
		result.lensInfo.focalPlaneYResolution = info.LensInfo.FocalPlaneYResolution;
		result.lensInfo.focalPlaneResolutionUnit = info.LensInfo.FocalPlaneResolutionUnit;
		result.lensInfo.make = Unicode::Widen(info.LensInfo.Make);
		result.lensInfo.model = Unicode::Widen(info.LensInfo.Model);

		return result;
	}
}
