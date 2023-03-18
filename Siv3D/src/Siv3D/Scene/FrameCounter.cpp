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

# include "FrameCounter.hpp"

namespace s3d
{
	void FrameCounter::operator ++() noexcept
	{
		++m_systemFrameCount;
		
		++m_userFrameCount;
	}

	uint64 FrameCounter::getSystemFrameCount() const noexcept
	{
		return m_systemFrameCount;
	}

	int32 FrameCounter::getUserFrameCount() const noexcept
	{
		return m_userFrameCount;
	}
}
