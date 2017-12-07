//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CCodec_Null.hpp"
# include <Siv3D/Wave.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CCodec_Null::CCodec_Null()
	{

	}

	CCodec_Null::~CCodec_Null()
	{

	}

	bool CCodec_Null::init()
	{
		LOG_INFO(U"ℹ️ Codec_Null initialized");

		return true;
	}

	Wave CCodec_Null::decode(IReader& reader)
	{
		// [Siv3D ToDo]
		return Wave();
	}
}

# endif
