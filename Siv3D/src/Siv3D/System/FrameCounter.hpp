//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class FrameCounter
	{
	private:

		uint64 m_systemFrameCount = 0;

		int32 m_userFrameCount = 0;

	public:

		void operator ++() noexcept
		{
			++m_systemFrameCount;

			++m_userFrameCount;
		}

		uint64 getSystemFrameCount() const noexcept
		{
			return m_systemFrameCount;
		}

		int32 getUserFrameCount() const noexcept
		{
			return m_userFrameCount;
		}

		void setUserFrameCount(const int32 count) noexcept
		{
			m_userFrameCount = count;
		}
	};
}
