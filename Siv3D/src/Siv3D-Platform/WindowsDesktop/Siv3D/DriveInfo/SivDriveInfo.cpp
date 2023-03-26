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

# include <Siv3D/DriveInfo.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool IsSSD(const std::wstring& driveName)
		{
			const std::wstring devicePath = (L"\\\\.\\" + driveName.substr(0, 2));

			HANDLE hDevice = ::CreateFileW(devicePath.c_str(),
				FILE_READ_ATTRIBUTES, (FILE_SHARE_READ | FILE_SHARE_WRITE), nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				return false;
			}

			{
				STORAGE_PROPERTY_QUERY query{};
				query.PropertyId = StorageDeviceSeekPenaltyProperty;
				query.QueryType = PropertyStandardQuery;

				DEVICE_SEEK_PENALTY_DESCRIPTOR desc{};
		
				DWORD bytesRead;

				if (::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
					&query, sizeof(query),
					&desc, sizeof(desc),
					&bytesRead, nullptr))
				{
					::CloseHandle(hDevice);
					return (not desc.IncursSeekPenalty);
				}
			}

			::CloseHandle(hDevice);
			
			return false;
		}
	}

	namespace System
	{
		Array<DriveInfo> EnumerateDrives()
		{
			Array<DriveInfo> driveInfos;

			const DWORD driveMask = ::GetLogicalDrives();

			for (int32 i = 0; i < 26; ++i)
			{
				if (driveMask & (1 << i))
				{
					const wchar_t rootPathName[4] = { wchar_t(L'A' + i), L':', L'\\', L'\0' };
					wchar_t volumeName[MAX_PATH + 1] = {};
					wchar_t fileSystemName[MAX_PATH + 1] = {};

					DWORD serialNumber = 0;
					DWORD maxComponentLength = 0;
					DWORD fileSystemFlags = 0;

					if (::GetVolumeInformationW(rootPathName, volumeName, static_cast<DWORD>(std::ssize(volumeName)),
						&serialNumber, &maxComponentLength, &fileSystemFlags, fileSystemName, static_cast<DWORD>(std::ssize(fileSystemName))))
					{
						DriveInfo driveInfo
						{
							.rootPath = { char32(U'A' + i), U':', U'/' },
							.volumeName = Unicode::FromWstring(volumeName),
							.fileSystem = Unicode::FromWstring(fileSystemName),
							.driveType = static_cast<DriveType>(::GetDriveTypeW(rootPathName))
						};

						ULARGE_INTEGER freeBytesAvailable;
						ULARGE_INTEGER totalNumberOfBytes;

						if (::GetDiskFreeSpaceExW(rootPathName, &freeBytesAvailable, &totalNumberOfBytes, nullptr))
						{
							driveInfo.freeSpaceBytes = freeBytesAvailable.QuadPart;
							driveInfo.totalSizeBytes = totalNumberOfBytes.QuadPart;
						}

						driveInfo.isSSD = detail::IsSSD(rootPathName);

						driveInfos.push_back(std::move(driveInfo));
					}
				}
			}

			return driveInfos;
		}
	}
}
