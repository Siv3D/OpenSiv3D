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

# include <Siv3D/Icon.hpp>
# include <Siv3D/Image.hpp>
# include "../Siv3DEngine.hpp"
# include "../Font/IFont.hpp"

namespace s3d
{
	Image Icon::LoadImage(const uint32 _code, const int32 _size)
	{
		return Siv3DEngine::GetFont()->getAwesomeIcon(static_cast<uint16>(_code), _size);
	}
}
