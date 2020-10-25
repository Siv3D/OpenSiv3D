﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer2D_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer2D_Null::CRenderer2D_Null() = default;

	CRenderer2D_Null::~CRenderer2D_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Null::~CRenderer2D_Null()");
	}

	void CRenderer2D_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Null::init()");
	}

	void CRenderer2D_Null::flush()
	{

	}

	void CRenderer2D_Null::test_renderRectangle(const RectF&, const ColorF&)
	{

	}

	void CRenderer2D_Null::drawFullScreenTriangle(const TextureFilter)
	{

	}
}
