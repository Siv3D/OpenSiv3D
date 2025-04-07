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

# include "CScene.hpp"

namespace s3d
{
	ISiv3DScene* ISiv3DScene::Create()
	{
		return new CScene;
	}
}
