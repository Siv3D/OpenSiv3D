//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Gamepad.hpp>
# include <Siv3D/Point.hpp>
# include <Siv3D/HashTable.hpp>
# include "../Siv3DEngine.hpp"
# include "IGamepad.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr int32 Get8Direction(const int32 deg)
		{
			if (deg <= 22.5)
				return 0;
			else if (deg <= 67.5)
				return 1;
			else if (deg <= 112.5)
				return 2;
			else if (deg <= 157.5)
				return 3;
			else if (deg <= 202.5)
				return 4;
			else if (deg <= 247.5)
				return 5;
			else if (deg <= 292.5)
				return 6;
			else if (deg <= 337.5)
				return 7;
			else
				return 0;
		}

		String FindGamepadName(const int32 vendorID, const int32 productID)
		{
			static const HashTable<Point, String> table =
			{
				{ { 0x57e, 0x2006 }, U"Joy-Con (L)"},
				{ { 0x57e, 0x2007 }, U"Joy-Con (R)"},
				{ { 0x57e, 0x2009 }, U"Pro Controller" },
			};

			if (const auto it = table.find(Point(vendorID, productID)); it != table.end())
			{
				return it->second;
			}

			return String();
		}

		Gamepad_impl::Gamepad_impl(const size_t _userIndex)
			: userIndex(static_cast<uint32>(_userIndex))
			, axes(2, 0.0)
			, povUp(InputDevice::Gamepad, 0x80, static_cast<uint8>(userIndex))
			, povDown(InputDevice::Gamepad, 0x82, static_cast<uint8>(userIndex))
			, povLeft(InputDevice::Gamepad, 0x83, static_cast<uint8>(userIndex))
			, povRight(InputDevice::Gamepad, 0x81, static_cast<uint8>(userIndex))
		{

		}

		bool Gamepad_impl::isConnected() const
		{
			return Siv3DEngine::GetGamepad()->isConnected(userIndex);
		}

		Gamepad_impl::operator bool() const
		{
			return isConnected();
		}

		const GamepadInfo& Gamepad_impl::getInfo() const
		{
			return Siv3DEngine::GetGamepad()->getInfo(userIndex);
		}

		Optional<int32> Gamepad_impl::povD8() const
		{
			if (const Optional<int32> povDegree = Siv3DEngine::GetGamepad()->povDegree(userIndex))
			{
				return detail::Get8Direction(povDegree.value());
			}

			return none;
		}

		const Gamepad_impl& Gamepad_helper::operator()(const size_t userIndex) const
		{
			return Siv3DEngine::GetGamepad()->getInput(userIndex);
		}
	}
}

# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <RegStr.h>

# include <Siv3D/Unicode.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		String GetDeviceName(const uint32 index, const wchar_t *szRegKey)
		{
			const std::wstring regKey = std::wstring(REGSTR_PATH_JOYCONFIG) + L"\\" + szRegKey + L"\\" + REGSTR_KEY_JOYCURR;

			HKEY hTopKey = HKEY_LOCAL_MACHINE;

			HKEY hKey;
			
			if (::RegOpenKeyExW(hTopKey, regKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
			{
				hTopKey = HKEY_CURRENT_USER;

				if (::RegOpenKeyExW(hTopKey, regKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
				{
					return String();
				}
			}

			const std::wstring regValue = L"Joystick" + std::to_wstring(index + 1) + REGSTR_VAL_JOYOEMNAME;

			wchar_t regName[256];

			DWORD regsize = sizeof(regName);

			LONG regresult = ::RegQueryValueExW(hKey, regValue.c_str(), nullptr, nullptr, (LPBYTE)regName, &regsize);
			
			::RegCloseKey(hKey);

			if (regresult != ERROR_SUCCESS)
			{
				return String();
			}

			const std::wstring regKey2 = std::wstring(REGSTR_PATH_JOYOEM) + L"\\" + regName;

			if (::RegOpenKeyExW(hTopKey, regKey2.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
			{
				return String();
			}

			Array<wchar_t> name;

			if (DWORD size = 0; ::RegQueryValueExW(hKey, REGSTR_VAL_JOYOEMNAME, nullptr, nullptr, nullptr, &size) == ERROR_SUCCESS)
			{	
				name.resize(size / sizeof(wchar_t));

				::RegQueryValueExW(hKey, REGSTR_VAL_JOYOEMNAME, nullptr, nullptr,(LPBYTE)name.data(), &size);
			}

			::RegCloseKey(hKey);

			name.pop_back();

			return Unicode::FromWString(std::wstring_view(name.data(), name.size()));
		}
	}

	namespace System
	{
		Array<GamepadInfo> EnumerateGamepads()
		{
			Array<GamepadInfo> results;

			for (uint32 i = 0; i < Gamepad.MaxUserCount; ++i)
			{
				JOYCAPSW caps = {};

				if (::joyGetDevCapsW(i, &caps, sizeof(caps)) == JOYERR_NOERROR)
				{
					GamepadInfo info;
					info.index = i;
					info.vendorID = caps.wMid;
					info.productID = caps.wPid;

					if (const auto name = detail::FindGamepadName(info.vendorID, info.productID))
					{
						info.name = name;
					}
					else
					{
						info.name = detail::GetDeviceName(i, caps.szRegKey);
					}

					results << info;
				}
			}

			return results;
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Unicode.hpp>

extern "C" {
GLFWAPI const char* siv3dGetJoystickInfo(int joy, unsigned* vendorID, unsigned* productID, unsigned* version);
}

namespace s3d
{
	namespace System
	{
		Array<GamepadInfo> EnumerateGamepads()
		{
			Array<GamepadInfo> results;
			
			unsigned vendorID = 0, productID = 0, version = 0;
			
			for (uint32 i = 0; i < Gamepad.MaxUserCount; ++i)
			{
				const char* name = siv3dGetJoystickInfo(i, &vendorID, &productID, &version);
				
				if (name)
				{
					GamepadInfo info;
					info.index = i;
					info.vendorID = vendorID;
					info.productID = productID;
					info.name = Unicode::Widen(name);
					results << info;
				}
			}
			
			return results;
		}
	}
}

# endif
