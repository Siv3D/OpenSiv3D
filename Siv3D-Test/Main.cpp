# include <Siv3D.hpp>

void Main()
{
	Window::Resize(640, 720);

	if (const auto exif = ExifInfo::Read(U"test/photo.jpg"))
	{
		Print << U"Camera make: " << exif->make;
		Print << U"Camera model: " << exif->model;
		Print << U"Software: " << exif->software;
		Print << U"Bits per sample: " << exif->bitsPerSample;
		Print << U"Image width: " << exif->imageWidth;
		Print << U"Image height: " << exif->imageHeight;
		Print << U"Image description: " << exif->imageDescription;
		Print << U"Image orientation: " << exif->orientation;
		Print << U"Image copyright: " << exif->copyright;
		Print << U"Image date/time: " << exif->dateTime;
		Print << U"Original date/time: " << exif->dateTimeOriginal;
		Print << U"Digitize date/time: " << exif->dateTimeDigitized;

		Print << U"Exposure time: 1/" << Math::Round(1.0 / exif->exposureTime) << U" s";
		Print << U"F-stop: f/{:.1f}"_fmt(exif->FNumber);
		Print << U"Exposure program: " << exif->exposureProgram;
		Print << U"ISO speed: " << exif->ISOSpeedRatings;
		Print << U"Subject distance: " << exif->subjectDistance << U" m";
		Print << U"Exposure bias: " << exif->exposureBiasValue << U" EV";

		Print << U"Flash: " << exif->flash;
		Print << U"Flash returned light: " << exif->flashReturnedLight;
		Print << U"Flash mode: " << exif->flashMode;
		Print << U"Metering mode: " << exif->meteringMode;
		Print << U"Lens focal length: " << exif->focalLength << U" mm";
		Print << U"35mm focal length: " << exif->focalLengthIn35mm << U" mm";

		Print << U"GPS Latitude: {} deg ({} deg, {} min, {} sec {})"_fmt(
			exif->geoLocation.latitude,
			exif->geoLocation.latComponents.degrees,
			exif->geoLocation.latComponents.minutes,
			exif->geoLocation.latComponents.seconds,
			exif->geoLocation.latComponents.direction
			);
		Print << U"GPS Longitude: {} deg ({} deg, {} min, {} sec {})"_fmt(
			exif->geoLocation.longitude,
			exif->geoLocation.lonComponents.degrees,
			exif->geoLocation.lonComponents.minutes,
			exif->geoLocation.lonComponents.seconds,
			exif->geoLocation.lonComponents.direction
		);
		Print << U"GPS Altitude: " << exif->geoLocation.altitude << U" m";
		Print << U"GPS Precision (DOP): " << exif->geoLocation.DOP;

		//Print << U"Lens min focal length: " << exif->lensInfo.focalLengthMin << U" mm";
		//Print << U"Lens max focal length: " << exif->lensInfo.focalLengthMax << U" mm";
		//Print << U"Lens f-stop min: f/{:.1f}"_fmt(exif->lensInfo.FStopMin);
		//Print << U"Lens f-stop max: f/{:.1f}"_fmt(exif->lensInfo.FStopMax);
		//Print << U"Lens make: " << exif->lensInfo.make;
		//Print << U"Lens model: " << exif->lensInfo.model;
		//Print << U"Focal plane XRes: " << exif->lensInfo.focalPlaneXResolution;
		//Print << U"Focal plane YRes: " << exif->lensInfo.focalPlaneYResolution;
	}

	while (System::Update())
	{

	}
}
