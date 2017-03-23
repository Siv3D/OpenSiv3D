//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <thread>
# include <algorithm>
# include <Siv3D/Threading.hpp>

namespace s3d
{
	namespace Threading
	{
		size_t GetConcurrency()
		{
			static const size_t n = std::max<size_t>(1, std::thread::hardware_concurrency());

			return n;
		}
	}
}
