//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <ThirdParty/soloud/include/soloud.h>

namespace s3d
{
	struct AudioBus
	{
		SoLoud::Bus bus;

		SoLoud::handle handle = 0;

		std::array<std::unique_ptr<SoLoud::Filter>, 8> filters;
	};
}
