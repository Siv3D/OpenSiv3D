//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Threading
	{
		/// @brief サポートされるスレッド数を返します。 | Returns the number of concurrent threads supported by the implementation.
		/// @return サポートされるスレッド数 | Number of concurrent threads supported
		[[nodiscard]]
		size_t GetConcurrency() noexcept;
	}
}
