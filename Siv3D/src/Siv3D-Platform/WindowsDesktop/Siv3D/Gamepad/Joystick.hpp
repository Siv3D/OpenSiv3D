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

# pragma once
# include <algorithm>
# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Windows/Windows.hpp>
# define DIRECTINPUT_VERSION 0x0800
# include <dinput.h>

//
// modified version of glfw/src/win32_joystick.c
// 
//========================================================================
// GLFW 3.4 Win32 - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2019 Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//

namespace s3d::detail
{
	constexpr uint32 GLFW_HAT_CENTERED = 0;
	constexpr uint32 GLFW_HAT_UP = 1;
	constexpr uint32 GLFW_HAT_RIGHT = 2;
	constexpr uint32 GLFW_HAT_DOWN = 4;
	constexpr uint32 GLFW_HAT_LEFT = 8;
	constexpr uint32 GLFW_HAT_RIGHT_UP = (GLFW_HAT_RIGHT | GLFW_HAT_UP);
	constexpr uint32 GLFW_HAT_RIGHT_DOWN = (GLFW_HAT_RIGHT | GLFW_HAT_DOWN);
	constexpr uint32 GLFW_HAT_LEFT_UP = (GLFW_HAT_LEFT  | GLFW_HAT_UP);
	constexpr uint32 GLFW_HAT_LEFT_DOWN = (GLFW_HAT_LEFT  | GLFW_HAT_DOWN);

	constexpr int32 _GLFW_TYPE_AXIS = 0;
	constexpr int32 _GLFW_TYPE_SLIDER = 1;
	constexpr int32 _GLFW_TYPE_BUTTON = 2;
	constexpr int32 _GLFW_TYPE_POV = 3;

	struct GLFWjoyobjectWin32
	{
		int32 offset = 0;
		int32 type = 0;
	};

	struct GLFWjoystickWin32
	{
		Array<GLFWjoyobjectWin32> objects;
		int32 objectCount = 0;
		IDirectInputDevice8W* device = nullptr;
		DWORD index = 0;
		GUID guid = {};
	};

	struct GLFWjoystick
	{
		bool present = false;
		Array<float> axes;
		Array<uint8> buttons;
		Array<uint8> hats;
		String name;
		uint32 vendorID = 0;
		uint32 productID = 0;
		char guid[33];
		GLFWjoystickWin32 win32;
	};

	struct GLFWobjenumWin32
	{
		IDirectInputDevice8W* device = nullptr;
		Array<GLFWjoyobjectWin32> objects;
		int32 objectCount = 0;
		int32 axisCount = 0;
		int32 sliderCount = 0;
		int32 buttonCount = 0;
		int32 povCount = 0;
	};

	struct DInputSharedData
	{
		std::array<GLFWjoystick, Gamepad.MaxPlayerCount> joysticks;
	
		IDirectInput8W* dinput = nullptr;
	};

	static bool CompareJoystickObjects(const GLFWjoyobjectWin32& first, const GLFWjoyobjectWin32& second)
	{
		if (first.type != second.type)
		{
			return ((first.type - second.type) < 0);
		}

		return ((first.offset - second.offset) < 0);
	}

	static GLFWjoystick* AllocJoystick(DInputSharedData& data, const String& name, const char* guid, int32 axisCount, int32 buttonCount, int32 hatCount)
	{
		int32 jid = 0;
		GLFWjoystick* js;

		for (; jid < Gamepad.MaxPlayerCount; ++jid)
		{
			if (not data.joysticks[jid].present)
			{
				break;
			}
		}

		if ((Gamepad.MaxPlayerCount - 1) < jid)
		{
			return nullptr;
		}

		js = (data.joysticks.data() + jid);
		js->present = true;
		js->name = name;
		js->axes.resize(axisCount);
		js->buttons.resize(buttonCount + hatCount * 4);
		js->hats.resize(hatCount);
		js->productID = 0;

		strncpy_s(js->guid, guid, sizeof(js->guid) - 1);

		return js;
	}

	static void CloseJoystick(GLFWjoystick* js)
	{
		if (js->win32.device)
		{
			js->win32.device->Unacquire();
			js->win32.device->Release();
		}

		*js = GLFWjoystick{};
	}

	static BOOL CALLBACK DeviceObjectCallback(const DIDEVICEOBJECTINSTANCEW* doi, void* userData)
	{
		GLFWobjenumWin32* data = static_cast<GLFWobjenumWin32*>(userData);
		GLFWjoyobjectWin32* object = (data->objects.data() + data->objectCount);

		if (DIDFT_GETTYPE(doi->dwType) & DIDFT_AXIS)
		{
			DIPROPRANGE dipr;

			if (std::memcmp(&doi->guidType, &GUID_Slider, sizeof(GUID)) == 0)
				object->offset = DIJOFS_SLIDER(data->sliderCount);
			else if (std::memcmp(&doi->guidType, &GUID_XAxis, sizeof(GUID)) == 0)
				object->offset = DIJOFS_X;
			else if (std::memcmp(&doi->guidType, &GUID_YAxis, sizeof(GUID)) == 0)
				object->offset = DIJOFS_Y;
			else if (std::memcmp(&doi->guidType, &GUID_ZAxis, sizeof(GUID)) == 0)
				object->offset = DIJOFS_Z;
			else if (std::memcmp(&doi->guidType, &GUID_RxAxis, sizeof(GUID)) == 0)
				object->offset = DIJOFS_RX;
			else if (std::memcmp(&doi->guidType, &GUID_RyAxis, sizeof(GUID)) == 0)
				object->offset = DIJOFS_RY;
			else if (std::memcmp(&doi->guidType, &GUID_RzAxis, sizeof(GUID)) == 0)
				object->offset = DIJOFS_RZ;
			else
				return DIENUM_CONTINUE;

			ZeroMemory(&dipr, sizeof(dipr));
			dipr.diph.dwSize = sizeof(dipr);
			dipr.diph.dwHeaderSize = sizeof(dipr.diph);
			dipr.diph.dwObj = doi->dwType;
			dipr.diph.dwHow = DIPH_BYID;
			dipr.lMin = -32768;
			dipr.lMax = 32767;

			if (FAILED(IDirectInputDevice8_SetProperty(data->device,
				DIPROP_RANGE,
				&dipr.diph)))
			{
				return DIENUM_CONTINUE;
			}

			if (std::memcmp(&doi->guidType, &GUID_Slider, sizeof(GUID)) == 0)
			{
				object->type = _GLFW_TYPE_SLIDER;
				data->sliderCount++;
			}
			else
			{
				object->type = _GLFW_TYPE_AXIS;
				data->axisCount++;
			}
		}
		else if (DIDFT_GETTYPE(doi->dwType) & DIDFT_BUTTON)
		{
			object->offset = DIJOFS_BUTTON(data->buttonCount);
			object->type = _GLFW_TYPE_BUTTON;
			data->buttonCount++;
		}
		else if (DIDFT_GETTYPE(doi->dwType) & DIDFT_POV)
		{
			object->offset = DIJOFS_POV(data->povCount);
			object->type = _GLFW_TYPE_POV;
			data->povCount++;
		}

		data->objectCount++;
		return DIENUM_CONTINUE;
	}

	static BOOL CALLBACK DeviceCallback(const DIDEVICEINSTANCE* di, void* userData)
	{
		DInputSharedData* pData = static_cast<DInputSharedData*>(userData);

		GLFWjoystick* js = nullptr;

		for (int32 jid = 0; jid < Gamepad.MaxPlayerCount; ++jid)
		{
			js = (pData->joysticks.data() + jid);

			if (js->present)
			{
				if (std::memcmp(&js->win32.guid, &di->guidInstance, sizeof(GUID)) == 0)
				{
					return DIENUM_CONTINUE;
				}
			}
		}

		IDirectInputDevice8* device = nullptr;

		if (FAILED(pData->dinput->CreateDevice(di->guidInstance, &device, nullptr)))
		{
			return DIENUM_CONTINUE;
		}

		if (FAILED(device->SetDataFormat(&c_dfDIJoystick2)))
		{
			device->Release();
			return DIENUM_CONTINUE;
		}

		DIDEVCAPS dc{};
		dc.dwSize = sizeof(dc);

		if (FAILED(device->GetCapabilities(&dc)))
		{
			device->Release();
			return DIENUM_CONTINUE;
		}

		DIPROPDWORD dipd{};
		dipd.diph.dwSize = sizeof(dipd);
		dipd.diph.dwHeaderSize = sizeof(dipd.diph);
		dipd.diph.dwHow = DIPH_DEVICE;
		dipd.dwData = DIPROPAXISMODE_ABS;

		if (FAILED(device->SetProperty(DIPROP_AXISMODE, &dipd.diph)))
		{
			device->Release();
			return DIENUM_CONTINUE;
		}

		GLFWobjenumWin32 data{};
		{
			data.device = device;
			const size_t count = dc.dwAxes + (size_t)dc.dwButtons + dc.dwPOVs;
			data.objects.resize(count);
		}

		if (FAILED(device->EnumObjects(DeviceObjectCallback, &data, (DIDFT_AXIS | DIDFT_BUTTON | DIDFT_POV))))
		{
			device->Release();
			return DIENUM_CONTINUE;
		}

		data.objects.sort_by(CompareJoystickObjects);

		const std::string name = Unicode::FromWstring(di->tszInstanceName).toUTF8();

		char guid[33] = {};

		// Generate a joystick GUID that matches the SDL 2.0.5+ one
		if (memcmp(&di->guidProduct.Data4[2], "PIDVID", 6) == 0)
		{
			sprintf_s(guid, "03000000%02x%02x0000%02x%02x000000000000",
				(uint8_t)di->guidProduct.Data1,
				(uint8_t)(di->guidProduct.Data1 >> 8),
				(uint8_t)(di->guidProduct.Data1 >> 16),
				(uint8_t)(di->guidProduct.Data1 >> 24));
		}
		else
		{
			sprintf_s(guid, "05000000%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x00",
				name[0], name[1], name[2], name[3],
				name[4], name[5], name[6], name[7],
				name[8], name[9], name[10]);
		}

		js = AllocJoystick(*pData, Unicode::FromUTF8(name), guid,
			(data.axisCount + data.sliderCount), data.buttonCount, data.povCount);

		if (not js)
		{
			device->Release();
			return DIENUM_STOP;
		}

		js->vendorID = static_cast<uint16>(LOWORD(di->guidProduct.Data1));
		js->productID = static_cast<uint16>(HIWORD(di->guidProduct.Data1));
		js->win32.device = device;
		js->win32.guid = di->guidInstance;
		js->win32.objects = data.objects;
		js->win32.objectCount = data.objectCount;

		return DIENUM_CONTINUE;
	}
}
