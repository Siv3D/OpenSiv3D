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

# include "SystemLog.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Version.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/CPUInfo.hpp>
# include <ThirdParty/infoware/system.hpp>
# include <ThirdParty/infoware/version.hpp>
# include <ThirdParty/infoware/cpu.hpp>

namespace s3d
{
	namespace SystemLog
	{
		void Initial()
		{
			LOG_INFO(U"ℹ️ {}"_fmt(DateTime::Now()));

			if constexpr (SIV3D_BUILD(DEBUG))
			{
				LOG_INFO(U"ℹ️ Siv3D Engine (" SIV3D_VERSION_STRING U") " SIV3D_PLATFORM_NAME U" [Debug build]");
			}
			else
			{
				LOG_INFO(U"ℹ️ Siv3D Engine (" SIV3D_VERSION_STRING U") " SIV3D_PLATFORM_NAME U" [Release build]");
			}
			
			{
				const auto os = iware::system::OS_info();

			# if SIV3D_PLATFORM(WINDOWS)
				LOG_INFO(U"ℹ️ Windows version: {}.{}.{}.{}"_fmt(
					os.major, os.minor, os.patch, os.build_number));
			# else
				LOG_INFO(U"ℹ️ OS: {} ({}.{}.{}.{})"_fmt(
					Unicode::Widen(os.full_name),
					os.major, os.minor, os.patch, os.build_number));
			# endif
			}

			{
				const auto cpu = GetCPUInfo();
				const auto quantities = iware::cpu::quantities();
				LOG_INFO(U"ℹ️ CPU: {} {} {}.{}.{} (CPU packages: {}, Physical CPUs: {}, Logical CPUs: {})"_fmt(
					cpu.vendor, cpu.brand, cpu.family, cpu.model, cpu.stepping,
					quantities.packages, quantities.physical, quantities.logical));
			}

			{
				const auto memory = iware::system::memory();
				LOG_INFO(U"ℹ️ Memory: [Physical Available: {} Total: {}] [Virtual: Available: {} Total: {}]"_fmt(
					FormatDataSize(memory.physical_available), FormatDataSize(memory.physical_total),
					FormatDataSize(memory.virtual_available), FormatDataSize(memory.virtual_total)));
			}

			{
				const auto displays = iware::system::displays();
				LOG_INFO(U"ℹ️ Connected displays: {}"_fmt(
					displays.size()));

				//if (displays.empty())
				//{
				//	LOG_INFO(U"ℹ️ Displays: None connected or no detection method enabled");
				//}
				//else
				//{
				//	for (size_t i = 0; i < displays.size(); ++i)
				//	{
				//		const auto& display = displays[i];

				//		LOG_INFO(U"ℹ️ Display[{}]: Resolution: {}x{}, DPI: {}, Color depth: {}, Refresh rate: {} Hz"_fmt(
				//			i, (int)display.width, (int)display.height, display.dpi, display.bpp, display.refresh_rate));
				//	}
				//}
			}

			LOG_INFO(U"⌛ Preparing for setup...");
		}

		void Final()
		{
			LOG_INFO(U"✅ Siv3D engine has terminated");

			LOG_INFO(U"ℹ️ {}"_fmt(DateTime::Now()));
		}
	}
}
