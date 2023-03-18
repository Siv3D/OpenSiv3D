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
# include <ThirdParty/cpu_features/cpuinfo_x86.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static CPUInfo InitCPUInfo() noexcept
		{
			static_assert(sizeof(s3d::X86Features) == sizeof(cpu_features::X86Features));

			const cpu_features::X86Info x86Info = cpu_features::GetX86Info();
			
			char brand[49] = {};
			cpu_features::FillX86BrandString(brand);

			CPUInfo result;
			std::memcpy(&result.features, &x86Info.features, sizeof(s3d::X86Features));
			result.family	= x86Info.family;
			result.model	= x86Info.model;
			result.stepping	= x86Info.stepping;
			result.vendor	= Unicode::Widen(x86Info.vendor);
			result.brand	= Unicode::Widen(brand);

			return result;
		}
	}

	const CPUInfo g_CPUInfo = detail::InitCPUInfo();

	const CPUInfo& GetCPUInfo() noexcept
	{
		return g_CPUInfo;
	}
}
