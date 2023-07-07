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

TEST_CASE("AsyncHTTPTask (#38)")
{
	const URL url = U"https://raw.githubusercontent.com/Siv3D/siv3d.docs.images/master/logo/logo.png";
	const FilePath saveFilePath = U"test/image/png/logo2.png";

	// ファイルの非同期ダウンロードを開始
	AsyncHTTPTask task = SimpleHTTP::SaveAsync(url, saveFilePath);

	while (System::Update())
	{
		if (task.isReady())
		{
			REQUIRE(task.getResponse().isOK() == true);

			Image image{ saveFilePath };

			REQUIRE(image.size() == Size(523, 523));

			break;
		}
	}

	REQUIRE(task.isReady() == false);
}
