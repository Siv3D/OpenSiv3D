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
	/// @brief ドライブの情報 | Drive information
	struct DriveInfo
	{
		/// @brief ルートパス | Root path
		String rootPath;

		/// @brief ボリューム名 | Volume name
		String volumeName;

		/// @brief ファイルシステム名 | File system name
		String fileSystem;

		/// @brief ドライブの種類 | Drive type
		DriveType driveType = DriveType::Unknown;
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
