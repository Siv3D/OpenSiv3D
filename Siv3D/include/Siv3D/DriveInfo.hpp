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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "DriveType.hpp"

namespace s3d
{
	/// @brief ドライブの情報 | Represents information about a drive.
	struct DriveInfo
	{
		/// @brief ルートパス | The root path of the drive
		String rootPath;

		/// @brief ボリューム名 | The name of the drive's volume
		String volumeName;

		/// @brief ファイルシステム名 | The name of the drive's file system
		String fileSystem;

		/// @brief ドライブの種類 | The type of the drive
		DriveType driveType = DriveType::Unknown;

		/// @brief 空き容量（バイト） | The amount of free space available on the drive, in bytes
		uint64 freeSpaceBytes = 0;

		/// @brief 総容量（バイト） | The total size of the drive, in bytes
		uint64 totalSizeBytes = 0;

		/// @brief SSD であるか | Whether the drive is an SSD
		bool isSSD = false;
	};

	namespace System
	{
		/// @brief ドライブの情報を列挙します。 | Enumerates the drive information.
		/// @return ドライブの情報の配列 | Array of drive information
		/// @remark Windows 以外では空の配列を返します。 | Returns an empty array on non-Windows platforms.
		[[nodiscard]]
		Array<DriveInfo> EnumerateDrives();
	}
}
