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

TEST_CASE("Monitor")
{
	auto monitors = System::EnumerateMonitors();

	REQUIRE(monitors.size() == 1);

	const auto& monitor = monitors[0];

	REQUIRE(monitor.id == U"1");
	REQUIRE(monitor.name == U"HTML5 WebGL Canvas");
	REQUIRE(monitor.isPrimary == true);

	REQUIRE(monitor.displayRect.pos == Point{0, 0});
	REQUIRE(monitor.workArea.pos == Point{0, 0});
	REQUIRE(monitor.refreshRate == none);
	REQUIRE(monitor.sizeMillimeter == none);
	REQUIRE(monitor.scaling == 1.0);
}
