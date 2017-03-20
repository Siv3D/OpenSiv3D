
# include <Siv3D.hpp>

void Main()
{
	/*
	const FilePath title = L"Night";
	const FilePath dir = L"nc";

	const FilePath originalPath(dir + L"/" + L"original.png");
	const Image original(originalPath);

	Log << L"## {}\n"_fmt(title);
	Log << L"|original|";
	Log << L"|:---:|";
	Log << L"|{}bytes|"_fmt(ThousandsSeparate(FileSystem::FileSize(originalPath)));
	Log << L"|![](images/{}/original.png)|"_fmt(dir);

	Log << L"### libjpeg-turbo 1.5.1\n";
	Log << L"|quality     |size  |butteraugli score|image      |";
	Log << L"|:----------:|:-----:|:------:|:-------------------:|";

	for (int32 quality = 80; quality <= 100; ++quality)
	{
		const FilePath path = dir + L"/" + L"{}.jpg"_fmt(quality);
		original.saveJPEG(path, quality);
		Log << L"|" << quality << L"|" << ThousandsSeparate(FileSystem::FileSize(path)) << L"|" << Imaging::PerceivedDifferences(original, Image(path)) << L"|" << L"[■](images/{}/{}.jpg)"_fmt(dir, quality) << L"|";
	}

	Log << L"### Guetzli\n";
	Log << L"|target     |size  |butteraugli score|image      |";
	Log << L"|:----------:|:-----:|:------:|:-------------------:|";

	for (int32 t = 20; t >= 0; --t)
	{
		const double target = t / 10.0;
		const FilePath path = dir + L"/" + L"b{}.jpg"_fmt(ToFixed(target, 2));
		original.savePerceptualJPEG(path, target);
		Log << L"|" << ToFixed(target, 2) << L"|" << ThousandsSeparate(FileSystem::FileSize(path)) << L"|" << Imaging::PerceivedDifferences(original, Image(path)) << L"|" << L"[■](images/{}/b{}.jpg)"_fmt(dir, ToFixed(target, 2)) << L"|";
	}
	*/

	for (const auto& output : Graphics::EnumOutputs())
	{
		Log << L"---" << output.name;
		Log << output.desktopRect;
		Log << output.displayModes.map([](const DisplayMode& mode)
		{
			return Format(mode.size, L"@", mode.refreshRateHz, L"Hz");
		});
	}
	
	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}
