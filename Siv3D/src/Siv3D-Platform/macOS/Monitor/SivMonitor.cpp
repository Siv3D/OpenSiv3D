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

# include <Siv3D/Monitor.hpp>
# include <Siv3D/Window.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

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
		Array<Monitor> EnumerateActiveMonitors()
		{
			Array<Monitor> results;
			
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			for (int32 i = 0; i < numMonitors; ++i)
			{
				GLFWmonitor* monitor = monitors[i];
				
				Monitor result;
				result.name = Unicode::Widen(::glfwGetMonitorName(monitor));
				
				uint32 displayID, unitNumber;
				int32 xPos, yPos, width, height;
				int32 wx, wy, ww, wh;
				glfwGetMonitorInfo_Siv3D(monitor, &displayID, &unitNumber,
										 &xPos, &yPos, &width, &height,
										 &wx, &wy, &ww, &wh);
				result.id = Format(displayID);
				result.displayDeviceName = Format(unitNumber);
				result.displayRect.x = xPos;
				result.displayRect.y = yPos;
				result.displayRect.w = width;
				result.displayRect.h = height;
				result.workArea.x = wx;
				result.workArea.y = wy;
				result.workArea.w = ww;
				result.workArea.h = wh;
				result.isPrimary = (i == 0);
				
				results.push_back(result);
			}
			
			return results;
		}
		
		size_t GetCurrentMonitorIndex()
		{
			const auto& state = Window::GetState();
			const Point pos = state.bounds.pos;
			const Size size = state.bounds.size;
			
			const auto monitors = EnumerateActiveMonitors();
			int32 bestoverlap = 0;
			size_t bestIndex = 0;
			
			for (size_t i = 0; i < monitors.size(); ++i)
			{
				const auto& monitor = monitors[i];
				const Point mPos = monitor.displayRect.pos;
				const Size mSize = monitor.displayRect.size;
				
				const int32 overlap =
				std::max(0, std::min(pos.x + size.x, mPos.x + mSize.x) - std::max(pos.x, mPos.x)) *
				std::max(0, std::min(pos.y + size.y, mPos.y + mSize.y) - std::max(pos.y, mPos.y));
				
				if (bestoverlap < overlap)
				{
					bestoverlap = overlap;
					bestIndex = i;
				}
			}
			
			return bestIndex;
		}
	}

	void Formatter(FormatData& formatData, const Monitor& value)
	{
		String output;
		output += U"Name: " + value.name + U"\n";
		output += U"ID: " + value.id + U"\n";
		output += U"DisplayDeviceName: " + value.displayDeviceName + U"\n";
		output += U"DisplayRect: " + Format(value.displayRect) + U"\n";
		output += U"WorkArea: " + Format(value.workArea) + U"\n";
		output += U"Primary: " + Format(value.isPrimary);
		formatData.string.append(output);
	}
}
