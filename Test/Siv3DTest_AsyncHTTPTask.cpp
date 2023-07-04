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

# if SIV3D_PLATFORM(WEB)

__attribute__((import_name("siv3dRequestAnimationFrame")))
extern void siv3dRequestAnimationFrame();

# endif

TEST_CASE("AsyncHTTPTask (#38)")
{
	const URL url = U"https://raw.githubusercontent.com/Siv3D/siv3d.docs.images/master/logo/logo.png";
	const FilePath saveFilePath = U"test/image/png/logo2.png";

	// ファイルの非同期ダウンロードを開始
	AsyncHTTPTask task = SimpleHTTP::SaveAsync(url, saveFilePath);

	while (true)
	{
	# if SIV3D_PLATFORM(WEB)
		// [BUGBUG] calling System::Update() with Headless mode causes unreachable
		siv3dRequestAnimationFrame();
	# else
		if (not System::Update())
		{
			break;
		}
	# endif

		if (task.isReady())
		{
			REQUIRE(task.getResponse().isOK() == true);

			Image image{ saveFilePath };

			REQUIRE(image.width() == 523);
			REQUIRE(image.height() == 523);

			break;
		}
	}

	REQUIRE(task.isReady() == false);
}
