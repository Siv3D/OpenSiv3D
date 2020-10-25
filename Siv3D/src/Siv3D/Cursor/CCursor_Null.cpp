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

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor_Null.hpp"

namespace s3d
{
	CCursor_Null::CCursor_Null() = default;

	CCursor_Null::~CCursor_Null()
	{
		LOG_SCOPED_TRACE(U"CCursor_Null::~CCursor_Null()");
	}

	void CCursor_Null::init()
	{
		LOG_SCOPED_TRACE(U"CCursor_Null::init()");
	}

	bool CCursor_Null::update()
	{
		return true;
	}

	const CursorState& CCursor_Null::getState() const noexcept
	{
		return m_state;
	}

	bool CCursor_Null::registerCursor(StringView, const Image&, const Point&)
	{
		return true;
	}

	void CCursor_Null::requestStyle(StringView)
	{

	}
}
