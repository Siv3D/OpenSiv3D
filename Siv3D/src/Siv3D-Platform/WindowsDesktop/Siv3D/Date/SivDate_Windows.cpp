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

# include <Siv3D/Common.hpp>
# include <Siv3D/Date.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	Date Date::Today() noexcept
	{
		SYSTEMTIME sysTime;
		::GetLocalTime(&sysTime);
		return Date(sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	}
}
