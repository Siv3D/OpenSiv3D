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

# include <cstring>
# include <Siv3D/CPUInfo.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static CPUInfo InitCPUInfo() noexcept
		{
			constexpr bool SSEEnabled
		# if defined(__SSE4_2__)
				= true;
		# else
				= false;
		# endif

			CPUInfo result
			{
				.features = 
				{
					.mmx = SSEEnabled,
					.sse = SSEEnabled,
					.sse2 = SSEEnabled,
					.sse3 = SSEEnabled,
					.sse4_1 = SSEEnabled,
					.sse4_2 = SSEEnabled,
				},

				.family	= 0,
				.model	= 0,
				.stepping = 0,

				.vendor	= U"Unknown",
				.brand	= U"Unknown"
			};

			return result;
		}
	}

	const CPUInfo g_CPUInfo = detail::InitCPUInfo();

	const CPUInfo& GetCPUInfo() noexcept
	{
		return g_CPUInfo;
	}
}
