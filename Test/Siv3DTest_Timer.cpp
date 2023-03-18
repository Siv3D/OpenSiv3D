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

TEST_CASE("Timer 1")
{
	SECTION("Timer{}")
	{
		Timer t;
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.pause();

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.resume();
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.start();
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.pause();

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == true);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.reset();

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.set(15s);

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() == 1.0);
		REQUIRE(t.progress0_1() == 0.0);
		REQUIRE(t.us() == (15 * 1000LL * 1000LL));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() == 15s);
		REQUIRE(15s <= t);
		REQUIRE(t <= 15s);

		t.restart();
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 1.0);
		REQUIRE(t.progress0_1() > 0.0);
		REQUIRE(InRange<int64>(t.us(), (14 * 1000LL * 1000LL), (15 * 1000LL * 1000LL)));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() < 15s);
		REQUIRE(14s < t);
		REQUIRE(t < 15s);

		t.set(15s);
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 1.0);
		REQUIRE(t.progress0_1() > 0.0);
		REQUIRE(InRange<int64>(t.us(), (14 * 1000LL * 1000LL), (15 * 1000LL * 1000LL)));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() < 15s);
		REQUIRE(14s < t);
		REQUIRE(t < 15s);

		t.start();

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 1.0);
		REQUIRE(t.progress0_1() > 0.0);
		REQUIRE(InRange<int64>(t.us(), (14 * 1000LL * 1000LL), (15 * 1000LL * 1000LL)));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() < 15s);
		REQUIRE(14s < t);
		REQUIRE(t < 15s);

		t.resume();

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 1.0);
		REQUIRE(t.progress0_1() > 0.0);
		REQUIRE(InRange<int64>(t.us(), (14 * 1000LL * 1000LL), (15 * 1000LL * 1000LL)));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() < 15s);
		REQUIRE(14s < t);
		REQUIRE(t < 15s);

		t.setRemaining(3s);
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 0.2);
		REQUIRE(t.progress0_1() > 0.8);
		REQUIRE(InRange<int64>(t.us(), (2 * 1000LL * 1000LL), (3 * 1000LL * 1000LL)));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() < 3s);
		REQUIRE(2s < t);
		REQUIRE(t < 3s);

		t.setRemaining(0.001s);
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);

		t.restart(10s);
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 1.0);
		REQUIRE(t.progress0_1() > 0.0);
		REQUIRE(InRange<int64>(t.us(), (9 * 1000LL * 1000LL), (10 * 1000LL * 1000LL)));
		REQUIRE(t.duration() == 10s);
		REQUIRE(t.remaining() < 10s);
		REQUIRE(9s < t);
		REQUIRE(t < 10s);
	}
}

TEST_CASE("Timer 2")
{
	SECTION("Timer{ 0s }")
	{
		Timer t{ 0s };
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);
	}

	SECTION("Timer{ 15s }")
	{
		Timer t{ 15s };
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() == 1.0);
		REQUIRE(t.progress0_1() == 0.0);
		REQUIRE(t.us() == (15 * 1000LL * 1000LL));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() == 15s);
		REQUIRE(15s <= t);
		REQUIRE(t <= 15s);
	}

	SECTION("Timer{ 15s, StartImmediately::No }")
	{
		Timer t{ 15s, StartImmediately::No };
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == false);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == false);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() == 1.0);
		REQUIRE(t.progress0_1() == 0.0);
		REQUIRE(t.us() == (15 * 1000LL * 1000LL));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() == 15s);
		REQUIRE(15s <= t);
		REQUIRE(t <= 15s);
	}

	SECTION("Timer{ 15s, StartImmediately::Yes }")
	{
		Timer t{ 15s, StartImmediately::Yes };
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == false);
		REQUIRE(t.progress1_0() < 1.0);
		REQUIRE(t.progress0_1() > 0.0);
		REQUIRE(t.us() < (15 * 1000LL * 1000LL));
		REQUIRE(t.duration() == 15s);
		REQUIRE(t.remaining() < 15s);
		REQUIRE(14s < t);
		REQUIRE(t < 15s);
	}

	SECTION("Timer{ 0.001s, StartImmediately::Yes }")
	{
		Timer t{ 0.001s, StartImmediately::Yes };
		System::Sleep(0.01s);

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0.001s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);
	}

	SECTION("Timer{ 0s, StartImmediately::Yes }")
	{
		Timer t{ 0s, StartImmediately::Yes };

		REQUIRE(t.isStarted() == true);
		REQUIRE(t.isPaused() == false);
		REQUIRE(t.isRunning() == true);
		REQUIRE(t.reachedZero() == true);
		REQUIRE(t.progress1_0() == 0.0);
		REQUIRE(t.progress0_1() == 1.0);
		REQUIRE(t.us() == 0);
		REQUIRE(t.duration() == 0s);
		REQUIRE(t.remaining() == 0s);
		REQUIRE(0s <= t);
		REQUIRE(t <= 0s);
	}
}
