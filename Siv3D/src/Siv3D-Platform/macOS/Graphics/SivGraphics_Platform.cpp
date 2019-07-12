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

# include <Siv3D/Graphics.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

extern"C"
{
	GLFWAPI void glfwGetMonitorRect_Siv3D(GLFWmonitor* handle, int* xpos, int* ypos, int* w, int* h);
}

namespace s3d
{
	namespace Graphics
	{
		Array<DisplayOutput> EnumOutputs()
		{
			Array<DisplayOutput> outputs;
			
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			for (int32 i = 0; i < numMonitors; ++i)
			{
				GLFWmonitor* monitor = monitors[i];
				
				DisplayOutput output;
				
				output.name = Unicode::Widen(::glfwGetMonitorName(monitor));
				
				int32 xPos, yPos, width, height;
				
				glfwGetMonitorRect_Siv3D(monitor, &xPos, &yPos, &width, &height);
				output.displayRect.x = xPos;
				output.displayRect.y = yPos;
				output.displayRect.w = width;
				output.displayRect.h = height;
				
				int32 numModes;
				const GLFWvidmode* videoModes = ::glfwGetVideoModes(monitor, &numModes);
				
				for (int32 i = 0; i < numModes; ++i)
				{
					const GLFWvidmode& videoMode = videoModes[i];
					
					DisplayMode mode;
					
					mode.size.set(videoMode.width, videoMode.height);
					
					mode.refreshRateHz = videoMode.refreshRate;
					
					output.displayModes.push_back(mode);
				}
				
				outputs.push_back(output);
			}
			
			return outputs;
		}
	}
}
