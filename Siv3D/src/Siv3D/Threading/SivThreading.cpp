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

# include <thread>
# include <Siv3D/Threading.hpp>
# include <Siv3D/Utility.hpp>

namespace s3d
{
	namespace Threading
	{
		size_t GetConcurrency() noexcept
		{
			static const size_t n = Max<size_t>(1, std::thread::hardware_concurrency());
			return n;
		}
	}
}
