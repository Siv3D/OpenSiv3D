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

# include <Siv3DTest.hpp>
# include "MockSiv3DDialog.hpp"

TEST_CASE("Dialog")
{
	SECTION("Save")
	{
		REQUIRE(Dialog::SaveFile() == none);
	}

	SECTION("Open")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"/tmp/file.txt");

		auto opened = Dialog::OpenFile();

		REQUIRE(opened.has_value());
		REQUIRE(*opened == U"/tmp/file.txt");
	}

	SECTION("Open Empty")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"");

		REQUIRE(Dialog::OpenFile() == none);
	}

	SECTION("Open Mulpiple")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"/tmp/file.txt");

		auto opened = Dialog::OpenFiles();

		REQUIRE(opened.size() == 1);
		REQUIRE(opened[0] == U"/tmp/file.txt");
	}

	SECTION("Open Multiple Empty")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"");

		auto opened = Dialog::OpenFiles();

		REQUIRE(opened.size() == 0);
	}

	SECTION("Open Image")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"/example/bay.jpg");

		auto opened = Dialog::OpenImage();

		REQUIRE(static_cast<bool>(opened) == true);
	}

	SECTION("Open Texture")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"/example/bay.jpg");

		auto opened = Dialog::OpenTexture();

		REQUIRE(static_cast<bool>(opened) == true);
	}

	SECTION("Open Wave")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"/example/shot.mp3");

		auto opened = Dialog::OpenWave();

		REQUIRE(static_cast<bool>(opened) == true);
	}

	SECTION("Open Audio")
	{
		SetReturnValue_siv3dOpenDialogAsync(U"/example/shot.mp3");

		auto opened = Dialog::OpenAudio();

		REQUIRE(static_cast<bool>(opened) == true);
	}
}
