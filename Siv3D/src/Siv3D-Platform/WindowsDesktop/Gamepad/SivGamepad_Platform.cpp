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
# include <RegStr.h>
# include <Siv3D/Gamepad.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail
	{
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
					GamepadInfo info
					{
						.index		= i,
						.vendorID	= caps.wMid,
						.productID	= caps.wPid,
					};

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
