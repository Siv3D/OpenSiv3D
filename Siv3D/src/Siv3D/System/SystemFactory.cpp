//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/System/CSystem.hpp>

namespace s3d
{
	ISiv3DSystem* ISiv3DSystem::Create()
	{
		return new CSystem;
	}
}
