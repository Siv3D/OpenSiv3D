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

# include "ConstantBufferDetail_Metal.hpp"
# include <Siv3D/Error.hpp>

namespace s3d
{
	ConstantBufferDetail_Metal::ConstantBufferDetail_Metal(const size_t size)
	{
		if (4096 < size)
		{
			throw EngineError{ U"OpenSiv3D Metal backend: Maximum ConstantBuffer size is currently 4,096 bytes. (*experimental)" };
		}
	}

	bool ConstantBufferDetail_Metal::update(const void*, const size_t)
	{
		return true;
	}
}
