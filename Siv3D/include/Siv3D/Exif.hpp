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
# include "Common.hpp"
# include "Optional.hpp"
# include "String.hpp"
# include "IReader.hpp"

namespace s3d
{
	//
	// https://github.com/mayanklahiri/easyexif/blob/master/exif.h
	//
	struct Exif
	{
		[[nodiscard]]
		static Optional<Exif> Read(FilePathView path);

		[[nodiscard]]
		static Optional<Exif> Read(const IReader& reader);

		String imageDescription;	// Image description
		String make;				// Camera manufacturer's name
		String model;				// Camera model
		uint16 orientation;			// Image orientation, start of data corresponds to
									// 0: unspecified in EXIF data
									// 1: upper left of image
									// 3: lower right of image
									// 6: upper right of image
									// 8: lower left of image
									// 9: undefined
		uint16 bitsPerSample;		// Number of bits per component
		String software;			// Software used
		String dateTime;			// File change date and time
		String dateTimeOriginal;	// Original file date and time (may not exist)
		String dateTimeDigitized;	// Digitization date and time (may not exist)
		String subSecTimeOriginal;	// Sub-second time that original picture was taken
		String copyright;			// File copyright information
		double exposureTime;		// Exposure time in seconds
		double FNumber;				// F/stop
		uint16 exposureProgram;		// Exposure program
									// 0: Not defined
									// 1: Manual
									// 2: Normal program
									// 3: Aperture priority
									// 4: Shutter priority
									// 5: Creative program
									// 6: Action program
									// 7: Portrait mode
									// 8: Landscape mode
		uint16 ISOSpeedRatings;		// ISO speed
		double shutterSpeedValue;	// Shutter speed (reciprocal of exposure time)
		double exposureBiasValue;	// Exposure bias value in EV
		double subjectDistance;		// Distance to focus point in meters
		double focalLength;			// Focal length of lens in millimeters
		uint16 focalLengthIn35mm;	// Focal length in 35mm film
		bool flash;					// 0 = no flash, 1 = flash used
		uint16 flashReturnedLight;	// Flash returned light status
									// 0: No strobe return detection function
									// 1: Reserved
									// 2: Strobe return light not detected
									// 3: Strobe return light detected
		uint16 flashMode;			// Flash mode
									// 0: Unknown
									// 1: Compulsory flash firing
									// 2: Compulsory flash suppression
									// 3: Automatic mode
		uint16 meteringMode;		// Metering mode
									// 1: average
									// 2: center weighted average
									// 3: spot
									// 4: multi-spot
									// 5: multi-segment
		uint32 imageWidth;			// Image width reported in EXIF data
		uint32 imageHeight;			// Image height reported in EXIF data
		
		struct Geolocation_t		// GPS information embedded in file
		{
			double latitude;		// Image latitude expressed as decimal
			double longitude;		// Image longitude expressed as decimal
			double altitude;		// Altitude in meters, relative to sea level
			int32 altitudeRef;		// 0 = above sea level, -1 = below sea level
			double DOP;				// GPS degree of precision (DOP)
			
			struct Coord_t
			{
				double degrees;
				double minutes;
				double seconds;
				char32 direction;
			} latComponents, lonComponents;   // Latitude, Longitude expressed in deg/min/sec
		} geoLocation;

		struct LensInfo_t	// Lens information
		{
			double FStopMin;					// Min aperture (f-stop)
			double FStopMax;					// Max aperture (f-stop)
			double focalLengthMin;				// Min focal length (mm)
			double focalLengthMax;				// Max focal length (mm)
			double focalPlaneXResolution;		// Focal plane X-resolution
			double focalPlaneYResolution;		// Focal plane Y-resolution
			uint16 focalPlaneResolutionUnit;	// Focal plane resolution unit
												// 1: No absolute unit of measurement.
												// 2: Inch.
												// 3: Centimeter.
												// 4: Millimeter.
												// 5: Micrometer.
			String make;						// Lens manufacturer
			String model;						// Lens model
		} lensInfo;
	};
}
