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

# include "MF/CCodec_MF.hpp"
# include "Null/CCodec_Null.hpp"

namespace s3d
{
	ISiv3DCodec* ISiv3DCodec::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CCodec_MF;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		return new CCodec_Null;

	# endif
	}
}

