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

# include "Siv3DTest.hpp"

TEST_CASE("VideoReader")
{
	VideoReader videoReader { U"example/video/river.mp4" };

	SECTION("Can read video file")
	{
		REQUIRE(videoReader.isOpen() == true);
		REQUIRE(videoReader.path() == U"/example/video/river.mp4");

		REQUIRE(videoReader.getSize() == Size { 1280, 720 });
		REQUIRE(videoReader.getFPS() == 29.7);
		REQUIRE(Math::Abs(videoReader.getLengthSec() - 25.091733) <= 0.1);

		REQUIRE(videoReader.getCurrentFrameIndex() == 0);
	}
	
	SECTION("Can read first frame")
	{
		Image frame;
		Image referenceFrame { U"test/video/river_frame1.png" };

		REQUIRE(videoReader.readFrame(frame) == true);
		REQUIRE(videoReader.getCurrentFrameIndex() == 1);
		REQUIRE_NOTHROW(AssertImagesAreEqual(referenceFrame, frame));
	}
}
