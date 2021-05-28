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

# include "CNetwork.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CNetwork::CNetwork() {}

	CNetwork::~CNetwork()
	{
		LOG_SCOPED_TRACE(U"CNetwork::~CNetwork()");
	}
}
