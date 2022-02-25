//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <ThirdParty/Obfuscate/obfuscate.h>

# ifndef SIV3D_OBFUSCATE_DEFAULT_KEY
#	define SIV3D_OBFUSCATE_DEFAULT_KEY AY_OBFUSCATE_DEFAULT_KEY
# endif

/// @brief 文字列は難読化された形で実行ファイルに格納されます。
# define SIV3D_OBFUSCATE(data) AY_OBFUSCATE_KEY(data, SIV3D_OBFUSCATE_DEFAULT_KEY)

/// @brief 文字列は難読化された形で実行ファイルに格納されます。
# define SIV3D_OBFUSCATE_KEY(data, key) AY_OBFUSCATE_KEY(data, key)
