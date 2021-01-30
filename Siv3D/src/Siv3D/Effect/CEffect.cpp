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

# include <Siv3D/Effect.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CEffect.hpp"

namespace s3d
{
	CEffect::CEffect()
	{
		// do nothing
	}

	CEffect::~CEffect()
	{
		LOG_SCOPED_TRACE(U"CEffect::~CEffect()");
	}

	void CEffect::init()
	{
		LOG_SCOPED_TRACE(U"CEffect::init()");

	}

	void CEffect::update()
	{

	}
}
