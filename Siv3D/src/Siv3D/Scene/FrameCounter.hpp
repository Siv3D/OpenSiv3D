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

# pragma once
# include <Siv3D/Common.hpp>

namespace s3d
{
	class FrameCounter
	{
	private:

		uint64 m_systemFrameCount = 0;

		int32 m_userFrameCount = 0;

	public:

		void operator ++() noexcept;

		[[nodiscard]]
		uint64 getSystemFrameCount() const noexcept;
		
		[[nodiscard]]
		int32 getUserFrameCount() const noexcept;
	};
}
