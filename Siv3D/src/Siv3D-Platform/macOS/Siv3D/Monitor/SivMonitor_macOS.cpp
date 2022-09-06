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

# include <Siv3D/Monitor.hpp>
# include <Siv3D/MonitorInfo.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Common/OpenGL.hpp>

extern"C"
{
	GLFWAPI void glfwGetMonitorInfo_Siv3D(GLFWmonitor* handle, uint32_t* displayID, uint32_t* unitNumber,
										  int* xpos, int* ypos, int* w, int* h,
										  int* wx, int* wy, int* ww, int* wh);
}

namespace s3d
{
	namespace System
	{
		Array<MonitorInfo> EnumerateMonitors()
		{
			Array<MonitorInfo> results;
			
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			for (int32 i = 0; i < numMonitors; ++i)
			{
				GLFWmonitor* monitor = monitors[i];

				uint32 displayID, unitNumber;
				int32 xPos, yPos, width, height;
				int32 wx, wy, ww, wh;
				glfwGetMonitorInfo_Siv3D(monitor, &displayID, &unitNumber,
										 &xPos, &yPos, &width, &height,
										 &wx, &wy, &ww, &wh);
				
				Optional<Size> sizeMillimeter;
				{
					int32 pw = 0, ph = 0;
					::glfwGetMonitorPhysicalSize(monitor, &pw, &ph);
					if (pw > 0 && ph > 0)
					{
						sizeMillimeter = Size{ pw, ph };
					}
				}

				Optional<double> scaling;
				{
					float xscale = 1.0f, yscale = 1.0f;
					::glfwGetMonitorContentScale(monitor, &xscale, &yscale);
					if (const double scale = Max(xscale, yscale); scale > 0.0)
					{
						scaling = scale;
	
						xPos = static_cast<int32>(xPos * scale);
						yPos = static_cast<int32>(yPos * scale);
						width = static_cast<int32>(width * scale);
						height = static_cast<int32>(height * scale);
						
						//wx = static_cast<int32>(wx * scale);
						//wy = static_cast<int32>(wy * scale);
						//ww = static_cast<int32>(ww * scale);
						//wh = static_cast<int32>(wh * scale);
					}
				}
				
				Optional<double> refreshRate;
				{
					if (const GLFWvidmode* vidMode = ::glfwGetVideoMode(monitor))
					{
						if (vidMode->refreshRate > 0)
						{
							refreshRate = vidMode->refreshRate;
						}
					}
				}
				
				Size fullscreenResolution{ 0, 0 };
				{
					int32 numModes = 0;
					if (const GLFWvidmode* vidModes = ::glfwGetVideoModes(monitor, &numModes))
					{
						if (numModes)
						{
							fullscreenResolution.set(vidModes[numModes - 1].width, vidModes[numModes - 1].height);
						}
					}
				}

				const MonitorInfo info =
				{
					.name					= Unicode::Widen(::glfwGetMonitorName(monitor)),
					.id						= Format(displayID),
					.displayDeviceName		= Format(unitNumber),
					.displayRect			= Rect{ xPos, yPos, width, height },
					.workArea				= Rect{ wx, wy, ww, wh },
					.fullscreenResolution	= fullscreenResolution,
					.isPrimary				= (i == 0),
					.sizeMillimeter			= sizeMillimeter,
					.scaling				= scaling,
					.refreshRate			= refreshRate,
				};
				
				results.push_back(info);
			}
			
			return results;
		}
	}
}
