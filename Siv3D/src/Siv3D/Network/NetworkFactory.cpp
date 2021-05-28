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

namespace s3d
{
	ISiv3DNetwork* ISiv3DNetwork::Create()
	{
		return new CNetwork;
	}
}
