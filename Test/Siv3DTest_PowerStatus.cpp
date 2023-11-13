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

TEST_CASE("PowerStatus")
{
# if SIV3D_PLATFORM(WEB)
    SECTION("Web (no support)")
    {
        const auto status = System::GetPowerStatus();

        REQUIRE(status.ac == ACLineStatus::Unknown);
        REQUIRE(status.battery == BatteryStatus::Unknown);
        REQUIRE(status.batteryLifePercent == none);
        REQUIRE(status.batteryLifeTimeSec == none);
        REQUIRE(status.batterySaver == false);
        REQUIRE(status.batteryTimeToFullChargeSec == none);
        REQUIRE(status.charging == false);
    }
# endif
}
