//-----------------------------------------------
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
# include "CKeyboard.hpp"

namespace s3d
{
	CKeyboard::CKeyboard() = default;

	CKeyboard::~CKeyboard()
	{
		LOG_SCOPED_TRACE(U"CKeyboard::~CKeyboard()");
	}

	void CKeyboard::init()
	{
		LOG_SCOPED_TRACE(U"CKeyboard::init()");
	}

	void CKeyboard::update()
	{

	}

	bool CKeyboard::down(const uint32 index) const
	{
		return(false);
	}

	bool CKeyboard::pressed(const uint32 index) const
	{
		return(false);
	}

	bool CKeyboard::up(const uint32 index) const
	{
		return(false);
	}

	Duration CKeyboard::pressedDuration(const uint32 index) const
	{
		return(Duration{ 0 });
	}

	const Array<Input>& CKeyboard::getAllInput() const noexcept
	{
		return m_allInputs;
	}
}
