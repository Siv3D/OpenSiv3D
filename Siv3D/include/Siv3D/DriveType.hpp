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

namespace s3d
{
	/// @brief ドライブの種類 | Drive type
	enum class DriveType : uint8
	{
		/// @brief 不明 | Unknown
		Unknown,

		/// @brief ドライブが存在しない | Drive does not exist
		NoRootDirectory,

		/// @brief リムーバブルメディア | Removable media
		Removable,

		/// @brief 固定ディスク | Fixed disk
		Fixed,

		/// @brief ネットワークドライブ | Network drive
		Remote,

		/// @brief CD-ROM ドライブ | CD-ROM drive
		CDROM,

		/// @brief RAM ディスク | RAM disk
		RAMDisk,
	};
}
