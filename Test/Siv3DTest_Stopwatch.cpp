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

TEST_CASE("Stopwatch 1")
{
	SECTION("Stopwatch{}")
	{
		Stopwatch s;
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == false);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == 0);
		REQUIRE(s.elapsed() == 0s);
		REQUIRE(0s <= s);
		REQUIRE(s <= 0s);

		s.pause();

		REQUIRE(s.isStarted() == false);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == 0);
		REQUIRE(s.elapsed() == 0s);
		REQUIRE(0s <= s);
		REQUIRE(s <= 0s);

		s.resume();
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == false);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == 0);
		REQUIRE(s.elapsed() == 0s);
		REQUIRE(0s <= s);
		REQUIRE(s <= 0s);

		s.start();
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > 0);
		REQUIRE(s.elapsed() > 0s);
		REQUIRE(0s < s);
		REQUIRE(s > 0s);

		s.pause();

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == true);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() > 0);
		REQUIRE(s.elapsed() > 0s);
		REQUIRE(0s < s);
		REQUIRE(s > 0s);

		s.reset();

		REQUIRE(s.isStarted() == false);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == 0);
		REQUIRE(s.elapsed() == 0s);
		REQUIRE(0s <= s);
		REQUIRE(s <= 0s);

		s.set(15s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == true);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() == 15s);
		REQUIRE(15s <= s);
		REQUIRE(s <= 15s);

		s.restart();
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > 0);
		REQUIRE(s.elapsed() > 0s);
		REQUIRE(0s < s);
		REQUIRE(s > 0s);

		s.set(15s);
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() > 15s);
		REQUIRE(15s < s);
		REQUIRE(s < 16s);

		s.start();

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() > 15s);
		REQUIRE(15s < s);
		REQUIRE(s < 16s);

		s.resume();

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() > 15s);
		REQUIRE(15s < s);
		REQUIRE(s < 16s);
	}
}

TEST_CASE("Stopwatch 2")
{
	SECTION("Stopwatch{ StartImmediately::No }")
	{
		Stopwatch s{ StartImmediately::No };
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == false);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == 0);
		REQUIRE(s.elapsed() == 0s);
		REQUIRE(0s <= s);
		REQUIRE(s <= 0s);
	}

	SECTION("Stopwatch{ StartImmediately::Yes }")
	{
		Stopwatch s{ StartImmediately::Yes };
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > 0);
		REQUIRE(s.elapsed() > 0s);
		REQUIRE(0s < s);
		REQUIRE(s > 0s);
	}

	SECTION("Stopwatch{ 15s }")
	{
		Stopwatch s{ 15s };
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == true);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() == 15s);
		REQUIRE(15s <= s);
		REQUIRE(s <= 15s);
	}

	SECTION("Stopwatch{ 0s, StartImmediately::No }")
	{
		Stopwatch s{ 0s, StartImmediately::No };
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == true);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == 0);
		REQUIRE(s.elapsed() == 0s);
		REQUIRE(0s <= s);
		REQUIRE(s <= 0s);
	}

	SECTION("Stopwatch{ 15s, StartImmediately::No }")
	{
		Stopwatch s{ 15s, StartImmediately::No };
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == true);
		REQUIRE(s.isRunning() == false);
		REQUIRE(s.us() == (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() == 15s);
		REQUIRE(15s <= s);
		REQUIRE(s <= 15s);
	}

	SECTION("Stopwatch{ 15s, StartImmediately::Yes }")
	{
		Stopwatch s{ 15s, StartImmediately::Yes };
		System::Sleep(0.01s);

		REQUIRE(s.isStarted() == true);
		REQUIRE(s.isPaused() == false);
		REQUIRE(s.isRunning() == true);
		REQUIRE(s.us() > (15 * 1000LL * 1000LL));
		REQUIRE(s.elapsed() > 15s);
		REQUIRE(15s < s);
		REQUIRE(s < 16s);
	}
}
