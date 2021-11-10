//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

/// @biref ライブラリのメジャーバージョン | Library major version
# define SIV3D_VERSION_MAJOR			0

/// @biref ライブラリのマイナーバージョン | Library minor version
# define SIV3D_VERSION_MINOR			6

/// @biref ライブラリのリビジョンバージョン | Library revision version
# define SIV3D_VERSION_REVISION			3

/// @biref プレリリースタグ | Pre-release tag
# define SIV3D_VERSION_PRERELEASE_TAG	U""

/// @biref ライブラリのバージョン | Library version
# define SIV3D_VERSION			((SIV3D_VERSION_MAJOR * 100 * 100) + (SIV3D_VERSION_MINOR * 100) + (SIV3D_VERSION_REVISION))

/// @biref ライブラリのバージョンの文字列（簡易版） | Short Library version
# define SIV3D_VERSION_SHORT_STRING	U"0.6.3"

/// @biref ライブラリのバージョンの文字列 | Library version
# define SIV3D_VERSION_STRING	U"0.6.3" SIV3D_VERSION_PRERELEASE_TAG

/// @biref ライブラリのバージョン名 | Library version name
# define SIV3D_VERSION_NAME		U"Siv3D November 2021"
