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

TEST_CASE("Image")
{
	SECTION("Decoder BMP")
	{
		{
			const FilePathView path = U"test/image/bmp/1x1_24.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8);
			REQUIRE(info->size == Size(1, 1));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(1, 1));
			REQUIRE(image[0][0] == Color(11, 22, 33));
		}

		{
			const FilePathView path = U"test/image/bmp/3x3_24.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(3, 3));
			REQUIRE(image[0][0] == Color(11, 22, 33));
			REQUIRE(image[0][1] == Color(11, 22, 33));
			REQUIRE(image[0][2] == Color(11, 22, 33));
			REQUIRE(image[1][0] == Color(11, 22, 33));
			REQUIRE(image[1][1] == Color(11, 22, 33));
			REQUIRE(image[1][2] == Color(11, 22, 33));
			REQUIRE(image[2][0] == Color(222, 111, 0));
			REQUIRE(image[2][1] == Color(0, 222, 111));
			REQUIRE(image[2][2] == Color(111, 0, 222));
		}

		{
			const FilePathView path = U"test/image/bmp/1x1_256.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8);
			REQUIRE(info->size == Size(1, 1));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(1, 1));
			REQUIRE(image[0][0] == Color(0, 32, 64));
		}

		{
			const FilePathView path = U"test/image/bmp/3x3_256.bmp";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::BMP);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(3, 3));
			REQUIRE(image[0][0] == Color(0, 32, 64));
			REQUIRE(image[0][1] == Color(0, 32, 64));
			REQUIRE(image[0][2] == Color(0, 32, 64));
			REQUIRE(image[1][0] == Color(0, 32, 64));
			REQUIRE(image[1][1] == Color(0, 32, 64));
			REQUIRE(image[1][2] == Color(0, 32, 64));
			REQUIRE(image[2][0] == Color(224, 96, 0));
			REQUIRE(image[2][1] == Color(0, 224, 128));
			REQUIRE(image[2][2] == Color(96, 0, 192));
		}
	}

	SECTION("Decoder PNG")
	{
		{
			const FilePathView path = U"test/image/png/1x1.png";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::PNG);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8A8);
			REQUIRE(info->size == Size(1, 1));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(1, 1));
			REQUIRE(image[0][0] == Color(11, 22, 33));
		}

		{
			const FilePathView path = U"test/image/png/3x3.png";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::PNG);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8A8);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(3, 3));
			REQUIRE(image[0][0] == Color(11, 22, 33));
			REQUIRE(image[0][1] == Color(11, 22, 33));
			REQUIRE(image[0][2] == Color(11, 22, 33));
			REQUIRE(image[1][0] == Color(11, 22, 33));
			REQUIRE(image[1][1] == Color(11, 22, 33));
			REQUIRE(image[1][2] == Color(11, 22, 33));
			REQUIRE(image[2][0] == Color(222, 111, 0));
			REQUIRE(image[2][1] == Color(0, 222, 111));
			REQUIRE(image[2][2] == Color(111, 0, 222));
		}

		{
			const FilePathView path = U"test/image/png/1x1_8.png";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::PNG);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8A8);
			REQUIRE(info->size == Size(1, 1));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(1, 1));
			REQUIRE(image[0][0] == Color(11, 22, 33));
		}

		{
			const FilePathView path = U"test/image/png/3x3_8.png";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::PNG);
			REQUIRE(info->pixelFormat == ImagePixelFormat::R8G8B8A8);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			const Image image(path);
			REQUIRE(image.size() == Size(3, 3));
			REQUIRE(image[0][0] == Color(11, 22, 33));
			REQUIRE(image[0][1] == Color(11, 22, 33));
			REQUIRE(image[0][2] == Color(11, 22, 33));
			REQUIRE(image[1][0] == Color(11, 22, 33));
			REQUIRE(image[1][1] == Color(11, 22, 33));
			REQUIRE(image[1][2] == Color(11, 22, 33));
			REQUIRE(image[2][0] == Color(222, 111, 0));
			REQUIRE(image[2][1] == Color(0, 222, 111));
			REQUIRE(image[2][2] == Color(111, 0, 222));
		}

		{
			const FilePathView path = U"test/image/png/3x3_gray16.png";
			const auto info = ImageDecoder::GetImageInfo(path);
			REQUIRE(info.has_value());
			REQUIRE(info->imageFormat == ImageFormat::PNG);
			REQUIRE(info->pixelFormat == ImagePixelFormat::Gray16);
			REQUIRE(info->size == Size(3, 3));
			REQUIRE(info->isAnimated == false);

			{
				const Image image(path);
				REQUIRE(image.size() == Size(3, 3));
				REQUIRE(image[0][0] == Color(65));
				REQUIRE(image[0][1] == Color(88));
				REQUIRE(image[0][2] == Color(121));
				REQUIRE(image[1][0] == Color(88));
				REQUIRE(image[1][1] == Color(121));
				REQUIRE(image[1][2] == Color(160));
				REQUIRE(image[2][0] == Color(121));
				REQUIRE(image[2][1] == Color(160));
				REQUIRE(image[2][2] == Color(199));
			}

			{
				const Grid<uint16> image = ImageDecoder::DecodeGray16(path);
				REQUIRE(image.size() == Size(3, 3));
				REQUIRE(image[0][0] == 16712);
				REQUIRE(image[0][1] == 22592);
				REQUIRE(image[0][2] == 31172);
				REQUIRE(image[1][0] == 22592);
				REQUIRE(image[1][1] == 31172);
				REQUIRE(image[1][2] == 41123);
				REQUIRE(image[2][0] == 31174);
				REQUIRE(image[2][1] == 41123);
				REQUIRE(image[2][2] == 51073);
			}
		}
	}
}
