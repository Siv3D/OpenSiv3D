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
	GLFWAPI void glfwGetMonitorInfo_Siv3D(GLFWmonitor* handle, uint32_t* displayID,
                                      int* xpos, int* ypos, int* w, int* h);
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

				uint32 displayID;
				int32 xPos, yPos, width, height;
				glfwGetMonitorInfo_Siv3D(monitor, &displayID,
										 &xPos, &yPos, &width, &height);

				int32 wx, wy, ww, wh;
				::glfwGetMonitorWorkarea(monitor, &wx, &wy, &ww, &wh);
				
				Optional<Size> sizeMillimeter;
				{
					int32 pw = 0, ph = 0;
					::glfwGetMonitorPhysicalSize(monitor, &pw, &ph);
					if (pw > 0 && ph > 0)
					{
						sizeMillimeter = Size(pw, ph);
					}
				}

				Optional<double> scaling;
				{
					float xscale = 1.0f, yscale = 1.0f;
					::glfwGetMonitorContentScale(monitor, &xscale, &yscale);
					if (const double scale = Max(xscale, yscale); scale > 0.0)
					{
						scaling = scale;
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

				const String name = Unicode::Widen(::glfwGetMonitorName(monitor));

				const MonitorInfo info =
				{
					.name					= name,
					.id						= Format(displayID),
					.displayDeviceName		= name,
					.displayRect			= Rect(xPos, yPos, width, height),
					.workArea				= Rect(wx, wy, ww, wh),
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
