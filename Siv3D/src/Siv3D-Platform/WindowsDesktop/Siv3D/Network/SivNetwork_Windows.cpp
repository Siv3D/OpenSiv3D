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
# include <Siv3D/Network.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <wininet.h>

namespace s3d
{
	namespace Network
	{
		bool IsConnected()
		{
			DWORD flags = 0;
			return ::InternetGetConnectedState(&flags, 0);
		}
	}
}
