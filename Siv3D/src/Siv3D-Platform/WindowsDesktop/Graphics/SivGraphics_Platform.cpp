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

# include <Siv3D/Windows.hpp>
# include <Siv3D/Graphics.hpp>
# include <Siv3D/Monitor.hpp>

namespace s3d
{
	namespace Graphics
	{
		Array<DisplayOutput> EnumOutputs()
		{
			Array<DisplayOutput> outputs;

			for (const auto& monitor : System::EnumerateActiveMonitors())
			{
				DisplayOutput output;
				output.name = monitor.name;
				output.displayRect = monitor.displayRect;

				DEVMODEW devMode = {};
				uint32 index = 0;
				Array<std::tuple<int32, int32, double>> modes;

				while (::EnumDisplaySettingsW(monitor.displayDeviceName.toWstr().c_str(), index++, &devMode))
				{
					std::tuple<int32, int32, double> mode;
					std::get<0>(mode) = devMode.dmPelsWidth;
					std::get<1>(mode) = devMode.dmPelsHeight;
					std::get<2>(mode) = devMode.dmDisplayFrequency;
					modes << mode;
				}

				output.displayModes = modes.unique().map([](const std::tuple<int32, int32, double> & t)
					{
						return DisplayMode{ Size(std::get<0>(t), std::get<1>(t)), std::get<2>(t) };
					});
				outputs << output;
			}

			return outputs;
		}
	}
}
